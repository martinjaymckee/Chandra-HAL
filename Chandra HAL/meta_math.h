/*
 * meta_math.h
 *
 *  Created on: May 19, 2017
 *      Author: martin
 */

#ifndef CHANDRA_META_MATH_H
#define CHANDRA_META_MATH_H

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

} /*namespace meta*/
} /*namespace chandra*/


#endif /*CHANDRA_META_MATH_H*/
