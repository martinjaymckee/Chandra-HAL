/*
 * chrono.h
 *
 *  Created on: Jan 16, 2018
 *      Author: martin
 */

#ifndef CHRONO_H
#define CHRONO_H


#define TIMESTAMP_CLOCK_MODE SCT_HARDWARE_TIMESTAMP_MODE
//#define TIMESTAMP_CLOCK_MODE SYSTICK_SOFTWARE_TIMESTAMP_MODE

namespace chandra
{
namespace chrono
{

class frequency
{
	public:
		using rep = uint32_t;

		static rep main() { return SystemCoreClock; }
		static rep core() { return main() / LPC_SYSCON->SYSAHBCLKDIV; }
		static rep tick() { return 0; }
		static rep timer(size_t) { return core(); }
		static rep usart(size_t) { return core(); }
		static rep spi(size_t) { return core(); }
		static rep i2c(size_t) { return core(); }
		static rep adc(size_t) { return core(); }
		static rep dac(size_t) { return core(); }
};

class timestamp_clock
{
	public:
		using rep = uint32_t;
		using period = std::micro;
		using duration = std::chrono::duration<rep, period>;
		using time_point = std::chrono::time_point<timestamp_clock>;
		static constexpr bool is_steady = false;

		static time_point now() noexcept {
			return time_point{duration{LPC_SCT->COUNT_U}};
//			++counter_;
//			return time_point{duration{counter_}};
		}

		static void init() noexcept {
			const uint32_t counts = static_cast<uint32_t>((frequency::core() / 1000000UL)) - 1UL;
			SystemClock::enable(0, 8, true);
			//LPC_SYSCON->SYSAHBCLKCTRL |= 1<<8;
			PeripheralActivity::reset(0, 8);
			//LPC_SYSCON->PRESETCTRL &= ~(1<<8);
			//LPC_SYSCON->PRESETCTRL |= 1<<8;
			LPC_SCT->CONFIG = (1<<0); // Configure as a unified 32-bit counter
			LPC_SCT->CTRL_U = (counts<<5) | (1<<3); // Set Prescaler, clear counter and start counting
			return;
		}

		// Map to C API
//		static time_t to_time_t(const timepoint_& t) noexcept;
//		static time_point from_time_t(time_t t) noexcept;

	protected:
//		static volatile rep counter_;
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
	return (start + us) < end;
}

template<class Clock>
bool before(const std::chrono::duration<uint32_t, std::micro>& _us,
			const std::chrono::time_point<Clock>& start,
			const std::chrono::time_point<Clock>& end = Clock::now()) {
	return !after(_us, start, end);
}

} /*namespace chrono*/
} /*namespace chandra*/

#endif /*CHANDRA_CHRONO_H*/
