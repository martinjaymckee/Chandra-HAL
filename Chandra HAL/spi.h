#ifndef CHANDRA_SPI_H
#define CHANDRA_SPI_H

#include <stdint.h>

#include <chip.h>

#include "chip_utils.h"
#include "chrono.h"
#include "gpio.h"

namespace chandra
{
namespace io
{
namespace internal
{

} /*namespace internal*/

struct SPI
{
        using cs_t = uint8_t;

        enum transfer_mode_t {
            START,
            STOP,
            WRAP
        };

        enum : cs_t {
            CS0 = static_cast<cs_t>(~0x01),
            CS1 = static_cast<cs_t>(~0x02),
            CS2 = static_cast<cs_t>(~0x04),
            CS3 = static_cast<cs_t>(~0x08)
        };
};

class SPIMaster
{
	public:
        using value_t = uint8_t;
        using pin_t = chandra::io::IO;
        using cs_t = SPI::cs_t;
        using transfer_mode_t = SPI::transfer_mode_t;

        SPIMaster( uint8_t _num, pin_t _miso, pin_t _mosi, pin_t _sclk,
             pin_t _cs0, const pin_t& _cs1, const pin_t& _cs2, const pin_t& _cs3)
            : num_(_num), spi_(getSPI(_num)), len_(8)
		{
	#if defined(__LPC82X__)
			//	Initialize the peripheral clock and peripheral reset
            if(num_ == 0) {
				SystemClock::enable(0, 11);
				PeripheralActivity::reset(0, 0);
            } else if (num_ == 1) {
				SystemClock::enable(0, 12);
				PeripheralActivity::reset(0, 1);
			}
	#elif defined(__LPC15XX__)
			//	Initialize the peripheral clock and peripheral reset
            if(num_ == 0) {
				SystemClock::enable(1, 9);
				PeripheralActivity::reset(1, 9);
			} else if ( spi_ == LPC_SPI1 ) {
				SystemClock::enable(1, 10);
				PeripheralActivity::reset(1, 10);
			}
	#endif
			// Configure the Pins
			setPins(_miso, _mosi, _sclk, _cs0, _cs1, _cs2, _cs3);
		}

        SPIMaster( uint8_t _num, pin_t _miso, pin_t _mosi, pin_t _sclk,
             pin_t _cs0, const pin_t& _cs1, const pin_t& _cs2)
            : SPIMaster(_num, _miso, _mosi, _sclk, _cs0, _cs1, _cs2, io::IO(14, 31)) {}

        SPIMaster( uint8_t _num, pin_t _miso, pin_t _mosi, pin_t _sclk,
             pin_t _cs0, const pin_t& _cs1)
            : SPIMaster(_num, _miso, _mosi, _sclk, _cs0, _cs1, io::IO(14, 31), io::IO(14, 31)) {}

        SPIMaster( uint8_t _num, pin_t _miso, pin_t _mosi, pin_t _sclk, pin_t _cs0)
            : SPIMaster(_num, _miso, _mosi, _sclk, _cs0, io::IO(14, 31), io::IO(14, 31), io::IO(14, 31)) {}

        auto freq(const units::mks::Q_Hz<uint32_t> _freq) {
            // Setup Clock Divisor
            const auto fspi = chrono::frequency::spi(num_);
            const auto ratio = (fspi / _freq).value();
            const auto div = ratio > 1? ratio - 1 : 1;
            spi_->DIV = div;
            return units::mks::Q_Hz<uint32_t>(fspi/(div+1)); // TODO: CHECK IF THIS IS ACCURATE....
        }

        auto freq() { return freq(units::mks::Q_Hz<uint32_t>(1000000)); }

		bool enable( bool _enable, uint8_t _mode = 0 ) {
			if(_enable) {
				if(spi_->DIV == 0) freq(); // Set Default frequency if currently unset
				spi_->CFG = (_mode<<3) | (1<<2); // Enable, In Master Mode
				spi_->CFG |= (1<<0);
			} else {
				spi_->CFG = 0; //&= ~((1<<2) | (1<<0)); -- TODO: CHCK THIS AND FIX IT IF IT ISN'T CORRECT
			}
			return _enable;
		}

		bool enable() const { return spi_->CFG & (1<<0); }
		uint8_t mode() const { return (spi_->CFG >> 4) & 0x03; }

        void tx(const value_t* _buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = transfer_mode_t::WRAP) const {
			uint16_t ctrl = 0;

			//	Set Transfer Packet Length and RXIGNORE
			ctrl = ((len_-1) << 8) | (1<<6);

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= (_cs&0x0F);
			}

			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
                if((index == (_cnt-1)) && ((_transfer_mode == transfer_mode_t::STOP) | (_transfer_mode == transfer_mode_t::WRAP))){
					ctrl |= (1<<4);
				}

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = (ctrl<<16) | *_buf;
				++_buf;
			}

			return;
		}

