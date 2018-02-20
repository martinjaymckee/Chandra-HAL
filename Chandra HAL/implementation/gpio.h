/*
 * gpio.h
 *
 *  Created on: Apr 6, 2016
 *      Author: martin
 */

#ifndef CHANDRA_GPIO_H
#define CHANDRA_GPIO_H

#include <stdint.h>

#include <chip.h>

#include "chip_utils.h"
#include "chrono.h"

namespace chandra
{
namespace io
{

namespace internal
{
struct IODef
{
	constexpr IODef(const uint8_t& _port = 255, const uint8_t& _pin = 255, const bool& _inverted = false)
	: port(_port), pin(_pin), inverted(_inverted) {}
	const uint8_t port;
	const uint8_t pin;
	const bool inverted;
};
} /*namespace internal*/

class IO
{
	public:
		enum Mode { // TODO: IMPLEMENT SETTING THE PIN MODE
			Pullup,
			Pulldown,
			HiZ
		};

		static IO Input( uint8_t _port, uint8_t _pin, bool _inverted = false ) { return {_port, _pin, false, _inverted}; }
		static IO Input( const internal::IODef& _io) { return {_io.port, _io.pin, true, _io.inverted}; }
		static IO Output( uint8_t _port, uint8_t _pin, bool _inverted = false ) { return {_port, _pin, true, _inverted}; }
		static IO Output( const internal::IODef& _io) { return {_io.port, _io.pin, true, _io.inverted}; }

		IO(uint8_t _port, uint8_t _pin, bool _is_output = false, bool _inverted = false)
		: port_(_port), pin_(_pin), mask_(1UL<<_pin), inverted_(_inverted) {
			init();
			output(_is_output);
		}

		IO(const internal::IODef& _io, bool _is_output = false) : IO(_io.port, _io.pin, _is_output, _io.inverted) {}

		IO( const IO& _other ) : port_(_other.port_), pin_(_other.pin_), mask_(_other.mask_), inverted_(_other.inverted_) {
			const bool is_output = _other.output(); // TODO: FIGURE OUT IF THIS ACUTALLY NEEDS TO BE REDONE ON COPY....
			output(is_output);
		}

		void init() {
			// Enable AHB clock to the GPIO domain.
			GPIO::enableClk(port_);
		}

		bool output(bool _output) {
			return GPIO::direction(port_, pin_, _output);
		}

		bool output() const {
			return GPIO::direction(port_, pin_);
		}

		bool inverted() const { return inverted_; }

		template<class T>
		IO& operator = ( const T& _value ) {
	#if defined(__LPC82X__)
			if(inverted_^bool(_value)){
				LPC_GPIO_PORT->SET[0] |= mask_;
			} else {
				LPC_GPIO_PORT->CLR[0] |= mask_;
			}
	#elif defined(__LPC15XX__)
			if(inverted_ ? !bool(_value) : bool(_value)){
				LPC_GPIO->SET[port_] |= mask_;
			} else {
				LPC_GPIO->CLR[port_] |= mask_;
			}
	#endif
			return *this;
		}

		IO& operator ~ () {
	#if defined(__LPC82X__)
			LPC_GPIO_PORT->NOT[0] |= mask_;
	#elif defined(__LPC15XX__)
			LPC_GPIO->NOT[port_] |= mask_;
	#endif
			return *this;
		}

		operator bool() const {
	#if defined(__LPC82X__)
			const bool read = (LPC_GPIO_PORT->PIN[0] & mask_);
	#elif defined(__LPC15XX__)
			const bool read = (LPC_GPIO->PIN[port_] & mask_);
	#endif
			return inverted_ ? !read : read;
		}

		uint8_t port() const { return port_; }
		uint8_t pin() const { return pin_; }


		// TODO: ADD "WAIT" TRIGGERS, WITH AND WITHOUT TIMEOUTS... THEY DON'T BELONG IN GPIO, HOWEVER, THEY SHOULD BE IN
		//	THE CHANDRA EVENT SYSTEM SOMEWHERE....  MAYBE SOMETHING LIKE UNTILTRUE AND UNTILFALSE, OR SOMETHING AS SIMPLE AS
		//	UNTILSTATE WITH A PASSED IN STATE... IN ANY CASE SOME BOOLEAN TRIGGER THAT HANDLES LOTS OF DIFFERENT INPUT TYPES
		//	WOULD BE AWESOME

/*		bool waitForState(const bool& _state){
			if( _timeout_us.count() == 0 ) {
				while(this->operator bool() != _state){}
				return true;
			}

			return true;
		}

		bool waitForStateWithTimeout(const bool& _state, const std::chrono::duration<uint32_t, std::micro>& _timeout_us){
			auto start = chandra::chrono::timestamp_clock::now();
			while(this->operator bool() != _state){
				if(chandra::chrono::after(start, _timeout_us)) return false;
			}

			return true;
		}
*/
	private:
		const uint8_t port_;
		const uint8_t pin_;
		const uint32_t mask_; // TODO: THIS SHOULD BE BASED ON "REGISTER_T"
		const bool inverted_;
};

// TODO: BASE THE LED CLASS UPON PREVIOUSLY DEFINED "NON-BLOCKING" IO OPERATIONS
class LED
{
	public:
		typedef enum {
			Fixed,
			Pulse,
			PWM
		} mode_t; // TODO: THIS COULD ( SHOULD? ) BE GENERALIZED TO AN LED "COMMAND"

