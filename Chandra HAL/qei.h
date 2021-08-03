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
      {
        reset();
      }

    constexpr chandra::io::IO A() const {
      return A_;
    }

    constexpr chandra::io::IO B() const {
      return B_;
    }

    constexpr chandra::io::IO IDX() const {
      return IDX_;
    }

    bool reset() {
      auto A_debounce = chandra::io::debounce(A_);
      auto B_debounce = chandra::io::debounce(B_);
      while(!(A_debounce.valid() and B_debounce.valid())) {
        A_debounce();
        B_debounce();
      }
      A_ = bool(A_debounce);
      B_ = bool(B_debounce);
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

    QEI::Event update() {
      return QEI::Event::None;
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