        value_t* rx(value_t* const _out_buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = transfer_mode_t::WRAP, const value_t& _stuff = 0xFF) const {
			value_t* out_buf = _out_buf;
			uint16_t ctrl = 0;

			//	Set Transfer Packet Length
			ctrl = ((len_-1) << 8);

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= (_cs&0x0F);
			}

			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
                if((index == (_cnt-1)) && ((_transfer_mode == transfer_mode_t::STOP) | (_transfer_mode == transfer_mode_t::WRAP))){
					ctrl |= (1<<4);
				}

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = (ctrl<<16) | _stuff;

				//	Wait for RXRDY and Read Data
				while( !(spi_->STAT & (1<<0)) ){}
				const value_t new_data = (spi_->RXDAT&0xFFFF);
				*out_buf = new_data;
				++out_buf;
			}

			return out_buf; // NOTE: THE OUTPUT BUFFER POINTS "PAST" WHAT WAS WRITTEN
		}


        value_t* txrx(const value_t* _in_buf, value_t* const _out_buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = transfer_mode_t::WRAP) const {
			value_t* out_buf = _out_buf;
			uint16_t ctrl = 0;

			//	Set Transfer Packet Length
			ctrl = ((len_-1) << 8);

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= (_cs&0x0F);
			}


			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
                if((index == (_cnt-1)) && ((_transfer_mode == transfer_mode_t::STOP) | (_transfer_mode == transfer_mode_t::WRAP))){
					ctrl |= (1<<4);
				}

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = (ctrl<<16) | *_in_buf;
				++_in_buf;

				//	Wait for RXRDY and Read Data
				while( !(spi_->STAT & (1<<0)) ){}
				const value_t new_data = (spi_->RXDAT&0xFF);
				*out_buf = new_data;
				++out_buf;
			}

			return out_buf; // NOTE: THE OUTPUT BUFFER POINTS "PAST" WHAT WAS WRITTEN
		}


	private:
        LPC_SPI_T* getSPI(uint8_t _num) {
            switch(_num) {
                case 0:
                default:
                    return LPC_SPI0;
                case 1:
                    return LPC_SPI1;
            }
            return nullptr;
        }


        uint8_t ID(const chandra::io::IO& _pin) {
            return (32*_pin.port()) + _pin.pin();
        }

        uint8_t ID(const chandra::io::internal::NullIO&) { return 255; }

        void setPins(const pin_t& _miso, const pin_t& _mosi, const pin_t& _sclk, const pin_t& _cs0,
                      const pin_t& _cs1, const pin_t& _cs2, const pin_t& _cs3) {
            const auto miso = ID(_miso);
            const auto mosi = ID(_mosi);
            const auto sclk = ID(_sclk);
            const auto cs0 = ID(_cs0);
            const auto cs1 = ID(_cs1);
            const auto cs2 = ID(_cs2);
            const auto cs3 = ID(_cs3);

			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 12);

#if defined(__LPC82X__)
			//
			// Setup the Main SPI Pins
			//
            if(num_ == 0){
                LPC_SWM->PINASSIGN[3] = (LPC_SWM->PINASSIGN[3] & 0x00FFFFFF) | (sclk<<24);
                LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0xFF000000) | (cs0<<16) | (miso<<8) | mosi;
			} else {
                LPC_SWM->PINASSIGN[5] = (LPC_SWM->PINASSIGN[5] & 0xFFFF) | (mosi<<24) | (sclk<<16);
                LPC_SWM->PINASSIGN[6] = (LPC_SWM->PINASSIGN[6] & 0xFFFF0000) | (cs0<<8) | miso;
			}

			//
			// Setup the Chip Select lines
			//
            if(num_ == 0){
                LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0x00FFFFFF) | (cs1<<24);
                LPC_SWM->PINASSIGN[5] = (LPC_SWM->PINASSIGN[5] & 0xFFFFFF00) | cs2;
                LPC_SWM->PINASSIGN[5] = (LPC_SWM->PINASSIGN[5] & 0xFFFF00FF) | (cs3<<8);
			} else {
                LPC_SWM->PINASSIGN[6] = (LPC_SWM->PINASSIGN[6] & 0xFF00FFFF) | (cs1<<16);
			}
#elif defined(__LPC15XX__)
			//
			// Setup the Main SPI Pins
			//
            if(num_ == 0){
                LPC_SWM->PINASSIGN[3] = (LPC_SWM->PINASSIGN[3] & 0x000000FF) | (miso<<24) | (mosi<<16) | (sclk<<8);
                LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[3] & 0xFFFFFF00) | cs0;
			} else {
                LPC_SWM->PINASSIGN[5] = (cs0<<24) | (miso<<16) | (mosi<<8) | sclk;
			}

			//
			// Setup the Chip Select lines
			//
            if(num_ == 0){
                LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0xFFFF00FF) | (cs1<<8);
                LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0xFF00FFFF) | (cs2<<16);
                LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0x00FFFFFF) | (cs3<<24);
			} else {
                LPC_SWM->PINASSIGN[6] = (LPC_SWM->PINASSIGN[6] & 0xFFFFFF00) | cs1;
			}
#endif

			//	Disable AHB clock domain for SWM
			SystemClock::enable(0, 12, false);
			return;
		}

        uint8_t num_;
        mutable LPC_SPI_T* spi_;
		uint8_t len_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_SPI_H*/
