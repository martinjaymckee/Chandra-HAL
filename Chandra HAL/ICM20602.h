#ifndef CHANDRA_ICM20602_H
#define CHANDRA_ICM20602_H

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

#include "units.h"
using namespace chandra::units::mks::literals;

namespace chandra
{
namespace drivers
{
namespace internal
{

template<class Value, class BaseUnits, class Comm>
class ICM20602ImplBase : public chandra::drivers::internal::BaseInertialProxyImpl<Value, BaseUnits>
{
  public:
    using scalar_t = Value;

    // Register Access Type
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    ICM20602ImplBase(const register_access_t& _regs, const scalar_t& _scale)
      : regs_(_regs), scale_(_scale) {}

    // Register Addresses
    enum register_t {
//        DEVICE_CONFIG = 0x11,
//        DRIVE_CONFIG = 0x13,
//        INT_CONFIG = 0x14,
//        FIFO_CONFIG = 0x16,

		SAMPLE_RATE_DIV = 0x19,
		CONFIG = 0x1A,
		GYRO_CONFIG = 0x1B,
		ACCEL_CONFIG_1 = 0x1C,
		ACCEL_CONFIG_2 = 0x1D,

		FIFO_ENABLE = 0x23,



        ACCEL_X_H = 0x3B,
        ACCEL_X_L = 0x3C,
        ACCEL_Y_H = 0x3D,
        ACCEL_Y_L = 0x3E,
        ACCEL_Z_H = 0x3F,
        ACCEL_Z_L = 0x40,
        TEMP_H = 0x41,
        TEMP_L = 0x42,
        GYRO_X_H = 0x43,
        GYRO_X_L = 0x44,
        GYRO_Y_H = 0x45,
        GYRO_Y_L = 0x46,
        GYRO_Z_H = 0x47,
        GYRO_Z_L = 0x48,

        INT_STATUS = 0x3A,

		USER_CTRL = 0x6A,
        PWR_MGMT_1 = 0x6B,
        PWR_MGMT_2 = 0x6C,
        I2C_IF = 0x70,
        WHO_AM_I = 0x75
        // TODO: FILL IN THE REMAINDER OF THE REGISTERS
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
class ICM20602AccelImpl : public ICM20602ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = ICM20602ImplBase<Value, BaseUnits, Comm>;
    using register_t = typename base_t::register_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    ICM20602AccelImpl(const register_access_t& _regs)
      : base_t(_regs, 4.788403e-3) {
    	this->scale_ = scalar_t(4.788403e-3);
    }

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
        // this->regs_.update(register_t::CTRL1_XL, 0x03<<2, bits);

        return actual;
    }

    scalar_t get_fs() const {
        static constexpr scalar_t accel_2(2.181662);
        static constexpr scalar_t accel_4(4.363323);
        static constexpr scalar_t accel_8(8.726646);
        static constexpr scalar_t accel_16(17.453293);
        // const uint8_t bits = uint8_t(this->regs_.byte(register_t::CTRL1_XL)>>2) & uint8_t(0x03);
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
        return this->scale_;
    }

    scalar_t set_odr(scalar_t _freq) {
        const uint8_t bits = this->calcOdrBits(_freq);
        // this->regs_.update(register_t::CTRL1_XL, 0xF0, static_cast<uint8_t>(bits<<4));
        return this->calcOdrFreq(bits);
    }

    scalar_t get_odr() const {
        // const uint8_t bits = uint8_t(this->regs_.byte(register_t::CTRL1_XL) >> 4) & 0x0F;
        // return this->calcOdrFreq(bits);
        return 0;
    }
};

template<class Value, class BaseUnits, class Comm>
class ICM20602GyroImpl : public ICM20602ImplBase<Value, BaseUnits, Comm>
{
  public:
    using scalar_t = Value;
    using base_t = ICM20602ImplBase<Value, BaseUnits, Comm>;
    using register_t = typename base_t::register_t;
    using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    ICM20602GyroImpl(const register_access_t& _regs)
      : base_t(_regs, 1.331581e-4) {
    	this->scale_ = scalar_t(1.331581e-4);
    }

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

//        this->regs_.update(register_t::CTRL2_G, 0x07<<1, bits);
        return actual;
    }

