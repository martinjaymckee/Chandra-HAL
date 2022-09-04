/*
 * chrono.h
 *
 *  Created on: Jan 16, 2018
 *      Author: martin
 */

#ifndef CHRONO_H
#define CHRONO_H

#include <chrono>
#include <cstddef>
#include <ratio>
#include <utility>

#include "chip_utils.h"
#include "units.h"

//#define SYSTICK_SOFTWARE_TIMESTAMP_MODE
//#define SCT_HARDWARE_TIMESTAMP_MODE

namespace chandra
{
using namespace std::literals::chrono_literals;

namespace chrono
{


// TODO: ADD A PROTECTED CORE(FREQ) OVERLOAD THAT CAN BE USED BY FRIEND FUNCTIONS
//	TO UPDATE THIS. THIS SHOULD STILL HANDLE ANY PRESCALAR/DIVIDERS ETC. IN THE PROCESSOR
class frequency
{
	public:
    using rep = chandra::units::mks::Q_Hz<uint32_t>;

	#if defined(__LPC84X__)
    static rep core() { return f_core_; }
	#elif defined(__CHANDRA_MOCK__)
    static rep core() { return rep{50000000}; }
	#else
		static rep core() { return f_core_; }
	#endif

  #if defined(__LPC55XX__)
	  static rep main() { return rep{SYSCON->AHBCLKDIV * core()}; }
  #elif defined(__CHANDRA_MOCK__)
		static rep main() { return rep{ 50000000 }; }
	#else
  	static rep main() { return rep{LPC_SYSCON->SYSAHBCLKDIV * core()}; }
	#endif

    static rep tick() { return rep{0}; }
		static rep timer(size_t) { return core(); }
    static rep usart(size_t) { return main(); }
		static rep spi(size_t) { return core(); }
		static rep i2c(size_t) { return core(); }
		static rep adc(size_t) { return core(); }
		static rep dac(size_t) { return core(); }

		#if defined(__LPC84X__)
		static bool setFROClock(const rep& _f) {
			// TODO: VALIDATE THE VALUE OF _F...
			#define FRO_SET_CLOCK_API_ADDR 0x0F0026F5U
			using func_t = void (*)(uint32_t);
			func_t fro_set_func = reinterpret_cast<func_t>(FRO_SET_CLOCK_API_ADDR);
			fro_set_func(_f.value()/1000); // THE API FUNCTION TAKES A VALUE IN kHz....
			//(*reinterpret_cast<void (*)(uint32_t)>(FRO_SET_CLOCK_API_ADDR))(_f.value());
			// Set FRO Direct Mode
			LPC_SYSCON->FROOSCCTRL |= 1<<17; // Set direct mode bit
			LPC_SYSCON->FRODIRECTCLKUEN = 0; // Update to direct mode
			LPC_SYSCON->FRODIRECTCLKUEN = 1;
			frequency::f_core_ = _f;
			return true;
		}
		#endif

	protected:
		static rep f_core_;
};

class timestamp_clock
{
	public:
	#if defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
//        friend void SysTick_Handler();
	#endif
		using rep = uint32_t;
		using period = std::micro;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<timestamp_clock>;
		static constexpr bool is_steady = false;

		static time_point now() noexcept {
	#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
		#if defined(__LPC84X__)
			return time_point{duration{LPC_SCT->COUNT}};
		#elif defined(__LPC15XX__)
			return time_point{duration{LPC_SCT3->COUNT_U}};
		#elif defined(__LPC55XX__)
			return time_point{duration{LPC_SCT0->COUNT}};
		#else
			return time_point{duration{LPC_SCT->COUNT_U}};
		#endif
	#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
	    NVIC_DisableIRQ(SysTick_IRQn);
      const auto counts = SysTick->VAL;
      const auto high_bits = high_bits_;
      NVIC_EnableIRQ(SysTick_IRQn);
      const rep lower = (mult_ * (top_ - counts))>>16;
      const rep upper = rep(high_bits)<<16;
      const duration time{upper|lower};
      return time_point{time};
	#elif defined(__CHANDRA_MOCK__)
//			#warning "Chandra clock frequencies parsed as mock."
      return time_point{duration{0}}; // TODO: IMPLEMENT MOCK FUNCTIONALITY FOR THE TIMESTAMP CLOCK
	#else
			#error "No Timestamp Clock Mode Defined!"
	#endif
		}

