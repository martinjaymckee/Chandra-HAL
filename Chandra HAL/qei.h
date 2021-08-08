#ifndef CHANDRA_QEI_H
#define CHANDRA_QEI_H

#include <chrono>

#include "debounce.h"
#include "gpio.h"
#include "quantity.h"

namespace chandra
{
namespace io
{

// TODO: NEED TO ADD A "TIME SOURCE" PARAMETER TO THE QEI BASE IMPLEMENTATION

// TODO: NEED TO ADD A "VELOCITY OBSERVER" PARAMETER TO THE QEI BASE IMPLEMENTATION

// TODO: IMPLEMENT A QUADRATURE ENCODER DECODER WITH POSITION AND VELOCITY DETECTION
//  -- THIS SHOULD HANDLE 1X, 2X, AND 4X MODE
//  -- THE BASIC VERSION SHOULD
//  -- EVENTS INCLUDE INCREMENT / DECREMENT / ERROR
//  -- THERE SHOULD ALSO BE A SUBCLASS FOR PANEL QUADRATURE ENCODERS WHICH DOES VELOCITY CONTROL
//  -- IDEA FOR ALGORITHM https://www.youtube.com/watch?v=i7uhvK2AL_s&t=462s

struct QEI
{
  enum class Mode {
    Full,     // Step on full cycle (every four edges)
    Half,     // Step on half cycle (every two edges)
    Quarter   // Step on quarter cycle (every edge)
  };

  enum class Event {
    None,
    CW,
    CCW
  };
};

namespace detail
{
template<class Value, class PositionUnits>
struct EncoderPosition
{
  using type = chandra::units::Quantity<Value, PositionUnits>;
};

template<class Value>
struct EncoderPosition<Value, void>
{
  using type = Value;
};

template<class Value, class PositionUnits>
struct EncoderVelocity
{
  using velocity_units_t = decltype(PositionUnits() / chandra::units::mks::s());
  using type = chandra::units::Quantity<Value, PositionUnits>;
};

template<class Value>
struct EncoderVelocity<Value, void>
{
  using type = Value;
};

// Base QEI Implementation
template<
  class Counts,
  class Value,
  class PositionUnits = void
>
class BaseIncrementalEncoderImplementation
{
  public:
    using count_t = Counts;
    using position_t = typename EncoderPosition<Value, PositionUnits>::type;
    using velocity_t = typename EncoderVelocity<Value, PositionUnits>::type;

    BaseIncrementalEncoderImplementation(
      const count_t _ppr,
      const chandra::io::IO& _A,
      const chandra::io::IO& _B,
      const chandra::io::IO& _IDX = chandra::io::NC
    )
      : ppr_{_ppr},
        A_{_A}, B_{_B}, IDX_{_IDX}
      {}

    constexpr chandra::io::IO A() const {
      return A_;
    }

    constexpr chandra::io::IO B() const {
      return B_;
    }

    constexpr chandra::io::IO IDX() const {
      return IDX_;
    }

    bool init() {
      // initialize the time source
      // initialize the velocity observer
      return reset();
    }

    bool reset() {
      auto A_debounce = chandra::io::debounce(A_);
      auto B_debounce = chandra::io::debounce(B_);
      while(!(A_debounce.valid() and B_debounce.valid())) {
        A_debounce();
        B_debounce();
      }
      A_last_ = bool(A_debounce);
      B_last_ = bool(B_debounce);
      counts_ = 0;
      return true;
    }

    uint32_t ppr(const uint32_t _ppr) {
      ppr_ = _ppr;
      return ppr();
    }

    constexpr uint32_t ppr() const {
      return ppr_;
    }

    constexpr count_t raw_counts() const {
      return counts_;
    }