		using clock_t = chandra::chrono::timestamp_clock;
		using duration_t = clock_t::duration;
		using time_point_t = clock_t::time_point;

	public:
		LED( uint8_t _port, uint8_t _pin, bool _inverted = false ) : pin_(_port, _pin, true, _inverted ), mode_(Fixed) {
			init();
		}

		LED(const IO& _io) : pin_(_io), mode_(Fixed) {
			pin_.output(true);
			init();
		}

		LED(const internal::IODef& _io) : LED(IO(_io)) {}

		void init() {

		}

		template<class T>
		LED& operator = ( const T& _value ) {
			const bool value = bool(_value);
			mode_ = Fixed;
			pin_ = value;
			return *this;
		}

		IO& pin() {
			return pin_;
		}

		mode_t mode() const {
			return mode_;
		}

		LED& operator ~ () {
			mode_ = Fixed;
			~pin_;
			return *this;
		}

		template<typename Scale = uint32_t>
		LED& pwm( const duration_t& _period, const Scale& _duty_cycle = 50, const bool& _inverted = false, const bool& _reset = true ){
			active_period_ = duration_t( (_duty_cycle * _period.count()) / 100); // TODO: FIGURE OUT IF THERE IS A SAFER WAY TO DO THIS
			inactive_period_ = _period - active_period_;
			mode_ = PWM;
			if(_reset) {
				pin_ = !_inverted;
				state_ = !_inverted;
				timestamp_ = clock_t::now();
			}
			return *this;
		}

		template<typename Scale = uint32_t>
		LED& pwmUpdate(const duration_t& _period, const Scale& _duty_cycle = 50, const bool& _inverted = false, const bool& _reset = true ) {
			return pwm(_period, _duty_cycle, _inverted, false);
		}

		LED& pulse(const duration_t& _active_period, const duration_t& _total_period = duration_t{0}, const bool& _blocking = false ) {
			active_period_ = _active_period;
			inactive_period_ = ( _total_period <= _active_period ) ? duration_t(0) : _total_period - _active_period;
			mode_ = Pulse;
			~pin_;
			timestamp_ = clock_t::now();
			state_ = true;
			if(_blocking) {
				do {
					update();
				} while( mode_ == Pulse );
			}
			return *this;
		}

		bool update() {
			bool updated = false;

			auto current = clock_t::now();

			if( mode_ == Pulse ){
				if( state_ ) {
					if( chandra::chrono::after(active_period_, timestamp_, current) ) {
						~pin_;
						state_ = false;
						timestamp_ = current;
					}
				} else {
					if( chandra::chrono::after(inactive_period_, timestamp_, current) ) {
						mode_ = Fixed;
						updated = true;
					}
				}
			} else if ( mode_ == PWM ) {
				if( state_ ) {
					if( chandra::chrono::after(active_period_, timestamp_, current) ) {
						~pin_;
						state_ = !state_;
						timestamp_ = current;
					}
				} else {
					if( chandra::chrono::after(inactive_period_, timestamp_, current) ) {
						~pin_;
						state_ = !state_;
						timestamp_ = current;
						updated = true;
					}
				}
			}

			return updated;
		}

	private:
		IO pin_;
		mode_t mode_;

		bool state_;
		duration_t active_period_;
		duration_t inactive_period_;
		time_point_t timestamp_;
};


//
// GPIO Related Functions
//

// TODO: THIS SHOULD BE PROTECTED WITH BETTER TYPES...
template<typename GPIO, typename Clock = chandra::chrono::timestamp_clock>
void pulseOut(GPIO& _io, auto _delay, const typename Clock::time_point& _start = Clock::now()) {
	~_io;
	chandra::chrono::delay(_delay, _start);
	~_io;
}

// TODO: TEST THE PULSEIN FUNCTIONS
template<typename GPIO, typename Clock = chandra::chrono::timestamp_clock>
typename Clock::duration pulseIn(GPIO& _io, const bool& _init) {
	while(_io != _init) {}
	const auto start = Clock::now();
	while(_io == _init) {}
	return Clock::now() - start;
}

template<typename GPIO, typename Clock = chandra::chrono::timestamp_clock>
typename Clock::duration pulseIn(GPIO& _io) {
	return pulseIn(_io, bool(_io));
}

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_GPIO_H*/