		template<class Func>
		static void init(Func _func) noexcept {
#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
		#if defined(__LPC15XX__)
				const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
				SystemClock::enable(1, 5, true);
				PeripheralActivity::reset(1, 5);
				LPC_SCT3->CONFIG = (1<<0); // Configure as a unified 32-bit counter
				_func();
				LPC_SCT3->CTRL_U = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
				return;
		#elif defined(__LPC55XX__)
				#if defined(FRO_CLOCK)
					frequency::setFROClock(frequency::rep{FRO_CLOCK});
				#endif
				const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
				SystemClock::enable(0, 8, true);
				PeripheralActivity::reset(0, 8);
				LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
				_func();
				LPC_SCT->CTRL = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
				return;
		#elif defined(__LPC84X__)
				#if defined(FRO_CLOCK)
					frequency::setFROClock(frequency::rep{FRO_CLOCK});
				#endif
				const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
				SystemClock::enable(0, 8, true);
				PeripheralActivity::reset(0, 8);
				LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
				_func();
				LPC_SCT->CTRL = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
				return;
		#else
				const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
	      SystemClock::enable(0, 8, true);
	      PeripheralActivity::reset(0, 8);
				LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
				_func();
				LPC_SCT->CTRL_U = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
				return;
		#endif
#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
	    // TODO: THIS SHOULD BE BASED ON THE REFERENCE FREQUENCY, IN MOST CASES....
	    // TODO: FIGURE OUT IF THERE IS A WAY TO DO THIS WITHOUT 64-BIT MATH
	    top_ = (uint64_t(65536UL)* frequency::core().value()) / 1000000UL;
	    mult_ = 0xFFFFFFFFUL / top_;
			_func();
	    SysTick_Config(top_);
	    NVIC_EnableIRQ(SysTick_IRQn);
	    return;
#elif defined(__CHANDRA_MOCK__)
//		#warning "Chandra clock init parsed as mock."
#else
		#error "No Timestamp Clock Mode Defined!"
#endif
		}

		static void init() noexcept {
			init([](){});
		}

    static void reset() noexcept {
			updateTimerCounter(0);
			return;
    }

		template<class Clock>
		static time_point set(const std::chrono::time_point<Clock>& _t) noexcept {
			const duration us{std::chrono::duration_cast<duration>(_t.time_since_epoch()).count()};
			updateTimerCounter(us.count());
			return now();
		}

	protected:
		static void updateTimerCounter(uint32_t _counts) {
			#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
				#if defined(__LPC82X__)
					LPC_SCT->CTRL_U |= (1<<2); // Set Halt Bit
			    LPC_SCT->COUNT_U = _counts;
					LPC_SCT->CTRL_U &= ~static_cast<uint32_t>(1<<2); // Clear Halt Bit
				#elif defined(__LPC84X__)
					LPC_SCT->CTRL |= (1<<2); // Set Halt Bit
			    LPC_SCT->COUNT = _counts;
					LPC_SCT->CTRL &= ~static_cast<uint32_t>(1<<2); // Clear Halt Bit
				#elif defined(__LPC15XX__)
					LPC_SCT3->CTRL_U |= (1<<2); // Set Halt Bit
			    LPC_SCT3->COUNT_U = _counts;
					LPC_SCT3->CTRL_U &= ~static_cast<uint32_t>(1<<2); // Clear Halt Bit
				#elif defined(__LPC55XX__)
					LPC_SCT->CTRL |= (1<<2); // Set Halt Bit
					LPC_SCT->COUNT = _counts;
					LPC_SCT->CTRL &= ~static_cast<uint32_t>(1<<2); // Clear Halt Bit
				#else
					#error "Chrono Reset is undefined for processor type!"
				#endif
			#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
				// TODO: VALIDATE THAT THIS IS WORKING PROPERLY....
				SysTick->VAL = top_- ((_counts & 0xFFFFFF) + 1);
			  high_bits_ = (_counts>>24) & 0xFF;
			#elif defined(__CHANDRA_MOCK__)
//				#warning "Chandra clock set parsed as mock."
			#else
				#error "No Timestamp Clock Mode Defined!"
			#endif
				return;
		}
// Map to C API
//		static time_t to_time_t(const timepoint_& t) noexcept;
//		static time_point from_time_t(time_t t) noexcept;

#if defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
    public:
        static volatile uint16_t high_bits_;
        static uint32_t top_;
        static uint32_t mult_;
#endif
};

class mock_clock
{
	public:
		using rep = uint32_t;
		using period = std::micro;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<mock_clock>;
		static constexpr bool is_steady = false;

