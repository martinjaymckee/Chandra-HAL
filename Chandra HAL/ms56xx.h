#ifndef CHANDRA_MS56XX_H
#define CHANDRA_MS56XX_H

#include "i2c.h"
#include "timing.h"

namespace chandra
{
namespace drivers
{

template<class Value>
class MS5637
{
  protected:
    enum update_state_t {
        PressureTrigger,
        PressureSample,
        TemperatureTrigger,
        TemperatureSample
    };

    enum calc_mode_t {
        OnPressure,
        OnTemperature,
        OnBoth
    };

    struct SampleConfig
    {
      uint8_t cmd = 0;
      uint16_t osr = 256;
      uint16_t scale = 0;
      uint32_t adc_delay_us = 0;
      chandra::chrono::Timer<> timer;
    };

  public:
    static const uint8_t addr = 0x76;

    class ValueProxy
    {
      public:
        ValueProxy(Value& _val) : val_(_val) {}

        template<class T>
        operator T () const { return static_cast<T>(val_); }

      private:
        Value& val_;
    };

    MS5637(chandra::io::I2CMaster& _i2c)
      : pressure(pressure_val_), temperature(temperature_val_), i2c_(_i2c) {}

    bool init() { // TODO: THIS FUNCTION (AND LATER THE I2C INIT FUNCTION AS WELL, NEED TO TAKE A FREQUENCY QUANTITY RATHER THAN JUST A NUMBER)
      pressure_cfg_.cmd = 0x40;
      temperature_cfg_.cmd = 0x50;

      i2c_.init(400000);
      i2c_.enable(true);

      pressure_val_ = 12;
      temperature_val_ = 34;

      loadCalibrationValues();

      updateOSRConfig(pressure_cfg_, 8192);
      updateOSRConfig(temperature_cfg_, 1024);
      updateFrequencyConfig(pressure_cfg_, 50);
      updateFrequencyConfig(temperature_cfg_, 1);

      return valid();
    }

    bool update() {
      switch(update_state_) {
        default:
        case PressureTrigger:
          if(pressure_cfg_.timer()) {
            sendCMD(pressure_cfg_.cmd);
            adc_timer_.duration(std::chrono::microseconds{pressure_cfg_.adc_delay_us});
            adc_timer_.reset();
            update_state_ = PressureSample;
          } else {
            update_state_ = TemperatureTrigger;
          }
          break;

        case PressureSample:
          if(adc_timer_()) {
            pressure_raw_ = readADC();
            update_state_ = TemperatureTrigger;
            if( (calc_mode_==OnPressure) or (calc_mode_==OnBoth) ) {
              return calculateCorrectedValues();
            }
          }
          break;

        case TemperatureTrigger:
          if(temperature_cfg_.timer()) {
            sendCMD(temperature_cfg_.cmd);
            adc_timer_.duration(std::chrono::microseconds{temperature_cfg_.adc_delay_us});
            adc_timer_.reset();
            update_state_ = TemperatureSample;
          } else {
            update_state_ = PressureTrigger;
          }
          break;

        case TemperatureSample:
          if(adc_timer_()) {
            temperature_raw_ = readADC();
            update_state_ = PressureTrigger;
            if( (calc_mode_==OnTemperature) or (calc_mode_==OnBoth) ) {
              return calculateCorrectedValues();
            }
          }
          break;
      }

      return false;
    }

    // TODO: THIS NEEDS TO BE CONST.  FIX THE CRC CALCULATION
    bool valid() { // TODO: DECIDE IF THERE IS ANYTHING ELSE THAT SHOULD BE CHECKED TO DETERMINE VALIDITY
      const uint8_t crc = (C_[0] >> 12) & 0x0F;
      return crc == crc4(C_);
    }

    ValueProxy pressure;
    ValueProxy temperature;

  protected:
    void loadCalibrationValues() {
      uint8_t bytes[2];
    	for(uint8_t idx=0; idx<7; ++idx) {
    		const uint8_t cmd_byte = 0xA0 | (idx<<1);
    		i2c_.writeCMD(addr, cmd_byte);
    		i2c_.readBytes(addr, bytes, 2);
    		C_[idx] = (static_cast<uint16_t>(bytes[0])<<8) | bytes[1];
    	}

      return;
    }

    void sendCMD(uint8_t _cmd) const {
      i2c_.writeCMD(addr, _cmd);
    }

