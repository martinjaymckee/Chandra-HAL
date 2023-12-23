#ifndef CHANDRA_ICM42688_H
#define CHANDRA_ICM42688_H

#include <cmath>
#include "chrono.h"
#include "inertial.h"
#include "math_conversions.h"
#include "meta_types.h"
#include "register_device.h"
#include "sensor_utils.h"
#include "spi.h"
#include "thermal.h"
#include "timing.h"

// TODO: FIGURE OUT HOW THIS CAN BE SPECIALIZED FOR LSM6DSM, LSM6DS3, LSM6DS...
//  ARE THERE DIFFERENCES IN THE REGISTER MAP?  IF SO, HOW LARGE ARE THEY? DO
//  THOSE DIFFERENCES REQUIRE DIFFRENT ALGORITHMS?

namespace chandra
{
namespace drivers
{
namespace internal
{

template<class Value, class BaseUnits, class Comm>
class ICM42688ImplBase : public chandra::drivers::internal::BaseInertialProxyImpl<Value, BaseUnits>
{
  public:
    using scalar_t = Value;

    // Register Access Type
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    ICM42688ImplBase(const register_access_t& _regs, const scalar_t& _scale)
      : regs_(_regs), scale_(_scale) {}

    // Register Addresses
    //  Bank 0 Values
    enum bank0_t {
        DEVICE_CONFIG = 0x11,
        DRIVE_CONFIG = 0x13,
        INT_CONFIG = 0x14,
        FIFO_CONFIG = 0x16,
        TEMP_H = 0x1D,
        TEMP_L = 0x1E,
        ACCEL_X_H = 0x1F,
        ACCEL_X_L = 0x20,
        ACCEL_Y_H = 0x21,
        ACCEL_Y_L = 0x22,
        ACCEL_Z_H = 0x23,
        ACCEL_Z_L = 0x24,
        GYRO_X_H = 0x25,
        GYRO_X_L = 0x26,
        GYRO_Y_H = 0x27,
        GYRO_Y_L = 0x28,
        GYRO_Z_H = 0x29,
        GYRO_Z_L = 0x2A,
        TMST_FSYNC_H = 0x2B,
        TMST_FSYNC_L = 0x2C,
        INT_STATUS1 = 0x2D,
        FIFO_COUNT_H = 0x2E,
        FIFO_COUNT_L = 0x2F,
        FIFO_DATA = 0x30,
        APEX_DATA0 = 0x31,
        APEX_DATA1 = 0x32,
        APEX_DATA2 = 0x33,
        APEX_DATA3 = 0x34,
        APEX_DATA4 = 0x35,
        APEX_DATA5 = 0x36,
        INT_STATUS2 = 0x37,
        INT_STATUS3 = 0x38,
        SIGNAL_PATH_RESET = 0x4B,
        INTF_CONFIG0 = 0x4C,
        INTF_CONFIG1 = 0x4D,
        PWR_MGMT0 = 0x4E,
        GYRO_CONFIG0 = 0x4F,
        ACCEL_CONFIG0 = 0x50,
        GYRO_CONFIG1 = 0x51,
        GYRO_ACCEL_CONFIG0 = 0x52,
        ACCEL_CONFIG1 = 0x53,
        TMST_CONFIG = 0x54,
        APEX_CONFIG0 = 0x56,
        SMD_CONFIG = 0x57,
        FIFO_CONFIG1 = 0x5F,
        FIFO_CONFIG2 = 0x60,
        FIFO_CONFIG3 = 0x61,
        FSYNC_CONFIG = 0x62,
        INT_CONFIG0 = 0x63,
        INT_CONFIG1 = 0x64,
        INT_SOURCE0 = 0x65,
        INT_SOURCE1 = 0x66,
        INT_SOURCE3 = 0x68,
        INT_SOURCES = 0x69,
        FIFO_LOST_PKT0 = 0x6C,
        FIFO_LOST_PKT1 = 0x6D,
        SELF_TEST_CONFIG = 0x70,
        WHO_AM_I = 0x75,
        BANK_SEL = 0x76
    };

