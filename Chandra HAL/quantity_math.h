#ifndef CHANDRA_QUANTITY_MATH_H
#define CHANDRA_QUANTITY_MATH_H

#include <cmath>

#include "quantity.h"
#include "units_utils.h"

namespace std
{
template<class Value, class SrcUnits>
auto sqrt(const chandra::units::Quantity<Value, SrcUnits>& _q) {
	using result_units = chandra::units::sqrtOf<SrcUnits>;
	return chandra::units::Quantity<Value, result_units>(std::sqrt(_q.value()));
}
} /* namespace std */

#endif /*CHANDRA_QUANTITY_MATH_H */