    scalar_t get_fs() const {
        static constexpr scalar_t gyro_125(2.181662);
        static constexpr scalar_t gyro_250(4.363323);
        static constexpr scalar_t gyro_500(8.726646);
        static constexpr scalar_t gyro_1000(17.453293);
        static constexpr scalar_t gyro_2000(34.906585);
        // const uint8_t bits = uint8_t(this->regs_.byte(register_t::CTRL2_G)>>1) & uint8_t(0x07);
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
        return this->scale_;
    }

    scalar_t set_odr(scalar_t _freq) {
        const uint8_t bits = this->calcOdrBits(_freq);
        // this->regs_.update(register_t::CTRL2_G, 0xF0, static_cast<uint8_t>(bits<<4));
        return this->calcOdrFreq(bits);
    }

    scalar_t get_odr() const {
        // const uint8_t bits = uint8_t(this->regs_.byte(register_t::CTRL2_G) >> 4) & 0x0F;
        // return this->calcOdrFreq(bits);
        return 0;
    }
};

} /*namespace internal*/

template<
  class Value,
  class Comm = chandra::io::SPIMaster,
  class AccelUnits = units::mks::m_per_s2,
  class GyroUnits = units::mks::rad_per_s,
  class TempUnits = units::mks::degC
>
class ICM20602
        : public AccelGyro<ICM20602<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::ICM20602AccelImpl<Value, AccelUnits, Comm>, internal::ICM20602GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>,
          public Thermometer<ICM20602<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, TempUnits>
{
    protected:
        using register_access_t = chandra::drivers::RegisterDevice<Comm>;
        using register_t = typename internal::ICM20602AccelImpl<Value, AccelUnits, Comm>::register_t;

    public:
        friend class AccelGyro<ICM20602<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::ICM20602AccelImpl<Value, AccelUnits, Comm>, internal::ICM20602GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>;
        using base_t = AccelGyro<ICM20602<Value, Comm, AccelUnits, GyroUnits, TempUnits>, Value, internal::ICM20602AccelImpl<Value, AccelUnits, Comm>, internal::ICM20602GyroImpl<Value, GyroUnits, Comm>, 3, AccelUnits, GyroUnits>;
        using scalar_t = typename base_t::scalar_t;
 //       using value_t = typename base_t::value_t;
        using ref_t = ICM20602<Value, Comm, AccelUnits, GyroUnits, TempUnits>;
        using status_t = chandra::drivers::SensorUpdateStatus<>;
        ICM20602(register_access_t _regs) : base_t(_regs), regs_(_regs) {}

        bool init() {
          chandra::chrono::delay(std::chrono::microseconds(2000)); // Wait for reset
          regs_.write(register_t::I2C_IF, uint8_t{1<<6});
          regs_.write(register_t::USER_CTRL, uint8_t{0x00});
          regs_.write(register_t::FIFO_ENABLE, uint8_t{0x00});

          if(valid() and enable(true)) {
        	  //this->accelerometer.fullscale(16_gees_);
        	  //this->gyroscope.fullscale(2000_deg_per_s_);
        	  regs_.write(register_t::CONFIG, uint8_t{0x02}); // DLPF_CFG = 2 for 92 Hz BW
//        	  regs_.write(register_t::CONFIG, uint8_t{0x00}); // DLPF_CFG = 0 for 250 Hz BW
//        	  regs_.write(register_t::GYRO_CONFIG, uint8_t{0x03<<3}); // FS = +/- 2000 deg/s
        	  regs_.write(register_t::GYRO_CONFIG, uint8_t{0x00}); // FS = +/- 250 deg/s
        	  regs_.write(register_t::ACCEL_CONFIG_1, uint8_t{0x03<<3}); // FS = +/- 16 g
        	  regs_.write(register_t::ACCEL_CONFIG_2, uint8_t{0x02}); // DLPF_CFG = 2 for 99Hz BW
//      	    regs_.write(register_t::ACCEL_CONFIG_2, uint8_t{0x01}); // DLPF_CFG = 1 for 218.1Hz BW

//        	  regs_.write(register_t::SAMPLE_RATE_DIV, uint8_t{255}); // NOTE: THIS SHOULD BE ROUGHLY 3.9Hz....
        	  regs_.write(register_t::SAMPLE_RATE_DIV, uint8_t{3}); // NOTE: THIS SHOULD BE ROUGHLY 250Hz....
//        	  regs_.write(register_t::SAMPLE_RATE_DIV, uint8_t{9}); // NOTE: THIS SHOULD BE ROUGHLY 100Hz....
//        	  regs_.write(register_t::SAMPLE_RATE_DIV, uint8_t{99}); // NOTE: THIS SHOULD BE ROUGHLY 10Hz....

        	  return true;
          }
          return false;
        }

        bool enable(bool _enable, const bool& _force_reset=true) {
//          constexpr uint8_t reset_mask{1<<7};
          constexpr uint8_t sleep_mask{1<<6};
//          constexpr uint8_t clock_mask{0x03};
//          constexpr static uint8_t enable_mask{sleep_mask | clock_mask};

          if(_enable) {
        	if(_force_reset) {
        		regs_.write(register_t::PWR_MGMT_1, uint8_t{(1<<7) | 0x01});
        		chandra::chrono::delay(std::chrono::microseconds(2000)); // TODO: CHECK RESET TIME
        	}

        	// Wakeup and set clock source
            regs_.write(register_t::PWR_MGMT_1, uint8_t{0x01});
            chandra::chrono::delay(std::chrono::microseconds(200)); // TODO: CHECK WAKEUP FROM SLEEP TIME

        	// Place accelerometer and gyroscope into standby
            regs_.write(register_t::PWR_MGMT_2, uint8_t{0x1F});

            // Configure accelerometer and gyroscope

            // Place accelerometer and gyroscope into active
            regs_.write(register_t::PWR_MGMT_2, uint8_t{0x00});

          } else {
            regs_.write(register_t::PWR_MGMT_1, sleep_mask);
          }

          return enabled();
        }

        bool enabled() {
          constexpr static uint8_t mask{1<<6};
          return (regs_.byte(register_t::PWR_MGMT_1) & mask) == 0x00;
        }

        bool valid() {
          // TODO: CHECK FOR VALID ID AND RUN VALID SELF-TEST???
          return id() == 0x12;
        }

        uint8_t id() { return regs_.byte(register_t::WHO_AM_I); }

        status_t update() {
            status_t status;
            constexpr uint8_t read_num = 14;
            static uint8_t buffer[read_num];
            const auto accel_scale = this->accelerometer.scale();
            const auto gyro_scale = this->gyroscope.scale();

            // NOTE: THIS IS JUST CHECKING THE DATA READ BIT IN THE STATUS REGISTER
            if(chandra::is_bit_set<0>(regs_.byte(register_t::INT_STATUS))) {
              regs_.bytes(register_t::ACCEL_X_H, read_num, buffer);
              // const auto ay = accel_scale * val16(buffer[2], buffer[3]);
              // const auto az = accel_scale * val16(buffer[4], buffer[5]);
              this->accel_raw_.x = chandra::units::mks::Q_m_per_s2<scalar_t>(accel_scale * val16(buffer[0], buffer[1]));
              this->accel_raw_.y = chandra::units::mks::Q_m_per_s2<scalar_t>(accel_scale * val16(buffer[2], buffer[3]));
              this->accel_raw_.z = chandra::units::mks::Q_m_per_s2<scalar_t>(accel_scale * val16(buffer[4], buffer[5]));

              this->temp_raw_= convertTemp(val16(buffer[6], buffer[7]));

              this->gyro_raw_.x = chandra::units::mks::Q_rad_per_s<scalar_t>(gyro_scale * val16(buffer[8], buffer[9]));
              this->gyro_raw_.y = chandra::units::mks::Q_rad_per_s<scalar_t>(gyro_scale * val16(buffer[10], buffer[11]));
              this->gyro_raw_.z = chandra::units::mks::Q_rad_per_s<scalar_t>(gyro_scale * val16(buffer[12], buffer[13]));

              // const auto gx = gyro_scale * val16(buffer[8], buffer[9]);
              // const auto gy = gyro_scale * val16(buffer[10], buffer[11]);
              // const auto gz = gyro_scale * val16(buffer[12], buffer[13]);
              // this->gyro_raw_ = value_t({gx, gy, gz});
              status.processed = true;
            } else {
            	(void) status;
            }
            //update_status.errors = SensorUpdateStatus::TimeoutError;
            //update_status.errors = SensorUpdateStatus::ArithmeticError;
            return status;
        }

    protected:
        static constexpr auto convertTemp(int16_t x) {
            constexpr scalar_t scale(1/326.8);
            constexpr scalar_t offset(25.0);
            return (scale*x) + offset; //chandra::units::mks::Q_degC<scalar_t>{(scale*x) + offset};
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

#endif /*CHANDRA_ICM20602_H*/
