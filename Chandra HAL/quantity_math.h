#ifndef CHANDRA_QUANTITY_MATH_H
#define CHANDRA_QUANTITY_MATH_H

#include <cmath>

#include "quantity.h"
#include "units_utils.h"

namespace std
{
template<class Value, class SrcUnits>
auto sqrt(const chandra::units::Quantity<Value, SrcUnits>& _q) {
	// TODO: CHECK THAT IT IS VALID TO TAKE THE SQUARE ROOT OF THE UNITS...
	using result_units = chandra::units::sqrtOf<SrcUnits>;
	return chandra::units::Quantity<Value, result_units>(std::sqrt(_q.value()));
}

template<class Value, class SrcUnits>
auto abs(const chandra::units::Quantity<Value, SrcUnits>& _q) {
	// TODO: HOW DOES THIS PLAY WITH ABSOLUTE VS. RELATIVE UNITS???
	if(_q.value() < 0) {
		return chandra::units::Quantity<Value, SrcUnits>(-_q.value());
	}
	return _q;
}

template<class V, class U>
auto atan(const chandra::units::Quantity<V, U>& _v) {
	// TODO: CHECK THAT U IS SCALAR UNITS
	return static_cast<V>(std::atan(static_cast<V>(_v.value())));
}

template<class V1, class U1, class V2, class U2>
auto atan2(const chandra::units::Quantity<V1, U1>& _y, const chandra::units::Quantity<V2, U2>& _x) {
	// TODO: CHECK THAT U1 AND U2 HAVE THE SAME DIMENSIONS
	using return_t = typename std::common_type<V1, V2>::type;
	return return_t( std::atan2(return_t(_y.value()), return_t(_x.value())));
}

template<class V, class U>
auto sin(const chandra::units::Quantity<V, U>& _theta) {
	// TODO: CHECK THAT U IS ANGLE UNITS
	return static_cast<V>(std::sin(static_cast<V>(_theta.value())));
}

template<class V, class U>
auto cos(const chandra::units::Quantity<V, U>& _theta) {
	// TODO: CHECK THAT U IS ANGLE UNITS
	return static_cast<V>(std::cos(static_cast<V>(_theta.value())));
}

template<class V, class U>
auto tan(const chandra::units::Quantity<V, U>& _theta) {
	// TODO: CHECK THAT U IS ANGLE UNITS
	return static_cast<V>(std::tan(static_cast<V>(_theta.value())));
}


// TODO: IMPLEMENT MORE TRIG FUNCTIONS, AND CHECK THAT THE INPUTS ARE OF TYPE ANGLE.
} /* namespace std */

#endif /*CHANDRA_QUANTITY_MATH_H */
