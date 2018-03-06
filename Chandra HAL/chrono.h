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
namespace chrono
{

class frequency
{
	public:
        using rep = chandra::units::mks::Q_Hz<uint32_t>;

        static rep main() { return rep{SystemCoreClock}; }
		static rep core() { return main() / LPC_SYSCON->SYSAHBCLKDIV; }
        static rep tick() { return rep{0}; }
		static rep timer(size_t) { return core(); }
        static rep usart(size_t) { return main(); }
		static rep spi(size_t) { return core(); }
		static rep i2c(size_t) { return core(); }
		static rep adc(size_t) { return core(); }
		static rep dac(size_t) { return core(); }
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
            return time_point{duration{LPC_SCT->COUNT_U}};
#elif defined(SYSTICK_SOFTWARE_TIMESTAMP_MODE)
            NVIC_DisableIRQ(SysTick_IRQn);
            const auto counts = SysTick->VAL;
            const auto high_bits = high_bits_;
            NVIC_EnableIRQ(SysTick_IRQn);
            const rep lower = (mult_ * (top_ - counts))>>16;
            const rep upper = rep(high_bits)<<16;
            const duration time{upper|lower};
            return time_point{time};
#else
#error "No Timestamp Clock Mode Defined!"
#endif
		}

		static void init() noexcept {
#if defined(SCT_HARDWARE_TIMESTAMP_MODE)
			const uint32_t counts = static_cast<uint32_t>((frequency::core() / 1000000UL)) - 1UL;
            SystemClock::enable(0, 8, true);
            PeripheralActivity::reset(0, 8);
			LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
			LPC_SCT->CTRL_U = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
			return;
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
