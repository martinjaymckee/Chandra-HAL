#ifndef CHANDRA_MATH_OPS_H
#define CHANDRA_MATH_OPS_H

#include <cmath>

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
SinCosReturn<Value> sincos(const Value& _theta) {
  return {sin(_theta), cos(_theta)};
}

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATH_OPS_H*/
