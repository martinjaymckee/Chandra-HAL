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

  	static rep main() { return rep{LPC_SYSCON->SYSAHBCLKDIV * core()}; }
    static rep tick() { return rep{0}; }
		static rep timer(size_t) { return core(); }
    static rep usart(size_t) { return main(); }
		static rep spi(size_t) { return core(); }
		static rep i2c(size_t) { return core(); }
		static rep adc(size_t) { return core(); }
		static rep dac(size_t) { return core(); }

		// TODO: MAKE THIS ONLY AVAILABLE FOR PROCESSORS THAT HAVE IT
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
			#warning "Chandra clock frequencies parsed as mock."
      return time_point{duration{0}}; // TODO: IMPLEMENT MOCK FUNCTIONALITY FOR THE TIMESTAMP CLOCK
	#else
			#error "No Timestamp Clock Mode Defined!"
	#endif
		}

		static void init() noexcept {
#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
		#if defined(__LPC15XX__)
					const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
					SystemClock::enable(1, 5, true);
					PeripheralActivity::reset(1, 5);
					LPC_SCT3->CONFIG = (1<<0); // Configure as a unified 32-bit counter
					LPC_SCT3->CTRL_U = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
					return;

		#elif defined(__LPC84X__)
					#if defined(FRO_CLOCK)
					frequency::setFROClock(frequency::rep{FRO_CLOCK});
					#endif
					const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
					SystemClock::enable(0, 8, true);
					PeripheralActivity::reset(0, 8);
					LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
					LPC_SCT->CTRL = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
					return;
		#else
					const uint32_t counts = static_cast<uint32_t>((frequency::core().value() / 1000000UL)) - 1UL;
		      SystemClock::enable(0, 8, true);
		      PeripheralActivity::reset(0, 8);
					LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
					LPC_SCT->CTRL_U = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
					return;
		#endif
#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
	        // TODO: THIS SHOULD BE BASED ON THE REFERENCE FREQUENCY, IN MOST CASES....
	        // TODO: FIGURE OUT IF THERE IS A WAY TO DO THIS WITHOUT 64-BIT MATH
	        top_ = (uint64_t(65536UL)* frequency::core().value()) / 1000000UL;
	        mult_ = 0xFFFFFFFFUL / top_;
	        SysTick_Config(top_);
	        NVIC_EnableIRQ(SysTick_IRQn);
	        return;
//           __STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
//            {
//              if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk)  return (1);      /* Reload value impossible *///

//              SysTick->LOAD  = ticks - 1;                                  /* set reload register */
//              NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
//              SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
//              SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
//                               SysTick_CTRL_TICKINT_Msk   |
//                               SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
//              return (0);                                                  /* Function successful */
//            }            */
#elif defined(__CHANDRA_MOCK__)
#warning "Chandra clock init parsed as mock."
#else
#error "No Timestamp Clock Mode Defined!"
#endif
		}

        static void reset() noexcept {
#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
			#if defined(__LPC82X__)
        		LPC_SCT->COUNT_U = 0;
			#elif defined(__LPC84X__)
          	LPC_SCT->COUNT=0;
			#elif defined(__LPC15XX__)
          	LPC_SCT3->COUNT_U=0;

			#else
			#error "Chrono Reset is undefined for processor type!"
			#endif
            return;
#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
            SysTick->VAL = top_-1;
            high_bits_ = 0;
            return;
#elif defined(__CHANDRA_MOCK__)
#warning "Chandra clock reset parsed as mock."
#else
#error "No Timestamp Clock Mode Defined!"
#endif
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

template<class Clock = timestamp_clock>
void delay(const std::chrono::duration<uint32_t, std::micro>& _us, const std::chrono::time_point<Clock>& start = Clock::now()) {
	const auto us = std::chrono::duration_cast<typename Clock::duration>(_us); // NOTE: Avoid conversions below. (it may be better to use the ceiling rounding mode
	const auto end = start + us;
	while(Clock::now() < end){ // TODO: CHECK IF THIS IS GOING TO WORK PROPERLY IN ALL CASES, INCLUDING OVERFLOW.... IF NOT, FIGURE OUT THE BEST WAY TO IMPLEMENT IT
		// Is there anything to be done here... like yield?
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
} /*namespace chrono*/
} /*namespace chandra*/

// TODO: A CALL TO TIMESTAMP_CLOCK_IMPL SHOULD GO INTO CHANDRA_CORE.CPP
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
