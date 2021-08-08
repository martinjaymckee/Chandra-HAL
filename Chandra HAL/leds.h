/*
 * gpio.h
 *
 *  Created on: Apr 6, 2016
 *      Author: martin
 */

#ifndef CHANDRA_LEDS_H
#define CHANDRA_LEDS_H

#include <chrono>

#include "gpio.h"

namespace chandra
{
namespace io
{
// TODO: MOVE THE LED IMPLEMENTATION (AND RGBLED IMPLEMENTATION) OUT OF THE GPIO
//  FILE AND INTO LED.H, WHICH WILL DEPEND UPON GPIO.H

// TODO: USE THESE "COLORS" TO CREATE A NICE RGBLED OBJECT WHICH HANDLES THE LED IN
//  THE SAME WAY AS A SINGLE LED ONLY ALLOWS YOU TO USE "ACTIVE" AND "INACTIVE" COLORS
//  AND THEREFORE "BLINK" BETWEEN COLORS.

template<class T=uint8_t>
struct Color
{
  Color(const T& gray=0) : r(gray), g(gray), b(gray) {}

  Color(const T& _r, const T& _g, const T& _b)
    : r(_r), g(_g), b(_b) {}

  template<class T2>
  Color(const Color<T2>& _other)
    : r(static_cast<T>(_other.r)),
    g(static_cast<T>(_other.g)),
    b(static_cast<T>(_other.b)) {}

  template<class T2>
  Color<T>& operator = (const T2& _gray) {
    r = static_cast<T>(_gray);
    g = static_cast<T>(_gray);
    b = static_cast<T>(_gray);
    return *this;
  }

  template<class T2>
  Color<T>& operator = (const Color<T2>& _other) {
    r = static_cast<T>(_other.r);
    g = static_cast<T>(_other.g);
    b = static_cast<T>(_other.b);
    return *this;
  }

  T r;
  T g;
  T b;
};

// struct LEDColors {
//   using color_t = Color<uint8_t>;
//   constexpr static color_t Off = color_t{0, 0, 0};
//   constexpr static color_t Red = color_t{255, 0, 0};
//   constexpr static color_t Yellow = color_t{255, 255, 0};
//   constexpr static color_t Green = color_t{0, 255, 0};
//   constexpr static color_t Cyan = color_t{0, 255, 255};
//   constexpr static color_t Blue = color_t{0, 0, 255};
//   constexpr static color_t Magenta = color_t{255, 0, 255};
//   constexpr static color_t White = color_t{255, 255, 255};
// };

class LED
{
    public:
        enum mode_t {
            Fixed,
            Pulse,
            PWM,
            Breathe
        }; // TODO: THIS COULD ( SHOULD? ) BE GENERALIZED TO AN LED "COMMAND"

        using clock_t = chandra::chrono::timestamp_clock; // TODO: SHOULD THIS BE PASSED IN?
        using duration_t = clock_t::duration;
        using time_point_t = clock_t::time_point;

    public:
        LED( uint8_t _port, uint8_t _pin, bool _inverted = false ) : pin_(_port, _pin, true, _inverted ), mode_(Fixed) {
            init();
        }

        LED(const IO& _io) : pin_(_io), mode_(Fixed) {
            pin_.output(true);
            init();
        }

        LED(const internal::IODef& _io) : LED(IO(_io)) {}

        void init() { // TODO: DECIDE IF IT MAKES SENSE TO INCLUDE AN INIT METHOD EVEN THOUGH IT'S A NOP

        }

        template<class T>
        LED& operator = ( const T& _value ) {
            const bool value = bool(_value);
            mode_ = Fixed;
            pin_ = value;
            return *this;
        }

        IO& pin() {
            return pin_;
        }

        mode_t mode() const {
            return mode_;
        }

        LED& operator ~ () {
            mode_ = Fixed;
            ~pin_;
            return *this;
        }

        template<uint32_t DutyCycleMultiplier = 100, typename Scalar = uint32_t>
        LED& pwm( const duration_t& _period, const Scalar& _duty_cycle = 50, const bool& _inverted = false, const bool& _reset = true ){
            duty_cycle_ = _duty_cycle;
            active_period_ = calcActivePeriod(_period, DutyCycleMultiplier*_duty_cycle);
            inactive_period_ = _period - active_period_;
            cycle_period_ = active_period_ + inactive_period_;
            mode_ = PWM;
            if(_reset) {
                if(active_period_.count() > 0) pin_ = !_inverted;
                state_ = !_inverted;
                timestamp_ = clock_t::now();
            }
            return *this;
        }

