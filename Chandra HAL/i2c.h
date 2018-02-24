#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#include <chip.h>

#include "chip_utils.h"
#include "chrono.h"
#include "gpio.h"

namespace chandra
{
namespace io
{

class I2CMaster
{
	public:
		typedef uint32_t size_t;

		enum I2CCompletionState {
			I2C_OK,
			I2C_ADDR_NACKED,
			I2C_TX_NACKED,
			I2C_RX_FAILED,
			I2C_TIMEOUT
		};

		enum I2CFramingCMDs {
			I2C_BEGIN,
			I2C_END,
			I2C_WRAP,
			I2C_NONE
		};

		enum I2CMasterState {
			IDLE = 0x00,
			RX_AVAIL = 0x01,
			TX_OK = 0x02,
			ADDR_NACK = 0x03,
			DATA_NACK = 0x04,
			ARBITRATION_LOST = 0x08,
			START_STOP_ERROR = 0x10
		};

		struct I2CStatus
		{
			I2CStatus(const I2CCompletionState& _state = I2C_OK, const size_t& _cnt = 0) : state(_state), cnt(_cnt) {}
			I2CStatus(const I2CStatus& _other) : state(_other.state), cnt(_other.cnt) {}

			bool ok() const { return (state == I2C_OK); }

			I2CCompletionState state;
			size_t cnt;
		};


        I2CMaster(uint8_t _num) : i2c_(getI2CPeripheral(_num)) {} // TODO: ADD THE ABILITY TO CONFIGURE PINS ON SOME I2C PERIPHERALS

		void init(const uint32_t& _f_i2c = 400000 ) {
	#if defined(__LPC82X__)
			//	Enable the I2C Clock & Reset the Peripheral
			SystemClock::enable(0, 5); // TODO: CHECK THESE REGISTERS AND BITS
			PeripheralActivity::reset(0, 6);

			//	Configure I2C sub-system Clock Generation
			setI2CClockParams(SystemCoreClock, _f_i2c);

			//	Configure the SWM
			FixedFunctionIO::enable(0, 11);
			FixedFunctionIO::enable(0, 12);

			//	Set Pins for standard I2C Mode
			LPC_IOCON->PIO0[IOCON_PIO10] = 0x80; // Bit 7 is reserved and is supposed to be a 1
			LPC_IOCON->PIO0[IOCON_PIO11] = 0x80;
	#elif defined(__LPC15XX__)
			//	Enable the I2C Clock & Reset the Peripheral
			SystemClock::enable(1, 13);
			PeripheralActivity::reset(1, 13);

			//	Configure I2C sub-system Clock Generation
			setI2CClockParams(SystemCoreClock, _f_i2c);

			//	Configure the SWM
			FixedFunctionIO::enable(1, 3);
			FixedFunctionIO::enable(1, 4);

			//	Set Pins for standard I2C Mode
			LPC_IOCON->PIO[0][22] = 0x00; // TODO: CHECK THIS CONFIGURATION
			LPC_IOCON->PIO[0][23] = 0x00;
	#endif
		}

		bool enable(bool _enable = true) {
			static const uint32_t enable_mask = 1UL<<0;
			if(_enable){
				i2c_->CFG |= enable_mask;
			} else {
				i2c_->CFG &= ~enable_mask;
			}

			return enabled();
		}

		bool enabled() const {
			static const uint32_t enable_mask = 1UL<<0;
			return (i2c_->CFG & enable_mask) != 0;
		}

		I2CStatus writeCMD(const uint8_t& _addr, const uint8_t& _cmd) { return writeBytes( _addr, &_cmd, 1 ); }

		I2CStatus writeReg(const uint8_t& _addr, const uint8_t _reg, const uint8_t* const _data, const size_t& _cnt = 1) {
			size_t txrx_cnt = 0;
			I2CStatus status = writeBytes(_addr, &_reg, 1, I2C_BEGIN);
			txrx_cnt = status.cnt;
			if(status.ok()){
				status = writeBytes(_addr, _data, _cnt, I2C_END);
				txrx_cnt += status.cnt;
			}

			return I2CStatus(status.state, txrx_cnt);
		}

