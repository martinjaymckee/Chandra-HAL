#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#if defined(__LPC82X__) || defined(__LPC15XX__)
#include <chip.h>
#elif defined(__LPC84X__)
#include <LPC8xx.h>
#elif defined(__CHANDRA_MOCK__)
#warning "I2C file parsed in mock mode."
#else
#error "I2C processor undefined!"
#endif

#include "chip_utils.h"
#include "chrono.h"
#include "gpio.h"

// TODO: CHANGE THE INIT FUNCTION TO TAKE A FREQUENCY QUANTITY (IN HZ)

namespace chandra
{
namespace io
{


//template<class Clock = chandra::chrono::timestamp_clock>
class I2CMaster
{
	public:
		using clock_t = chandra::chrono::timestamp_clock; // This should come from a template parameter... Clock;
		using size_t = uint32_t;

		#if defined(__LPC82X__) || defined(__LPC15XX__)
    using lpc_peripheral_t = LPC_I2C_T;
    #elif defined(__LPC84X__)
    using lpc_peripheral_t = LPC_I2C_TypeDef;
    #endif

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
			// I2CStatus(const I2CStatus& _other) : state(_other.state), cnt(_other.cnt) {}

			bool ok() const { return (state == I2C_OK); }

			I2CCompletionState state;
			size_t cnt;
		};


    I2CMaster(uint8_t _num, const chandra::io::IO& _scl, const chandra::io::IO& _sda)
			: num_(_num), i2c_(getI2CPeripheral(_num)), scl_(_scl), sda_(_sda) {

			} // TODO: ADD THE ABILITY TO CONFIGURE PINS ON SOME I2C PERIPHERALS

		bool init(const uint32_t& _f_i2c = 400000, bool _auto_enable = true) {

			//	Enable the I2C Clock & Reset the Peripheral
			#if defined(__LPC82X__)
			switch(num_) {
				default:
				case 0:
					SystemClock::enable(0, 5);
					PeripheralActivity::reset(0, 6);
					break;
				case 1:
					SystemClock::enable(0, 21);
					PeripheralActivity::reset(0, 14);
					break;
				case 2:
					SystemClock::enable(0, 22);
					PeripheralActivity::reset(0, 15);
					break;
				case 3:
					SystemClock::enable(0, 23);
					PeripheralActivity::reset(0, 16);
					break;
			}
			#elif defined(__LPC84X__)
			LPC_SYSCON->FCLKSEL[5+num_] = 0x01;
			switch(num_) {
				default:
				case 0:
					SystemClock::enable(0, 5);
					PeripheralActivity::reset(0, 5);
					break;
				case 1:
					SystemClock::enable(0, 21);
					PeripheralActivity::reset(0, 21);
					break;
				case 2:
					SystemClock::enable(0, 22);
					PeripheralActivity::reset(0, 22);
					break;
				case 3:
					SystemClock::enable(0, 23);
					PeripheralActivity::reset(0, 23);
					break;
			}

			#elif defined(__LPC15XX__)
			SystemClock::enable(1, 13);
			PeripheralActivity::reset(1, 13);
			#endif

			//	Configure I2C sub-system Clock Generation
			setI2CClockParams(chandra::chrono::frequency::i2c(num_).value(), _f_i2c);

	#if defined(__LPC82X__)
			//	Configure the SWM
			FixedFunctionIO::enable(0, 11);
			FixedFunctionIO::enable(0, 12);

			//	Set Pins for standard I2C Mode
			SystemClock::enable(0, 18);
			LPC_IOCON->PIO0[IOCON_PIO10] = 0x80; // Bit 7 is reserved and is supposed to be a 1
			LPC_IOCON->PIO0[IOCON_PIO11] = 0x80;
			SystemClock::enable(0, 18, false);
	#elif defined(__LPC84X__)
			//	Configure the SWM
			//	Enable AHB clock domains for SWM
			SystemClock::enable(0, 7);

      //	Setup Switch Matrix
			const uint8_t scl_pin = 32*scl_.port() + scl_.pin();
			const uint8_t sda_pin = 32*sda_.port() + sda_.pin();

      switch(num_) {
        default:
				case 0:
					FixedFunctionIO::enable(0, 13);
					FixedFunctionIO::enable(0, 12);
					break;

        case 1:
          LPC_SWM->PINASSIGN[9] = 0x0000FFFF | (scl_pin<<24) | (sda_pin<<16);
          break;

        case 2:
          LPC_SWM->PINASSIGN[10] = 0xFFFF0000 | (scl_pin<<8) | sda_pin;
          break;

        case 3:
          LPC_SWM->PINASSIGN[10] = 0x0000FFFF | (scl_pin<<24) | (sda_pin<<16);
          break;
      }
			SystemClock::enable(0, 7, false);
	#elif defined(__LPC15XX__)
			//	Configure the SWM
			FixedFunctionIO::enable(1, 3);
			FixedFunctionIO::enable(1, 4);

			//	Set Pins for standard I2C Mode
			LPC_IOCON->PIO[0][22] = 0x00; // TODO: CHECK THIS CONFIGURATION
			LPC_IOCON->PIO[0][23] = 0x00;
	#endif
			return enable(_auto_enable);
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

		const chandra::io::IO& sda() const { return sda_; }
		const chandra::io::IO& scl() const { return scl_; }

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
					if(!waitForPending()) return I2CStatus(I2C_TIMEOUT);
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
					if(!waitForPending()) return I2CStatus(I2C_TIMEOUT);
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
					if(!waitForPending()) return START_STOP_ERROR;
					state = masterState();
					if((state == ARBITRATION_LOST) || (state == START_STOP_ERROR)){
						continueTXRX(); // Clear the error flags and try again
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

		// NOTE: THIS HAS BEEN MODIFIED TO HANDLE TIMEOUT...
		//	THIS REQUIRES MORE CODE BUT IT SHOULDN'T BE MUCH SLOWER... SINCE IT IS A BUSY LOOP ANYWAY.
		bool waitForPending() const {
			const auto start = clock_t::now();
			while( !((i2c_->STAT) & (1<<0)) ) {
				// TODO: FIX TIMEOUT HANDLING...
				if(false and chandra::chrono::after(10ms, start, clock_t::now())) return false;
			}
			return true;
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
        lpc_peripheral_t* getI2CPeripheral(const uint8_t& _idx) {
					switch(_idx) {
						default:
						case 0:
							return LPC_I2C0;

						case 1:
							return LPC_I2C1;

						case 2:
							return LPC_I2C2;

						case 3:
							return LPC_I2C3;
					}
        }

	private:
		uint8_t num_;
		mutable volatile lpc_peripheral_t* i2c_;  // TODO: FIGURE OUT IF BOTH MUTABLE AND VOLATILE ARE REQUIRED
		const chandra::io::IO scl_;
    const chandra::io::IO sda_;
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