        template<uint32_t DutyCycleMultiplier = 100, typename Scalar = uint32_t>
        LED& pwmUpdate(const duration_t& _period, const Scalar& _duty_cycle = 50, const bool& _inverted = false, const bool& _reset = true ) {
            return pwm<DutyCycleMultiplier, Scalar>(_period, _duty_cycle, _inverted, false);
        }

        LED& pulse(const duration_t& _active_period, const duration_t& _total_period = duration_t{0}, const bool& _blocking = false ) {
            active_period_ = _active_period;
            inactive_period_ = ( _total_period <= _active_period ) ? duration_t(0) : _total_period - _active_period;
            mode_ = Pulse;
            ~pin_;
            timestamp_ = clock_t::now();
            state_ = true;
            if(_blocking) {
                do {
                    update();
                } while( mode_ == Pulse );
            }
            return *this;
        }

        LED& pulse(const duration_t& _active_period, const bool& _blocking) {
          return pulse(_active_period, _active_period, _blocking);
        }

        LED& breathe(const duration_t& _cycle_period, const bool _reset=true, const duration_t& _pwm_period = std::chrono::milliseconds{20}) {
          const uint32_t steps = (_cycle_period.count() + (_pwm_period.count()/2)) / _pwm_period.count();
          duty_cycle_step_ = (20000 + (steps/2)) / steps;
          update_period_ = duration_t{(_cycle_period.count() + (steps/2)) / steps};
          mode_ = Breathe;
          if(_reset) {
              duty_cycle_ = 0;
              active_period_ = duration_t{0};
              inactive_period_ = _pwm_period;
              increasing_ = true;
              pin_ = false;
              state_ = false;
              timestamp_ = clock_t::now();
              update_timestamp_ = timestamp_;
          }

          return *this;
        }

        bool update() {
            bool updated = false;

            auto current = clock_t::now();

            if( mode_ == Pulse ){
                if( state_ ) {
                    if( chandra::chrono::after(active_period_, timestamp_, current) ) {
                        ~pin_;
                        state_ = false;
                        timestamp_ += active_period_;
                    }
                } else {
                    if( chandra::chrono::after(inactive_period_, timestamp_, current) ) {
                        mode_ = Fixed;
                        updated = true;
                    }
                }
            } else if ( (mode_ == PWM) or (mode_ == Breathe) ) {
                if(mode_ == Breathe) {
                  if(chandra::chrono::after(update_period_, update_timestamp_, current)){
                    update_timestamp_ += update_period_;
                    if(increasing_) {
                      if(10000-duty_cycle_ < duty_cycle_step_) {
                        duty_cycle_ = 10000;
                        increasing_ = false;
                      } else {
                        duty_cycle_ += duty_cycle_step_;
                      }
                    } else {
                      if(duty_cycle_ < duty_cycle_step_) {
                        duty_cycle_ = 0;
                        increasing_ = true;
                      } else {
                        duty_cycle_ -= duty_cycle_step_;
                      }
                    }
                  }
                  const auto pwm_period = active_period_+inactive_period_;
                  active_period_ = calcActivePeriod(pwm_period, duty_cycle_);
                  inactive_period_ = pwm_period-active_period_;
                }

                if( state_ ) {
                    if( chandra::chrono::after(active_period_, timestamp_, current) ) {
                      if(active_period_.count() > 0) ~pin_;
                        state_ = !state_;
                        timestamp_ += active_period_;
                    }
                } else {
                    if( chandra::chrono::after(inactive_period_, timestamp_, current) ) {
                        if(active_period_.count() > 0) ~pin_;
                        state_ = !state_;
                        timestamp_ += inactive_period_;
                        updated = true;
                    }
                }
            }

            return updated;
        }

    protected:
      template<class Scalar>
      duration_t calcActivePeriod(const duration_t& _period, const Scalar& _duty_cycle) {
        const auto num = static_cast<uint64_t>(_duty_cycle) * _period.count();
        return duration_t( (num + 5000) / 10000); // TODO: FIGURE OUT IF THERE IS A SAFER WAY TO DO THIS
      }

    private:
        IO pin_;
        mode_t mode_;

        bool state_;
        duration_t active_period_;
        duration_t inactive_period_;
        duration_t cycle_period_;
        duration_t update_period_;
        uint16_t duty_cycle_;
        uint16_t duty_cycle_step_;
        bool increasing_;
        time_point_t timestamp_;
        time_point_t update_timestamp_;
};

namespace internal
{
struct LEDConfig
{
  enum sequencing_t {
    Sequential,
    Simultaneous
  };


};

template<class RGBBase>
class SequentialSequencer
{
  protected:
    enum sequence_point_t {
        RedLed,
        GreenLed,
        BlueLed,
        Inactive
    };

