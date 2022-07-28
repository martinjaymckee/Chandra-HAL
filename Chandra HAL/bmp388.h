#ifndef CHANDRA_BMP388_H
#define CHANDRA_BMP388_H

//
// Standard Includes
//
#include <chrono>

//
// Chandra Includes
//
#include "barometric.h"
#include "chrono.h"
#include "i2c.h"
#include "timing.h"
#include "register_device.h"
#include "sensor_utils.h"
#include "spi.h"
#include "units.h"

namespace chandra
{
namespace drivers
{
namespace internal
{
template<class Value, class BaseUnits, class Comm>
struct BMP388ImplBase : BaseBarometricProxyImpl<Value, BaseUnits>
{
    // Register Access Type
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    using scalar_t = Value;

    BMP388ImplBase(const register_access_t& _regs, const scalar_t& _scale)
      : regs_(_regs), scale_(_scale) {}


    // Register Addresses
    enum registers_t {
        CHIP_ID = 0X00,
    		ERR_REG = 0x02,
    		STATUS = 0x03,
    		PRESS_L = 0x04,
    		PRESS_M = 0x05,
    		PRESS_H = 0x06,
    		TEMP_L = 0x07,
    		TEMP_M = 0x08,
    		TEMP_H = 0x09,
    		SENSOR_TIME_L = 0x0C,
    		SENSOR_TIME_ML = 0x0D,
    		SENSOR_TIME_HM = 0x0E,
    		SENSOR_TIME_H = 0x0F,
    		EVENT = 0x10,
    		INT_STATUS = 0x11,
    		FIFO_LENGTH_L = 0x12,
    		FIFO_LENGTH_H = 0x13,
    		FIFO_DATA = 0x14,
    		FIFO_WATERMARK_L = 0x15,
    		FIFO_WATERMARK_H = 0x16,
    		FIFO_CONFIG_1 = 0x17,
    		FIFO_CONFIG_2 = 0x18,
    		INT_CTRL = 0x19,
    		IF_CONFIG = 0x1A,
    		PWR_CTRL = 0x1B,
    		OSR = 0x1C,
    		ODR = 0x1D,
    		IIR_CONFIG = 0x1F,

    		NVM_CRC = 0x30,
    		NVM_T1_L = 0x31,
    		NVM_T1_H = 0x32,
    		NVM_T2_L = 0x33,
    		NVM_T2_H = 0x34,
    		NVM_T3 = 0x35,
    		NVM_P1_L = 0x36,
    		NVM_P1_H = 0x37,
    		NVM_P2_L = 0x38,
    		NVM_P2_H = 0x39,
    		NVM_P3 = 0x3A,
    		NVM_P4 = 0x3B,
    		NVM_P5_L = 0x3C,
    		NVM_P5_H = 0x3D,
    		NVM_P6_L = 0x3E,
    		NVM_P6_H = 0x3F,
    		NVM_P7 = 0x40,
    		NVM_P8 = 0x41,
    		NVM_P9_L = 0x42,
    		NVM_P9_H = 0x43,
    		NVM_P10 = 0x44,
    		NVM_P11 = 0x45,

    		CMD = 0x7E
      };

    auto set_odr(const units::Quantity<scalar_t, units::mks::Hz>&) {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto get_odr() {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto set_osr(const uint16_t&) {
      return 0;
    }

    auto get_osr() {
      return 0;
    }

    auto set_lpf(const units::Quantity<scalar_t, units::mks::Hz>&) {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }

    auto get_lpf() {
      return units::Quantity<scalar_t, units::mks::Hz>(0);
    }


    constexpr scalar_t scale() const { return scale_; }

  protected:
    register_access_t regs_;
    scalar_t scale_;
};

template<class Value, class BaseUnits, class Comm>
class BMP388PressureImpl : public BMP388ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = BMP388ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    BMP388PressureImpl(const register_access_t& _regs)
      : base_t(_regs, 5.98e-4) {}
};

template<class Value, class BaseUnits, class Comm>
class BMP388TemperatureImpl : public BMP388ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = BMP388ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    BMP388TemperatureImpl(const register_access_t& _regs)
      : base_t(_regs, 5.98e-4) {}
};

template<class Value>
class BMP388CompensationValues
{
	public:
		BMP388CompensationValues() : valid_(false) {}

