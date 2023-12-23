#ifndef CHANDRA_BMX160_H
#define CHANDRA_BMX160_H

#include <chrono>
#include <cstddef>
using namespace std::literals::chrono_literals;

#include "chrono.h"
#include "inertial.h"
#include "math_conversions.h"
#include "register_device.h"
#include "sensor_utils.h"
#include "spi.h"
#include "thermal.h"
#include "timing.h"

namespace chandra
{
namespace drivers
{
namespace internal
{

template<class Value, class BaseUnits, class Comm>
class BMX160ImplBase : public chandra::drivers::internal::BaseInertialProxyImpl<Value, BaseUnits>
{
  public:
    using scalar_t = Value;

    // Register Access Type
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    BMX160ImplBase(const register_access_t& _regs, const scalar_t& _scale)
      : regs_(_regs), scale_(_scale) {}

    // Command Definitions
    enum class cmds_t : uint8_t {
      START_FOC = 0x03,
      ACCEL_SET_PMU_STANDBY = (0x10 | 0b00),
      ACCEL_SET_PMU_NORMAL = (0x10 | 0b01),
      ACCEL_SET_PMU_LOW = (0x10 | 0b10),
      GYRO_SET_PMU_STANDBY = (0x14 | 0b00),
      GYRO_SET_PMU_NORMAL = (0x14 | 0b01),
      GYRO_SET_PMU_FAST = (0x14 | 0b11),
      MAG_SET_PMU_STANDBY = (0x18 | 0b00),
      MAG_SET_PMU_NORMAL = (0x18 | 0b01),
      MAG_SET_PMU_LOW = (0x18 | 0b10),
      PROG_NVM = 0xA0,
      FLUSH_FIFO = 0xB0,
      RESET_INT = 0xB1,
      CLEAR_STEP_CNT = 0xB2,
      SOFT_RESET = 0xB6
    };

    // Register Addresses
    enum registers_t {
    	 CHIP_ID = 0x00,
    		ERR_REG = 0x02,
    		PMU_STATUS = 0x03,
    		MAG_X_L = 0x04,
    		MAG_X_H = 0x05,
    		MAG_Y_L = 0x06,
    		MAG_Y_H = 0x07,
    		MAG_Z_L = 0x08,
    		MAG_Z_H = 0x09,
    		RHALL_L = 0x0A,
    		RHALL_H = 0x0B,
    		GYRO_X_L = 0x0C,
    		GYRO_X_H = 0x0D,
    		GYRO_Y_L = 0x0E,
    		GYRO_Y_H = 0x0F,
    		GYRO_Z_L = 0x10,
    		GYRO_Z_H = 0x11,
    		ACCEL_X_L = 0x12,
    		ACCEL_X_H = 0x13,
    		ACCEL_Y_L = 0x14,
    		ACCEL_Y_H = 0x15,
    		ACCEL_Z_L = 0x16,
    		ACCEL_Z_H = 0x17,
    		SENSOR_TIME_L = 0x18,
    		SENSOR_TIME_M = 0x19,
    		SENSOR_TIME_H = 0x1A,
    		STATUS = 0x1B,
    		INT_STATUS_0 = 0x1C,
    		INT_STATUS_1 = 0x1D,
    		INT_STATUS_2 = 0x1E,
    		INT_STATUS_3 = 0x1F,
    		TEMP_L = 0x20,
    		TEMP_H = 0x21,
    		FIFO_LENGTH_L = 0x22,
    		FIFO_LENGTH_H = 0x23,
    		FIFO_DATA = 0x24,
    		ACCEL_CONFIG = 0x40,
    		ACCEL_RANGE = 0x41,
    		GYRO_CONFIG = 0x42,
    		GYRO_RANGE = 0x43,
    		MAG_CONFIG = 0x44,
    		FIFO_DOWNS = 0x45,
    		FIFO_CONFIG_0 = 0x46,
    		FIFO_CONFIG_1 = 0x47,
    		MAG_IF_0 = 0x4C,
    		MAG_IF_1 = 0x4D,
    		MAG_IF_2 = 0x4E,
    		MAG_IF_3 = 0x4F,
    		INT_EN_0 = 0x50,
    		INT_EN_1 = 0x51,
    		INT_EN_2 = 0x52,
    		INT_OUT_CTRL = 0x53,
    		INT_LATCH = 0x54,
    		INT_MAP_0 = 0x55,
    		INT_MAP_1 = 0x56,
    		INT_MAP_2 = 0x57,
    		INT_DATA_0 = 0x58,
    		INT_DATA_1 = 0x59,
    		INT_LOWHIGH_0 = 0x5A,
    		INT_LOWHIGH_1 = 0x5B,
    		INT_LOWHIGH_2 = 0x5C,
    		INT_LOWHIGH_3 = 0x5D,
    		INT_LOWHIGH_4 = 0x5E,
    		INT_MOTION_0 = 0x5F,
    		INT_MOTION_1 = 0x60,
    		INT_MOTION_2 = 0x61,
    		INT_MOTION_3 = 0x62,
    		INT_TAP_0 = 0x63,
    		INT_TAP_1 = 0x64,
    		INT_ORIENT_0 = 0x65,
    		INT_ORIENT_1 = 0x66,
    		INT_FLAT_0 = 0x67,
    		INT_FLAT_1 = 0x68,
    		FOC_CONFIG = 0x69,
    		CONFIG = 0x6A,
    		IF_CONFIG = 0x6B,
    		PMU_TRIGGER = 0x6C,
    		SELF_TEST = 0x6D,
    		NV_CONFIG = 0x70,
    		ACCEL_OFFSET_X = 0x71,
    		ACCEL_OFFSET_Y = 0x72,
    		ACCEL_OFFSET_Z = 0x73,
    		GYRO_OFFSET_X_L = 0x74,
    		GYRO_OFFSET_Y_L = 0x75,
    		GYRO_OFFSET_Z_L = 0x76,
    		GYRO_OFFSET_ADDITIONAL = 0x77,
    		STEP_CNT_0 = 0x78,
    		STEP_CNT_1 = 0x79,