    enum bank1_t {
      SENSOR_CONFIG0 = 0x03,
      GYRO_CONFIG_STATIC2 = 0x0B,
      GYRO_CONFIG_STATIC3 = 0x0C,
      GYRO_CONFIG_STATIC4 = 0x0D,
      GYRO_CONFIG_STATIC5 = 0x0E,
      GYRO_CONFIG_STATIC6 = 0x0F,
      GYRO_CONFIG_STATIC7 = 0x10,
      GYRO_CONFIG_STATIC8 = 0x11,
      GYRO_CONFIG_STATIC9 = 0x12,
      GYRO_CONFIG_STATIC10 = 0x13,
      GYRO_SELF_TEST_X = 0x5F,
      GYRO_SELF_TEST_Y = 0x60,
      GYRO_SELF_TEST_Z = 0x61,
      TMST_L = 0x62,
      TMST_M = 0x63,
      TMST_H = 0x64,
      INTF_CONFIG4 = 0x7A,
      INTF_CONFIG5 = 0x7B,
      INTF_CONFIG6 = 0x7C,
    };

    enum bank2_t {
      ACCEL_CONFIG_STATIC2 = 0x03,
      ACCEL_CONFIG_STATIC3 = 0x04,
      ACCEL_CONFIG_STATIC4 = 0x05,
      ACCEL_SELF_TEST_X = 0x0E,
      ACCEL_SELF_TEST_Y = 0x0F,
      ACCEL_SELF_TEST_Z = 0x10,
    };

    enum bank4_t {
      APEX_CONFIG1 = 0x40,
      APEX_CONFIG2 = 0x41,
      APEX_CONFIG3 = 0x42,
      APEX_CONFIG4 = 0x43,
      APEX_CONFIG5 = 0x44,
      APEX_CONFIG6 = 0x45,
      APEX_CONFIG7 = 0x46,
      APEX_CONFIG8 = 0x47,
      APEX_CONFIG9 = 0x48,
      ACCEL_WOM_THRESH_X = 0x4A,
      ACCEL_WOM_THRESH_Y = 0x4B,
      ACCEL_WOM_THRESH_Z = 0x4C,
      INT_SOURCE6 = 0x4D,
      INT_SOURCE7 = 0x4E,
      INT_SOURCE8 = 0x4F,
      INT_SOURCE9 = 0x50,
      INT_SOURCE10 = 0x51,
      OFFSET0 = 0x77,
      OFFSET1 = 0x78,
      OFFSET2 = 0x79,
      OFFSET3 = 0x7A,
      OFFSET4 = 0x7B,
      OFFSET5 = 0x7C,
      OFFSET6 = 0x7D,
      OFFSET7 = 0x7E,
      OFFSET8 = 0x7F,
    };

    constexpr scalar_t scale() const { return scale_; }

  protected:
      constexpr uint32_t log2(uint32_t x) const {
        //return __builtin_ctz (x);
        uint32_t count = 0;
        while(x){
            x >>= 1;
            ++count;
        }
        return count;
      }

      constexpr uint8_t calcOdrBits(const Value& _freq) const {
        uint8_t bits(0);
        if(_freq == 0) {
            bits = 0x00;
        } else {
            const auto div = _freq / 13;
            bits = log2(div) + 1;
        }
        return bits;
      }

      constexpr uint32_t calcOdrFreq(const uint8_t& bits) const {
        return (bits == 0) ? 0 : (13 * (1UL << (bits-1UL)));
      }

      register_access_t regs_;
      scalar_t scale_;
};

template<class Value, class BaseUnits, class Comm>
class ICM42688AccelImpl : public ICM42688ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = ICM42688ImplBase<Value, BaseUnits, Comm>;
    using bank0_t = typename base_t::bank0_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    ICM42688AccelImpl(const register_access_t& _regs)
      : base_t(_regs, 4.788403e-3) {}

    scalar_t set_fs(scalar_t fs) {
        static constexpr scalar_t accel_2(2.181662);
        static constexpr scalar_t accel_4(4.363323);
        static constexpr scalar_t accel_8(8.726646);
        static constexpr scalar_t accel_16(17.453293);
        scalar_t actual(accel_16);
        uint8_t bits(0);

        if(fs >= accel_8) { // 16 gees
            actual = accel_16;
            this->scale_ = scalar_t(4.788403e-3);
            bits = 0x01<<2;
        } else if(fs >= accel_4) { // 8 gees
            actual = accel_8;
            this->scale_ = scalar_t(2.394202e-3);
            bits = 0x03<<2;
        } else if(fs >= accel_2) { // 4 gees
            actual = accel_4;
            this->scale_ = scalar_t(1.197101e-3);
            bits = 0x02<<2;
        } else { // 2 gees
            this->scale_ = scalar_t(5.985504e-4);
        }
        // this->regs_.update(bank0_t::CTRL1_XL, 0x03<<2, bits);

        return actual;
    }

