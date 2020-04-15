#ifndef CHANDRA_MPU60X0_H
#define CHANDRA_MPU60X0_H


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
class MPU60X0ImplBase : public chandra::drivers::internal::BaseInertialProxyImpl<Value, BaseUnits>
{
  public:
    using scalar_t = Value;

    // Register Access Type
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    MPU60X0ImplBase(const register_access_t& _regs, const scalar_t& _scale)
      : regs_(_regs), scale_(_scale) {}

    // Register Addresses
    enum registers_t {
        SMPLRT_DIV = 0x19,
        CONFIG = 0x1A,
        GYRO_CONFIG = 0x1B,
        ACCEL_CONFIG = 0x1C,
        // Lots of registers
        ACCEL_X_H = 0X3B,
        ACCEL_X_L = 0X3C,
        ACCEL_Y_H = 0X3D,
        ACCEL_Y_L = 0X3E,
        ACCEL_Z_H = 0X3F,
        ACCEL_Z_L = 0X40,
        TEMP_H = 0X41,
        TEMP_L = 0X42,
        GYRO_X_H = 0X43,
        GYRO_X_L = 0X44,
        GYRO_Y_H = 0X45,
        GYRO_Y_L = 0X46,
        GYRO_Z_H = 0X47,
        GYRO_Z_L = 0X48,
        // lots of registers
        USER_CTRL = 0x6A,
        PWR_MGMT_1 = 0x6B,
        PWR_MGMT_2 = 0x6C,
        // FIFO Registers
        WHO_AM_I = 0x75
      };

      constexpr scalar_t scale() const { return scale_; }

    protected:
      scalar_t getGyroClock() const {
          const uint8_t cfg = regs_.byte(registers_t::CONFIG) & 0x07;
          return ((cfg == 0x07) or (cfg == 0x00)) ? 8000 : 1000;
      }

      register_access_t regs_;
      scalar_t scale_;
};

template<class Value, class BaseUnits, class Comm>
class MPU60X0AccelImpl : public MPU60X0ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = MPU60X0ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    MPU60X0AccelImpl(const register_access_t& _regs)
      : base_t(_regs, 2.0*9.81/32767.0) {}

    scalar_t set_fs(scalar_t fs) {
        // static constexpr scalar_t accel_2(2.181662);
        // static constexpr scalar_t accel_4(4.363323);
        // static constexpr scalar_t accel_8(8.726646);
        // static constexpr scalar_t accel_16(17.453293);
        // scalar_t actual(accel_2);
        // uint8_t bits(0);
        //
        // if(fs >= accel_8) { // 16 gees
        //     actual = accel_16;
        //     this->scale_ = scalar_t(4.788403e-3);
        //     bits = 0x01<<2;
        // } else if(fs >= accel_4) { // 8 gees
        //     actual = accel_8;
        //     this->scale_ = scalar_t(2.394202e-3);
        //     bits = 0x03<<2;
        // } else if(fs >= accel_2) { // 4 gees
        //     actual = accel_4;
        //     this->scale_ = scalar_t(1.197101e-3);
        //     bits = 0x02<<2;
        // } else { // 2 gees
        //     this->scale_ = scalar_t(5.985504e-4);
        // }
        // this->regs_.update(registers_t::CTRL1_XL, 0x03<<2, bits);
        //
        // return actual;
        return 0;
    }

    scalar_t get_fs() const {
        // static constexpr scalar_t accel_2(2.181662);
        // static constexpr scalar_t accel_4(4.363323);
        // static constexpr scalar_t accel_8(8.726646);
        // static constexpr scalar_t accel_16(17.453293);
        // const uint8_t bits = uint8_t(this->regs_.byte(registers_t::CTRL1_XL)>>2) & uint8_t(0x03);
        //
        // switch(bits) {
        //     case 0x00:
        //     default:
        //         return accel_2;
        //     case 0x01:
        //         return accel_16;
        //     case 0x02:
        //         return accel_4;
        //     case 0x03:
        //         return accel_8;
        // }
        return 0;
    }

    scalar_t set_odr(scalar_t _freq) {
        // const uint8_t bits = this->calcOdrBits(_freq);
        // this->regs_.update(registers_t::CTRL1_XL, 0xF0, static_cast<uint8_t>(bits<<4));
        // return this->calcOdrFreq(bits);
        return 0;
    }

    scalar_t get_odr() const {
        // const uint8_t bits = uint8_t(this->regs_.byte(registers_t::CTRL1_XL) >> 4) & 0x0F;
        // return this->calcOdrFreq(bits);
        return 0;
    }

  protected:
    scalar_t accel_scale_;
};

