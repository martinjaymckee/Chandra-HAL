#ifndef CHANDRA_LPC_TIMER_H
#define CHANDRA_LPC_TIMER_H

#include <LPC8xx.h>
#include "../chrono.h"
#include "../chip_utils.h"
#include "../gpio.h"
#include "../units.h"

namespace chandra
{
namespace peripheral
{
namespace nxp
{

// NOTE: THE TIMER READ FUNCTIONS WILL ONLY WORK WHEN THE TIMER IS ENABLED... DOES THAT MAKE SENSE, OR SHOULD
//  IT JUST TURN ON THE REGISTER CLOCK TO READ/WRITE THE REGISTERS IF IT IS NOT CURRENTLY RUNNING?

// NOTE: USE MR[3] FOR THE MATCH REGISTER TO RESET WITH.  THIS SHOULD BE USED TO CONFIGURE THE PWM FREQUENCY
//  MATCH 0-2 CAN BE USED TO PRODUCE PWM SIGNALS.  IT WOULD BE BEST TO USE A PREDEFINED VALUE TO DO DUTY CYCLE CONTROL
//  IN THE TIMER.  I NEED TO BE ABLE TO DO CONTANT FREQUENCY / VARIABLE DUTY CYCLE AS WELL AS CONSTANT DUTY-CYCLE/ VARIABLE FREQUENCY.
//  AS SUCH, IT WOULD PROBABLY BE BEST TO USE A PWM MODULE AND PROVIDE FREQUENCY & ON-TIME VALUES TO THE MATCH REGISTER

class CTimer
{
  public:
    using timer_t = LPC_TIMER_TypeDef;
    using frequency_t = chandra::units::Quantity<uint64_t, chandra::units::mks::mHz>;
    using duration_t = std::chrono::duration<uint32_t, std::micro>;

  protected:
    class CTimerMatch
    {
      public:
        using frequency_t = typename CTimer::frequency_t;
        using duration_t = typename CTimer::duration_t;

        CTimerMatch(CTimer& _parent, const uint8_t& _idx)
          : parent_(_parent), idx_(_idx), port_{255}, pin_{255} { parent_.timer_.MR[idx_]=0; }

        bool pwm_enable(bool _active, bool _interrupt=false) {
          if(_active){
            parent_.timer_.MCR |= (1<<10);
            parent_.timer_.EMR |= (0x02<<((2*idx_) + 4));
            parent_.timer_.PWMC |= (1<<idx_);

            interrupt(_interrupt);
          } else {
            parent_.timer_.MCR &= ~(1<<10);
            parent_.timer_.EMR &= ~(0x02<<((2*idx_) + 4));
            parent_.timer_.PWMC &= ~(1<<idx_);
          }

          return _active;
        }

        bool pwm_enabled() const {
          return parent_.timer_.PWMC & (1<<idx_);
        }

        frequency_t frequency(const frequency_t& _f, const frequency_t& f_clk) {
          // TODO: HANDLE LOW FREQUNCIES WITH PRESCALAR
          const uint32_t pre = parent_.prescalar();
          const uint32_t cnt = (f_clk.value() + _f.value()/2) / (_f.value() * pre);
          parent_.timer_.MR[3] = cnt;

          const auto f_actual = f_clk.value() / (pre * cnt);
          return frequency_t{f_actual};
        }

        frequency_t frequency(const frequency_t& _f) {
          return frequency(_f, chandra::chrono::frequency::timer(parent_.num()));
        }

        frequency_t frequency() const {
          const frequency_t f_clk = chandra::chrono::frequency::timer(parent_.num());
          const uint32_t pre = parent_.prescalar();
          const uint32_t cnt = parent_.timer_.MR[3];
          const auto f_actual = f_clk.value() / (pre * cnt);
          return frequency_t{f_actual};
        }

        duration_t cycle_time() const {
            const frequency_t f_clk = chandra::chrono::frequency::timer(parent_.num());
            const uint64_t cnt = parent_.timer_.MR[3];
            uint32_t us = (1000000000UL * cnt * parent_.prescalar()) / f_clk.value();
            return duration_t{us};
        }

        duration_t on_time(const duration_t& _t, const frequency_t& f_clk) {
        const auto t_max = cycle_time();
          const auto t = t_max - _t;
          const auto denom = 1000000000UL * uint64_t(parent_.prescalar());
          const auto cnt = ((t.count() * f_clk.value()) + (denom / 2)) / denom;
          parent_.timer_.MR[idx_] = cnt;
          return on_time(f_clk);
        }

        duration_t on_time(const duration_t& _t) {
          const frequency_t f_clk{chandra::chrono::frequency::timer(parent_.num())};
          return on_time(_t, f_clk);
        }

        duration_t on_time(const frequency_t& f_clk) const {
          const uint64_t cnt = parent_.timer_.MR[idx_];
          uint32_t us = (100000000UL * cnt * parent_.prescalar()) / f_clk.value();
          return duration_t{us};
        }

        duration_t on_time() const {
          return on_time(chandra::chrono::frequency::timer(parent_.num()));
        }

        operator uint32_t() {
          return parent_.timer_.MR[idx_];
        }

        CTimerMatch& operator = (const uint32_t& _cnt) {
          parent_.timer_.MR[idx_] = _cnt;
          return *this;
        }

        bool attach(const chandra::io::IO& _io) {
          if(idx_ < 3) {
            PinMap::set(13, idx_+1, PinMap::pinIndex(_io.port(), _io.pin()));
          } else {
            PinMap::set(14, 0, PinMap::pinIndex(_io.port(), _io.pin()));
          }
          port_ = _io.port();
          pin_ = _io.pin();
          return true;
        }

