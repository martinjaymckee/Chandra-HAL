#ifndef CHANDRA_INEMO_H
#define CHANDRA_INEMO_H


#include "clock.h"
#include "sensor_utils.h"
#include "spi.h"
#include "timing.h"
#include "vector.h"

namespace chandra
{
namespace io
{

// TODO: Rather than use an axis_order object, it would be nice to simply pass in an axis transformer to allow for non-orthagonal
//	axis transformations ( AS I AM GOING TO NEED FOR THE CURRENT PROJECT!)

// TODO: NEED TO BE ABLE TO CONFIGURE BOTH SCALE AND GAIN, AT THE CHIP LEVEL, AS WELL AS TO OUTPUT VALUES SCALED TO THE PROPER
//	UNITS (AS DEFINED BY THE "UNITS" LIBRARY... WHICH STILL NEEDS TO BE FOLDED IN

// TODO: NEED A SCOPED SPI MODE CHANGER SO THAT EVERY COMMAND CAN "ENABLE" THE SPI TO THE CORRECT MODE (0) AND SET IT BACK BEFORE
//	THE FUNCTION EXITS

template<class value_type, class axis_order = AxesXYZ>
class LSM6DSM
{
    protected:
        typedef axis_order axes_map_t;

    public:
        using value_t = value_type;

        using accelerations_t = Vector3D<value_t>;
        using angular_rates_t = Vector3D<value_t>;
        using temperature_t = value_t;

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

        LSM6DSM( SPIMaster& _spi, const SPIMaster::cs_t& _cs = SPIMaster::CS0 ) : spi_(_spi), cs_(_cs), sample_timer_(10000) {}

        bool init(const uint32_t& _freq = 100) {
            // Set Update Frequency
            freq(_freq);

            // Configure Device
            writeRegister(INT1_CTRL, 0x01); // Use Int1 for XL DRDY
            writeRegister(INT2_CTRL, 0x02); // Use Int2 for G DRDY

            // Configure Scale Factors
            accel_divisor_ = 16768.0; // TODO: FIX THIS VALUE... THIS SHOULD BE ADJUSTABLE -- PLACE IT IN A FUNCTION
            gyro_divisor_ = (32768.0 / 250.0); // FIX THIS VALUE... ALSO MAKE IT ADJUSTABLE IN A FUNCTION

            //return status.ok();
            return true;
        }

        // TODO: THIS SHOULD HAVE AN ENABLE FUNCTION (WHICH IS CALLED BY DEFAULT FROM THE INIT)

        bool freq(const uint32_t _freq) {
            // TODO: MAKE THIS ACTUALLY CHECK FOR VALIDITY, ETC.
            // TODO: THIS NEEDS TO UPDATE THE INTERNAL DATA-RATE TO BE LARGE ENOUGH
            uint8_t freq_bits = 0;
            if(_freq < 26) {
                freq_bits = 0x0B;
            } else {
                const auto div = _freq / 13;
                freq_bits = log2(div) + 1;
            }
            writeRegister(CTRL2_G, freq_bits<<4); // TODO: THIS SHOULD USE AN updateRegister(reg, mask, val) COMMAND
            writeRegister(CTRL1_XL, freq_bits<<4);

            sample_timer_.us(1000000UL / _freq);
            return true;
        }

        uint8_t id() { return readRegister(WHO_AM_I); } // TODO: FIGURE OUT IF IT IS POSSIBLE TO MAKE THIS CONST... RIGHT NOW THE SPI COMMANDS ARE NON-CONST

        UpdateStatus update() {
            UpdateStatus update_status;
            static const uint8_t read_num = 14;
            static const uint8_t cmd = (1<<7) | OUT_TEMP_L;
            static uint8_t buffer[read_num];
            if( sample_timer_.expired(Timer::AUTO_RESET)) {
                spi_.tx(&cmd, 1, cs_, SPIMaster::START);
                spi_.rx(buffer, read_num, cs_, SPIMaster::STOP);
                raw_temperature_ = (static_cast<uint16_t>(buffer[1])<<8)|buffer[0];
                raw_gyroscopes_[axes_map_t::x] = static_cast<int16_t>((static_cast<uint32_t>(buffer[3])<<8)|buffer[2]);
                raw_gyroscopes_[axes_map_t::y] = static_cast<int16_t>((static_cast<uint32_t>(buffer[5])<<8)|buffer[4]);
                raw_gyroscopes_[axes_map_t::z] = static_cast<int16_t>((static_cast<uint32_t>(buffer[7])<<8)|buffer[6]);
                raw_accelerations_[axes_map_t::x] = static_cast<int16_t>((static_cast<uint32_t>(buffer[9])<<8)|buffer[8]);
                raw_accelerations_[axes_map_t::y] = static_cast<int16_t>((static_cast<uint32_t>(buffer[11])<<8)|buffer[10]);
                raw_accelerations_[axes_map_t::z] = static_cast<int16_t>((static_cast<uint32_t>(buffer[13])<<8)|buffer[12]);
                update_status.updated = true;
            }

            return update_status;
        }

        accelerations_t accelerations() const { // TODO: CONSIDER ADDING THIS TO A PROCESS METHOD SO THAT IT ISN'T DONE EACH TIME THE VALUES ARE READ
            const value_t x(raw_accelerations_[0]);
            const value_t y(raw_accelerations_[1]);
            const value_t z(raw_accelerations_[2]);

            return accelerations_t(x/accel_divisor_, y/accel_divisor_, z/accel_divisor_);
        }

        angular_rates_t angularRates() const { // TODO: CONSIDER ADDING THIS TO A PROCESS METHOD SO THAT IT ISN'T DONE EACH TIME THE VALUES ARE READ
            const value_t x(raw_gyroscopes_[0]);
            const value_t y(raw_gyroscopes_[1]);
            const value_t z(raw_gyroscopes_[2]);

            return angular_rates_t(x/gyro_divisor_, y/gyro_divisor_, z/gyro_divisor_);
        }

        temperature_t temperature() const {
            return temperature_t(raw_temperature_); // TODO: NEED TO ACTUALLY PROCESS THIS!!!!!
        }

    protected: // TODO: THESE SHOULD MOVE TO A BASE CLASS....
        int log2 (uint32_t x) const {
            //return __builtin_ctz (x);
            int count = 0;
            while(x){
                x >>= 1;
                ++count;
            }
            return count;

        }

        uint8_t readRegister(const uint8_t reg) {
            const uint8_t cmd = (1<<7) | reg;
            uint8_t val = 0x12;
            spi_.tx(&cmd, 1, cs_, SPIMaster::START);
            spi_.rx(&val, 1, cs_, SPIMaster::STOP);
            return val;
        }

        void writeRegister(const uint8_t reg, const uint8_t data) {
            const uint8_t cmd[2] = {reg, data};
            spi_.tx(cmd, 2, cs_);
            return;
        }


    private:
        SPIMaster& spi_;
        SPIMaster::cs_t cs_;
        Timer sample_timer_;
        int16_t raw_accelerations_[3];
        int16_t raw_gyroscopes_[3];
        uint16_t raw_temperature_;
        value_t accel_divisor_; // TODO: DECIDE IF THESE SAME VALUE TYPES SHOULD BE USED FOR ACCELEROMETER AND GYROSCOPE
        value_t gyro_divisor_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_INEMO_H*/

