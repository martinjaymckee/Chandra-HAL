#ifndef CHANDRA_BMX160_H
#define CHANDRA_BMX160_H


#include "chrono.h"
#include "inertial_crtp.h"
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

    protected:
//      // TODO: AT LEAST THIS LOG 2 NEEDS TO MOVE TO A UTILITY CLASS....
//      constexpr uint32_t log2(uint32_t x) const {
//        //return __builtin_ctz (x);
//        uint32_t count = 0;
//        while(x){
//            x >>= 1;
//            ++count;
//        }
//        return count;
//      }
//
//      constexpr uint8_t calcOdrBits(const Value& _freq) const {
//        uint8_t bits(0);
//        if(_freq == 0) {
//            bits = 0x00;
//        } else {
//            const auto div = _freq / 13;
//            bits = log2(div) + 1;
//        }
//        return bits;
//      }
//
//      constexpr uint32_t calcOdrFreq(const uint8_t& bits) const {
//        return (bits == 0) ? 0 : (13 * (1UL << (bits-1UL)));
//      }

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

  protected:
    scalar_t accel_scale_;
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

  protected:
    scalar_t gyro_scale_;
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

  protected:
    scalar_t mag_scale_;
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

    public:
        friend class AccelGyroMag<BMX160<Value, Comm, AccelUnits, GyroUnits, MagUnits, TempUnits>, Value, internal::BMX160AccelImpl<Value, AccelUnits, Comm>, internal::BMX160GyroImpl<Value, GyroUnits, Comm>, internal::BMX160MagImpl<Value, MagUnits, Comm>, 3, AccelUnits, GyroUnits, MagUnits>;
        using base_t = AccelGyroMag<BMX160<Value, Comm, AccelUnits, GyroUnits, MagUnits, TempUnits>, Value, internal::BMX160AccelImpl<Value, AccelUnits, Comm>, internal::BMX160GyroImpl<Value, GyroUnits, Comm>, internal::BMX160MagImpl<Value, MagUnits, Comm>, 3, AccelUnits, GyroUnits, MagUnits>;
        using scalar_t = typename base_t::scalar_t;
        using value_t = typename base_t::value_t;
        using ref_t = BMX160<Value, Comm, AccelUnits, GyroUnits, TempUnits>;
        using status_t = SensorUpdateStatus<>;

        BMX160(register_access_t _regs) : base_t(_regs), regs_(_regs) {}

        bool init() {
          enable(true);
          return valid();
        }

        bool enable(bool) {

            return true;
        }

        // RUN SELF TESTS FOR VALIDATATION....

        uint8_t id() { return regs_.byte(registers_t::CHIP_ID); }

        bool valid() const { return id() == 0xD8; }

        status_t update() {
            status_t status;
            return status;
        }

    private:
        register_access_t regs_;
        scalar_t accel_scale_;
        scalar_t gyro_scale_;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_BMX160_H*/
