/*
 * cstr_utils.h
 *
 *  Created on: Feb 3, 2017
 *      Author: martin
 */

#ifndef CHANDRA_CSTR_UTILS_H
#define CHANDRA_CSTR_UTILS_H

#include "stdint.h"

namespace chandra
{
namespace cstr
{
//
// Get the length of a null terminated list
//
template<class T>
size_t length(const T * const _buffer){
	const T * p = _buffer;
    size_t len = 0;
	while(*p) {
		++len;
		++p;
	}
	return len;
}

//
// Copy a c-string into a buffer but only if the buffer is large enough to accommodate it
//	Returns: Number of characters written "excluding" the final '\0'
//	Copy with explicit length -- TODO: THIS SHOULD BE MADE AN EXTERNAL FUNCTION WITH THE DEFINITION IN AN IMPLEMENTATION FILE
template<class T>
size_t copy(T * const _buffer, const size_t _max_length, const T * _cstr) {
    const size_t len = length(_cstr);
	if(len >= _max_length){
		*(_buffer+_max_length) = '\0';
		return 0;
	}
	T* p = _buffer;
	T c;
	while((c = *_cstr)) {
		*p = c;
		++p;
		++_cstr;
	}
	return len - 1;
}

//	Copy with implicit length taken from buffer
template<typename T, size_t _buffer_length>
size_t copy(T (& _buffer)[_buffer_length], const T* _cstr) {
	return copy(_buffer, _buffer_length, _cstr);
}

//
// Append a c-string onto a buffer, but only if the buffer is large enough to accommodate it
//
//	Append with explicit length
template<class T>
size_t append(T* _buffer, const size_t _max_length, const T* _cstr) {
    const size_t src_length = length(_cstr);
	if(src_length >= _max_length){
		*(_buffer+_max_length) = '\0';
		return 0;
	}
    const size_t dest_length = length(_cstr);
	if(dest_length >= _max_length){
		*(_buffer+_max_length) = '\0';
		return 0;
	}
	return copy((_buffer+dest_length), _max_length-dest_length, _cstr);
}

//	Append with implicit length taken from buffer
template<class T, size_t _buffer_length>
size_t append(T (&_buffer)[_buffer_length], const T * _cstr) {
    const size_t dest_length = length(_buffer);
	if(dest_length >= _buffer_length){
		_buffer[_buffer_length-1] = '\0';
		return 0;
	}
	return copy(&_buffer[dest_length], (_buffer_length-dest_length), _cstr);
}

} /*namespace cstr*/
} /*namespace chandra*/

#endif /*CHANDRA_CSTR_UTILS_H*/