template<class Value, class BaseUnits, class Comm>
class MPU60X0GyroImpl : public MPU60X0ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = MPU60X0ImplBase<Value, BaseUnits, Comm>;
    using registers_t = typename base_t::registers_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    MPU60X0GyroImpl(const register_access_t& _regs)
      : base_t(_regs, 250.0/(57.3*32767.0)) {}

    scalar_t set_fs(scalar_t fs) {
        // static constexpr scalar_t gyro_125(2.181662);
        // static constexpr scalar_t gyro_250(4.363323);
        // static constexpr scalar_t gyro_500(8.726646);
        // static constexpr scalar_t gyro_1000(17.453293);
        // static constexpr scalar_t gyro_2000(34.906585);
        // scalar_t actual(gyro_125);
        // uint8_t bits = 0x00;
        //
        // if(fs >= gyro_1000) { // 2000 dps
        //     actual = gyro_2000;
        //     this->scale_ = scalar_t(1.065264e-3);
        //     bits = 0x06<<1;
        // } else if(fs >= gyro_500) { // 1000 dps
        //     actual = gyro_1000;
        //     this->scale_ = scalar_t(5.326322e-4);
        //     bits = 0x04<<1;
        // } else if(fs >= gyro_250) { // 500 dps
        //     actual = gyro_500;
        //     this->scale_ = scalar_t(2.663161e-4);
        //     bits = 0x02<<1;
        // } else if(fs >= gyro_125) { // 250 dps
        //     actual = gyro_250;
        //     this->scale_ = scalar_t(1.331581e-4);
        //     bits = 0x01<<1;
        // } else { // 125 dps
        //     this->scale_ = scalar_t(6.657903e-5);
        // }
        // this->regs_.update(registers_t::CTRL2_G, 0x07<<1, bits);
        // return actual;
        return 0;
    }

    scalar_t get_fs() const {
        // static constexpr scalar_t gyro_125(2.181662);
        // static constexpr scalar_t gyro_250(4.363323);
        // static constexpr scalar_t gyro_500(8.726646);
        // static constexpr scalar_t gyro_1000(17.453293);
        // static constexpr scalar_t gyro_2000(34.906585);
        // const uint8_t bits = uint8_t(this->regs_.byte(registers_t::CTRL2_G)>>1) & uint8_t(0x07);
        //
        // switch(bits) {
        //     case 0x00:
        //     default:
        //         return gyro_125;
        //     case 0x01:
        //         return gyro_250;
        //     case 0x02:
        //         return gyro_500;
        //     case 0x04:
        //         return gyro_1000;
        //     case 0x06:
        //         return gyro_2000;
        // }
        return 0;
    }

    scalar_t set_odr(scalar_t _freq) {
        // const uint8_t bits = this->calcOdrBits(_freq);
        // this->regs_.update(registers_t::CTRL2_G, 0xF0, static_cast<uint8_t>(bits<<4));
        // return this->calcOdrFreq(bits);
        return 0;
    }

    scalar_t get_odr() const {
        // const uint8_t bits = uint8_t(this->regs_.byte(registers_t::CTRL2_G) >> 4) & 0x0F;
        // return this->calcOdrFreq(bits);
        return 0;
    }

  protected:
    scalar_t gyro_scale_;
};

} /*namespace internal*/

template<
  class Value,
  class Comm,
  class AccelUnits = units::mks::m_per_s2,
  class GyroUnits = units::mks::rad_per_s,
  class TempUnits = units::mks::degC
