#ifndef CHANDRA_CHIP_UTILS_H
#define CHANDRA_CHIP_UTILS_H

namespace chandra
{

class PeripheralActivity
{
	public:
    static void activate(const uint8_t& /*_reg*/, const uint8_t /*_bit*/ ) {}

    static void deactivate(const uint8_t& /*_reg*/, const uint8_t /*_bit*/ ) {}

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
			return _state;
		}

    static bool state(const uint8_t& /*_reg*/, const uint8_t& /*_bit*/) {
      return false;
		}
};

class PowerConfiguration
{
	public:
    static bool enable( const uint8_t& /*_reg*/, const uint8_t& /*_bit*/, const bool& _state = true ) {
			return _state;
		}
};

class FixedFunctionIO
{
	public:
    static bool enable( const uint8_t& /*_reg*/, const uint8_t& /*_bit*/, const bool& _state = true ) {
			return _state;
		}

    static bool enabled(const uint8_t& /*_reg*/, const uint8_t& /*_bit*/) {
			return false;
		}
};

class GPIOImpl
{
	public:
    static constexpr uint8_t clkIndex(const uint8_t& /*_port*/) {
			return 6;
		}

    static bool enableClk(const uint8_t& _port, const bool& _value=true ) {
			return SystemClock::enable(0, clkIndex(_port), _value);
		}

    static bool direction(const uint8_t& /*_port*/, const uint8_t& /*_pin*/, const bool& _output) {
			return _output;
		}

    static bool direction(const uint8_t& /*_port*/, const uint8_t& /*_pin*/) {
      return false;
		}
};

class PinMap
{
	public:
    static bool set(const uint8_t& /*_reg*/, const uint8_t& /*_offset*/, const uint8_t /*_pin_index*/) {
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