    scalar_t get_fs() const {
        static constexpr scalar_t accel_2(2.181662);
        static constexpr scalar_t accel_4(4.363323);
        static constexpr scalar_t accel_8(8.726646);
        static constexpr scalar_t accel_16(17.453293);
        // const uint8_t bits = uint8_t(this->regs_.byte(bank0_t::CTRL1_XL)>>2) & uint8_t(0x03);
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
        return accel_2;
    }

    scalar_t set_odr(scalar_t _freq) {
        const uint8_t bits = this->calcOdrBits(_freq);
        // this->regs_.update(bank0_t::CTRL1_XL, 0xF0, static_cast<uint8_t>(bits<<4));
        return this->calcOdrFreq(bits);
    }

    scalar_t get_odr() const {
        // const uint8_t bits = uint8_t(this->regs_.byte(bank0_t::CTRL1_XL) >> 4) & 0x0F;
        // return this->calcOdrFreq(bits);
        return 0;
    }

  protected:
    scalar_t accel_scale_;
};

template<class Value, class BaseUnits, class Comm>
class ICM42688GyroImpl : public ICM42688ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = ICM42688ImplBase<Value, BaseUnits, Comm>;
    using bank0_t = typename base_t::bank0_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    ICM42688GyroImpl(const register_access_t& _regs)
      : base_t(_regs, 1.065264e-3) {}

    scalar_t set_fs(scalar_t fs) {
        static constexpr scalar_t gyro_15_625(chandra::math::radians(15.625));
        static constexpr scalar_t gyro_31_25(chandra::math::radians(31.25));
        static constexpr scalar_t gyro_62_5(chandra::math::radians(62.5));
        static constexpr scalar_t gyro_125(2.181662);
        static constexpr scalar_t gyro_250(4.363323);
        static constexpr scalar_t gyro_500(8.726646);
        static constexpr scalar_t gyro_1000(17.453293);
        static constexpr scalar_t gyro_2000(34.906585);
        scalar_t actual(gyro_125);
        uint8_t bits = 0x00;

        if(fs >= gyro_1000) { // 2000 dps
            actual = gyro_2000;
            this->scale_ = scalar_t(1.065264e-3);
            bits = 0x06<<1;
        } else if(fs >= gyro_500) { // 1000 dps
            actual = gyro_1000;
            this->scale_ = scalar_t(5.326322e-4);
            bits = 0x04<<1;
        } else if(fs >= gyro_250) { // 500 dps
            actual = gyro_500;
            this->scale_ = scalar_t(2.663161e-4);
            bits = 0x02<<1;
        } else if(fs >= gyro_125) { // 250 dps
            actual = gyro_250;
            this->scale_ = scalar_t(1.331581e-4);
            bits = 0x01<<1;
        } else { // 125 dps
            this->scale_ = scalar_t(6.657903e-5);
        }
        // this->regs_.update(bank0_t::CTRL2_G, 0x07<<1, bits);
        return actual;
    }

    scalar_t get_fs() const {
        static constexpr scalar_t gyro_125(2.181662);
        static constexpr scalar_t gyro_250(4.363323);
        static constexpr scalar_t gyro_500(8.726646);
        static constexpr scalar_t gyro_1000(17.453293);
        static constexpr scalar_t gyro_2000(34.906585);
        // const uint8_t bits = uint8_t(this->regs_.byte(bank0_t::CTRL2_G)>>1) & uint8_t(0x07);
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
        const uint8_t bits = this->calcOdrBits(_freq);
        // this->regs_.update(bank0_t::CTRL2_G, 0xF0, static_cast<uint8_t>(bits<<4));
        return this->calcOdrFreq(bits);
    }

    scalar_t get_odr() const {
        // const uint8_t bits = uint8_t(this->regs_.byte(bank0_t::CTRL2_G) >> 4) & 0x0F;
        // return this->calcOdrFreq(bits);
        return 0;
    }

  protected:
    scalar_t gyro_scale_;
};

} /*namespace internal*/

template<
  class Value,
  class Comm = chandra::io::SPIMaster,
  class AccelUnits = units::mks::m_per_s2,
  class GyroUnits = units::mks::rad_per_s,
  class TempUnits = units::mks::degC