		static time_point now() noexcept {
			return time_point(t_offset_);
		}

		static void init() noexcept {
			reset();
			return;
		}

		static void reset() noexcept {
			t_offset_ = duration{0};
			return;
		}

		template<class Clock>
		static time_point set(const std::chrono::time_point<Clock>& _t) noexcept {
			t_offset_ = std::chrono::duration_cast<duration>(_t.time_since_epoch());
			return now();
		}

		template<class Rep, class Period>
		static time_point advance(const std::chrono::duration<Rep, Period> _d) noexcept {
			t_offset_ += std::chrono::duration_cast<duration>(_d);
			return now();
		}

	protected:
		static duration t_offset_;
};

#if defined(USE_MOCK_CLOCK)
#define MOCK_CLOCK_IMPL	chandra::chrono::mock_clock::duration chandra::chrono::mock_clock::t_offset_{0};
#else
#define MOCK_CLOCK_IMPL #error "Attempting to instantiate chandra::chrono::mock_clock without preprocessor USE_MOCK_CLOCK"
#endif

template<class PrimaryClock, class SecondaryClock>
class compound_clock
{
	public:
		using primary_clock_t = PrimaryClock;
		using secondary_clock_t = SecondaryClock;

		using rep = typename std::common_type<typename primary_clock_t::duration::rep, typename secondary_clock_t::duration::rep>::type;
		using period = std::micro;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<compound_clock>;
		static constexpr bool is_steady = false;

		static time_point now() noexcept {
			if(primary_selected_) return time_point{primary_clock_t::now().time_since_epoch()};
			return time_point{secondary_clock_t::now().time_since_epoch()};
		}

		static void init() noexcept {
			primary_selected_ = true;
			primary_clock_t::init();
			secondary_clock_t::init();
			return;
		}

		static void reset() noexcept {
			primary_clock_t::reset();
			secondary_clock_t::reset();
			return;
		}

		template<class Clock>
		static time_point set(const std::chrono::time_point<Clock>& _t) noexcept {
			if(primary_selected_) return primary_clock_t::set(_t);
			return secondary_clock_t::set(_t);
		}

		template<class Rep, class Period>
		static time_point advance(const std::chrono::duration<Rep, Period> _d) noexcept {
			if(primary_selected_) {
				doAdvance<primary_clock_t>(_d);
			} else {
				doAdvance<secondary_clock_t>(_d);
			}
			return now();
		}

		static bool source(bool _primary) noexcept {
			if(_primary) {
				if(!primary_selected_) {
					primary_selected_ = true;
					const auto t = secondary_clock_t::now();
					primary_clock_t::set(t);
				}
			} else {
				if(primary_selected_) {
					primary_selected_ = false;
					const auto t = primary_clock_t::now();
					secondary_clock_t::set(t);
				}
			}

			return source();
		}

		static constexpr bool source() noexcept {
			return primary_selected_;
		}

	protected:
		template<class Clock, class... Args>
		static void doAdvance(Args...) {
			return;
		}

		template<
			class Clock,
			class Rep,
			class Period,
			class = decltype(Clock::advance(std::chrono::duration<Rep, Period>{0}))
		>
		static void doAdvance(const std::chrono::duration<Rep, Period>& _d) {
			Clock::advance(_d);
			return;
		}