		I2CStatus readReg(const uint8_t& _addr, const uint8_t& _reg, uint8_t* const _data, const size_t& _cnt = 1) {
			size_t txrx_cnt = 0;
			I2CStatus status = writeBytes(_addr, &_reg, 1, I2C_BEGIN);
			txrx_cnt = status.cnt;
			if(status.ok()) {
				status = readBytes(_addr, _data, _cnt, I2C_WRAP);
				txrx_cnt += status.cnt;
			}

			return I2CStatus(status.state, txrx_cnt);
		}

		I2CStatus writeBytes(const uint8_t& _addr, const uint8_t* const _data, const size_t& _cnt, const I2CFramingCMDs& _framing=I2C_WRAP) {
			I2CMasterState status = startWrite(_framing, _addr);

			if(status == TX_OK){
				for(size_t index = 0; index < _cnt; ++index) {
					status = masterState();
					if( (index != (_cnt - 1)) && (status != TX_OK) ) {
						stop(_framing);
						return I2CStatus(I2C_TX_NACKED, index+1);
					}

					i2c_->MSTDAT = _data[index];
					continueTXRX();
					waitForPending();
				}
				stop(_framing);
			} else if(status == IDLE) {
				return I2CStatus();
			} else {
				return I2CStatus(I2C_ADDR_NACKED);
			}

			return I2CStatus(I2C_OK,_cnt);
		}

		I2CStatus readBytes(const uint8_t _addr, uint8_t* const _data, const size_t& _cnt, const I2CFramingCMDs& _framing = I2C_WRAP){
			I2CMasterState state = startRead(_framing, _addr);

			if(state == RX_AVAIL){
				for(size_t index = 0; index < _cnt; ++index) {
					_data[index] = i2c_->MSTDAT;
					continueTXRX();
					waitForPending();
					state = masterState();
					if(state != RX_AVAIL){
						// ?? STOP
						return I2CStatus(I2C_RX_FAILED, index+1);
					}
				}
				stop(_framing);
			} else if(state == IDLE) {
				return I2CStatus();
			} else {
				// ?? STOP
				return I2CStatus(I2C_ADDR_NACKED, 0);
			}

			return I2CStatus(I2C_OK, _cnt);
		}


	protected:
		I2CMasterState start( const I2CFramingCMDs& _framing, const uint8_t _addr, bool _read, const uint8_t& _max_attempts = 10 ) {
			I2CMasterState state;

			if((_framing == I2C_BEGIN) || (_framing == I2C_WRAP)) {
				const uint8_t start_byte =(_addr<<1) | (_read?0x01:0x00);
				bool valid = false;
				uint8_t attempt = 1;
				while(!valid) {
					i2c_->MSTDAT = start_byte;
					i2c_->STAT;
					i2c_->MSTCTL = (1<<1); // Trigger the start
					waitForPending();
					state = masterState();
					if((state == ARBITRATION_LOST) || (state == START_STOP_ERROR)){
						continueTXRX(); // Clear the error flags and tries again
						valid = false;
						if(attempt >= _max_attempts) break;
						++attempt;
					} else {
						valid = true;
					}
				}
			} else {
				state = masterState();
			}

			return state;
		}

		I2CMasterState startRead(const I2CFramingCMDs& _framing, const uint8_t& _addr) { return start(_framing, _addr, true); }
		I2CMasterState startWrite(const I2CFramingCMDs& _framing, const uint8_t& _addr) { return start(_framing, _addr, false); }

		I2CMasterState stop( const I2CFramingCMDs& _framing ) {
			if((_framing == I2C_WRAP) || (_framing == I2C_END)) i2c_->MSTCTL = (1<<2); // STOP
			return masterState();
		}

		I2CMasterState continueTXRX() {
			i2c_->MSTCTL = (1<<0);
			return masterState();
		}

		void waitForPending() const {
			while( !((i2c_->STAT) & (1<<0)) ) {};
		}