    		CMD = 0x7E
      };

      constexpr scalar_t scale() const { return scale_; }

      register_access_t regs_;
      scalar_t scale_;
};

template<class Value, class BaseUnits, class Comm>
class BMX160AccelImpl : public BMX160ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = BMX160ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    BMX160AccelImpl(const register_access_t& _regs)
      : base_t(_regs, 5.98e-4) {}

    scalar_t set_fs(scalar_t fs) {
        return 0;
    }

    scalar_t get_fs() const {
    	return 0;
    }

    scalar_t set_odr(scalar_t _freq) {
    	return 0;
    }

    scalar_t get_odr() const {
    	return 0;
    }
};

template<class Value, class BaseUnits, class Comm>
class BMX160GyroImpl : public BMX160ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = BMX160ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    BMX160GyroImpl(const register_access_t& _regs)
      : base_t(_regs, 1.33e-4) {}

    scalar_t set_fs(scalar_t fs) {
        return 0;
    }

    scalar_t get_fs() const {
        return 0;
    }

    scalar_t set_odr(scalar_t _freq) {
        return 0;
    }

    scalar_t get_odr() const {
    	return 0;
    }
};

template<class Value, class BaseUnits, class Comm>
class BMX160MagImpl : public BMX160ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = BMX160ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    BMX160MagImpl(const register_access_t& _regs)
      : base_t(_regs, 1.33e-4) {}

    scalar_t set_fs(scalar_t fs) {

        return 0;
    }

    scalar_t get_fs() const {
        return 0;
    }

    scalar_t set_odr(scalar_t _freq) {
    	return 0;
    }

    scalar_t get_odr() const {
    	return 0;
    }
};
} /*namespace internal*/

template<
  class Value,
  class Comm = chandra::io::SPIMaster,
  class AccelUnits = units::mks::m_per_s2,
  class GyroUnits = units::mks::rad_per_s,
  class MagUnits = units::mks::T,
  class TempUnits = units::mks::degC
