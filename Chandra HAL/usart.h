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

#if defined(__LPC82X__) || defined(__LPC15XX__)
#include <chip.h>
#elif defined(__LPC84X__)
#include <LPC8xx.h>
#elif defined(__CHANDRA_MOCK__)
#warning "USART file parsed in mock mode."
#else
#error "Undefined processor type for USART implementation."
#endif

#include "circular_buffer.h"
#include "chip_utils.h"
#include "chrono.h"
#include "format.h"
#include "gpio.h"
#include "stream.h"
#include "usart_utils.h"

namespace chandra
{
namespace io
{

template<uint32_t tx_buffer_length = 128, uint32_t rx_buffer_length = tx_buffer_length, bool _timestamped=false>
class USART : public Stream< USART<tx_buffer_length, rx_buffer_length> >
{
	protected:
    using calc_t = int64_t; // TODO: THIS NEEDS TO BE RECONSIDERED
    using clock_t = chandra::chrono::timestamp_clock;
    using encoder_t = internal::RX<char, typename clock_t::time_point, _timestamped>;

    #if defined(__LPC82X__) || defined(__LPC15XX__)
    using lpc_peripheral_t = LPC_USART_T;
    #elif defined(__LPC84X__)
    using lpc_peripheral_t = LPC_USART_TypeDef;
    #endif

	public:
    using tx_value_t = char;
    using rx_value_t = decltype(encoder_t::encode('0'));

	protected:
		template<class P1, class P2, class HACK>
    USART( const uint8_t& _num, const P1& _tx, const P2& _rx, HACK /*hack to force delegation*/ )
        : num_(_num), irq_num_(getIRQNum(_num)), usart_(getUSART(_num)), tx_(_tx), rx_(_rx)
		{
    #if defined(__LPC82X__)
      SystemClock::enable(0, 14+num_);// Turn on USARTx Clock
      PeripheralActivity::reset(0, 2); // Reset Fractional Divider
      PeripheralActivity::reset(0, 3+num_); // Reset USARTx
      LPC_SYSCON->UARTCLKDIV = 1; // Enable baudrate clock
    #elif defined(__LPC15XX__)
			SystemClock::enable(1, 17+num_);// Turn on USART Clock
			PeripheralActivity::reset(1, 17+num_); // Reset USARTx
			LPC_SYSCON->UARTCLKDIV = 1;
    #elif defined(__LPC84X__)
      if(num_ <= 2) {
        const uint8_t idx = 14+num_;
        SystemClock::enable(0, idx);
        PeripheralActivity::reset(0, idx);
      } else {
        const uint8_t idx = 30+num_-2;
        SystemClock::enable(0, idx);
        PeripheralActivity::reset(0, idx);
      }
    #elif defined(__CHANDRA_MOCK__)
      #warning "Chandra USART constructor parsed as mock."
    #else
      #error "USART clock configuration not defined for this processor"
    #endif

			//	Configure the Pins for this USART
      setPins();

			//	Configure USART Interrupts
			usart_->INTENSET = (1<<0);
			NVIC_EnableIRQ(irq_num_);

			//	Initialize the USART Clock to a reasonable rate if it has not, already, been.
		  if(getFractionalInputClockDiv() == 0) uclk();

			//	Initialize to 8-databits, No parity and 1 stop bit
			mode();
		}

  public:
    USART(
			const uint8_t& _num,
    	const io::IO& _tx,
      const io::IO& _rx )
		: USART(_num, _tx, _rx, 0) {}

    USART(
			const uint8_t& _num,
      const io::internal::NullIO& _tx,
      const io::IO& _rx )
		: USART(_num, _tx, _rx, 0) {}

    USART(
			const uint8_t& _num,
      const io::IO& _tx,
      const io::internal::NullIO& _rx )
		: USART(_num, _tx, _rx, 0) {}

    USARTClockStatus<calc_t> uclk(calc_t target_uclk = 0) {
			USARTClockStatus<calc_t> status;

			if(target_uclk != 0) {
        const calc_t sys_clk = static_cast<calc_t>(chandra::chrono::frequency::usart(num_).value());
        const int32_t div(256);
        const uint32_t mult = multCalc(sys_clk, target_uclk, div);
        setFractionalInputClock(num_, mult, div);
        status.clk = uclkCalc(sys_clk, mult, div);
        status.ppm = ppmCalc(target_uclk, status.clk);
      }

			return status;
		}

