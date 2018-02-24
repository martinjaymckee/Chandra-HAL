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
struct SPI
{
        enum transfer_mode_t {
            START,
            STOP,
            WRAP
        };
};

class SPIMaster
{
	public:
        using value_t = uint8_t;
        using cs_t = uint8_t;
        using pin_t = chandra::io::IO;

		static const cs_t  CS0 = ~0x01, CS1 = ~0x02, CS2 = ~0x04, CS3 = ~0x08;

        SPIMaster( uint8_t _num, pin_t _miso, pin_t _mosi, pin_t _sclk,
             pin_t _cs0, auto _cs1=255, auto _cs2=255, auto _cs3=255 )
            : spi_(getSPI(_num)), len_(8)
		{
	#if defined(__LPC82X__)
			//	Initialize the peripheral clock and peripheral reset
			if(spi_ == LPC_SPI0) {
				SystemClock::enable(0, 11);
				PeripheralActivity::reset(0, 0);
			} else if ( spi_ == LPC_SPI1 ) {
				SystemClock::enable(0, 12);
				PeripheralActivity::reset(0, 1);
			}
	#elif defined(__LPC15XX__)
			//	Initialize the peripheral clock and peripheral reset
			if(spi_ == LPC_SPI0) {
				SystemClock::enable(1, 9);
				PeripheralActivity::reset(1, 9);
			} else if ( spi_ == LPC_SPI1 ) {
				SystemClock::enable(1, 10);
				PeripheralActivity::reset(1, 10);
			}
	#endif
			// Configure the Pins
			setPins(_miso, _mosi, _sclk, _cs0, _cs1, _cs2, _cs3);

			// Setup Clock Divisor
            spi_->DIV = chandra::chrono::frequency::spi(num_) - 1UL;
		}

		bool enable( bool _enable, uint8_t _mode = 0 ) {
			if(_enable) {
				spi_->CFG = (_mode<<3) | (1<<2); // Enable, In Master Mode
				spi_->CFG |= (1<<0);
			} else {
				spi_->CFG = 0; //&= ~((1<<2) | (1<<0)); -- TODO: CHCK THIS AND FIX IT IF IT ISN'T CORRECT
			}
			return _enable;
		}

		bool enable() const { return spi_->CFG & (1<<0); }
		uint8_t mode() const { return (spi_->CFG >> 4) & 0x03; }

		void tx(const value_t* _buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = WRAP){
			uint16_t ctrl = 0;

			//	Set Transfer Packet Length and RXIGNORE
			ctrl = ((len_-1) << 8) | (1<<6);

			//	Initialize the Slave Select Lines
			if(_cs != 255) {
				ctrl |= (_cs&0x0F);
			}

			for(size_t index = 0; index < _cnt; ++index ) {
				//	Prepare to Deassert the Slave Select Lines -- Send End of Transfer
				if((index == (_cnt-1)) && ((_transfer_mode == STOP) | (_transfer_mode == WRAP))){
					ctrl |= (1<<4);
				}

				//	Wait for TXRDY and Write Data
				while( !(spi_->STAT & (1<<1)) ){}
				spi_->TXDATCTL = (ctrl<<16) | *_buf;
				++_buf;
			}

			return;
		}

		value_t* rx(value_t* const _out_buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = WRAP, const value_t& _stuff = 0xFF) {
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
				if((index == (_cnt-1)) && ((_transfer_mode == STOP) | (_transfer_mode == WRAP))){
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


		value_t* txrx(const value_t* _in_buf, value_t* const _out_buf, size_t _cnt, cs_t _cs = 255, const transfer_mode_t& _transfer_mode = WRAP) {
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
				if((index == (_cnt-1)) && ((_transfer_mode == STOP) | (_transfer_mode == WRAP))){
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
        SPI_PERIPHERAL_TYPE* getSPI(uint8_t _num) {
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
                      auto _cs1=255, auto _cs2=255, auto _cs3=255) {
			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 12);

#if defined(__LPC82x__)
			//
			// Setup the Main SPI Pins
			//
			if( spi_ == LPC_SPI0 ){
				LPC_SWM->PINASSIGN[3] = (LPC_SWM->PINASSIGN[3] & 0x00FFFFFF) | (_sclk<<24);
				LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0xFF000000) | (_cs0<<16) | (_miso<<8) | _mosi;
			} else {
				LPC_SWM->PINASSIGN[5] = (LPC_SWM->PINASSIGN[5] & 0xFFFF) | (_mosi<<24) | (_sclk<<16);
				LPC_SWM->PINASSIGN[6] = (LPC_SWM->PINASSIGN[6] & 0xFFFF0000) | (_cs0<<8) | _miso;
			}

			//
			// Setup the Chip Select lines
			//
			if( spi_== LPC_SPI0 ){
				if(_cs1 != 255) LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0x00FFFFFF) | (_cs1<<24);
				if(_cs2 != 255) LPC_SWM->PINASSIGN[5] = (LPC_SWM->PINASSIGN[5] & 0xFFFFFF00) | _cs2;
				if(_cs3 != 255) LPC_SWM->PINASSIGN[5] = (LPC_SWM->PINASSIGN[5] & 0xFFFF00FF) | (_cs3<<8);
			} else {
				if(_cs1 != 255) LPC_SWM->PINASSIGN[6] = (LPC_SWM->PINASSIGN[6] & 0xFF00FFFF) | (_cs1<<16);
			}
#elif defined(__LPC15XX__)
			//
			// Setup the Main SPI Pins
			//
			if( spi_ == LPC_SPI0 ){
				LPC_SWM->PINASSIGN[3] = (LPC_SWM->PINASSIGN[3] & 0x000000FF) | (_miso<<24) | (_mosi<<16) | (_sclk<<8);
				LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[3] & 0xFFFFFF00) | _cs0;
			} else {
				LPC_SWM->PINASSIGN[5] = (_cs0<<24) | (_miso<<16) | (_mosi<<8) | _sclk;
			}

			//
			// Setup the Chip Select lines
			//
			if( spi_== LPC_SPI0 ){
				if(_cs1 != 255) LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0xFFFF00FF) | (_cs1<<8);
				if(_cs2 != 255) LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0xFF00FFFF) | (_cs2<<16);
				if(_cs3 != 255) LPC_SWM->PINASSIGN[4] = (LPC_SWM->PINASSIGN[4] & 0x00FFFFFF) | (_cs3<<24);
			} else {
				if(_cs1 != 255) LPC_SWM->PINASSIGN[6] = (LPC_SWM->PINASSIGN[6] & 0xFFFFFF00) | _cs1;
			}
#endif

			//	Disable AHB clock domain for SWM
			SystemClock::enable(0, 12, false);
			return;
		}

		SPI_PERIPHERAL_TYPE* spi_;
		uint8_t len_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_SPI_H*/
