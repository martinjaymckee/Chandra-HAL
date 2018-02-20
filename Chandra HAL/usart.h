/*
 * usart.h
 *
 *  Created on: Apr 9, 2016
 *      Author: martin
 */

#ifndef CHANDRA_USART_H
#define CHANDRA_USART_H

#include <cstdio>
#include <cmath>
#include <stdint.h>
#include <string.h>

#include <chip.h>

#include "circular_buffer.h"
#include "chip_utils.h"
#include "chrono.h"
#include "format.h"
#include "gpio.h"
#include "stream.h"

namespace chandra // TODO: ADD RX TIMESTAMPING
{
namespace io
{

template <class T>
struct USARTClockStatus
{
        T clk;
        T ppm;
};

enum class Parity {
    None = 0x00,
    Even = 0x02,
    Odd = 0x03
};

namespace internal
{
template<class Value, class Timepoint>
struct TimestampedValue
{
        Value value;
        Timepoint timestamp;
        operator Value () const { return value; }
};

template<class Value, class Timepoint, bool _timestamped=false>
struct RX
{
        static Value encode(const Value& _value) { return _value; }
};


template<class Value, class Timepoint>
struct RX<Value, Timepoint, true>
{
        static TimestampedValue<Value, Timepoint> encode(const Value& _value) {
            return {_value, Timepoint::clock::now()};
        }
};
} /*namespace internal*/

template<uint32_t tx_buffer_length = 128, uint32_t rx_buffer_length = tx_buffer_length, bool _timestamped=false>
class USART : public Stream< USART<tx_buffer_length, rx_buffer_length> >
{
	protected:
        using calc_t = int64_t; // TODO: THIS NEEDS TO BE RECONSIDERED
        using clock_t = chandra::chrono::timestamp_clock;
        using encoder_t = internal::RX<char, typename clock_t::time_point, _timestamped>;

	public:
        using tx_value_t = char;
        using rx_value_t = decltype(encoder_t::encode('0'));

	protected:
        USART( const uint8_t& _num, const auto& _tx, const auto& _rx, auto /*hack to force delegation*/ )
            : num_(_num), irq_num_(getIRQNum(_num)), usart_(getUSART(_num)), tx_(_tx), rx_(_rx) {
			// TODO: CHANGE THIS TO WORK FOR ANY OF THE USARTS
	#if defined(__LPC82X__)
            SystemClock::enable(0, 14+num_);// Turn on USARTx Clock
            PeripheralActivity::reset(0, 2); // Reset Fractional Divider
            PeripheralActivity::reset(0, 3+num_); // Reset USARTx
	#elif defined(__LPC15XX__)
			SystemClock::enable(1, 17);// Turn on USART Clock
			PeripheralActivity::reset(1, 17); // Reset USART0
			//PeripheralActivity::reset(0, ??); // Reset Fractional Divider
	#endif
			//	Configure the Pins for this USART
            setPins();

			//	Configure USART Interrupts
			usart_->INTENSET = (1<<0);
			NVIC_EnableIRQ(irq_num_); // TODO: CHANGE THIS TO WORK FOR ANY OF THE USARTS

			//	Initialize the USART Clock to a reasonable rate if it has not, already, been.
			if(LPC_SYSCON->UARTCLKDIV == 0) uclk();

			//	Initialize to 8-databits, No parity and 1 stop bit
			mode();
		}

    public:
        USART( const uint8_t& _num,
               const io::IO& _tx,
               const io::IO& _rx ) : USART(_num, _tx, _rx, 0) {}

        USART( const uint8_t& _num,
               const io::internal::NullIO& _tx,
               const io::IO& _rx ) : USART(_num, _tx, _rx, 0) {}

        USART( const uint8_t& _num,
               const io::IO& _tx,
               const io::internal::NullIO& _rx ) : USART(_num, _tx, _rx, 0) {}

		USARTClockStatus<calc_t> uclk( unsigned long _clk = ( 4 * 115200 * 16 ) ) {
			// TODO: IT WOULD BE GREAT TO SET THE UCLK TO THE HIGHEST MULTIPLE OF THE STANDARD USART RATE POSSIBLE IF A DEFAULT VALUE IS PASSED
			USARTClockStatus<calc_t> status;

			//	Configure USART Clocking
			//		-- Calculate the clock divider
			//		-- Calculate the fractional multiplier
			//		-- Calculate the actual clock rate and error
            const calc_t sys_clk = static_cast<calc_t>(chandra::chrono::frequency::usart(0));
			const calc_t clk_div = (sys_clk + (_clk/2)) / _clk;
			const calc_t mult = (((256.0 * sys_clk) + (_clk * clk_div / 2.0)) / (_clk * clk_div)) - 256.0;
			const calc_t denom = (clk_div * (256.0 + mult));
			status.clk = (256.0 * sys_clk + (denom/2.0)) / denom;
			status.ppm = (1000000.0 *(status.clk - _clk)) / _clk;
			LPC_SYSCON->UARTCLKDIV = clk_div; // USART Clock Divisor
	#if defined(__LPC82X__)
			LPC_SYSCON->UARTFRGDIV = 0xFF; // Set Divisor to 255 + 1 (256)
			LPC_SYSCON->UARTFRGMULT = mult; // Set Multiplier to value calculated above
	#elif defined(__LPC15XX__)
			LPC_SYSCON->FRGCTRL = (mult<<8) | 0xFF; // Set divisor to 255 + 1 ( 256 ) and multiplier to value calculated above
	#endif
			return status;
		}