		calc_t actual_uclk() {
      const calc_t sys_clk = static_cast<calc_t>(chandra::chrono::frequency::usart(num_).value());
      const calc_t div = getFractionalInputClockDiv();
      const calc_t mult = getFractionalInputClockMult();
      if(isClockRunning()) return 0; // If the clock is stopped
      return uclkCalc(sys_clk, mult, div);
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
                // IF BAUD, ETC ARE NOT CONFIGURED, DO A DEFAULT SETUP HERE
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

		USARTClockStatus<calc_t> baud( unsigned int _baud, bool _recalc_uclk = false, unsigned int _osr = 16 ) {
			// TODO: ALLOW THIS TO USE SEPERATE FRGs ON THE 84X
			const bool was_enabled = enabled();
			if(was_enabled) {
				while(sending()) {}
			}
			enable(false);
      USARTClockStatus<calc_t> status;
      const int32_t sys_clk = static_cast<calc_t>(chandra::chrono::frequency::usart(num_).value());
      int32_t running_uclk = actual_uclk();
      if(running_uclk == 0 or _recalc_uclk) {
          const int32_t target_brg = brgCalc((2*sys_clk)/3, _baud, _osr);
          const int32_t target_uclk = target_brg * _baud * _osr;
          running_uclk = uclk(target_uclk).clk;
      }
      const calc_t brg = brgCalc(running_uclk, _baud, _osr);
      status.clk = baudCalc(running_uclk, brg, _osr);
      status.ppm = ppmCalc(_baud, status.clk);
      usart_->BRG = brg-1; // Set Baud Rate Generator Divisor to value calculated above ( less 1 for rollover )

		#if defined(__LPC82X__) || defined(__LPC84X__)
	    usart_->OSR = _osr-1; // TODO: FIGURE OUT WHY THIS ISN'T WORKING....
		#elif defined(__LPC15XX__)
			//usart_->OSR = _osr-1;
			//#warning "OSR register not defined in LPC15xx LPCOpen API."
		#endif
		#if defined(__LPC84X__)
      LPC_SYSCON->FCLKSEL[num_] = 0x02; // Use FRG0 as source clock
		#endif
			enable(was_enabled);
			return status;
		}

		USARTClockStatus<calc_t> baud() const {
			USARTClockStatus<calc_t> status;
      const int32_t sys_clk = static_cast<calc_t>(chandra::chrono::frequency::usart(num_).value());
      int32_t running_uclk = actual_uclk();
      const calc_t brg = usart_->brg+1;
			const auto osr = usart_->OSR+1;
      status.clk = baudCalc(running_uclk, brg, osr);
      status.ppm = ppmCalc(_baud, status.clk);
			return status;
		}

    size_t available() const {
			return rx_buffer_.size();
		}

    bool sending() const { // not buffer empty or transmit active
      return !tx_buffer_.empty() or ((usart_->STAT & (1<<3)) == 0);
    }

		//
		// Stream Functionality
		//
		bool put(char _ch, bool /*_raw*/ = false ) {
//            NVIC_DisableIRQ(irq_num_);
			waitForBuffer();
            tx_buffer_ << _ch;
//            NVIC_EnableIRQ(irq_num_);
			prime_tx();
			return true;
		}

		bool puts( const char* _str ) {
//            NVIC_DisableIRQ(irq_num_);
			while( *_str ) {
				waitForBuffer();
				tx_buffer_ << *_str;
				++_str;
			}
//            NVIC_EnableIRQ(irq_num_);
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
    #if defined(__LPC82X__) || defined(__LPC15XX__)
				usart_->TXDATA = char(tx_buffer_);
    #elif defined(__LPC84X__)
				usart_->TXDAT = char(tx_buffer_);
		#endif
				usart_->INTENSET = (1<<3) | (1<<2); // Enable the TX Ready and TX Idle Interrupts
			} else {
				usart_->INTENCLR = (1<<3) | (1<<2); // Disable the TX Ready and TX Idle Interrupts
			}
			return;
		}

