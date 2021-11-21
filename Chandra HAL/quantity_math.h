#ifndef CHANDRA_QUANTITY_MATH_H
#define CHANDRA_QUANTITY_MATH_H

#include <cmath>

#include "quantity.h"
#include "units_utils.h"

namespace std
{
template<class Value, class SrcUnits>
auto sqrt(const chandra::units::Quantity<Value, SrcUnits>& _q) {
	using base_units = chandra::units::internal::BaseUnits<SrcUnits>;
	using result_units = chandra::units::sqrtOf<SrcUnits>;
	const auto value_in_base = chandra::units::convert<Value, base_units, SrcUnits>(_q.value());
	return chandra::units::Quantity<Value, result_units>(std::sqrt(value_in_base));
}
} /* namespace std */

#endif /*CHANDRA_QUANTITY_MATH_H */