		bool update(const uint8_t* _buffer) {
			// TODO: OPTIMIZE CODE (REMOVE DIVISIONS AT LEAST) AND REMOVE DEPENDENCE ON FLOATING-POINT VALUES

			// Calculate CRC -- If Valid, continue, else return false
			uint8_t target_crc = _buffer[0];
			CRC crc;
			for(uint8_t idx = 1; idx < 22; ++idx) {
				crc.update(_buffer[idx]);
			}
			valid_ = crc.match(target_crc);


			// Calculation Compensation Values
			uint16_t data;

			//	T1
			data = _buffer[2];
			data = (data<<8) | _buffer[1];
			T_[0] = Value(256.0) * static_cast<Value>(data);

			//	T2
			data = _buffer[4];
			data = (data<<8) | _buffer[3];
			T_[1] = static_cast<Value>(data) / Value(1073741824.0);

			//	T3
			T_[2] = static_cast<Value>(static_cast<int8_t>(_buffer[5])) / Value(2.814749767e14);

			//	P1
			data = _buffer[7];
			data = (data<<8) | _buffer[6];
			P_[0] = (static_cast<Value>(static_cast<int16_t>(data)) - Value(16384.0)) / Value(1048576.0);

			//	P2
			data = _buffer[9];
			data = (data<<8) | _buffer[8];
			P_[1] = (static_cast<Value>(static_cast<int16_t>(data)) - Value(16384.0)) / Value(536870912.0);

			//	P3
			P_[2] = static_cast<Value>(static_cast<int8_t>(_buffer[10])) / Value(4294967296.0);

			//	P4
			P_[3] = static_cast<Value>(static_cast<int8_t>(_buffer[11])) / Value(137438953472.0);

			//	P5
			data = _buffer[13];
			data = (data<<8) | _buffer[12];
			P_[4] = Value(8.0) * static_cast<Value>(data);

			//	P6
			data = _buffer[15];
			data = (data<<8) | _buffer[14];
			P_[5] = static_cast<Value>(data) / Value(64.0);

			//	P7
			P_[6] = static_cast<Value>(static_cast<int8_t>(_buffer[16])) / Value(256.0);

			//	P8
			P_[7] = static_cast<Value>(static_cast<int8_t>(_buffer[17])) / Value(32768.0);

			//	P9
			data = _buffer[19];
			data = (data<<8) | _buffer[18];
			P_[8] = static_cast<Value>(static_cast<int16_t>(data)) / Value(2.814749767e14);

			//	P10
			P_[9] = static_cast<Value>(static_cast<int8_t>(_buffer[20])) / Value(2.814749767e14);

			//	P11
			P_[10] = static_cast<Value>(static_cast<int8_t>(_buffer[21])) / Value(3.68934881474e19);

			return valid_;
		}

		Value T(const uint8_t& _idx) const { return T_[_idx-1]; }
		Value P(const uint8_t& _idx) const { return P_[_idx-1]; }
		bool valid() const { return valid_; }

	protected:
		class CRC
		{
			protected:
				static const uint8_t poly = 0x1D;

			public:
				CRC() : crc_(0xFF) {}

				bool reset() {
					crc_ = 0xFF;
					return true;
				}

				uint8_t update(uint8_t _val) {
					for(uint8_t idx = 0; idx < 8; ++idx) {
						const bool do_xor = ((crc_ ^ _val) & 0x80) == 0x80;
						crc_ = (crc_ & 0x7F) << 1;
						_val = (_val & 0x7F) << 1;
						if(do_xor) crc_ ^= poly;
					}

					return crc();
				}

				uint8_t crc() const { return 0xFF ^ crc_; }

				bool match(const uint8_t _crc) {
					const uint8_t ref = crc();
					return (ref == _crc);
				}

			protected:
				uint8_t crc_;
		};

