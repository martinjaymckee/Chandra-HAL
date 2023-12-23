#ifndef CHANDRA_PARITY_H
#define CHANDRA_PARITY_H

#include <stdint.h>

namespace chandra
{

template<class T>
constexpr bool odd_parity(T _data) {
	const size_t count = pop_ones(_data);
	return (count & 0x01) ? false : true;
}

template<class T>
constexpr bool even_parity(T _data) {
	const size_t count = pop_ones(_data);
	return (count & 0x01) ? true : false;
}

} /*namespace chandra*/

#endif /*CHANDRA_PARITY_H*/
