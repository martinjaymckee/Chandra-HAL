/*
 * chip_utils.h
 *
 *  Created on: Jun 14, 2016
 *      Author: martin
 */

#ifndef CHANDRA_CHIP_UTILS_H
#define CHANDRA_CHIP_UTILS_H

#include <chip.h>

namespace chandra
{

class PeripheralActivity
{
	public:
        static void activate(const uint8_t& /*_reg*/, const uint8_t _bit ) {
			LPC_SYSCON->PRESETCTRL |= (1<<_bit);
		}

        static void deactivate(const uint8_t& /*_reg*/, const uint8_t _bit ) {
			LPC_SYSCON->PRESETCTRL &= ~(1<<_bit);
		}

        static void reset(const uint8_t& _reg, const uint8_t _bit ) {
			deactivate(_reg, _bit);
			activate(_reg, _bit);
		}
};

class SystemClock
{
	public:
      static bool enable(const uint8_t& /*_reg*/, const uint8_t& _bit, const bool& _state = true) {
			if(_bit > 31) return false;
			if(_state) {
				LPC_SYSCON->SYSAHBCLKCTRL |= (1<<_bit);
			} else {
				LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<_bit);
			}
			return _state;
		}

        static bool state(const uint8_t& /*_reg*/, const uint8_t& _bit) {
			if(_bit > 31) return false;
			return static_cast<bool>(LPC_SYSCON->SYSAHBCLKCTRL & (1<<_bit));
		}
};

class PowerConfiguration
{
	public:
        static bool enable( const uint8_t& /*_reg*/, const uint8_t& _bit, const bool& _state = true ) {
			if(_state) {
				LPC_SYSCON->PDRUNCFG &= ~(1<<_bit);
			} else {
				LPC_SYSCON->PDRUNCFG |= (1<<_bit);
			}

			return _state;
		}
};

class FixedFunctionIO
{
	public:
        static bool enable( const uint8_t& /*_reg*/, const uint8_t& _bit, const bool& _state = true ) {
			const bool state = SystemClock::state(0, 7);
			SystemClock::enable(0, 7, true);

			if(_state) {
				LPC_SWM->PINENABLE0 &= ~(1<<_bit);
			} else {
				LPC_SWM->PINENABLE0 |= (1<<_bit);
			}

			SystemClock::enable(0, 7, state);
			return _state;
		}

        static bool enabled(const uint8_t& /*_reg*/, const uint8_t& _bit) {
			const auto mask = 1<<_bit;
			return (LPC_SWM->PINENABLE0 & mask) != 0;
		}
};

class GPIO
{
	public:
        static constexpr uint8_t clkIndex(const uint8_t& /*_port*/) {
			return 6;
		}

        static bool enableClk(const uint8_t& _port, const bool& _value=true ) {
			return SystemClock::enable(0, clkIndex(_port), _value);
		}

        static bool direction(const uint8_t& _port, const uint8_t& _pin, const bool& _output) {
			const uint32_t mask = 1UL<<_pin;
			if( _output ){
                //if(_port == 0 and _pin == 4) { // TODO: THIS IS ONLY NEEDED IF THE TIMER IS RUNNING....
                //    LPC_PMU->DPDCTRL |= 1<<1; // Disable Wakeup Pin
                //}
                LPC_GPIO_PORT->DIR[_port] |= mask;
			} else {
                LPC_GPIO_PORT->DIR[_port] &= ~mask;
			}
			return _output;
		}

        static bool direction(const uint8_t& _port, const uint8_t& _pin) {
			const uint32_t mask = 1UL<<_pin;
			return static_cast<bool>( LPC_GPIO_PORT->DIR[_port] & mask );
		}
};

class PinMap
{
	public:
        static bool set(const uint8_t& _reg, const uint8_t& _offset, const uint8_t _pin_index) {
			const bool state = SystemClock::state(0, 7);
			SystemClock::enable(0, 7, true);

			const uint32_t shift = 8UL*_offset;
			const uint32_t mask = 0xFFUL << shift;
			LPC_SWM->PINASSIGN[_reg] = (LPC_SWM->PINASSIGN[_reg]&~mask) |(_pin_index<<shift);

			SystemClock::enable(0, 7, state);
			return true;
		}

        static bool set(const uint8_t _map_index, const uint8_t _pin_index) {
			const uint8_t reg = regFromIndex(_map_index);
			const uint8_t offset = offsetFromIndex(_map_index);
			return set(reg, offset, _pin_index);
		}

        static constexpr uint8_t pinIndex(const uint8_t& _port, const uint8_t& _pin) {
			// TODO: THIS SHOULD DO SOME COMPILE-TIME CHECKING TO MAKE SURE THAT THE PIN IS VALID
			const uint8_t index = (32UL*_port) + _pin;
			return index;
		}

	protected:
        static constexpr uint8_t regFromIndex(const uint8_t _map_index) { return _map_index / 4; }
        static constexpr uint8_t offsetFromIndex(const uint8_t _map_index) { return _map_index % 4; }
};

} /*namespace chandra*/

#endif /*CHANDRA_CHIP_UTILS_H*/
