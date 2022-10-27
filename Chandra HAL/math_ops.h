#ifndef CHANDRA_MATH_OPS_H
#define CHANDRA_MATH_OPS_H

#include <cmath>

#include "quantity_math.h"

namespace chandra
{
namespace math
{
template<class Value>
struct SinCosReturn
{
    SinCosReturn(Value _sin, Value _cos)
      : sin{_sin}, cos{_cos} {}

    const Value sin;
    const Value cos;
};

template<class Value>
auto sincos(const Value& _theta) {
    using value_t = decltype(std::sin(_theta));
    using return_t = SinCosReturn<value_t>;
    const auto s = std::sin(_theta);
    const auto c = std::cos(_theta);
  return return_t(s, c);
}

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATH_OPS_H*/