>
class MPU60X0
        : public AccelGyro<MPU60X0<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::MPU60X0AccelImpl<Value, AccelUnits, Comm>, internal::MPU60X0GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>,
          public Thermometer<MPU60X0<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, TempUnits>
{
    protected:
        using register_access_t = chandra::drivers::RegisterDevice<Comm>;
        using registers_t = typename internal::MPU60X0AccelImpl<Value, AccelUnits, Comm>::registers_t;

    public:
        friend class AccelGyro<MPU60X0<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::MPU60X0AccelImpl<Value, AccelUnits, Comm>, internal::MPU60X0GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>;
        using base_t = AccelGyro<MPU60X0<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::MPU60X0AccelImpl<Value, AccelUnits, Comm>, internal::MPU60X0GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>;
        using scalar_t = typename base_t::scalar_t;
        using value_t = typename base_t::value_t;
        using ref_t = MPU60X0<Value, Comm, AccelUnits, GyroUnits, TempUnits>;

        MPU60X0(register_access_t _regs) : base_t(_regs), regs_(_regs) {}

        bool init() {
          regs_.write(registers_t::USER_CTRL, uint8_t(0)); // NO SPECIAL FEATURES
          regs_.write(registers_t::PWR_MGMT_1, uint8_t(0x01)); // USE X AXIS GYROSCOPE CLOCK

          regs_.write(registers_t::SMPLRT_DIV, uint8_t(0)); // SET MAXIMUM SAMPLE RATE
          regs_.write(registers_t::CONFIG, uint8_t(0)); // SET NO EXTERAL SYNC AND LOWPASS FILTER OFF
          regs_.write(registers_t::GYRO_CONFIG, uint8_t(0)); // SET GYROSCOPE FULLSCALE TO 250 DEG/SEC
          regs_.write(registers_t::ACCEL_CONFIG, uint8_t(0)); // SET ACCELEROMETER FULLSCALE TO +/-2 GEES

          enable(true);
          return id() == 0x68;
        }

        bool enable(bool) {
            return true;
        }

        // TODO: THIS SHOULD HAVE AN ENABLE FUNCTION (WHICH IS CALLED BY DEFAULT FROM THE INIT)

        uint8_t id() { return regs_.byte(registers_t::WHO_AM_I); }

        SensorUpdateStatus update() {
            SensorUpdateStatus status;
             constexpr uint8_t read_num = 14;
             static uint8_t buffer[read_num];
             const auto accel_scale = this->accelerometer.scale();
             const auto gyro_scale = this->gyroscope.scale();
            // //if( sample_timer_.expired(Timer::AUTO_RESET)) {
             regs_.bytes(registers_t::ACCEL_X_H, read_num, buffer);
             const auto ax = accel_scale * val16(buffer[0], buffer[1]);
             const auto ay = accel_scale * val16(buffer[2], buffer[3]);
             const auto az = accel_scale * val16(buffer[4], buffer[5]);
             this->accel_raw_ = value_t({ax, ay, az});
             this->temp_raw_= convertTemp(val16(buffer[6], buffer[7]));
             const auto gx = gyro_scale * val16(buffer[8], buffer[9]);
             const auto gy = gyro_scale * val16(buffer[10], buffer[11]);
             const auto gz = gyro_scale * val16(buffer[12], buffer[13]);
             this->gyro_raw_ = value_t({gx, gy, gz});
             status.updated = true;
            // //}
            // //update_status.errors = SensorUpdateStatus::TimeoutError;
            // //update_status.errors = SensorUpdateStatus::ArithmeticError;
            return status;
        }

    protected:
        static constexpr auto convertTemp(int16_t x) {
            constexpr scalar_t scale(0.00390625);
            constexpr scalar_t offset(25.0);
            return (scale*x) + offset;
        }

        static constexpr auto val16(uint32_t h, uint8_t l) {
            return static_cast<int16_t>((h<<8)|l);
        }

    private:
        register_access_t regs_;
        scalar_t accel_scale_;
        scalar_t gyro_scale_;
};

template<
  class Value,
  class AccelUnits = units::mks::m_per_s2,
  class GyroUnits = units::mks::rad_per_s,
  class TempUnits = units::mks::degC
>
using MPU6000 = MPU60X0<Value, chandra::io::SPIMaster, AccelUnits, GyroUnits, TempUnits>;

template<
  class Value,
  class AccelUnits = units::mks::m_per_s2,
  class GyroUnits = units::mks::rad_per_s,
  class TempUnits = units::mks::degC
>
using MPU6050 = MPU60X0<Value, chandra::io::I2CMaster, AccelUnits, GyroUnits, TempUnits>;


} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_MPU60X0_H*/