		calc_t actual_uclk() {
			const calc_t clk_div = static_cast<calc_t>(LPC_SYSCON->UARTCLKDIV);
	#if defined(__LPC82X__)
			const calc_t mult = static_cast<calc_t>(LPC_SYSCON->UARTFRGMULT);
	#elif defined(__LPC15XX__)
			const calc_t mult = static_cast<calc_t>((LPC_SYSCON->FRGCTRL>>8)&0xFF);
	#endif
			if(clk_div == 0) return 0; // If the clock is stopped
            return (256 * static_cast<calc_t>(chandra::chrono::frequency::usart(0))) / (clk_div * (256 + mult));
		}

        bool mode(const uint8_t& _data_bits=8, const Parity& _parity = Parity::None, const uint8_t& _stop_bits=1) {
			static const uint32_t mode_mask = (0x1F<<2);
			const uint32_t mode_bits = ((uint32_t(_stop_bits) - 1) << 6) | (uint32_t(_parity) << 4) | ((uint32_t(_data_bits)-7) << 2);
			usart_->CFG = (usart_->CFG & mode_mask) | mode_bits;
			return true;
		}

		//	Enable USART0 and Configure 8-1-N
		bool enable(bool _enable) { // TODO: CONFIGURE THIS METHOD TO PROPERLY ENABLE/DISABLE AND CONFIGURE THE TRANSMISSION FORMAT
			static const uint32_t enable_mask = (1<<0);
			if(_enable) {
				usart_->CFG |= enable_mask;
			} else {
				usart_->CFG &= ~enable_mask;
			}
			return enabled();
		}

		bool enabled() const { return static_cast<bool>( usart_->CFG & (1<<0) ); }

		bool rxInv(bool _inverted) {
			static const uint32_t mask = (1<<22);
			if(_inverted) {
				usart_->CFG |= mask;
			} else {
				usart_->CFG &= ~mask;
			}

			return _inverted;
		}

		bool rxInv() const { return usart_->CFG &= (1<<22); }

		bool txInv(bool _inverted) {
			static const uint32_t mask = (1<<23);
			if(_inverted) {
				usart_->CFG |= mask;
			} else {
				usart_->CFG &= ~mask;
			}

			return _inverted;
		}

		bool txInv() const { return usart_->CFG &= (1<<23); }

		USARTClockStatus<calc_t> baud( unsigned int _baud, unsigned int _osr = 16 ){ // IT WOULD BE BETTER TO SET THE CLOCK DIVIDER AND MULTIPLIER IN A SEPERATE METHOD SO THAT MULTIPLE USARTS CAN BE USED
			USARTClockStatus<calc_t> status;

			//	Configure USART Clocking
			//		-- Calculate Baud Rate Generator
            const calc_t sys_clk = static_cast<calc_t>(chandra::chrono::frequency::usart(0));
			const calc_t clk_div = static_cast<calc_t>(LPC_SYSCON->UARTCLKDIV);
	#if defined(__LPC82X__)
			const calc_t mult = static_cast<calc_t>(LPC_SYSCON->UARTFRGMULT);
	#elif defined(__LPC15XX__)
			const calc_t mult = static_cast<calc_t>((LPC_SYSCON->FRGCTRL>>8)&0xFF);
	#endif
			double denom = (_osr * _baud * clk_div * (256.0 + mult));
			const calc_t brg = static_cast<calc_t>((256.0 * sys_clk + (denom/2.0)) / denom);

			const calc_t denom_2 = _osr * brg * clk_div * (256.0 + mult);
			status.clk = (256.0 * sys_clk + (denom_2 / 2.0)) / denom_2;
			status.ppm = (1000000.0 * (status.clk - _baud)) / _baud;
			usart_->BRG = brg-1; // Set Baud Rate Generator Divisor to value calculated above ( less 1 for rollover )
			// usart_->OSR = _osr-1; // TODO: FIGURE OUT WHY THIS ISN'T WORKING....

			return status;
		}

        size_t available() const {
            return rx_buffer_.size();
		}

        bool sending() const { // not buffer empty and transmit idle
            return !(tx_buffer_.empty() and (usart_->STAT & (1<<3)));
        }

		//
		// Stream Functionality
		//
		bool put( char _ch ) {
            NVIC_DisableIRQ(irq_num_);
			waitForBuffer();
            tx_buffer_ << _ch;
            NVIC_EnableIRQ(irq_num_);
			prime_tx();
			return true;
		}

		bool puts( const char* _str ) {
            NVIC_DisableIRQ(irq_num_);
			while( *_str ) {
				waitForBuffer();
				tx_buffer_ << *_str;
				++_str;
			}
            NVIC_EnableIRQ(irq_num_);
			prime_tx();
			return true;
		}

