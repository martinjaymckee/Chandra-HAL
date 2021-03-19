#ifndef CHANDRA_MATH_CONVERSIONS_H
#define CHANDRA_MATH_CONVERSIONS_H
#include <cmath>

#include "math_constants.h"

namespace chandra
{
namespace math
{

template<class Value>
static constexpr Value radians(Value _val) {
  return (chandra::math::pi<Value> * _val) / Value(180.0);
}

template<class Value>
static constexpr Value degrees(Value _val) {
  return (Value(180) * _val) / chandra::math::pi<Value>;
}

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATH_CONVERSIONS_H*/