>
class BMX160
        : public AccelGyroMag<BMX160<Value, Comm, AccelUnits, GyroUnits, MagUnits, TempUnits>, Value, internal::BMX160AccelImpl<Value, AccelUnits, Comm>, internal::BMX160GyroImpl<Value, GyroUnits, Comm>, internal::BMX160MagImpl<Value, MagUnits, Comm>, 3, AccelUnits, GyroUnits, MagUnits>,
          public Thermometer<BMX160<Value, Comm, AccelUnits, GyroUnits, MagUnits, TempUnits>, Value, TempUnits>
{
    protected:
        using register_access_t = chandra::drivers::RegisterDevice<Comm>;
        using registers_t = typename internal::BMX160ImplBase<Value, AccelUnits, Comm>::registers_t;
        using cmds_t = typename internal::BMX160ImplBase<Value, AccelUnits, Comm>::cmds_t;

    public:
        friend class AccelGyroMag<BMX160<Value, Comm, AccelUnits, GyroUnits, MagUnits, TempUnits>, Value, internal::BMX160AccelImpl<Value, AccelUnits, Comm>, internal::BMX160GyroImpl<Value, GyroUnits, Comm>, internal::BMX160MagImpl<Value, MagUnits, Comm>, 3, AccelUnits, GyroUnits, MagUnits>;
        using base_t = AccelGyroMag<BMX160<Value, Comm, AccelUnits, GyroUnits, MagUnits, TempUnits>, Value, internal::BMX160AccelImpl<Value, AccelUnits, Comm>, internal::BMX160GyroImpl<Value, GyroUnits, Comm>, internal::BMX160MagImpl<Value, MagUnits, Comm>, 3, AccelUnits, GyroUnits, MagUnits>;
        using scalar_t = typename base_t::scalar_t;
//        using value_t = typename base_t::value_t;
        using ref_t = BMX160<Value, Comm, AccelUnits, GyroUnits, TempUnits>;
        using status_t = SensorUpdateStatus<>;

        BMX160(register_access_t _regs) : base_t(_regs), regs_(_regs) {}

        bool init() {
          regs_.write(registers_t::CMD, uint8_t(cmds_t::SOFT_RESET));
          chandra::chrono::delay(500us);
          regs_.write(registers_t::CMD, uint8_t(cmds_t::RESET_INT));
          chandra::chrono::delay(500us);

          enable(true);

          // Configure Accelerometer
          regs_.write(registers_t::ACCEL_RANGE, static_cast<uint8_t>(0b1100)); // +/- 16 g
          accel_scale_ = 9.80665 * 16.0 / 32767.0;
          regs_.write(registers_t::ACCEL_CONFIG, static_cast<uint8_t>(0b00101011)); // ODR = 800, OSR = 4, BW ~ 81 Hz (65Hz on Z)

          // Configure Gyroscope
          regs_.write(registers_t::GYRO_RANGE, static_cast<uint8_t>(0)); // +/- 2000 deg/s
          gyro_scale_ = chandra::math::radians(2000.0) / 32767.0;
          regs_.write(registers_t::GYRO_CONFIG, static_cast<uint8_t>(0b00101011)); // ODR = 800, OSR = 4, BW ~ 63 Hz

          // Configure Magnetometer
          mag_scale_ = 1;

          // Configure Temperature
          temp_scale_ = 0.002;
          temp_offset_ = 23;

          return valid();
        }

        bool enable(bool _enable) {
            if(_enable) {
              // Set Acclerometer to Normal Mode
              regs_.write(registers_t::CMD, uint8_t(cmds_t::ACCEL_SET_PMU_NORMAL));
              chandra::chrono::delay(380ms);

              // Set Gyro to Normal Mode
              regs_.write(registers_t::CMD, uint8_t(cmds_t::GYRO_SET_PMU_NORMAL));
              chandra::chrono::delay(80ms);

              // Set Mag to Normal Mode and Enable
              //	Enable Mag Interface
              regs_.write(registers_t::CMD, uint8_t(cmds_t::MAG_SET_PMU_NORMAL));
              chandra::chrono::delay(500us);
              //	Enter Manual Control Mode
              regs_.write(registers_t::MAG_IF_0, uint8_t(0x80));
              chandra::chrono::delay(50ms);
              //	Power Up Mag
              regs_.write(registers_t::MAG_IF_3, uint8_t(0x01)); // Power On
              regs_.write(registers_t::MAG_IF_2, uint8_t(0x4B)); // Write ADDR -> Power Control Register
              //	Set Repetitions
              regs_.write(registers_t::MAG_IF_3, uint8_t(0x04)); // Rep.  X/Y = 9 (1+2*REP)
              regs_.write(registers_t::MAG_IF_2, uint8_t(0x51)); // Write ADDR -> REPXY Register
              regs_.write(registers_t::MAG_IF_3, uint8_t(0x0E)); // Rep.  Z = 15 (1+REP)
              regs_.write(registers_t::MAG_IF_2, uint8_t(0x52)); // Write ADDR -> REPZ Register
              //	Sampling Mode
//              regs_.write(registers_t::MAG_IF_3, uint8_t(0x02)); // ODR = Default (10Hz), Forced Mode
              regs_.write(registers_t::MAG_IF_3, uint8_t(0b00111000)); // ODR = 30Hz, Normal Mode
              regs_.write(registers_t::MAG_IF_2, uint8_t(0x4C)); // Configuration Register
              regs_.write(registers_t::MAG_IF_1, uint8_t(0x42)); // Read ADDR -> mx (low) *** TODO: CHECK IF THIS IS NECESSARY ***
              regs_.write(registers_t::MAG_CONFIG, uint8_t(0x08)); // MAG ODR = 100 Hz
              //	Exit Manual Control Mode
              regs_.write(registers_t::MAG_IF_0, uint8_t(0x03)); // Set Readout Burst -> 6 Bytes
              chandra::chrono::delay(50ms);

              // Configure Fast Offset Calibration
              regs_.write(registers_t::FOC_CONFIG, uint8_t(0x40)); // Enable Calibration of Gyro only

              // Run Fast Offset Calibration
              regs_.write(registers_t::CMD, uint8_t(cmds_t::START_FOC));
              chandra::chrono::delay(250ms); // WAIT WHILE FOC_RDY BIT IN STATUS REGISTER IS "0" TO DO IT BETTER THAN JUST DELAYING

              // Enable Offset Correction
              regs_.update(registers_t::GYRO_OFFSET_ADDITIONAL, uint8_t(0xC0), uint8_t(0xC0));
            } else {
              // Set Acclerometer to Standby
              regs_.write(registers_t::CMD, uint8_t(cmds_t::ACCEL_SET_PMU_STANDBY));
              chandra::chrono::delay(380us);

              // Set Gyro to Standby
              regs_.write(registers_t::CMD, uint8_t(cmds_t::GYRO_SET_PMU_STANDBY));
              chandra::chrono::delay(80ms);

              // Set Mag to Standby
              regs_.write(registers_t::CMD, uint8_t(cmds_t::MAG_SET_PMU_STANDBY));
              chandra::chrono::delay(500us);
            }

            return true;
        }

        // RUN SELF TESTS FOR VALIDATATION....

        uint8_t id() const { return regs_.byte(registers_t::CHIP_ID); }

        bool valid() const { return id() == 0xD8; }

        status_t update() {
          status_t status;
          uint8_t buffer[20];

          // Read Temperature Bytes
          regs_.bytes(registers_t::TEMP_L, 2, buffer);
          const auto T_raw = buffer_to_signed<scalar_t>(buffer, 1, 0);
          this->temp_raw_ = (temp_scale_ * T_raw) + temp_offset_;

          // Read IMU Data
          regs_.bytes(registers_t::MAG_X_L, 20, buffer);

          // Assemble Raw Values
          const auto ax = typename base_t::accelerometer_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 15, 14)};
          const auto ay = typename base_t::accelerometer_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 17, 16)};
          const auto az = typename base_t::accelerometer_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 19, 18)};
          this->accel_raw_ = accel_scale_ * typename base_t::accelerometer_proxy_t::vector_t{ax, ay, az};

          const auto gx = typename base_t::gyroscope_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 9, 8)};
          const auto gy = typename base_t::gyroscope_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 11, 10)};
          const auto gz = typename base_t::gyroscope_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 13, 12)};
          this->gyro_raw_ = gyro_scale_ * typename base_t::gyroscope_proxy_t::vector_t{gx, gy, gz};

          const auto rhall = buffer_to_signed<scalar_t>(buffer, 7, 6);
          (void) rhall; // NOTE: THIS NEEDS TO BE USED TO ADJUST THE VALUES....
          const auto mx = typename base_t::magnetometer_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 1, 0)};
          const auto my = typename base_t::magnetometer_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 3, 2)};
          const auto mz = typename base_t::magnetometer_proxy_t::quantity_t{buffer_to_signed<scalar_t>(buffer, 5, 4)};
          this->mag_raw_ = mag_scale_ * typename base_t::magnetometer_proxy_t::vector_t{mx, my, mz};

          status.calculated = true;
      	  status.processed = true;
