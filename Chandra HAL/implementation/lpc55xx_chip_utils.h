#ifndef CHANDRA_CHIP_UTILS_H
#define CHANDRA_CHIP_UTILS_H

#include <fsl_device_registers.h>

namespace chandra
{
	class PeripheralActivity
	{
	public:
		static void activate(const uint8_t& _reg, const uint8_t _bit ) {
			SYSCON->PRESETCTRLX[_reg] &= ~(1<<_bit);
		}

		static void deactivate(const uint8_t& _reg, const uint8_t _bit ) {
			SYSCON->PRESETCTRLX[_reg] |= (1<<_bit);
		}

		static void reset(const uint8_t& _reg, const uint8_t _bit ) {
			deactivate(_reg, _bit);
			activate(_reg, _bit);
		}
	};

	class SystemClock
	{
		public:
			static bool enable(const uint8_t& _reg, const uint8_t& _bit, const bool& _state = true) {
				if(_bit > 31) return false;
				if(_state) {
					SYSCON->AHBCLKCTRLX[_reg] |= (1<<_bit);
				} else {
					SYSCON->AHBCLKCTRLX[_reg] &= ~(1<<_bit);
				}
				return _state;
			}

			static bool state(const uint8_t& _reg, const uint8_t& _bit) {
				if(_bit > 31) return false;
				return static_cast<bool>(SYSCON->AHBCLKCTRLX[_reg] & (1<<_bit));
			}
	};

	class PowerConfiguration
	{
		public:
			static bool enable( const uint8_t& /*_reg*/, const uint8_t& _bit, const bool& _state = true ) {
				if(_state) {
					PMC->PDRUNCFG0 &= ~(1<<_bit);
				} else {
					PMC->PDRUNCFG0 |= (1<<_bit);
				}

				return _state;
			}
	};

	class GPIOImpl
	{
		public:
			static constexpr uint8_t clkIndex(const uint8_t& _port) {
				return _port == 0 ? 6 : 20;
			}

			static bool enableClk(const uint8_t& _port, const bool& _value=true ) {
				return SystemClock::enable(0, clkIndex(_port), _value);
			}

			static bool direction(const uint8_t& _port, const uint8_t& _pin, const bool& _output) {
				const uint32_t mask = 1UL<<_pin;
				if( _output ){
					GPIO->DIR[_port] |= mask;
				} else {
					GPIO->DIR[_port] &= ~mask;
				}
				return _output;
			}

			static bool direction(const uint8_t& _port, const uint8_t& _pin) {
				const uint32_t mask = 1UL<<_pin;
				return static_cast<bool>( GPIO->DIR[_port] & mask );
			}
	};
} /*namespace chandra*/

#endif /*CHANDRA_CHIP_UTILS_H*/