>
class ICM42688
        : public AccelGyro<ICM42688<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::ICM42688AccelImpl<Value, AccelUnits, Comm>, internal::ICM42688GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>,
          public Thermometer<ICM42688<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, TempUnits>
{
    protected:
        using register_access_t = chandra::drivers::RegisterDevice<Comm>;
        using bank0_t = typename internal::ICM42688AccelImpl<Value, AccelUnits, Comm>::bank0_t;

    public:
        friend class AccelGyro<ICM42688<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::ICM42688AccelImpl<Value, AccelUnits, Comm>, internal::ICM42688GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>;
        using base_t = AccelGyro<ICM42688<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::ICM42688AccelImpl<Value, AccelUnits, Comm>, internal::ICM42688GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>;
        using scalar_t = typename base_t::scalar_t;
        //using value_t = typename base_t::value_t;
        using ref_t = ICM42688<Value, Comm, AccelUnits, GyroUnits, TempUnits>;
        using status_t = chandra::drivers::SensorUpdateStatus<>;

        ICM42688(register_access_t _regs) : base_t(_regs), regs_(_regs) {}

        bool init() {
          return enable(true) and valid();
        }

        bool enable(bool _enable) {
          constexpr static uint8_t mask{0x0F};
          if(_enable) {
            regs_.update(bank0_t::PWR_MGMT0, mask, uint8_t{0x0F});
            chandra::chrono::delay(std::chrono::microseconds(200));
          } else {
            regs_.update(bank0_t::PWR_MGMT0, mask, uint8_t{0x00});
          }

          return enabled();
        }

        bool enabled() {
          constexpr static uint8_t mask{0x0F};
          return (regs_.byte(bank0_t::PWR_MGMT0)&mask) != 0;
        }

        bool valid() {
          // TODO: CHECK FOR VALID ID AND RUN VALID SELF-TEST???
          return id() == 0x47;
        }

        uint8_t id() {
        	const auto val = regs_.byte(bank0_t::WHO_AM_I);
        	return val;
        }

        status_t update() {
            status_t status;
            constexpr uint8_t read_num = 14;
            static uint8_t buffer[read_num];
            const auto accel_scale = this->accelerometer.scale();
            const auto gyro_scale = this->gyroscope.scale();

            // NOTE: THIS IS JUST CHECKING THE DATA READ BIT IN THE STATUS REGISTER
            if(chandra::is_bit_set<3>(regs_.byte(bank0_t::INT_STATUS1))) {
              regs_.bytes(bank0_t::TEMP_H, read_num, buffer);

              this->accel_raw_.x = chandra::units::mks::Q_m_per_s2<scalar_t>(accel_scale * val16(buffer[0], buffer[1]));
              this->accel_raw_.y = chandra::units::mks::Q_m_per_s2<scalar_t>(accel_scale * val16(buffer[2], buffer[3]));
              this->accel_raw_.z = chandra::units::mks::Q_m_per_s2<scalar_t>(accel_scale * val16(buffer[4], buffer[5]));

              this->temp_raw_= convertTemp(val16(buffer[6], buffer[7]));

              this->gyro_raw_.x = chandra::units::mks::Q_rad_per_s<scalar_t>(gyro_scale * val16(buffer[8], buffer[9]));
              this->gyro_raw_.y = chandra::units::mks::Q_rad_per_s<scalar_t>(gyro_scale * val16(buffer[10], buffer[11]));
              this->gyro_raw_.z = chandra::units::mks::Q_rad_per_s<scalar_t>(gyro_scale * val16(buffer[12], buffer[13]));

//              this->temp_raw_= convertTemp(val16(buffer[0], buffer[1]));
//              const auto ax = accel_scale * val16(buffer[2], buffer[3]);
//              const auto ay = accel_scale * val16(buffer[4], buffer[5]);
//              const auto az = accel_scale * val16(buffer[6], buffer[7]);
//              this->accel_raw_ = value_t({ax, ay, az});
//              const auto gx = gyro_scale * val16(buffer[8], buffer[9]);
//              const auto gy = gyro_scale * val16(buffer[10], buffer[11]);
//              const auto gz = gyro_scale * val16(buffer[12], buffer[13]);
//              this->gyro_raw_ = value_t({gx, gy, gz});
              status.processed = true;
            }
            //update_status.errors = SensorUpdateStatus::TimeoutError;
            //update_status.errors = SensorUpdateStatus::ArithmeticError;
            return status;
        }

    protected:
        void setRegisterBank(const uint8_t& _bank) {
          regs_.write(bank0_t::BANK_SEL, _bank);
          return;
        }

        static constexpr auto convertTemp(int16_t x) {
            constexpr scalar_t scale(1/132.48);
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
        chandra::chrono::Timer<> sample_timer_;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_ICM42688_H*/