    uint32_t readADC() const {
      uint8_t bytes[3];
      i2c_.writeCMD(addr, 0x00);
      i2c_.readBytes(addr, bytes, 3);
      return (static_cast<uint32_t>(bytes[0]) << 16) | (static_cast<uint32_t>(bytes[1]) << 8) | bytes[2];
    }

    uint8_t crc4(const uint16_t (&_C)[8]) const {
      uint16_t C[8];
      for(uint8_t cnt = 0; cnt < 8; ++cnt) {
        C[cnt] = _C[cnt];
      }
    	uint16_t rem = 0; // crc reminder

    	C[0] &= 0x0FFF;
    	C[7] = 0;

    	for (uint8_t cnt = 0; cnt < 16; cnt++) {
        const uint16_t v = C[cnt>>1];

    		if(cnt%2==1) {
    			rem ^= (v & 0x00FF);
    		} else {
    			rem ^= (v>>8);
    		}

    		for(uint8_t bit = 8; bit > 0; --bit) {
    			if(rem & (0x8000)) {
    				rem = (rem << 1) ^ 0x3000;
    			} else{
    				rem = (rem << 1);
    			}
    		}
    	}

    	return ((rem >> 12) & 0x000F); // final 4-bit reminder is CRC code
    }

    bool updateOSRConfig(SampleConfig& _cfg, const uint16_t& _osr) const {
      uint8_t shift = 0;
      _cfg.osr = 256;

    	const uint32_t us_slope = 513; // TODO: MOVE THIS TO THE TOP TO MAKE CONFIGURATION EASIER
    	const uint32_t us_offset = 34;

    	while( (_osr > _cfg.osr) and (_cfg.osr < 8192) ) {
    		++shift;
    		_cfg.osr *= 2;
    	}

    	const uint8_t scale = (1<<shift);
    	_cfg.adc_delay_us = us_slope * scale + us_offset;
    	_cfg.cmd = (_cfg.cmd & 0xF0) | (shift << 1);

    	return true;
    }

    bool updateFrequencyConfig(SampleConfig& _cfg, const uint8_t& _freq) {
      const uint32_t sample_us = 1000000UL / _freq;
      _cfg.timer.duration(std::chrono::microseconds{sample_us});
      return true;
    }

    bool calculateCorrectedValues() {
      const int64_t Tref = 256 * static_cast<int64_t>(C_[5]);
      const int64_t dT = static_cast<int64_t>(temperature_raw_) - Tref;
      const int64_t T = 2000 + ((dT * C_[6]) / 8388608LL);

      const int64_t dT2 = dT*dT;
      int64_t T2 = 0;
      int64_t off2 = 0;
      int64_t sens2 = 0;

      if( T > 2000 ) {
        T2 = (5LL * dT2) / 274877906944LL;
        // No adjustment to offset2 or sensitivity2 for temperatures above 20 degrees
      } else {
        T2 = (3LL * dT2) / 8589934592LL;
        const int64_t T_off1_sq = (T-2000) * (T-2000);
        off2 = (61LL * T_off1_sq) / 16LL;
        sens2 = (29LL *  T_off1_sq) / 16LL;
        if( T < -1500 ) {
          const int64_t T_off2_sq = (T + 1500) * (T + 1500);
          off2 += (17LL * T_off2_sq);
          sens2 += (9LL * T_off2_sq);
        }
      }

      int64_t off = (static_cast<int64_t>(C_[2])*131072LL) + ((static_cast<int64_t>(C_[4])*dT) / 64LL);
      int64_t sens = (static_cast<int64_t>(C_[1])*65536LL) + ((static_cast<int64_t>(C_[3])*dT) / 128LL);

      off -= off2;
      sens -= sens2;

      const int64_t P = (((static_cast<int64_t>(pressure_raw_) * sens) / 2097152) - off) / 32768LL;
      pressure_val_ = static_cast<Value>(P) / Value{100};
      temperature_val_ = static_cast<Value>(T) / Value{100};

      (void) T2;
      (void) P;
      return true;
    }

  private:
    update_state_t update_state_ = TemperatureTrigger;
    calc_mode_t calc_mode_ = OnPressure;
    chandra::chrono::Timer<> adc_timer_;
    chandra::io::I2CMaster& i2c_;
    SampleConfig pressure_cfg_;
    SampleConfig temperature_cfg_;
    uint32_t pressure_raw_;
    uint32_t temperature_raw_;
    Value pressure_val_;
    Value temperature_val_;
    uint16_t C_[8];
};

} /* namespace drivers */
} /* namespace chandra */


#endif /*CHANDRA_MS56XX_H*/