		// TODO: THE RX ISR NEEDS TO BE MODIFIED TO HANDLE THE TIMESTAMPED CASE ALSO
		//	SO THAT IT BECOMES POSSIBLE TO CONSTRUCT TIMESTAMPED VALUES
    void rxISR(char _ch) { rx_buffer_ << encoder_t::encode(_ch); }

    auto& rx_buffer() { return rx_buffer_; }
    auto& tx_buffer() { return tx_buffer_; }

  protected:
    static constexpr int32_t brgCalc(int32_t clk, int32_t baud, const int32_t& osr=16) {
      const int32_t denom = osr*baud;
      return (clk+(denom/2))/denom;
    }

    static constexpr int32_t baudCalc(int32_t clk, int32_t brg, const int32_t& osr=16) {
      const int32_t denom = osr*brg;
      return (clk+(denom/2))/denom;
    }

    static constexpr int32_t multCalc(int32_t clk, int32_t uclk, const int32_t& div=256) {
      return (((div*int64_t(clk)) + (uclk/2))/uclk) - div;
    }

    static constexpr int32_t uclkCalc(int32_t clk, int32_t mult, const int32_t& div=256) {
      return (div*int64_t(clk))/(div+mult);
    }

    static constexpr int32_t ppmCalc(int32_t target, int32_t actual) {
      return (int64_t(1000000)*(actual-target))/target;
    }

    static constexpr bool isClockRunning(const uint8_t& _num_frg = 0) {
    #if defined(__LPC82X__)
      (void)_num_frg;
      return LPC_SYSCON->UARTFRGDIV != 0xFF;
    #elif defined(__LPC84X__)
      if(_num_frg == 0) {
        return LPC_SYSCON->FRG0DIV != 0xFF;
      } else if(_num_frg == 1) {
        return LPC_SYSCON->FRG1DIV != 0xFF;
      }
      return 0;
    #elif defined(__LPC15XX__)
      (void)_num_frg;
      return (LPC_SYSCON->FRGCTRL&0xFF) != 0xFF;
    #endif
    }

    static constexpr calc_t getFractionalInputClockDiv(const uint8_t& _num_frg = 0) {
    #if defined(__LPC82X__)
      (void)_num_frg;
      return static_cast<calc_t>(LPC_SYSCON->UARTFRGDIV) + 1;
    #elif defined(__LPC84X__)
      if(_num_frg == 0) {
          return static_cast<calc_t>(LPC_SYSCON->FRG0DIV) + 1;
      } else if(_num_frg == 1) {
        return static_cast<calc_t>(LPC_SYSCON->FRG1DIV) + 1;
      }
      return 0;
    #elif defined(__LPC15XX__)
      (void)_num_frg;
      return static_cast<calc_t>(LPC_SYSCON->FRGCTRL&0xFF) + 1;
    #endif
    }

    static constexpr calc_t getFractionalInputClockMult(const uint8_t& _num_frg = 0) {
    #if defined(__LPC82X__)
      (void)_num_frg;
      return static_cast<calc_t>(LPC_SYSCON->UARTFRGMULT);
    #elif defined(__LPC84X__)
      if(_num_frg == 0) {
        return static_cast<calc_t>(LPC_SYSCON->FRG0MULT);
      } else if(_num_frg == 1) {
        return static_cast<calc_t>(LPC_SYSCON->FRG1MULT);
      }
      return 0;
    #elif defined(__LPC15XX__)
      (void)_num_frg;
      return static_cast<calc_t>((LPC_SYSCON->FRGCTRL>>8)&0xFF);
    #endif
    }

