#ifndef CHANDRA_QUANTITY_UTILS_H
#define CHANDRA_QUANTITY_UTILS_H

#include "quantity.h"

namespace chandra
{
namespace units
{

template<class Value, class Units>
bool isNonnegative(const units::Quantity<Value, Units>& _q) {
  return (_q.value() >= value_t{0});
}

template<class Value, class Units>
bool isNegative(const units::Quantity<Value, Units>& _q) {
  return (_q.value() < value_t{0});
}

template<class Value, class Units>
auto SaturateNonnegative(const units::Quantity<Value, Units>& _q) {
  if(_q.value() < value_t{0}) return units::Quantity<Value, Units>{0};
  return _q;
}

template<class Value, class Units>
auto SaturateNegative(const units::Quantity<Value, Units>& _q) {
  if(_q.value() > value_t{0}) return units::Quantity<Value, Units>{0};
  return _q;
}

} /* namespace units */
} /* namespace chandra */

#endif /*CHANDRA_QUANTITY_UTILS_H */
