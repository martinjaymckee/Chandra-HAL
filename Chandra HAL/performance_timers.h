#ifndef CHANDRA_PERFORMANCE_TIMERS_H
#define CHANDRA_PERFORMANCE_TIMERS_H

#include <chrono>

#include "chrono.h"
#include "circular_buffer.h"
#include "timing.h"

namespace chandra
{
namespace chrono
{

namespace detail
{
template<class Count, class Value>
struct BasicPerformanceStatistics
{
  Count count = Count{0};
  Value minimum = Value{0};
  Value mean = Value{0};
  Value maximum = Value{0};
  bool valid = false;
};
} /* namespace detail */

template<uint8_t Samples=16, bool Sampling=true, class Clock = chandra::chrono::timestamp_clock>
class ActivityTimer
{
  public:
    using timer_t = chandra::chrono::Timer<Clock>;
    using clock_t = Clock;
    using duration_t = typename timer_t::duration_t;
    using time_point_t = typename timer_t::time_point_t;
    using statistics_t = detail::BasicPerformanceStatistics<uint8_t, duration_t>;

    ActivityTimer(auto _period) : timer_(_period) {}

    ActivityTimer& reset() {
      activity_time_ = duration_t{0};
      timer_.reset();
      stats_ = statistics_t{};
      return *this;
    }

    bool start() {
      const time_point_t current = clock_t::now();
      if(Sampling) {
        start_time_ = current;
        return true;
      }
      return false;
    }

    bool end(const bool& _measure=true) {
      const time_point_t current = clock_t::now();
      if(Sampling) {
        if(_measure) {
          const auto expiration_status = timer_();
          const duration_t duration = current - start_time_;

          if(expiration_status.expired) {
            activity_time_ += (expiration_status.expiration - start_time_);
            insertSample();
            activity_time_ = current - expiration_status.expiration;
          } else {
            activity_time_ += duration;
          }
        }
      }
      return false;
    }

    statistics_t update() {
      if(timer_()) insertSample();

      return stats_;
    }

    statistics_t statistics() const { return stats_; }

  private:
    bool insertSample() {
      samples_ << activity_time_;

      if(samples_.full()) {
        stats_.valid = true;
        stats_.count = Samples;

        duration_t minimum;
        duration_t sum{0};
        duration_t maximum;

        for(uint8_t idx=0; idx<Samples; ++idx) {
          const auto val = samples_[idx];
          if(idx == 0) {
            stats_.minimum = val;
            stats_.maximum = val;
          } else {
            if(val < stats_.minimum) stats_.minimum = val;
            if(val > stats_.maximum) stats_.maximum = val;
          }
          sum += val;
        }
        stats_.mean = duration_t{sum.count()/Samples};
        return true;
      }

      return false;
    }

    chandra::FixedCircularBuffer<duration_t, Samples> samples_;
    timer_t timer_;
    time_point_t start_time_;
    duration_t activity_time_;
    statistics_t stats_;
};

} /* namespace chrono*/
} /* namespace chandra */
#endif /*CHANDRA_PERFORMANCE_TIMERS_H*/