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
		static void assert(const uint8_t& _reg, const uint8_t _bit ) {
			LPC_SYSCON->PRESETCTRL[_reg] &= ~(1<<_bit);
			return;
		}

		static void deassert(const uint8_t& _reg, const uint8_t _bit ) {
			LPC_SYSCON->PRESETCTRL[_reg] |= (1<<_bit);
			return;
		}

		static void reset(const uint8_t& _reg, const uint8_t _bit ) {
			deassert(_reg, _bit);
			assert(_reg, _bit);
			return;
		}
};

class SystemClock
{
	public:
		static bool enable( const uint8_t& _reg, const uint8_t& _bit, const bool& _state = true ) {
			(void) _reg;
			if(_bit > 31) return false;
			if(_state) {
				#if defined(__LPC82X__)
					LPC_SYSCON->SYSAHBCLKCTRL |= (1<<_bit);
				#elif defined(__LPC15XX__)
					LPC_SYSCON->SYSAHBCLKCTRL[_reg] |= (1<<_bit);
				#endif
			} else {
				#if defined(__LPC82X__)
					LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<_bit);
				#elif defined(__LPC15XX__)
					LPC_SYSCON->SYSAHBCLKCTRL[_reg] &= ~(1<<_bit);
				#endif
			}
			return _state;
		}

		static bool state( const uint8_t& _reg, const uint8_t& _bit, const bool& _state = true ) {
			(void) _reg;
			(void) _state;
			if(_bit > 31) return false;
			#if defined(__LPC82X__)
				return static_cast<bool>(LPC_SYSCON->SYSAHBCLKCTRL & (1<<_bit));
			#elif defined(__LPC15XX__)
				return static_cast<bool>(LPC_SYSCON->SYSAHBCLKCTRL[_reg] & (1<<_bit));
			#endif
		}
};

class PowerConfiguration
{
	public:
		static bool enable( const uint8_t&, const uint8_t& _bit, const bool& _state = true ) {
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
		static bool enable( const uint8_t& _reg, const uint8_t& _bit, const bool& _state = true ) {
			(void) _reg;
			#if defined(__LPC82X__)
				SystemClock::ScopedEnable en(0, 7);
			#elif defined(__LPC15XX__)
				SystemClock::ScopedEnable en(0, 12);
			#endif

			#if defined(__LPC82X__)
				if(_state) {
					LPC_SWM->PINENABLE0 &= ~(1<<_bit);
				} else {
					LPC_SWM->PINENABLE0 |= (1<<_bit);
				}
			#elif defined(__LPC15XX__)
				if(_state) {
					LPC_SWM->PINENABLE[_reg] &= ~(1<<_bit);
				} else {
					LPC_SWM->PINENABLE[_reg] |= (1<<_bit);
				}
			#endif

			return _state;
		}

		static bool enabled(const uint8_t& _reg, const uint8_t& _bit) {
			(void) _reg;
			const auto mask = 1<<_bit;
			#if defined(__LPC82X__)
				return (LPC_SWM->PINENABLE0 & mask) != 0;
			#elif defined(LPC15XX__)
				return (LPC_SWM->PINENABLE[_reg] & mask) != 0;
			#endif
		}
};

class GPIO
{
	public:
		static uint8_t clkIndex(const uint8_t& _port) {
			(void) _port;
			#if defined(__LPC82X__)
				return 6;
			#elif defined(__LPC15XX__)
				if(_port <=2 ) return 14 + _port;
			#endif
			return 0xFF; // INVALID PORT
		}

		static bool enableClk(const uint8_t& _port, const bool& _value=true ) {
			(void) _value;
			return SystemClock::enable(0, clkIndex(_port));
		}

		static bool direction(const uint8_t& _port, const uint8_t& _pin, const bool& _output) {
			(void) _port;
			const uint32_t mask = 1UL<<_pin;
			#if defined(__LPC82X__)
				if( _output ){
					LPC_GPIO_PORT->DIR[0] |= mask;
				} else {
					LPC_GPIO_PORT->DIR[0] &= ~mask;
				}
			#elif defined(__LPC15XX__)
				if( _output ){
					LPC_GPIO->DIR[_port] |= mask;
				} else {
					LPC_GPIO->DIR[_port] &= ~mask;
				}
			#endif

			return _output;
		}

		static bool direction(const uint8_t& _port, const uint8_t& _pin) {
			(void) _port;
			const uint32_t mask = 1UL<<_pin;
			#if defined(__LPC82X__)
				return static_cast<bool>( LPC_GPIO_PORT->DIR[0] & mask );
			#elif defined(__LPC15XX__)
				return static_cast<bool>( LPC_GPIO->DIR[_port] & mask );
			#endif
		}
};

class PinMap
{
	public:
		static bool set(const uint8_t& _reg, const uint8_t& _offset, const uint8_t _pin_index) {
			#if defined(__LPC82X__)
				SystemClock::ScopedEnable en(0, 7);
			#elif defined(__LPC15XX__)
				SystemClock::ScopedEnable en(0, 12);
			#endif

			const uint32_t shift = 8UL*_offset;
			const uint32_t mask = 0xFFUL << shift;
			LPC_SWM->PINASSIGN[_reg] = (LPC_SWM->PINASSIGN[_reg]&~mask) |(_pin_index<<shift);
			return true;
		}

		static bool set(const uint8_t _map_index, const uint8_t _pin_index) {
			const uint8_t reg = regFromIndex(_map_index);
			const uint8_t offset = offsetFromIndex(_map_index);
			return set(reg, offset, _pin_index);
		}

		static uint8_t pinIndex(const uint8_t& _port, const uint8_t& _pin) {
			// TODO: THIS SHOULD DO SOME COMPILE-TIME CHECKING TO MAKE SURE THAT THE PIN IS VALID
			const uint8_t index = (32UL*_port) + _pin;
			return index;
		}

	protected:
		static uint8_t regFromIndex(const uint8_t _map_index) { return _map_index / 4; }
		static uint8_t offsetFromIndex(const uint8_t _map_index) { return _map_index % 4; }
};

} /*namespace chandra*/
#endif /*CHANDRA_CHIP_UTILS_H*/