		static bool primary_selected_;

};

template<class PrimaryClock, class SecondaryClock>
bool compound_clock<PrimaryClock, SecondaryClock>::primary_selected_ = true;

template<class Clock = timestamp_clock>
void delay(const std::chrono::duration<uint32_t, std::micro>& _us, const std::chrono::time_point<Clock>& start = Clock::now()) {
	const auto us = std::chrono::duration_cast<typename Clock::duration>(_us); // NOTE: Avoid conversions below. (it may be better to use the ceiling rounding mode
	const auto end = start + us;
	while(Clock::now() < end){ // TODO: CHECK IF THIS IS GOING TO WORK PROPERLY IN ALL CASES, INCLUDING OVERFLOW.... IF NOT, FIGURE OUT THE BEST WAY TO IMPLEMENT IT
		// Is there anything to be done here... like yield?
	}
}

template<class Func, class Clock = timestamp_clock>
void call_while_delay(const std::chrono::duration<uint32_t, std::micro>& _us, Func _func, const std::chrono::time_point<Clock>& start = Clock::now()) {
	const auto us = std::chrono::duration_cast<typename Clock::duration>(_us); // NOTE: Avoid conversions below. (it may be better to use the ceiling rounding mode
	const auto end = start + us;
	auto t = start;
	while((t = Clock::now()) < end){ // TODO: CHECK IF THIS IS GOING TO WORK PROPERLY IN ALL CASES, INCLUDING OVERFLOW.... IF NOT, FIGURE OUT THE BEST WAY TO IMPLEMENT IT
		_func(t);
	}
}

template<class Clock>
bool after(	const std::chrono::duration<uint32_t, std::micro>& _us,
			const std::chrono::time_point<Clock>& start,
			const std::chrono::time_point<Clock>& end = Clock::now()) {
	const auto us = std::chrono::duration_cast<typename Clock::duration>(_us); // NOTE: Avoid conversions below. (it may be better to use the ceiling rounding mode
    return (start + us) <= end;
}

template<class Clock>
bool after(const std::chrono::time_point<Clock>& reference,
           const std::chrono::time_point<Clock>& check = Clock::now()) {
    return check >= reference;
}

template<class Clock>
bool before(const std::chrono::duration<uint32_t, std::micro>& _us,
			const std::chrono::time_point<Clock>& start,
			const std::chrono::time_point<Clock>& end = Clock::now()) {
	return !after(_us, start, end);
}

template<class Clock>
bool before(const std::chrono::time_point<Clock>& reference,
            const std::chrono::time_point<Clock>& check = Clock::now()) {
    return !after(reference, check);
}


template<class Func>
bool block_until(Func _func) {
	while(!_func()){}
	return true;
}

template<class Func, class Clock = timestamp_clock>
bool block_until(Func _func, const std::chrono::duration<uint32_t, std::micro>& _us, const std::chrono::time_point<Clock>& _start) {
	const auto us = std::chrono::duration_cast<typename Clock::duration>(_us); // NOTE: Avoid conversions below. (it may be better to use the ceiling rounding mode)
	while(!_func()) {
		if(chandra::chrono::after(_us, _start)) return false;
	}
	return true;
}

template<class Func, class Clock = timestamp_clock>
bool block_until(Func _func, const std::chrono::duration<uint32_t, std::micro>& _us) {
	return block_until(_func, _us, Clock::now());
}

} /*namespace chrono*/
} /*namespace chandra*/

#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
#define TIMESTAMP_CLOCK_IMPL
#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
#define TIMESTAMP_CLOCK_IMPL\
    volatile uint16_t chandra::chrono::timestamp_clock::high_bits_;\
    uint32_t chandra::chrono::timestamp_clock::top_;\
    uint32_t chandra::chrono::timestamp_clock::mult_;\
    extern "C" {\
    void SysTick_Handler(void) {\
        ++chandra::chrono::timestamp_clock::high_bits_;\
    }\
    }
#endif

#endif /*CHANDRA_CHRONO_H*/
