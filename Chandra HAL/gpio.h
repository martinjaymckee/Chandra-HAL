/*
 * gpio.h
 *
 *  Created on: Apr 6, 2016
 *      Author: martin
 */

#ifndef CHANDRA_GPIO_H
#define CHANDRA_GPIO_H

#include <stdint.h>

#if defined(__LPC82X__)
#include<chip.h>
#elif defined(__LPC84X__)
#include <LPC8xx.h>
#elif defined(__LPC15XX__)
#include <chip.h>
#endif

#include "chip_utils.h"
#include "chrono.h"
// TODO: NEED TO HANDLE DEFAULT CONSTRUCTED GPIO PINS IN A BETTER WAY SO THAT THEY ARE SAFER

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

struct NullIO {};
} /*namespace internal*/

static const internal::NullIO NC;

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

        IO() : port_(255), pin_(255), mask_(0), inverted_(false) {}

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

        // IO& operator = (const IO& _other) { // NOTE: THIS DOESN'T WORK BECAUSE THE VALUES ARE CONSTANT
        //   port_ = _other.port_;
        //   pin_ = _other.pin_;
        //   mask_ = _other.mask_;
        //   inverted_ = _other.inverted_;
        //   return *this;
        // }

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
    #elif defined(__LPC84X__)
            if(inverted_^bool(_value)){
                LPC_GPIO_PORT->SET[port_] |= mask_;
            } else {
                LPC_GPIO_PORT->CLR[port_] |= mask_;
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
    #elif defined(__LPC84X__)
            LPC_GPIO_PORT->NOT[port_] |= mask_;
    #elif defined(__LPC15XX__)
            LPC_GPIO->NOT[port_] |= mask_;
    #endif
            return *this;
        }

        operator bool() const {
    #if defined(__LPC82X__)
            const bool read = (LPC_GPIO_PORT->PIN[0] & mask_);
    #elif defined(__LPC84X__)
        const bool read = (LPC_GPIO_PORT->PIN[port_] & mask_);
    #elif defined(__LPC15XX__)
            const bool read = (LPC_GPIO->PIN[port_] & mask_);
    #endif
            return inverted_ ? !read : read;
        }

        constexpr uint8_t port() const { return port_; }
        constexpr uint8_t pin() const { return pin_; }
        constexpr uint8_t number() const { return (32*port_) + pin_; }

        constexpr bool valid() const { return mask_ != 0; }

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

// TODO: MOVE THE LED IMPLEMENTATION (AND RGBLED IMPLEMENTATION) OUT OF THE GPIO
//  FILE AND INTO LED.H, WHICH WILL DEPEND UPON GPIO.H

// TODO: USE THESE "COLORS" TO CREATE A NICE RGBLED OBJECT WHICH HANDLES THE LED IN
//  THE SAME WAY AS A SINGLE LED ONLY ALLOWS YOU TO USE "ACTIVE" AND "INACTIVE" COLORS
//  AND THEREFORE "BLINK" BETWEEN COLORS.

enum class colors_t {
    OFF = 0X00,
    RED = 0X01,
    GREEN = 0X02,
    YELLOW = 0X03,
    BLUE = 0X04,
    MAGENTA = 0x05,
    CYAN = 0X06,
    WHITE = 0X07
};

// TODO: BASE THE LED CLASS UPON PREVIOUSLY DEFINED "NON-BLOCKING" IO OPERATIONS
class LED
{
    public:
        enum mode_t {
            Fixed,
            Pulse,
            PWM,
            Breathe
        }; // TODO: THIS COULD ( SHOULD? ) BE GENERALIZED TO AN LED "COMMAND"

        using clock_t = chandra::chrono::timestamp_clock; // TODO: SHOULD THIS BE PASSED IN?
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