  public:
    using clock_t = typename RGBBase::clock_t;
    using time_point_t = typename RGBBase::time_point_t;
    using duration_t = typename RGBBase::duration_t;

    SequentialSequencer(RGBBase& _base) : base_(_base) {}

    template<class T>
    void calcPeriods(Color<T> _color) {
      const uint32_t period = base_.total_period_.count();
      const uint32_t duty_cycle = base_.brightness_;
      const uint32_t C = period * duty_cycle;
      const Color<uint32_t> color{_color};
      // TODO: FIGURE OUT HOW TO COMBINE THESE...
      // const uint32_t color_range = std::min(static_cast<uint32_t>(base_.color_max), (color.r + color.g + color.b));
      // const auto denom = base_.brightness_max * (color.r + color.g + color.b);
      // const auto denom = base_.brightness_max * base_.color_max * (
      //   ((color.r > 0) ? 1 : 0) + ((color.g > 0) ? 1 : 0) + ((color.b > 0) ? 1 : 0)
      // );
      // const uint32_t denom = base_.brightness_max * color_range;
      const auto denom = 3 * base_.color_max * base_.brightness_max;

      base_.red_period_ = duration_t{(color.r*C) / denom};
      base_.green_period_ = duration_t{(color.g*C) / denom};
      base_.blue_period_ = duration_t{(color.b*C) / denom};
      return;
    }

    bool reset(const time_point_t& _t) {
      base_.t_sequence_ = _t;
      base_.red_ = (base_.red_period_.count() > 0);
      seq_point_ = RedLed;
      return true;
    }

    bool reset() {
      return reset(clock_t::now());
    }

    bool update(const time_point_t& _t) {
      bool updated = false;
      switch(seq_point_) {
        case RedLed:
          if(chandra::chrono::after(base_.red_period_, t_last_, _t)) {
            base_.red_ = false;
            base_.green_ = (base_.green_period_.count() > 0);
            t_last_ = _t;
            seq_point_ = GreenLed;
          }
          break;

        case GreenLed:
          if(chandra::chrono::after(base_.green_period_, t_last_, _t)) {
            base_.green_ = false;
            base_.blue_ = (base_.blue_period_.count() > 0);
            t_last_ = _t;
            seq_point_ = BlueLed;
          }
          break;

        case BlueLed:
          if(chandra::chrono::after(base_.blue_period_, t_last_, _t)) {
            base_.blue_ = false;
            t_last_ = _t;
            seq_point_ = Inactive;
          }
          break;

        case Inactive:
        default:
          if(chandra::chrono::after(base_.total_period_, base_.t_sequence_, _t)) {
            base_.red_ = (base_.red_period_.count() > 0);
            base_.t_sequence_ = _t;
            t_last_ = _t;
            seq_point_ = RedLed;
            updated = true;
          }
          break;
      }

      return updated;
    }

  private:
    RGBBase& base_;
    sequence_point_t seq_point_ = Inactive;
    time_point_t t_last_;
};

template<class RGBBase>
class SimultaneousSequencer
{
  public:
    using clock_t = typename RGBBase::clock_t;
    using time_point_t = typename RGBBase::time_point_t;
    using duration_t = typename RGBBase::duration_t;

    SimultaneousSequencer(RGBBase& _base) : base_(_base) {}

    template<class T>
    void calcPeriods(Color<T> _color) {
      const uint32_t period = base_.total_period_.count();
      const uint32_t duty_cycle = base_.brightness_;
      const uint32_t C = period * duty_cycle;
      const auto denom = base_.brightness_max * base_.color_max;
      base_.red_period_ = duration_t{(_color.r*C) / denom};
      base_.green_period_ = duration_t{(_color.g*C) / denom};
      base_.blue_period_ = duration_t{(_color.b*C) / denom};
      return;
    }

    bool reset(const time_point_t& _t) {
      // TODO: IMPLEMENT THE SIMULTANEOUS SEQUENCER
      return true;
    }

    bool reset() {
      return reset(clock_t::now());
    }

    bool update(const time_point_t& _t) {
        return false;
    }

