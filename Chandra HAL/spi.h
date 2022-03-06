#ifndef CHANDRA_SPI_H
#define CHANDRA_SPI_H

#include <stdint.h>

#if defined(__LPC82X__) ||defined(__LPC15XX__)
#include <chip.h>
#elif defined(__LPC84X__)
#include <LPC8xx.h>
#else
#error "Undefined processor type for USART implementation."
#endif

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
        #if defined(__LPC82X__) || defined(__LPC15XX__)
        using lpc_peripheral_t = LPC_SPI_T;
        #elif defined(__LPC84X__)
        using lpc_peripheral_t = LPC_SPI_TypeDef;
        #endif

        using cs_t = uint8_t;

        enum transfer_mode_t {
            START,
            STOP,
            WRAP,
            PASS
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
    #elif defined(__LPC84X__)
            //	Initialize the peripheral clock and peripheral reset
            if(num_ == 0) {
                SystemClock::enable(0, 11);
                PeripheralActivity::reset(0, 11);
            } else if (num_ == 1) {
                SystemClock::enable(0, 12);
                PeripheralActivity::reset(0, 12);
            }
	#elif defined(__LPC15XX__)
			//	Initialize the peripheral clock and peripheral reset
            if(num_ == 0) {
				SystemClock::enable(1, 9);
				PeripheralActivity::reset(1, 9);
            } else if (num_ == 1) {
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

        auto frequency(const units::mks::Q_Hz<uint32_t> _freq) {
            // Setup Clock Divisor
            const auto fspi = chrono::frequency::spi(num_);
            const auto ratio = (fspi / _freq).value();
            const auto div = ratio > 1? ratio - 1 : 1;
            spi_->DIV = div;
#if defined(__LPC84X__)
            LPC_SYSCON->FCLKSEL[9+num_] = 0x01;
#endif
            return units::mks::Q_Hz<uint32_t>(fspi/(div+1)); // TODO: CHECK IF THIS IS ACCURATE....
        }

        auto frequency() {
          const auto fspi = chrono::frequency::spi(num_);
          const auto div = spi_->DIV;
          return units::mks::Q_Hz<uint32_t>(fspi/(div+1));
        }

		bool enable(bool _enable, uint8_t _mode = 0 ) {
			if(_enable) {
				if(spi_->DIV == 0) frequency(units::mks::Q_MHz<uint32_t>(1)); // Set Default frequency if currently unset
				spi_->CFG = (_mode<<3) | (1<<2); // Enable, In Master Mode
				spi_->CFG |= (1<<0);
				spi_->DLY = 0;
				ctrl_base_ = (((uint32_t(len_)-1) << 8) << 16);
			} else {
				spi_->CFG = 0;
			}
			return _enable;
		}

		bool enabled() const { return spi_->CFG & (1<<0); }
		uint8_t mode() const { return (spi_->CFG >> 4) & 0x03; }

    bool rebind(pin_t _miso, pin_t _mosi, pin_t _sclk, pin_t _cs0,
      const pin_t& _cs1, const pin_t& _cs2, const pin_t& _cs3) {
      const uint8_t cfg = spi_->CFG;
      const bool is_enabled = enabled();
      enable(false);
      setPins(_miso, _mosi, _sclk, _cs0, _cs1, _cs2, _cs3);
      spi_->CFG = cfg;
      enable(is_enabled);
      return enabled();
    }

    bool rebind(pin_t _miso, pin_t _mosi, pin_t _sclk, pin_t _cs0,
      const pin_t& _cs1, const pin_t& _cs2) {
        return rebind(_miso, _mosi, _sclk, _cs0, _cs1, _cs2, io::IO(14,31));
    }

    bool rebind(pin_t _miso, pin_t _mosi, pin_t _sclk, pin_t _cs0,
      const pin_t& _cs1) {
        return rebind(_miso, _mosi, _sclk, _cs0, _cs1, io::IO(14,31), io::IO(14,31));
    }

    bool rebind(pin_t _miso, pin_t _mosi, pin_t _sclk, pin_t _cs0) {
        return rebind(_miso, _mosi, _sclk, _cs0, io::IO(14,31), io::IO(14,31), io::IO(14,31));
    }

    bool rebind(pin_t _miso, pin_t _mosi, pin_t _sclk) {
        return rebind(_miso, _mosi, _sclk, io::IO(14,31), io::IO(14,31), io::IO(14,31), io::IO(14,31));
    }

    void tx(const value_t* _buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = transfer_mode_t::WRAP) const {

			//	Set Transfer Packet Length and RXIGNORE
			uint32_t ctrl = (((len_-1) << 8) | (1<<6)) << 16;

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= ((_cs&0x0F)<<16);
			}

      const uint32_t ctrl_end = ((_transfer_mode == transfer_mode_t::STOP) | (_transfer_mode == transfer_mode_t::WRAP)) ? (1<<4)<<16 : 0x00;
      const size_t end_cnt = _cnt-1;

			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
        if(index == end_cnt) ctrl |= ctrl_end;

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = ctrl | *_buf;
				++_buf;
			}

			return;
		}

    value_t* rx(value_t* const _out_buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = transfer_mode_t::WRAP, const value_t& _stuff = 0xFF) const {
			value_t* out_buf = _out_buf;

			//	Set Transfer Packet Length
			uint32_t ctrl = ctrl_base_ | _stuff;

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= ((_cs&0x0F)<<16);
			}

      const uint32_t ctrl_end = ((_transfer_mode == transfer_mode_t::STOP) | (_transfer_mode == transfer_mode_t::WRAP)) ? (1<<4)<<16 : 0x00;
      const size_t end_cnt = _cnt-1;

			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
        if(index == end_cnt) ctrl |= ctrl_end;

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = ctrl;

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

			//	Set Transfer Packet Length
			uint32_t ctrl = ((uint32_t(len_)-1) << 8)<<16;

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= ((_cs&0x0F)<<16);
			}

      const uint32_t ctrl_end = ((_transfer_mode == transfer_mode_t::STOP) | (_transfer_mode == transfer_mode_t::WRAP)) ? (1<<4)<<16 : 0x00;
      const size_t end_cnt = _cnt-1;
			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
        if(index == end_cnt) ctrl |= ctrl_end;

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = ctrl | *_in_buf;
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
        SPI::lpc_peripheral_t* getSPI(uint8_t _num) {
            switch(_num) {
                case 0:
                default:
                    return LPC_SPI0;
                case 1:
                    return LPC_SPI1;
            }
            return nullptr;
        }

        void setPins(const pin_t& _miso, const pin_t& _mosi, const pin_t& _sclk, const pin_t& _cs0,
                      const pin_t& _cs1, const pin_t& _cs2, const pin_t& _cs3) {
            const auto miso = chandra::io::ID(_miso);
            const auto mosi = chandra::io::ID(_mosi);
            const auto sclk = chandra::io::ID(_sclk);
            const auto cs0 = chandra::io::ID(_cs0);
            const auto cs1 = chandra::io::ID(_cs1);
            const auto cs2 = chandra::io::ID(_cs2);
            const auto cs3 = chandra::io::ID(_cs3);

			//	Enable AHB clock domains for SWM
#if defined(__LPC82X__)
			SystemClock::enable(0, 12);
#elif defined(__LPC84X__)
            SystemClock::enable(0, 7);
#else
#error "No system clock enable defined for this processor!"
#endif

#if defined(__LPC82X__) || defined(__LPC84X__)
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
#else
#error "No definition of SPI pin configuration for this processor!"
#endif

			//	Disable AHB clock domain for SWM
#if defined(__LPC82X__)
            SystemClock::enable(0, 12, false);
#elif defined(__LPC84X__)
            SystemClock::enable(0, 7, false);
#endif

			return;
		}

    uint8_t num_;
    mutable SPI::lpc_peripheral_t* spi_;
		uint8_t len_;
    uint32_t ctrl_base_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_SPI_H*/