        constexpr bool attached() const {
          return port_ != 255;
        }

        bool interrupt(bool _active) {
          if(_active){
            parent_.timer_.MCR |= (1<<9); // Interrupt on Match 3 Interrupt
            // Enable the Ctimer0 interrupt
            NVIC_EnableIRQ(CTIMER0_IRQn); // TODO: NEED TO SELECT THE CORRECT TIMER
          } else {
            parent_.timer_.MCR &= ~(1<<9); // Clear Interrupt on Match 3 Interrupt
          }
          return _active;
        }

        bool update() { return true; }

      private:
        CTimer& parent_;
        uint8_t idx_;
        uint8_t port_;
        uint8_t pin_;
    };

  public:
    CTimer(const uint8_t& _num) : num_(_num), timer_(getTimer(_num)) {}

    bool init() {
      SystemClock::enable(0, 25);
      PeripheralActivity::reset(0, 25);
      const bool enabled = enable();
      reset();
      if(enabled) {
        timer_.CTCR = 0x00; // Set in Timer Mode
        prescalar(1);
      }
      return enabled;
    }

    bool enable(const bool& _enabled = true) {
      if(_enabled) {
        timer_.TCR = 0x01; // Enable the timer
        return true;
      }
      timer_.TCR = 0; // Disable the timer
      return false;
    }

    bool reset() {
      if(timer_.TCR & 0x01) { // Timer is running
        timer_.TCR |= 0x02; // Request reset
        chandra::chrono::delay(1us);
        timer_.TCR &= ~0x02; // Clear reset
      }
      return false;
    }

    constexpr uint8_t num() const { return num_; }

    CTimerMatch match(const uint8_t _idx) {
      return CTimerMatch(*this, _idx);
    }

    uint32_t prescalar(const uint32_t& _pr) {
      timer_.PR = _pr - 1;
      return _pr;
    }

    uint32_t prescalar() {
      return timer_.PR + 1;
    }

  protected:
    timer_t& getTimer(const uint8_t&) {
      // HACK: THIS JUST RETURNS CTIMER0!
      return *LPC_CTIMER0;
    }

    uint8_t num_;
    timer_t& timer_;

};

template<class PwmImpl, class Value=float>
class PwmWrapper
{
  public:
    using frequency_t = typename PwmImpl::frequency_t;
    using duration_t = typename PwmImpl::duration_t;

    PwmWrapper(PwmImpl& _impl) : impl_(_impl) {}

    bool enable(const bool& _active) { return impl_.pwm_enable(_active); }
    bool enabled() { return impl_.pwm_enabled(); }

    frequency_t frequency(const frequency_t& _f) {
      const Value d = read_duty();
      const auto f_actual = impl_.frequency(_f);
      duty(d);
      return f_actual;
    }

    constexpr frequency_t frequency() const { return impl_.frequency(); }

    Value duty(Value _duty, const Value& _max=Value{100}) {
      const duration_t t_max = impl_.cycle_time();
      const duration_t t_tgt(static_cast<typename duration_t::rep>(((t_max.count() * _duty) + (_max / 2)) / _max));
      const duration_t t_on = impl_.on_time(t_tgt);
      return (_max * static_cast<Value>(t_on.count())) / static_cast<Value>(t_max.count());
    }

    // READ THE ACTUAL ONTIME AND FREQUENCY THEN CALCULATE THE DUTY CYCLE
    Value read_duty(Value _max = Value{100}) const {
      const duration_t t_max = impl_.cycle_time();
      const duration_t t_on = impl_.on_time();
      const Value d = (_max * static_cast<Value>(t_on.count())) / static_cast<Value>(t_max.count());
      return d;
    }

    bool update() { return impl_.update(); }

  private:
    PwmImpl& impl_;
};

template<class PwmImpl>
PwmWrapper<PwmImpl> make_pwm(PwmImpl& _impl) {
  return {_impl};
}


/*
static void pwmHACK(uint32_t f_clk, uint32_t f_pwm, uint32_t _duty) {
	// Enable clocks to relevant peripherals
  SystemClock::enable(0, 25);
  PeripheralActivity::reset(0, 25);

  LPC_CTIMER0->CTCR = 0x00; // Set in Timer Mode

  // Connect the Ctimer Match/PWM outputs, and the Capture 0 function, to port pins
  PinMap::set(13, 1, PinMap::pinIndex(0, 8));

  // Set the PWM period in counts/cycle of the TC
  const uint32_t pwm_cnt = (f_clk + (f_pwm/2)) / f_pwm;
  LPC_CTIMER0->MR[3] = pwm_cnt;

  // Set the PWM duty cycle in counts/cycle
  LPC_CTIMER0->MR[0] = ((100-_duty)*pwm_cnt + 50) / 100;

  // Prescalar of 1 (0+1)
  LPC_CTIMER0->PR = 0;

  // Configure the Match Control register to reset on match in MR3
  LPC_CTIMER0->MCR = (1<<10) | (1<<9); // Reset / Interrupt

  // Put the Match 0 outputs into PWM mode
  LPC_CTIMER0->PWMC = (1<<0);

  // Enable the Ctimer0 interrupt
  NVIC_EnableIRQ(CTIMER0_IRQn);

  // Start the action
  LPC_CTIMER0->TCR = 0x01;
}
*/

} /*namespace nxp*/
} /*namespace peripheral*/
} /*namespace chandra*/

#endif /*CHANDRA_LPC_TIMER_H*/
