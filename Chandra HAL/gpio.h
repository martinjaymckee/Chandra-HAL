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
            if(_is_output) this->operator = (false);
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
            GPIOImpl::enableClk(port_);
        }

        bool output(bool _output) {
            return GPIOImpl::direction(port_, pin_, _output);
        }

        bool output() const {
            return GPIOImpl::direction(port_, pin_);
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
    #elif defined(__LPC55XX__)
            if(inverted_ ? !bool(_value) : bool(_value)){
                GPIO->SET[port_] |= mask_;
            } else {
                GPIO->CLR[port_] |= mask_;
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
    #elif defined(__LPC55XX__)
            GPIO->NOT[port_] |= mask_;
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
    #elif defined(__LPC55XX__)
            const bool read = (GPIO->PIN[port_] & mask_);
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

//
// GPIO Related Functions
//

// TODO: THIS SHOULD BE PROTECTED WITH BETTER TYPES...
template<typename IOType, typename Delay, typename Clock = chandra::chrono::timestamp_clock>
void pulseOut(IOType& _io, Delay _delay, const typename Clock::time_point& _start = Clock::now()) {
    ~_io;
    chandra::chrono::delay(_delay, _start);
    ~_io;
}

// TODO: TEST THE PULSEIN FUNCTIONS
template<typename IOType, typename Clock = chandra::chrono::timestamp_clock>
typename Clock::duration pulseIn(IOType& _io, const bool& _init) {
    while(_io != _init) {}
    const auto start = Clock::now();
    while(_io == _init) {}
    return Clock::now() - start;
}

template<typename IOType, typename Clock = chandra::chrono::timestamp_clock>
typename Clock::duration pulseIn(IOType& _io) {
    return pulseIn(_io, bool(_io));
}

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_GPIO_H*/