    static constexpr bool setFractionalInputClock(
      const uint8_t&,
      const uint32_t& _mult,
      const uint32_t& _div,
      const uint8_t& _num_frg = 0 )
    {
    #if defined(__LPC82X__)
      (void)_div;
      (void)_num_frg;
      (void)_usart;
      LPC_SYSCON->UARTFRGMULT = _mult;
      LPC_SYSCON->UARTFRGDIV = 0xFF; // Must be 256 (255+1)
      return true;
    #elif defined(__LPC15XX__)
      (void)_div;
      (void)_num_frg;
      (void)_usart;
      LPC_SYSCON->FRGCTRL = (_mult<<8) | 0xFF; // Div must be 256 (255+1)
      return true;
    #elif defined(__LPC84X__)
      (void)_div;
      if(_num_frg == 0) {
        LPC_SYSCON->FRG0MULT = _mult;
        LPC_SYSCON->FRG0DIV = 0xFF; // Must be 256 (255+1)
        LPC_SYSCON->FRG0CLKSEL = 0x01; // Set Main Clock as Source
        return true;
      } else if(_num_frg == 1) {
        LPC_SYSCON->FRG1MULT = _mult;
        LPC_SYSCON->FRG1DIV = 0xFF; // Must be 256 (255+1)
        LPC_SYSCON->FRG1CLKSEL = 0x01; // Set Main Clock as Source
        return true;
      } else {
        return false;
      }
    #endif
    }

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
				// NVIC_EnableIRQ(irq_num_);
			}
			// NVIC_DisableIRQ(irq_num_);
		}

		void prime_tx() {
			if(usart_->STAT & (1<<2)) txISR();
			return;
		}

    constexpr uint8_t pinIndex(const chandra::io::IO& _io) const {
        return (32*_io.port()) + _io.pin();
    }

    void setPins() {
      const uint8_t rx_pin = pinIndex(rx_);
      const uint8_t tx_pin = pinIndex(tx_);
    #if defined(__LPC82X__)
			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 7);

      //	Setup Switch Matrix
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
    #elif defined(__LPC84X__)
      //	Enable AHB clock domains for SWM -- SWM Clock and USART0-2 are the same as LPC82X
      SystemClock::enable(0, 7);

      //	Setup Switch Matrix
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

        case 3:
          LPC_SWM->PINASSIGN[11] = 0x00FFFFFF | (tx_pin<<24);
          LPC_SWM->PINASSIGN[12] = 0xFFFFFF00 | rx_pin;
          break;

        case 4:
          LPC_SWM->PINASSIGN[2] = 0x0000FFFF | (rx_pin<<24) | (tx_pin<<16);
          break;
      }

      //	Disable AHB clock domain for SWM
      SystemClock::enable(0, 7, false);
    #elif defined(__LPC15XX__)
			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 12);

			//	Setup Switch Matrix
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
      #if defined(__LPC84X__)
        case 3:
          return UART3_IRQn;
        case 4:
          return UART4_IRQn;
      #endif
				default:
					return UART0_IRQn; // TODO: DECIDE IF THIS IS WHAT I WANT TO DO
			}
		}

    static lpc_peripheral_t* getUSART(const uint8_t& _num) {
			switch(_num) {
				case 0:
					return LPC_USART0;

				case 1:
					return LPC_USART1;

				case 2:
					return LPC_USART2;
      #if defined(__LPC84X__)
        case 3:
          return LPC_USART3;
        case 4:
          return LPC_USART4;
      #endif
				default:
					break;
			}
			return nullptr;
		}

	private:
    const uint8_t num_;
    const IRQn_Type irq_num_;
    volatile lpc_peripheral_t* usart_;
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
#if defined(__LPC82X__) || defined(__LPC15XX__)
#define USART_ISR_HANDLER(num, var)\
extern "C" {\
void USART_IRQ_NAME(num)(void){\
    if(USART_REGISTER(num)->INTSTAT & (0x3<<2)) {\
        var.txISR();\
    } else if( USART_REGISTER(num)->INTSTAT & (1<<0) ) {\
        const char c = USART_REGISTER(num)->RXDATA;\
        var.rxISR(c);\
    }\
}\
}
#elif defined(__LPC84X__)
#define USART_ISR_HANDLER(num, var)\
extern "C" {\
void USART_IRQ_NAME(num)(void){\
    if(USART_REGISTER(num)->INTSTAT & (0x3<<2)) {\
        var.txISR();\
    } else if( USART_REGISTER(num)->INTSTAT & (1<<0) ) {\
        const char c = USART_REGISTER(num)->RXDAT;\
        var.rxISR(c);\
    }\
}\
}
#endif
#endif /*CHANDRA_USART_H*/