		operator rx_value_t() { return read(); }

        rx_value_t read() { return rx_buffer_; }

		USART& operator >> ( char& _ch ) {
			_ch = read();
			return *this;
		}

		void txISR() {
			if(tx_buffer_.available()){
				while( !(usart_->STAT & (1<<2)) ) {} // Wait for TX Ready Flag
				usart_->TXDATA = char(tx_buffer_);
				usart_->INTENSET = (1<<2); // Enable the TX Ready Interrupt
			} else {
				usart_->INTENCLR = (1<<2); // Disable the TX Ready Interrupt
			}
		}

        void rxISR(char _ch) { rx_buffer_ << encoder_t::encode(_ch); }


        auto& rx_buffer() { return rx_buffer_; }
        auto& tx_buffer() { return tx_buffer_; }

	protected:
        // TODO: DECIDE IF MSB/LSB-FIRST HANDLING IS USEFUL AND HOW IT WOULD BE CONFIGURED
        //  IF IT IS TO BE USED, DECIDE UPON AN OPTIMIZED REVERSE IMPLEMENTATION
        constexpr char reverse(char b) const {
           b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
           b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
           b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
           return b;
        }

        void waitForBuffer() const {
			while(tx_buffer_.full()) {
				NVIC_EnableIRQ(irq_num_);
			}
			NVIC_DisableIRQ(irq_num_);
		}

		void prime_tx() {
			if(usart_->STAT & (1<<3)) txISR();
			return;
		}

        constexpr uint8_t pinIndex(const chandra::io::IO& _io) const {
            return (32*_io.port()) + _io.pin();
        }

        void setPins(){
	#if defined(__LPC82X__)
			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 7);

            //	Setup Switch Matrix
            const uint8_t rx_pin = pinIndex(rx_);
            const uint8_t tx_pin = pinIndex(tx_);
            switch(num_) {
                default:
                case 0:
                    LPC_SWM->PINASSIGN[0] = 0xFFFF0000 | (rx_pin<<8) | tx_pin;
                    break;

                case 1:
                    LPC_SWM->PINASSIGN[1] = 0xFF0000FF | (rx_pin<<16) | (tx_pin<<8);
                    break;

                case 2:
                    LPC_SWM->PINASSIGN[2] = 0x0000FFFF | (rx_pin<<24) | (tx_pin<<16);
                    break;
            }

			//	Disable AHB clock domain for SWM
			SystemClock::enable(0, 7, false);
	#elif defined(__LPC15XX__)
            // TODO: THIS IS NOT PROPERLY HANDLING SWM MAPPING FOR USARTS OTHER THAN 0
			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 12);

			//	Setup Switch Matrix -- TODO: CHANGE THIS TO WORK FOR ANY OF THE USARTS ( SELECT DIFFERENT PINASSIGN REGISTERS)
			LPC_SWM->PINASSIGN[0] = 0xFFFF0000 | (_rx_pin<<8) | _tx_pin;

			//	Disable AHB clock domain for SWM
			SystemClock::enable(0, 12, false);
	#else
		#error "USART Set Pin Functionality not defined for this processor!"
	#endif
			return;
		}

		static IRQn_Type getIRQNum(const uint8_t& _num) {
			switch(_num) {
				case 0:
					return UART0_IRQn;

				case 1:
					return UART1_IRQn;

				case 2:
					return UART2_IRQn;

				default:
					return UART0_IRQn; // TODO: DECIDE IF THIS IS WHAT I WANT TO DO
			}
		}

		static LPC_USART_T* getUSART(const uint8_t& _num) {
			switch(_num) {
				case 0:
					return LPC_USART0;

				case 1:
					return LPC_USART1;

				case 2:
					return LPC_USART2;

				default:
					break;
			}
			return nullptr;
		}

	private:
        const uint8_t num_;
        const IRQn_Type irq_num_;
        LPC_USART_T* usart_;
        const chandra::io::IO tx_;
        const chandra::io::IO rx_;
        bool msb_first_;
        FixedCircularBuffer<tx_value_t, tx_buffer_length> tx_buffer_;
        FixedCircularBuffer<rx_value_t, rx_buffer_length> rx_buffer_;
};

template<uint32_t tx_buffer_length = 128, uint32_t rx_buffer_length = tx_buffer_length>
using TimestampedUSART = USART<tx_buffer_length, rx_buffer_length, true>;

} /*namespace io*/
} /*namespace chandra*/

#define USART_IRQ_NAME(a) UART##a##_IRQHandler
#define USART_REGISTER(a) LPC_USART##a
#define USART_ISR_HANDLER(num, var)\
extern "C" {\
void USART_IRQ_NAME(num)(void){\
    if(USART_REGISTER(num)->INTSTAT & (1<<2)) {\
        var.txISR();\
    } else if( USART_REGISTER(num)->INTSTAT & (1<<0) ) {\
        const char c = USART_REGISTER(num)->RXDATA;\
        var.rxISR(c);\
    }\
}\
}

#endif /*CHANDRA_USART_H*/