		Value T_[3];
		Value P_[11];
		bool valid_;
};

} /*namespace internal*/

template<
	class Value,
	class Comm = chandra::io::SPIMaster,
	class PressureUnits=chandra::units::mks::hPa,
	class TemperatureUnits=chandra::units::mks::degC
>
class BMP388
		: public Barometric<
		  	  BMP388<Value, Comm, PressureUnits, TemperatureUnits>,
			  Value,
			  PressureUnits, TemperatureUnits,
			  internal::BMP388PressureImpl<Value, PressureUnits, Comm>,
			  internal::BMP388TemperatureImpl<Value, TemperatureUnits, Comm>
		>
{
  protected:
    friend class Barometric<BMP388<Value, Comm, PressureUnits, TemperatureUnits>, Value, PressureUnits, TemperatureUnits, internal::BMP388PressureImpl<Value, PressureUnits, Comm>, internal::BMP388TemperatureImpl<Value, TemperatureUnits, Comm>>;
    using base_t = Barometric<BMP388<Value, Comm, PressureUnits, TemperatureUnits>, Value, PressureUnits, TemperatureUnits, internal::BMP388PressureImpl<Value, PressureUnits, Comm>, internal::BMP388TemperatureImpl<Value, TemperatureUnits, Comm>>;
    using scalar_t = typename base_t::scalar_t;
    using value_t = typename base_t::value_t;
    using ref_t = BMP388<Value, Comm, PressureUnits, TemperatureUnits>;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    using clock_t = chandra::chrono::Timer<>::clock_t;
    using time_point_t = typename clock_t::time_point;
    using status_t = SensorUpdateStatus<>;

    using temperature_t = chandra::units::Quantity<scalar_t, TemperatureUnits>;
    using registers_t = typename internal::BMP388ImplBase<Value, PressureUnits, Comm>::registers_t;

  public:
    BMP388(register_access_t _regs)
      : base_t{regs_}, regs_{_regs} {}

    bool init() {
    	if(!reset()) return false;

		if(!loadCalibrationValues()) return false;

    	//0x19 - INT_CTRL (drdy_en(6), int_level(1))
    	//0x1B - PWR_CTRL (pressure enable/temperature enable/normal mode)
    	//0x1C - OSR
    	//0x1D - ODR (prescaler=1, odr_sel=0x00)
    	//
    	regs_.write(registers_t::INT_CTRL, static_cast<uint8_t>((1<<6)|(1<<1))); // Enable DRDY, Active-High
    	regs_.write(registers_t::OSR, static_cast<uint8_t>(0x0D)); // Pressure x32, Temperature 2x Oversample
    	regs_.write(registers_t::ODR, static_cast<uint8_t>(4)); // ODR = 12.5Hz


    	regs_.write(registers_t::PWR_CTRL, static_cast<uint8_t>(0x33)); // Pressure and Temperature on, Normal Mode
    	initialized_ = valid();
    	return initialized_;
    }

    bool initialized() const { return initialized_;}

    uint8_t id() const {
    	uint8_t buffer[2];
    	regs_.bytes(registers_t::CHIP_ID, 2, buffer);
    	return buffer[1];
    }

    bool reset() {
    	constexpr auto timeout_period = std::chrono::milliseconds{15};
    	const auto t_start = chandra::chrono::timestamp_clock::now();
    	// TODO: CHECK THAT THE BMP388 IS READY TO RECEIVE A COMMAND
    	regs_.write(registers_t::CMD, static_cast<uint8_t>(0xB6));
    	uint8_t buffer[2];
    	while(true) {
    		regs_.bytes(registers_t::EVENT, 2, buffer);
    		if(buffer[1] & 0x01) return true;
    		if(chandra::chrono::after(timeout_period, t_start)) break;
    	}

    	return false;
    }

    bool calibrate(bool _blocking = false) {
    	calibrated_ = true;
    	return true;
    }

    bool calibrated() const { return calibrated_; }

    const auto& CompensationValues() const {return C;}

    status_t update(const bool& _update, const bool& _forced) {
    	status_t status;
    	uint8_t buffer[7];

      bool data_available = _update;
      if(!_forced) {
    	  regs_.bytes(registers_t::INT_STATUS, 2, buffer);
    	  data_available = bool(buffer[1] & (1<<3));
      }

      if(data_available) {
    	  // Read Pressure and Temperature
    	  regs_.bytes(registers_t::PRESS_L, 7, buffer);

    	  // Assemble Raw Values
    	  const uint32_t P_raw = (static_cast<uint32_t>(buffer[3])<<16) | (static_cast<uint32_t>(buffer[2])<<8) | buffer[1];
    	  const uint32_t T_raw = (static_cast<uint32_t>(buffer[6])<<16) | (static_cast<uint32_t>(buffer[5])<<8) | buffer[4];

    	  // Calculate Corrected Values
    	  status.calculated = calculatePressureTemperature(P_raw, T_raw);
    	  status.processed = true;
      }

      return status;
    }

    status_t update() {
    	return update(false, false);
    }

    status_t update(const bool& _update) {
    	return update(_update, true);
    }

    bool valid() const {
    	return C.valid() and (id() == 0x50);
    }

    // TODO: THESE SHOULD BE MOVED TO THE BASE CLASS
    template<class U>
    temperature_t setSelfHeating(const chandra::units::Quantity<Value, U>& _Tinit) {
    	const auto Tinit = chandra::units::convert<TemperatureUnits, U>(_Tinit);
//      Tselfheating_ = temperature_val_ - Tinit_;
      return temperature_t{Tselfheating_};
    }

    temperature_t setSelfHeating() {
//      Tselfheating_ = temperature_val_ - Tinit_;
      return temperature_t{Tselfheating_};
    }

    temperature_t Tinit() const { return temperature_t{Tinit_}; }
    temperature_t Tselfheating() const { return temperature_t{Tselfheating_}; }

  protected:
    bool loadCalibrationValues(){
    	static constexpr uint8_t N = 23;
    	uint8_t buffer[N];
    	regs_.bytes(registers_t::NVM_CRC, N, buffer);
    	C.update(&buffer[1]);
    	return C.valid();
    }

    bool calculatePressureTemperature(const uint32_t& _P_raw, const uint32_t& _T_raw) {
    	// Calculate Compensated Temperature
    	const auto C1 = (_T_raw - C.T(1));
    	const auto C2 = (C.T(2) * C1);
    	this->temperature_raw_ = Value{C2 + (C.T(3) * C1 * C1)};

    	// Calculate Compensated Pressure
    	const auto T_squared = this->temperature_raw_ * this->temperature_raw_;
    	const auto T_cubed = this->temperature_raw_ * T_squared;
    	const auto P_squared = _P_raw * _P_raw;
    	const auto P_cubed = _P_raw * P_squared;
    	const auto C3 = (C.P(6) * this->temperature_raw_);
    	const auto C4 = (C.P(7) * T_squared);
    	const auto C5 = (C.P(8) * T_cubed);
    	const auto C6 = C.P(5) + C3 + C4 + C5;
    	const auto C7 = (C.P(2) * this->temperature_raw_);
    	const auto C8 = (C.P(3) * T_squared);
    	const auto C9 = (C.P(4) * T_cubed);
    	const auto C10 = _P_raw * (C.P(1) + C7 + C8 + C9);
    	const auto C11 = C.P(9) + (C.P(10) * this->temperature_raw_);
    	const auto C12 = (C11 * P_squared);
    	const auto C13 = C12 + (C.P(11) * P_cubed);
    	this->pressure_raw_ = Value{C6 + C10 + C13} / Value{100};
    	return true;
    }

  private:
    bool initialized_ = false;
    bool calibrated_ = false;
    chandra::drivers::RegisterDevice<Comm> regs_;
    internal::BMP388CompensationValues<double> C; // Note: Currently the compensation only works with floating-point values
    scalar_t Tinit_ = 0;
    scalar_t Tselfheating_ = 0;
};

} /* namespace drivers */
} /* namespace chandra */


#endif /*CHANDRA_BMP388_H*/