		I2CMasterState masterState() const {
			const uint32_t stat = i2c_->STAT;
			return static_cast<I2CMasterState>((stat>>1UL) & 0x1FUL);
		}

		void setI2CClockParams(const uint32_t& _f_clk, const uint32_t& _f_i2c) {
			const uint32_t div_nearest = (_f_clk + (_f_i2c/2)) / _f_i2c;
			uint32_t t_h=2, t_l=2, div = 0;
			uint32_t error,	best_t_h, f_actual;
			uint32_t best_error = _f_i2c;

			const bool even = (div_nearest&0x01) == 0;
			const uint32_t increment = even ? 0 : 1;
			const size_t search_maximum = even ? 10 : 9;

			for( size_t t = 2; t < search_maximum; ++t ) {
		        t_h = t;
		        t_l = t + increment;
		        div = div_nearest / (t_h+t_l);
		        f_actual = _f_clk / (div*(t_h+t_l));
		        error = (_f_i2c > f_actual) ? (_f_i2c-f_actual) : (f_actual-_f_i2c);
		        if( error == 0 ) {
		            break;
		        } else {
		        	best_t_h = 1; // HACK.  THIS FUNCTION NEEDS TO BE CHECKED
		            if( (error < best_error) ) {
		                best_error = error;
		                best_t_h = t_h;
		            }

					if( t == (search_maximum-1) ) {
						t_h = best_t_h;
						t_l = best_t_h + increment;
				        div = div_nearest / (t_h+t_l);
					}
				}
			}

			i2c_->CLKDIV = (div-1);
			i2c_->MSTTIME = ((t_h-2)<<4) | ((t_l-2)<<0);

			return;
		}

    protected:
        I2C_PERPIHERAL_TYPE* getI2CPeripheral(const uint8_t&) {
            return LPC_I2C0; // TODO: IMPLEMENT THIS SELECTION FUNCTION
        }

	private:
		I2C_PERIPHERAL_TYPE* i2c_;
};

template<class output_stream_type>
output_stream_type& operator << (output_stream_type& _stream, I2CMaster::I2CStatus _status) {
	_stream << "[ state = ";

	switch(_status.state) {
		case I2CMaster::I2C_OK:
			_stream << "I2C_OK";
			break;

		case I2CMaster::I2C_ADDR_NACKED:
			_stream << "I2C_ADDR_NACKED";
			break;

		case I2CMaster::I2C_TX_NACKED:
			_stream << "I2C_TX_NACKED";
			break;

		case I2CMaster::I2C_RX_FAILED:
			_stream << "I2C_RX_FAILED";
			break;

		case I2CMaster::I2C_TIMEOUT:
			_stream << "I2C_TIMEOUT";
			break;

		default:
			_stream << "UNKNOWN";
			break;
	}
	_stream << ", txrx bytes = " << static_cast<unsigned int>(_status.cnt) << " ]\n\r";

	return _stream;
}

template<class output_stream_type>
void printI2CStatus(output_stream_type& _stream, I2CMaster::I2CStatus _status, const char* _msg = 0) {
	_stream << "I2C Status ";
	if(_msg != 0) { _stream << "(" << _msg << ") "; }
	_stream << "[ state = ";

	switch(_status.state) {
		case I2CMaster::I2C_OK:
			_stream << "I2C_OK";
			break;

		case I2CMaster::I2C_ADDR_NACKED:
			_stream << "I2C_ADDR_NACKED";
			break;

		case I2CMaster::I2C_TX_NACKED:
			_stream << "I2C_TX_NACKED";
			break;

		case I2CMaster::I2C_RX_FAILED:
			_stream << "I2C_RX_FAILED";
			break;

		case I2CMaster::I2C_TIMEOUT:
			_stream << "I2C_TIMEOUT";
			break;

		default:
			_stream << "UNKNOWN";
			break;
	}
	_stream << ", txrx bytes = " << static_cast<unsigned int>(_status.cnt) << " ]\n\r";
}

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_I2C_H*/