    //
    // TODO: THE IMPLEMENTATION OF THE UPDATE METHODS NEEDS TO GO INTO THE DERIVED IMPLEMENTATIONS
    //    TODO: TAKE A TIMESTAMP PASSED IN....
    QEI::Event update(bool _A_state, bool _A_rising, bool _A_falling, bool _B_state, bool _B_rising, bool _B_falling) {
      QEI::Event event = QEI::Event::None;

      // NOTE: Only ONE edge can be processed at a time.... how should this be checked???

      if(_A_rising){
        if(!_B_state and _A_state) {
          event = QEI::Event::CW;
          A_last_ = _A_state;
        } else if (_B_state and _A_state) {
          event = QEI::Event::CCW;
          A_last_ = _A_state;
        } else {
          // This is an error
        }
      } else if(_A_falling) {
        if(!_B_state and !_A_state) {
          event = QEI::Event::CCW;
          A_last_ = _A_state;
        } else if (_B_state and !_A_state) {
          event = QEI::Event::CW;
          A_last_ = _A_state;
        } else {
          // This is an error
        }
      } else if(_B_rising) {
        if(!_A_state and _B_state) {
          event = QEI::Event::CCW;
          B_last_ = _B_state;
        } else if (_A_state and _B_state) {
          event = QEI::Event::CW;
          B_last_ = _B_state;
        } else {
          // This is an error
        }
      } else if(_B_falling) {
        if(!_A_state and !_B_state) {
          event = QEI::Event::CW;
          B_last_ = _B_state;
        } else if (_A_state and !_B_state) {
          event = QEI::Event::CCW;
          B_last_ = _B_state;
        } else {
          // This is an error
        }
      }

      if(event == QEI::Event::CW) {
        counts_ += 1;
      } else if(event == QEI::Event::CCW) {
        counts_ -= 1;
      }

      return event;
    }

    QEI::Event update() {
      // t = time_src_.now()
      // read edges
      const bool A_state = bool(A_);
      const bool B_state = bool(B_);

      const bool A_rising = (!A_last_ and A_state);
      const bool A_falling = (A_last_ and !A_state);
      const bool B_rising = (!B_last_ and B_state);
      const bool B_falling = (B_last_ and !B_state);

      // TODO: PASS IN THE TIMESTAMP
      return update(A_state, A_rising, A_falling, B_state, B_rising, B_falling);
    }

  protected:
    uint32_t ppr_;
    count_t counts_ = 0;
    bool A_last_;
    bool B_last_;
    chandra::io::IO A_;
    chandra::io::IO B_;
    chandra::io::IO IDX_;
};

} /* namespace detail */

//
// Incremental Encoder Implementations
//

// Pure Software Implementation (pin interrupts and timing using a clock source)
template<
  class Derived,
  class Value,
  class PositionUnits = void,
  class Counter = int32_t,
  class Clock = chandra::chrono::timestamp_clock
>
class SoftwareIncrementalEncoderImplementation : public detail::BaseIncrementalEncoderImplementation<Counter, Value, PositionUnits>
{
  public:
    using base_t = detail::BaseIncrementalEncoderImplementation<Counter, Value, PositionUnits>;
    using count_t = typename base_t::count_t;
    using position_t = typename base_t::position_t;
    using velocity_t = typename base_t::velocity_t;

    SoftwareIncrementalEncoderImplementation(
      const count_t _ppr,
      const chandra::io::IO& _A,
      const chandra::io::IO& _B,
      const chandra::io::IO& _IDX = chandra::io::NC
    ) : base_t(_ppr, _A, _B, _IDX) {}

};

// Dedicated Timer Timing (using timer (capture) interrupts for edge detection and timing)

// Dedicated Hardware Implementation (use a QEI peripheral, if avaliable)

//
// General Encoder Specialization
//

//
// Control Panel (HID) Encoder Specialization
//
template<
  class Value,
  class PositionUnits = void,
  class Counter = int32_t,
  class... Params
>
class HIDEncoder : public SoftwareIncrementalEncoderImplementation<HIDEncoder<Value, PositionUnits, Params...>, Value, PositionUnits, Counter, Params...>
{
  public:
    using base_t = SoftwareIncrementalEncoderImplementation<HIDEncoder<Value, PositionUnits, Params...>, Value, PositionUnits, Counter, Params...>;
    using count_t = typename base_t::count_t;
    using position_t = typename base_t::position_t;
    using velocity_t = typename base_t::velocity_t;

    HIDEncoder(
      const count_t _ppr,
      const chandra::io::IO& _A,
      const chandra::io::IO& _B,
      const chandra::io::IO& _IDX = chandra::io::NC
    ) : base_t(_ppr, _A, _B, _IDX) {}
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_QEI_H*/
