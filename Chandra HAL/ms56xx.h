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
    using clock_t = chandra::chrono::Timer<>::clock_t;
    using time_point_t = typename clock_t::time_point;

    const uint32_t sensor_settling_samples = 20;
    const uint32_t temp_point_samples = 10;
    const uint32_t press_cal_samples = 75;
    const uint32_t temp_cal_samples = 75;
    const uint32_t adc_flush_samples = 25;

    struct MeanVarianceEstimator
    {
        bool initialized = false;
        Value weight = 0.05;
        Value variance = 0;
        Value mean = 0;

        bool operator () (Value _val) {
          if(!initialized) {
            mean = _val;
            variance = 0;
            initialized = true;
          } else {
            mean = (weight * _val) + ((1-weight) * mean);
            const auto err = _val - mean;
            variance = (weight * (err * err)) + ((1-weight) * variance);
          }

          return true;
        }
    };

    enum update_state_t {
        PressureTrigger,
        PressureSample,
        TemperatureTrigger,
        TemperatureSample,
        InitUpdate,
        CalTemperature,
        CalPressureFlush,
        CalPressure
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
    struct UpdateStatus
    {
        // TODO: ADD SOMETHING TO SHOW THE "STATE" THAT THE MS5637 IS IN (NORMAL, INITIALIZING, CALIBRATING, ETC. )
        // TODO: ADD SOMETHING THAT SHOWS THE BEGINNING OF A NEW CYCLE
        UpdateStatus(const time_point_t& _timestamp) : timestamp{_timestamp} {}
        bool restart = false;
        bool processed = false;
        bool calculated = false;
        bool calibrating = false;
        time_point_t timestamp;
        operator bool() const { return calculated; }
    };

    const uint8_t addr = 0x76;

    // TODO: REMOVE THE CAL_MEAN AND CHANGE CAL_VARIANCE -> variance
    //  THIS SHOULD BE SPLIT INTO A PRESSURE PROXY AND TEMPERATURE PROXY?
    //  ALSO, THIS NEEDS TO RETURN A QUANTITY RATHER THAN A BARE NUMBER
    class ValueProxy
    {
      public:
        ValueProxy(const Value& _val, const Value& _cal_mean, const Value& _cal_variance)
          : cal_mean(_cal_mean), cal_variance(_cal_variance), val_(_val) {}

        Value value() const { return val_; }

        template<class T>
        operator T () const { return static_cast<T>(val_); }

        const Value& cal_mean;
        const Value& cal_variance;

      private:
        const Value& val_;
    };

    MS5637(chandra::io::I2CMaster& _i2c)
      : pressure(pressure_val_, pressure_cal_estimator_.mean, pressure_cal_estimator_.variance),
        temperature(temperature_val_, temperature_cal_estimator_.mean, temperature_cal_estimator_.variance),
        i2c_(_i2c) {}

    bool init(const uint32_t _f_i2c=400000) {// TODO: THIS FUNCTION (AND LATER THE I2C INIT FUNCTION AS WELL, NEED TO TAKE A FREQUENCY QUANTITY RATHER THAN JUST A NUMBER)
      pressure_cfg_.cmd = 0x40;
      temperature_cfg_.cmd = 0x50;

      i2c_.init(_f_i2c); // TODO: CHECK THAT THESE WORK...
      i2c_.enable(true);

      reset();

      // This should probably return communication errors
      loadCalibrationValues();

      updateOSRConfig(pressure_cfg_, 8192);
      updateOSRConfig(temperature_cfg_, 4096);
      updateFrequencyConfig(pressure_cfg_, 50);
      updateFrequencyConfig(temperature_cfg_, 0.5);
      // TODO: ENSURE THAT THE SAMPLE RATE IS VALID
      // I2C TIME IS 64/F_I2C SECONDS PER SAMPLE

      temperature_cal_estimator_.weight = 0.15;

      adc_timer_.run();

      if(!calibrated_) {
        calibrate();
      }

      return valid();
    }

    bool reset() {
      // TODO: TO MAKE THIS EVEN MORE LIKELY TO WORK, TAKE MANUAL CONTROL OF THE SCL PINS
      // AND TOGGLE THE SCL LINE SEVERAL TIMES BEFORE SENDING THE COMMAD...
      sendCMD(0x1E);
      // TODO: IT MAY MAKE SENSE TO USE SOME AMOUNT OF DELAY AFTER THE SOFTWARE RESET...?
      return true;
    }

    bool calibrate(bool _blocking = false) {
      update_state_ = initialized_ ? CalTemperature : InitUpdate;
      calibrated_ = false;
      sample_count_ = 0;
      temperature_cal_estimator_.initialized = false;
      pressure_cal_estimator_.initialized = false;
      if(_blocking){
        while(!calibrated_) update();
      }
      return true;
    }

    bool calibrated() const { return calibrated_; }

    UpdateStatus update() {
      UpdateStatus status{clock_t::now()};

      switch(update_state_) {
        default:
        case InitUpdate:
          if(initialized_) {
            if(calibrated_) {
              update_state_ = TemperatureTrigger;
            } else {
              update_state_ = CalTemperature;
              pressure_cal_estimator_.initialized = false;
              temperature_cal_estimator_.initialized = false;
            }
          } else {
            if(sample_count_ < (temp_point_samples+sensor_settling_samples)) {
              if(adc_running_) {
                if(adc_timer_(status.timestamp)) {
                  temperature_raw_ = readADC();
                  if(sample_count_ > sensor_settling_samples) {
                    status.calculated = calculateCorrectedValues();
                    temperature_cal_estimator_(temperature_val_);
                  }
                  ++sample_count_;
                  status.processed = true;
                  adc_running_ = false;
                }
              } else {
                sendCMD(temperature_cfg_.cmd);
                adc_timer_.duration(20ms);
                status.processed = true;
                adc_running_ = true;
              }
            } else {
              Tinit_ = temperature_cal_estimator_.mean;
              temperature_cal_estimator_.initialized = false;
              temperature_cal_estimator_.weight = 0.05;
              sample_count_ = 0;
              initialized_ = true;
              update_state_ = CalTemperature;
              status.processed = true;
            }
          }
          break;

        case PressureTrigger:
          if(pressure_cfg_.timer(status.timestamp)) {
            sendCMD(pressure_cfg_.cmd);
            adc_timer_.duration(std::chrono::microseconds{pressure_cfg_.adc_delay_us});
            adc_timer_.reset();
            update_state_ = PressureSample;
            status.processed = true;
          } else {
            update_state_ = TemperatureTrigger;
          }
          break;

        case PressureSample:
          if(adc_timer_(status.timestamp)) {
            pressure_raw_ = readADC();
            update_state_ = TemperatureTrigger;
            if( (calc_mode_==OnPressure) or (calc_mode_==OnBoth) ) {
              status.calculated = calculateCorrectedValues();
            }
            status.processed = true;
          }
          break;

        case TemperatureTrigger:
          if(temperature_cfg_.timer(status.timestamp)) {
            sendCMD(temperature_cfg_.cmd);
            adc_timer_.duration(std::chrono::microseconds{temperature_cfg_.adc_delay_us});
            adc_timer_.reset();
            update_state_ = TemperatureSample;
            status.processed = true;
          } else {
            update_state_ = PressureTrigger;
          }
          break;

        case TemperatureSample:
          if(adc_timer_(status.timestamp)) {
            temperature_raw_ = readADC();
            update_state_ = PressureTrigger;
            if( (calc_mode_==OnTemperature) or (calc_mode_==OnBoth) ) {
              status.calculated = calculateCorrectedValues();
            }
            status.processed = true;
          }
          break;

        case CalTemperature:
          status.calibrating = true;
          if(sample_count_ < temp_cal_samples) {
            if(adc_running_) {
              if(adc_timer_(status.timestamp)) {
                temperature_raw_ = readADC();
                status.calculated = calculateCorrectedValues();
                temperature_cal_estimator_(temperature_val_);
                ++sample_count_;
                status.processed = true;
                adc_running_ = false;
              }
            } else {
              sendCMD(temperature_cfg_.cmd);
              adc_timer_.duration(20ms);
              status.processed = true;
              adc_running_ = true;
            }
          } else {
            sample_count_ = 0;
            update_state_ = CalPressureFlush;
            status.processed = true;
          }
          break;

        case CalPressureFlush:
          status.calibrating = true;
          if(sample_count_ < adc_flush_samples) {
            if(adc_running_) {
              if(adc_timer_(status.timestamp)) {
                readADC();
                ++sample_count_;
                status.processed = true;
                adc_running_ = false;
              }
            } else {
              sendCMD(pressure_cfg_.cmd);
              adc_timer_.duration(20ms);
              status.processed = true;
              adc_running_ = true;
            }
          } else {
            sample_count_ = 0;
            update_state_ = CalPressure;
            status.processed = true;
          }
          update_state_ = CalPressure;
          break;

        case CalPressure:
          status.calibrating = true;
          if(sample_count_ < press_cal_samples) {
            if(adc_running_) {
              if(adc_timer_(status.timestamp)) {
                pressure_raw_ = readADC();
                status.calculated = calculateCorrectedValues();
                pressure_cal_estimator_(pressure_val_);
                ++sample_count_;
                status.processed = true;
                adc_running_ = false;
              }
            } else {
              sendCMD(pressure_cfg_.cmd);
              adc_timer_.duration(20ms);
              status.processed = true;
              adc_running_ = true;
            }
          } else {
            sample_count_ = 0;
            update_state_ = TemperatureTrigger;
            status.processed = true;
            calibrated_ = true;
          }
          break;
      }

      return status;
    }

    bool valid() const { // TODO: DECIDE IF THERE IS ANYTHING ELSE THAT SHOULD BE CHECKED TO DETERMINE VALIDITY
      const uint8_t crc = (C_[0] >> 12) & 0x0F;
      return (crc == crc4(C_)) and initialized_ and calibrated_;
    }

    Value setSelfHeating() {
      Tselfheating_ = temperature_val_ - Tinit_;
      return Tselfheating_;
    }

    Value Tinit() const { return Tinit_; }
    Value Tselfheating() const { return Tselfheating_; }

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

    uint8_t crc4(const uint16_t (&Ci)[8]) const {
      uint16_t C[8];
      for(uint8_t cnt = 0; cnt < 8; ++cnt) {
        C[cnt] = Ci[cnt];
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
    	const uint32_t us_offset = 45;

    	while( (_osr > _cfg.osr) and (_cfg.osr < 8192) ) {
    		++shift;
    		_cfg.osr *= 2;
    	}

    	const uint8_t scale = (1<<shift);
    	_cfg.adc_delay_us = us_slope * scale + us_offset;
    	_cfg.cmd = (_cfg.cmd & 0xF0) | (shift << 1);

    	return true;
    }

    bool updateFrequencyConfig(SampleConfig& _cfg, const auto& _freq) {
      const uint32_t sample_us = (1000000UL + (_freq/2)) / _freq;
      _cfg.timer.duration(std::chrono::microseconds{sample_us});
      return true;
    }

    // NOTE: IT MAKES SENSE TO MOVE THIS INTO A BASE CLASS SO THAT I CAN ALSO
    //  WRITE A FLOATING-POINT VERSION FOR USE WITH FLOATING-POINT VALUE TYPES.
    //  THIS WILL ALSO MAKE IT POSSIBLE TO MOVE THE CALCULATION OF THE CONSTANTS
    //  TO CALIBRATION LOAD TIME, WHICH IS A NICE OPTIMIZATION.
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
      temperature_val_ = static_cast<Value>(T+T2) / Value{100};

      return true;
    }

  private:
    bool initialized_ = false;
    bool calibrated_ = false;
    bool adc_running_ = false;
    uint32_t sample_count_;
    update_state_t update_state_ = InitUpdate;
    calc_mode_t calc_mode_ = OnPressure;
    chandra::chrono::Timer<> adc_timer_;
    chandra::io::I2CMaster& i2c_;
    SampleConfig pressure_cfg_;
    SampleConfig temperature_cfg_;
    uint32_t pressure_raw_;
    uint32_t temperature_raw_;
    Value pressure_val_;
    Value temperature_val_;
    MeanVarianceEstimator pressure_cal_estimator_;
    MeanVarianceEstimator temperature_cal_estimator_;
    Value Tinit_ = 0;
    Value Tselfheating_ = 0;
    uint16_t C_[8];
};

} /* namespace drivers */
} /* namespace chandra */


#endif /*CHANDRA_MS56XX_H*/
