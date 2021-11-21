/*
 * meta_math.h
 *
 *  Created on: May 19, 2017
 *      Author: martin
 */

#ifndef CHANDRA_META_MATH_H
#define CHANDRA_META_MATH_H

#include <cstdint>

namespace chandra
{
namespace meta
{

//
// Compile-time implementation of 2^n (n is an integer)
//
template<uint8_t _remaining>
struct pow2
{
	static constexpr unsigned long value = 2 * pow2<_remaining-1>::value;
};

template<>
struct pow2<0>
{
	static constexpr unsigned long value = 1;
};

//
// Compile-time implementation of 10^n (n is an integer)
//
template<uint8_t _remaining>
struct pow10
{
	static constexpr unsigned long value = 10 * pow10<_remaining-1>::value;
};

template<>
struct pow10<0>
{
	static constexpr unsigned long value = 1;
};


//
// Compile-time integer square root
//
namespace internal
{
template <typename T, std::intmax_t MaxIter>
constexpr T sqrt_impl(T v, T lower, T upper, std::intmax_t _iter) {
	const T middle = (lower + upper + 1) / 2; // Calculate range midpoint

	// Terminal condition
	if((lower == upper) || (_iter >= MaxIter)) return middle;

  if((v/middle) < middle) { // Search in lower half
    return sqrt_impl<T, MaxIter>(v, lower, middle-1, _iter+1);
  } else { // Search in upper half
    return sqrt_impl<T, MaxIter>(v, middle, upper, _iter+1);
  }
}
} /* namespace internal */

// NOTE: FOR EFFICIENCY, THIS SHOULD CHOOSE BETWEEN THE BINARY SEARCH OPTION FOR INTEGER OR 
//	A NEWTON-RAPHSON OPTION FOR FLOATING POINT
template <typename T, std::intmax_t MaxIter=250>
constexpr T sqrt(T v) {
	const T lower_limit{0};
	const T upper_limit{v/2 + 1};
	return internal::sqrt_impl<T, MaxIter>(v, lower_limit, upper_limit, 1);
}

} /*namespace meta*/
} /*namespace chandra*/


#endif /*CHANDRA_META_MATH_H*/
