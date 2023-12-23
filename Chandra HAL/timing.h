/*
 * timing.h
 *
 *  Created on: May 3, 2016
 *      Author: martin
 */

#ifndef CHANDRA_TIMING_H
#define CHANDRA_TIMING_H

#include "chrono.h"
#include "units.h"

namespace chandra
{
namespace chrono
{

// TODO: PULL COMMON CODE OUT OF TIMER CLASSES AND PULL INTO A TIMER BASE CLASS
//	BASE SHOULD HAVE BASE_, DURATION_, EXPIRATION_
//	OPTIMIZE STANDARD TIMER AND FIX RUN/RUNNING API (MINIMIZE CHECK TIME IF NOT RUNNING)

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
      ExpirationStatus(const bool& _expired, const time_point_t& _expiration)
				: expired(_expired), expiration(_expiration) {}

      const bool expired;
      const time_point_t expiration;

			operator bool() const { return expired; }
		};

    constexpr Timer(const time_point_t _base = clock_t::now())
      : duration_{0}, base_{_base}, expiration_{_base}, running_(false) {}

    constexpr Timer( const duration_t _duration )
      : duration_(_duration), base_(clock_t::now()), running_(_duration.count() != 0)
		{
        expiration_ = base_ + duration_;
    }


    constexpr Timer( const duration_t _duration, const time_point_t _base )
      : duration_(_duration), base_(_base),
				expiration_(_base+_duration), running_(_duration.count() != 0) {}

		template<class V, class U>
		constexpr Timer( const chandra::units::Quantity<V, U>& _t)
			: duration_(
					chandra::units::conversions::quantityToChrono<std::chrono::microseconds>(
						chandra::units::mks::Q_us<V>(_t)
					)
				), base_(clock_t::now())
		{
				expiration_ = base_ + duration_;
                running_ = duration_.count() != 0;
		}

		bool run(bool _running = true) {
			running_ = _running;
			reset();
			return running_;
		}

		constexpr bool running() const {
			return running_;
		}

    duration_t duration(duration_t _duration, const timer_control_t& _control = Reset) {
      duration_ = _duration;
      if(_control & Reset) reset();
      if(_control & Rebase) reset(clock_t::now());
      return duration_;
		}


    duration_t duration() const { return duration_; }

    time_point_t base(time_point_t _base) {
			base_ = _base;
			return base_;
	}

    time_point_t base() const { return base_; }

    time_point_t expiration() const { return expiration_; }

		template<class T>
    duration_t remaining(const T& _base = clock_t::now()) const {
      return expiration_ - _base;
		}

		template<class T>
    time_point_t reset(const T& _base) {
			base_ = _base;
      expiration_ = base_ + duration_;
			return base_;
		}

    time_point_t reset() { return reset(clock_t::now()); }

    ExpirationStatus operator() (
			time_point_t _check, const timer_control_t& _control = Reset)
		{
      if(chandra::chrono::after(expiration_, _check)) {
        const auto expiration = expiration_;
        if((_control & Rebase) || (_control & All)) reset(expiration_);
        else if(_control & Reset) reset(expiration_);
				else if(_control & Stop) run(false);
        overflowed_ = chandra::chrono::after(expiration_, _check);
        return {running_, expiration};
      }

      return {false, time_point_t{0us}};
    }

    ExpirationStatus operator () (const timer_control_t& _control = Reset) {
      return this->operator ()(clock_t::now(), _control);
    }

    bool overflowed() const {
      return overflowed_;
    }

	private:
    duration_t duration_;
    time_point_t base_;
    time_point_t expiration_;
    bool running_;
    bool overflowed_;
};

template<class Clock = chandra::chrono::timestamp_clock>
class RetriggerableTimer
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
      ExpirationStatus(const bool& _expired, const time_point_t& _expiration)
				: expired(_expired), expiration(_expiration) {}

      const bool expired;
      const time_point_t expiration;

			operator bool() const { return expired; }
		};

    RetriggerableTimer( const duration_t _duration )
      : duration_(_duration), active_(false)
		{}

		template<class D>
    duration_t duration(duration_t _duration, const timer_control_t& _control = Reset) {
      duration_ = _duration;
      if(_control & Reset) reset();
      if(_control & Rebase) reset(clock_t::now());
      return duration_;
		}

    duration_t duration() const { return duration_; }

    time_point_t base(time_point_t _base) {
			base_ = _base;
			return base_;
		}

    time_point_t base() const { return base_; }

    time_point_t expiration() const { return expiration_; }

		template<class T>
    duration_t remaining(const T& _base = clock_t::now()) const {
      return expiration_ - _base;
		}

    time_point_t reset(time_point_t _base) {
			base_ = _base;
      expiration_ = base_ + duration_;
			return base_;
		}

    time_point_t reset() { return reset(clock_t::now()); }

		ExpirationStatus operator() (
			time_point_t _check, const timer_control_t& _control = Reset)
		{
      if(chandra::chrono::after(expiration_, _check)) {
				active_ = false;
        const auto expiration = expiration_;
        return {false, time_point_t{0us}};
      }

      return {active_, expiration_};
    }

    ExpirationStatus operator () (const timer_control_t& _control = Reset) {
      return this->operator ()(clock_t::now(), _control);
    }

		bool trigger(bool _kick=true) {
			if(_kick) {
				active_ = true;
				reset();
			}
			return true;
		}

		constexpr bool active() const { return active_; }

	private:
    duration_t duration_;
    time_point_t base_;
    time_point_t expiration_;
    bool active_;
};

template<class Clock = chandra::chrono::timestamp_clock>
class LoopTimer
{
	public:
		using clock_t = Clock;
		using time_point_t = typename Clock::time_point;
		using duration_t = typename Clock::duration;
		using ref_t = LoopTimer<Clock>&;

		LoopTimer(){
			reset();
		}

		bool reset() {
			base_ = clock_t::now();
			return true;
		}

		auto as_count() {
			const auto t = clock_t::now();
			const auto dt = t - base_;
			base_ = t;
			return dt.count();
		}

		template<class Value=float>
		Value as_seconds() {
			const auto dt_count = as_count();
			using ratio_t = typename duration_t::period;
			return (Value(ratio_t::num) * dt_count) / Value(ratio_t::den);
		}

	private:
		time_point_t base_;
};

} /*namespace chrono*/
} /*namespace chandra*/
#endif /*CHANDRA_TIMING_H*/
