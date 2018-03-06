#ifndef CHANDRA_INEMO_H
#define CHANDRA_INEMO_H


#include "chrono.h"
#include "inertial.h"
#include "register_device.h"
#include "sensor_utils.h"
#include "spi.h"
#include "thermal.h"
#include "timing.h"

namespace chandra
{
namespace drivers
{

// TODO: THIS NEEDS TO DERIVE FROM ACCELGYRO
template<typename Value, typename Comm = chandra::io::SPIMaster>
class LSM6DSM
        : public AccelGyro<LSM6DSM<Value, Comm>, Value, 3>,
          public Thermometer<LSM6DSM<Value, Comm>, Value>
{
    protected:
        using register_access_t = chandra::drivers::RegisterDevice<Comm>;

    public:
        friend class AccelGyro<LSM6DSM<Value, Comm>, Value, 3>;
        using base_t = AccelGyro<LSM6DSM<Value, Comm>, Value, 3>;
        using scalar_t = typename base_t::scalar_t;
        using value_t = typename base_t::value_t;
        using ref_t = LSM6DSM<Value, Comm>;

        // Register Addresses
        enum registers_t {
            FUNC_CFG_ACCESS = 0X01,
            SENSOR_SYNC_TIME_FRAME = 0X04,
            SENSOR_SYNC_RES_RATIO = 0X05,
            FIFO_CTRL1 = 0x06,
            FIFO_CTRL2 = 0x07,
            FIFO_CTRL3 = 0x08,
            FIFO_CTRL4 = 0x09,
            FIFO_CTRL5 = 0x0A,
            DRDY_PULSE_CFG = 0x0B,
            INT1_CTRL = 0x0D,
            INT2_CTRL = 0x0E,
            WHO_AM_I = 0x0F,
            CTRL1_XL = 0x10,
            CTRL2_G = 0x11,
            CTRL3_C = 0x12,
            CTRL4_C = 0x13,
            CTRL5_C = 0x14,
            CTRL6_C = 0x15,
            CTRL7_G = 0x16,
            CTRL8_XL = 0x17,
            CTRL9_XL = 0x18,
            CTRL10_C = 0x19,
            MASTER_CONFIG = 0x1A,
            WAKE_UP_SRC = 0x1B,
            TAP_SRC = 0x1C,
            D6D_SRC = 0x1D,
            STATUS_REG = 0x1E, // ALSO STATUS_SPIaux
            OUT_TEMP_L = 0x20,
            OUT_TEMP_H = 0x21,
            OUTX_L_G = 0x22,
            OUTX_H_G = 0x23,
            OUTY_L_G = 0x24,
            OUTY_H_G = 0x25,
            OUTZ_L_G = 0x26,
            OUTZ_H_G = 0x27,
            OUTX_L_XL = 0x28,
            OUTX_H_XL = 0x29,
            OUTY_L_XL = 0x2A,
            OUTY_H_XL = 0x2B,
            OUTZ_L_XL = 0x2C,
            OUTZ_H_XL = 0x2D,
            // TODO: Sensor hub registers 0x2e - 0x39
            FIFO_STATUS1 = 0x3A,
            FIFO_STATUS2 = 0x3B,
            FIFO_STATUS3 = 0x3C,
            FIFO_STATUS4 = 0x3D,
            FIFO_DATA_OUT_L = 0x3E,
            FIFO_DATA_OUT_H = 0x3F,
            TIMESTAMP0_REG = 0x40,
            TIMESTAMP1_REG = 0x41,
            TIMESTAMP2_REG = 0x42,
            // Reserved 0x43 - 0x48
            // TODO: Step and Sensor hub registers 0x49 - 0x52
            FUNC_SRC1 = 0x53,
            FUNC_SRC2 = 0x54
            // TODO: Remainder of Registers
        };

        LSM6DSM(register_access_t _regs) : regs_(_regs) {}

        bool enable(bool) {
            // Configure Device
            //writeRegister(INT1_CTRL, 0x01); // Use Int1 for XL DRDY
            //writeRegister(INT2_CTRL, 0x02); // Use Int2 for G DRDY

            // Configure Scale Factors
            accel_scale_ = 5.98e-4;
            gyro_scale_ = 1.33e-4;

            return id() == 0x6A;
        }

        // TODO: THIS SHOULD HAVE AN ENABLE FUNCTION (WHICH IS CALLED BY DEFAULT FROM THE INIT)

        uint8_t id() { return regs_.byte(WHO_AM_I); }

        SensorUpdateStatus update() {
            SensorUpdateStatus status;
            constexpr uint8_t read_num = 14;
            static uint8_t buffer[read_num];
            //if( sample_timer_.expired(Timer::AUTO_RESET)) {
            regs_.bytes(OUT_TEMP_L, read_num, buffer);
            this->temp_raw_= convertTemp(val16(buffer[1], buffer[0]));
            const auto gx = gyro_scale_ * val16(buffer[3], buffer[2]);
            const auto gy = gyro_scale_ * val16(buffer[5], buffer[4]);
            const auto gz = gyro_scale_ * val16(buffer[7], buffer[6]);
            this->gyro_raw_ = value_t({gx, gy, gz});
            const auto ax = accel_scale_ * val16(buffer[9], buffer[8]);
            const auto ay = accel_scale_ * val16(buffer[11], buffer[10]);
            const auto az = accel_scale_ * val16(buffer[13], buffer[12]);
            this->accel_raw_ = value_t({ax, ay, az});
            status.updated = true;
            //}
            //update_status.errors = SensorUpdateStatus::TimeoutError;
            //update_status.errors = SensorUpdateStatus::ArithmeticError;
            return status;
        }

    protected:
        template<typename T> struct TD;

        static constexpr auto convertTemp(int16_t x) {
            constexpr scalar_t scale(0.00390625);
            constexpr scalar_t offset(25.0);
            return (scale*x) + offset;
        }

        static constexpr auto val16(uint32_t h, uint8_t l) {
            return static_cast<int16_t>((h<<8)|l);
        }

        static constexpr uint32_t log2(uint32_t x) {
            //return __builtin_ctz (x);
            uint32_t count = 0;
            while(x){
                x >>= 1;
                ++count;
            }
            return count;
        }

        static constexpr uint8_t calcOdrBits(const Value& _freq) {
            uint8_t bits(0);
            if(_freq == 0) {
                bits = 0x00;
            } else {
                const auto div = _freq / 13;
                bits = log2(div) + 1;
            }
            return bits;
        }

        static constexpr uint32_t calcOdrFreq(const uint8_t& bits) {
            return (bits == 0) ? 0 : (13 * (1UL << (bits-1UL)));
        }

        //
        // Proxy Callbacks
        //
        //  Accelerometer Callbacks
        scalar_t set_accel_fs(scalar_t fs) {
            static constexpr scalar_t accel_2(2.181662);
            static constexpr scalar_t accel_4(4.363323);
            static constexpr scalar_t accel_8(8.726646);
            static constexpr scalar_t accel_16(17.453293);
            scalar_t actual(accel_2);
            uint8_t bits(0);

            if(fs >= accel_8) { // 16 gees
                actual = accel_16;
                accel_scale_ = scalar_t(4.788403e-3);
                bits = 0x06<<2;
            } else if(fs >= accel_4) { // 8 gees
                actual = accel_8;
                accel_scale_ = scalar_t(2.394202e-3);
                bits = 0x04<<2;
            } else if(fs >= accel_2) { // 4 gees
                actual = accel_4;
                accel_scale_ = scalar_t(1.197101e-3);
                bits = 0x02<<2;
            } else { // 2 gees
                accel_scale_ = scalar_t(5.985504e-4);
            }
            regs_.update(CTRL1_XL, 0x03<<2, bits);

            return actual;
        }
        scalar_t get_accel_fs() const {
            static constexpr scalar_t accel_2(2.181662);
            static constexpr scalar_t accel_4(4.363323);
            static constexpr scalar_t accel_8(8.726646);
            static constexpr scalar_t accel_16(17.453293);
            const uint8_t bits = uint8_t(regs_.byte(CTRL1_XL)>>2) & uint8_t(0x03);

            switch(bits) {
                case 0x00:
                default:
                    return accel_2;
                case 0x01:
                    return accel_16;
                case 0x02:
                    return accel_4;
                case 0x03:
                    return accel_8;
            }
        }
        scalar_t set_accel_odr(scalar_t _freq) {
            const uint8_t bits = calcOdrBits(_freq);
            regs_.update(CTRL1_XL, 0xF0, static_cast<uint8_t>(bits<<4));
            return calcOdrFreq(bits);
        }
        scalar_t get_accel_odr() const {
            const uint8_t bits = uint8_t(regs_.byte(CTRL1_XL) >> 4) & 0x0F;
            return calcOdrFreq(bits);
        }

        scalar_t set_accel_lpf(scalar_t) { return 0; }
        scalar_t get_accel_lpf() const { return 0; }

        scalar_t set_accel_hpf(scalar_t) { return 0; }
        scalar_t get_accel_hpf() const { return 0;}

        //  Gyroscope Callbacks
        scalar_t set_gyro_fs(scalar_t fs) {
            static constexpr scalar_t gyro_125(2.181662);
            static constexpr scalar_t gyro_250(4.363323);
            static constexpr scalar_t gyro_500(8.726646);
            static constexpr scalar_t gyro_1000(17.453293);
            static constexpr scalar_t gyro_2000(34.906585);
            scalar_t actual(gyro_125);
            uint8_t bits = 0x00;

            if(fs >= gyro_1000) { // 2000 dps
                actual = gyro_2000;
                gyro_scale_ = scalar_t(1.065264e-3);
                bits = 0x06<<1;
            } else if(fs >= gyro_500) { // 1000 dps
                actual = gyro_1000;
                gyro_scale_ = scalar_t(5.326322e-4);
                bits = 0x04<<1;
            } else if(fs >= gyro_250) { // 500 dps
                actual = gyro_500;
                gyro_scale_ = scalar_t(2.663161e-4);
                bits = 0x02<<1;
            } else if(fs >= gyro_125) { // 250 dps
                actual = gyro_250;
                gyro_scale_ = scalar_t(1.331581e-4);
                bits = 0x01<<1;
            } else { // 125 dps
                gyro_scale_ = scalar_t(6.657903e-5);
            }
            regs_.update(CTRL2_G, 0x07<<1, bits);
            return actual;
        }
        scalar_t get_gyro_fs() const {
            static constexpr scalar_t gyro_125(2.181662);
            static constexpr scalar_t gyro_250(4.363323);
            static constexpr scalar_t gyro_500(8.726646);
            static constexpr scalar_t gyro_1000(17.453293);
            static constexpr scalar_t gyro_2000(34.906585);
            const uint8_t bits = uint8_t(regs_.byte(CTRL2_G)>>1) & uint8_t(0x07);

            switch(bits) {
                case 0x00:
                default:
                    return gyro_125;
                case 0x01:
                    return gyro_250;
                case 0x02:
                    return gyro_500;
                case 0x04:
                    return gyro_1000;
                case 0x06:
                    return gyro_2000;
            }
        }

        scalar_t set_gyro_odr(scalar_t _freq) {
            const uint8_t bits = calcOdrBits(_freq);
            regs_.update(CTRL2_G, 0xF0, static_cast<uint8_t>(bits<<4));
            return calcOdrFreq(bits);
        }
        scalar_t get_gyro_odr() const {
            const uint8_t bits = uint8_t(regs_.byte(CTRL2_G) >> 4) & 0x0F;
            return calcOdrFreq(bits);
        }

        scalar_t set_gyro_lpf(scalar_t) { return 0;}
        scalar_t get_gyro_lpf() const { return 0; }

        scalar_t set_gyro_hpf(scalar_t) { return 0; }
        scalar_t get_gyro_hpf() const { return 0; }

    private:
        register_access_t regs_;
        //Timer sample_timer_;
        //int16_t raw_accelerations_[3];
        //int16_t raw_gyroscopes_[3];
        //uint16_t raw_temperature_;
        scalar_t accel_scale_;
        scalar_t gyro_scale_;
        //value_t accel_divisor_; // TODO: DECIDE IF THESE SAME VALUE TYPES SHOULD BE USED FOR ACCELEROMETER AND GYROSCOPE
        //value_t gyro_divisor_;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_INEMO_H*/

