#ifndef CHANDRA_QUANTITY_MATH_H
#define CHANDRA_QUANTITY_MATH_H

#include <cmath>

#include "quantity.h"

namespace chandra
{
namespace units
{
template<class Value, class Units>
auto sqrt(const units::Quantity<Value, Units>& _q) {
  return units::Quantity<Value, units::sqrtOf<Units>>(std::sqrt(_q.value()));
}

} /* namespace units */
} /* namespace chandra */

#endif /*CHANDRA_QUANTITY_MATH_H */