//      	  const auto s = regs_.byte(registers_t::PMU_STATUS);
          return status;
        }

    protected:
      template<size_t N, class Index>
      auto buffer_to_uint16(uint8_t (&_buffer)[N], Index _idx_h, Index _idx_l) {
          return (static_cast<uint16_t>(_buffer[_idx_h]) << 8) | _buffer[_idx_l];
      }

      template<size_t N, class Index>
      auto buffer_to_int16(uint8_t (&_buffer)[N], Index _idx_h, Index _idx_l) {
          return static_cast<int16_t>(buffer_to_uint16<N, Index>(_buffer, _idx_h, _idx_l));
      }

      template<class Dest, size_t N, class Index>
      auto buffer_to_unsigned(uint8_t (&_buffer)[N], Index _idx_h, Index _idx_l) {
        return static_cast<Dest>(buffer_to_uint16<N, Index>(_buffer, _idx_h, _idx_l));
      }

      template<class Dest, size_t N, class Index>
      auto buffer_to_signed(uint8_t (&_buffer)[N], Index _idx_h, Index _idx_l) {
        return static_cast<Dest>(buffer_to_int16<N, Index>(_buffer, _idx_h, _idx_l));
      }

    private:
        register_access_t regs_;
        scalar_t accel_scale_;
        scalar_t gyro_scale_;
        scalar_t mag_scale_;
        scalar_t temp_scale_;
        scalar_t temp_offset_;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_BMX160_H*/
