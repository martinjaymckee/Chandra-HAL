#ifndef CHANDRA_BITCOUNT_H
#define CHANDRA_BITCOUNT_H

#include <stdint.h>

namespace chandra
{

template<class T>
constexpr size_t pop_ones(T _data) {
	// NOTE: THE TYPE T MUST BE OF INTEGRAL TYPE FOR THIS TO WORK, IT WOULD BE GOOD
	//	TO DO SOME TEMPLATE METAPROGRAMMING TO GUARANTEE THAT IT IS.
//	constexpr size_t max_bits = 8 * sizeof(T);
	size_t count = 0;
	while(_data != 0) {
		count += (_data & 0x01) ? 1 : 0;
		_data >>= 1;
	}
	return count;
}

template<class T>
constexpr size_t pop_zeros(T _data) {
	// NOTE: THE TYPE T MUST BE OF INTEGRAL TYPE FOR THIS TO WORK, IT WOULD BE GOOD
	//	TO DO SOME TEMPLATE METAPROGRAMMING TO GUARANTEE THAT IT IS.
//	constexpr size_t max_bits = 8 * sizeof(T);
	size_t count = 0;
	while(_data != 0) {
		count += (_data & 0x01) ? 0 : 1;
		_data >>= 1;
	}
	return count;
}

} /*namespace chandra*/

#endif /*CHANDRA_BITCOUNT_H*/