        void init() { // TODO: DECIDE IF IT MAKES SENSE TO INCLUDE AN INIT METHOD EVEN THOUGH IT'S A NOP

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

        template<typename Scalar = uint32_t>
        LED& pwm( const duration_t& _period, const Scalar& _duty_cycle = 50, const bool& _inverted = false, const bool& _reset = true ){
            duty_cycle_ = _duty_cycle;
            active_period_ = calcActivePeriod(_period, 100*_duty_cycle);
            inactive_period_ = _period - active_period_;
            cycle_period_ = active_period_ + inactive_period_;
            mode_ = PWM;
            if(_reset) {
                pin_ = !_inverted;
                state_ = !_inverted;
                timestamp_ = clock_t::now();
            }
            return *this;
        }

        template<typename Scalar = uint32_t>
        LED& pwmUpdate(const duration_t& _period, const Scalar& _duty_cycle = 50, const bool& _inverted = false, const bool& _reset = true ) {
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

        LED& pulse(const duration_t& _active_period, const bool& _blocking) {
          return pulse(_active_period, _active_period, _blocking);
        }

        LED& breathe(const duration_t& _cycle_period, const bool _reset=true, const duration_t& _pwm_period = std::chrono::milliseconds{10}) {
          const uint32_t steps = (_cycle_period.count() + (_pwm_period.count()/2)) / _pwm_period.count();
          duty_cycle_step_ = (20000 + (steps/2)) / steps;
          update_period_ = duration_t{(_cycle_period.count() + (steps/2)) / steps};
          mode_ = Breathe;
          if(_reset) {
              duty_cycle_ = 0;
              active_period_ = duration_t{0};
              inactive_period_ = _pwm_period;
              increasing_ = true;
              pin_ = false;
              state_ = false;
              timestamp_ = clock_t::now();
              update_timestamp_ = timestamp_;
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
                        timestamp_ += active_period_;
                    }
                } else {
                    if( chandra::chrono::after(inactive_period_, timestamp_, current) ) {
                        mode_ = Fixed;
                        updated = true;
                    }
                }
            } else if ( (mode_ == PWM) or (mode_ == Breathe) ) {
                if(mode_ == Breathe) {
                  if(chandra::chrono::after(update_period_, update_timestamp_, current)){
                    update_timestamp_ += update_period_;
                    if(increasing_) {
                      if(10000-duty_cycle_ < duty_cycle_step_) {
                        duty_cycle_ = 10000;
                        increasing_ = false;
                      } else {
                        duty_cycle_ += duty_cycle_step_;
                      }
                    } else {
                      if(duty_cycle_ < duty_cycle_step_) {
                        duty_cycle_ = 0;
                        increasing_ = true;
                      } else {
                        duty_cycle_ -= duty_cycle_step_;
                      }
                    }
                  }
                  const auto pwm_period = active_period_+inactive_period_;
                  active_period_ = calcActivePeriod(pwm_period, duty_cycle_);
                  inactive_period_ = pwm_period-active_period_;
                }

                if( state_ ) {
                    if( chandra::chrono::after(active_period_, timestamp_, current) ) {
                        ~pin_;
                        state_ = !state_;
                        timestamp_ += active_period_;
                    }
                } else {
                    if( chandra::chrono::after(inactive_period_, timestamp_, current) ) {
                        ~pin_;
                        state_ = !state_;
                        timestamp_ += inactive_period_;
                        updated = true;
                    }
                }
            }

            return updated;
        }

    protected:
      template<class Scalar>
      duration_t calcActivePeriod(const duration_t& _period, const Scalar& _duty_cycle) {
        const auto num = static_cast<uint64_t>(_duty_cycle) * _period.count();
        return duration_t( (num + 5000) / 10000); // TODO: FIGURE OUT IF THERE IS A SAFER WAY TO DO THIS
      }

    private:
        IO pin_;
        mode_t mode_;

        bool state_;
        duration_t active_period_;
        duration_t inactive_period_;
        duration_t cycle_period_;
        duration_t update_period_;
        uint16_t duty_cycle_;
        uint16_t duty_cycle_step_;
        bool increasing_;
        time_point_t timestamp_;
        time_point_t update_timestamp_;
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
