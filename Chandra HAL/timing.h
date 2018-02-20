/*
 * timing.h
 *
 *  Created on: May 3, 2016
 *      Author: martin
 */

#ifndef CHANDRA_TIMING_H
#define CHANDRA_TIMING_H

#include "chrono.h"

namespace chandra
{
namespace chrono
{

template<class Clock = chandra::chrono::timestamp_clock>
class Timer
{
	public:
        using clock_t = Clock;
        using time_point_t = typename Clock::time_point;
        using duration_t = typename Clock::duration;
        using ref_t = Timer<Clock>&;

        enum timer_control_t {
            None = 0x00,
            Rebase = 0x01,
            Reset = 0x02,
            Start = 0x04,
            Stop = 0x08,
            All = 0xFF
        };

		struct ExpirationStatus
		{
            ExpirationStatus(const bool& _expired, const time_point_t& _expiration) :
                expired(_expired), expiration(_expiration) {}

            const bool expired;
            const time_point_t expiration;

			operator bool() const { return expired; }
		};

        Timer(
                const duration_t& _duration = duration_t{0},
                const time_point_t& _base = clock_t::now() )
            : duration_(_duration), base_(_base),
              expiration_(_base+_duration), running_(true) {}


        duration_t duration(const auto& _duration, const timer_control_t& _control = None) {
            duration_ = _duration;
            if(_control & Reset) reset();
            if(_control & Rebase) reset(clock_t::now());
            return duration_;
		}

        duration_t duration() const { return duration_; }

        time_point_t base(const auto& _base) {
			base_ = _base;
			return base_;
		}

        time_point_t base() const { return base_; }

        time_point_t expiration() const { return expiration_; }

        duration_t remaining(const auto& _base = clock_t::now()) const {
            return expiration_ - _base;
		}

        time_point_t reset(const auto& _base) {
			base_ = _base;
            expiration_ = base_ + duration_;
			return base_;
		}

        time_point_t reset() { return reset(expiration_); }

        ExpirationStatus operator() (const auto& _check = clock_t::now(),
                                     const timer_control_t& _control = Reset) {
            if(chandra::chrono::after(expiration_, _check)) {
                const auto expiration = expiration_;
                if((_control & Rebase) || (_control & All)) reset(expiration_);
                else if(_control & Reset) reset(expiration_);
                return {true, expiration};
            }
            return {false, time_point_t{0us}};
        }

        ExpirationStatus operator () (const timer_control_t& _control = Reset) {
            return this->operator ()(clock_t::now(), _control);
        }

	private:
        duration_t duration_;
        time_point_t base_;
        time_point_t expiration_;
        bool running_;
};

} /*namespace chrono*/
} /*namespace chandra*/
#endif /*CHANDRA_TIMING_H*/