  private:
    RGBBase& base_;
};

template<class RGBBase, LEDConfig::sequencing_t Sequencing>
struct SequencerType
{
  using sequencing_t = SimultaneousSequencer<RGBBase>;
};

template<class RGBBase>
struct SequencerType<RGBBase, LEDConfig::sequencing_t::Sequential>
{
  using sequencer_t = SequentialSequencer<RGBBase>;
};

} /*namespace internal*/

template<
  internal::LEDConfig::sequencing_t Sequencing = internal::LEDConfig::sequencing_t::Sequential
  >
class RGBLED
{
  protected:
    static constexpr uint8_t color_max = 255;
    static constexpr uint16_t brightness_max = 10000;

    enum phase_t {
      PhaseA,
      PhaseB
    };

  public:
    using mode_t = LED::mode_t;
    using clock_t = chandra::chrono::timestamp_clock; // TODO: SHOULD THIS BE PASSED IN?
    using duration_t = clock_t::duration;
    using time_point_t = clock_t::time_point;
    using color_t = Color<uint8_t>;
    using ref_t = RGBLED<Sequencing>;
    using sequencer_t = typename internal::SequencerType<ref_t, Sequencing>::sequencer_t;
    friend class internal::SequencerType<ref_t, Sequencing>::sequencer_t;

    RGBLED(const IO& _red, const IO& _green, const IO& _blue)
      : red_(_red), green_(_green), blue_(_blue), sequencer_(*this) {}

    template<class T>
    ref_t& operator = (const Color<T>& _color){
      mode_ = LED::Fixed;
      sequencer_.calcPeriods(_color);
      return *this;
    }

    ref_t& operator = (const bool& _active){
      if(_active) {
        sequencer_.calcPeriods(active_color_);
      } else {
        sequencer_.calcPeriods(inactive_color_);
      }
      mode_ = LED::Fixed;
      is_active_ = _active;
      return *this;
    }

    template<class T>
    ref_t& setActiveColor(const Color<T>& _color) {
      active_color_ = _color;
      return *this;
    }

    template<class T>
    ref_t& setInactiveColor(const Color<T>& _color) {
      inactive_color_ = _color;
      return *this;
    }

    IO& red() { return red_; }
    IO& green() { return green_; }
    IO& blue() { return blue_; }

    ref_t& pulse(const duration_t& _active_period, const duration_t& _total_period = duration_t{0}, const bool& _blocking = false ) {
        active_period_ = _active_period;
        inactive_period_ = ( _total_period <= _active_period ) ? duration_t(0) : _total_period - _active_period;
        mode_ = LED::Pulse;
        phase_ = PhaseA;
        is_active_ = !is_active_;
        sequencer_.calcPeriods(is_active_ ? active_color_ : inactive_color_);
        timestamp_ = clock_t::now();
        sequencer_.reset();
        if(_blocking) {
            do {
                update();
            } while( mode_ == LED::Pulse );
        }
        return *this;
    }

    ref_t& pulse(const duration_t& _active_period, const bool& _blocking) {
      return pulse(_active_period, _active_period, _blocking);
    }

    bool update() {
      const auto t = clock_t::now();
      const bool updated = sequencer_.update(t);
      if(updated) {
        switch(mode_) {
          default:
          case LED::Fixed:
            break;

          case LED::Pulse:
            if(phase_ == PhaseA) {
              if(chandra::chrono::after(active_period_, t_mode_)) {
                is_active_ = !is_active_;
                sequencer_.calcPeriods(is_active_ ? active_color_ : inactive_color_);
                phase_ = PhaseB;
                t_mode_ += active_period_;
              }
            } else {
              if(chandra::chrono::after(inactive_period_, t_mode_)) {
                mode_ = LED::Fixed;
                t_mode_ += inactive_period_;
              }
            }
            break;

          case LED::PWM:
            break;

          case LED::Breathe:
            break;
        }
      }
      return updated;
    }

  protected:
    mode_t mode_ = LED::Fixed;
    phase_t phase_ = PhaseA;
    bool is_active_ = false;
    color_t active_color_{255, 0, 0};
    color_t inactive_color_{0, 0, 0};
    uint32_t brightness_ = 10000;
    duration_t total_period_ = std::chrono::milliseconds{10};
    duration_t active_period_;
    duration_t inactive_period_;
    duration_t red_period_;
    duration_t green_period_;
    duration_t blue_period_;
    time_point_t t_sequence_;
    time_point_t t_mode_;
    IO red_;
    IO green_;
    IO blue_;
    sequencer_t sequencer_;

    bool increasing_;
    time_point_t timestamp_;
    time_point_t update_timestamp_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_LEDS_H*/
