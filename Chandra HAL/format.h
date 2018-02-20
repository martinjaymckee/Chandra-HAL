/*
 * format.h
 *
 *  Created on: Apr 16, 2016
 *      Author: martin
 */

#ifndef CHANDRA_FORMAT_H
#define CHANDRA_FORMAT_H

#include "cstr_utils.h"
#include "meta_math.h"

//
// TODO: MAKE THE VALUE TYPES BIND IN THE "ENCODE" CALLS, RATHER THAN IN THE CLASS ARGUMENTS
//      DOING SO WILL MAKE IT MUCH MORE LIKELY TO CATCH LOCAL OPTIMIZATIONS AND WILL MAKE IT
//      LESS NECESSARY TO USE EXPLICIT SPECIALIZATIONS AS TYPE DEDUCTION COULD BE USED.
//

namespace chandra
{

// TODO: IT SHOULD BE POSSIBLE TO CALCULATE _TEMP_SIZE FROM THE SIZE OF THE VALUE
//
// Format unsigned integer values
//
template<class Value, uint8_t _temp_size = 10>
struct Unsigned
{
    using value_t = Value;
	using size_t = uint16_t;

	static size_t encode( value_t _val, char* _buffer, char (&_temp)[_temp_size] ) {
	    char* p = _temp;
		size_t bytes_written = 0;

	    do {
	        *p++ = char(_val % 10) + '0';
	        _val /= 10;
	    } while (_val > 0);

	    do {
	        *_buffer++ = *--p;
	        ++bytes_written;
	    } while (p != _temp);

	    *_buffer = '\0';
	    return bytes_written; // TODO: DECIDE IF THE NULL TERMINATOR SHOULD BE INCLUDED HERE
	}

	static size_t encode( value_t _val, char* _buffer) {
	    char temp[_temp_size];
	    return encode(_val, _buffer, temp);
	}

};

// TODO: SIGNED SHOULD IDEALLY BE IMPLEMENTED USING THE UNSIGNED FORMATTER ABOVE
//		THEN ALL THAT NEEDS TO BE ADDED/CHANGED, IS THE MINUS SIGN
// TODO: IT WOULD BE NICE TO MAKE THIS ADD A PLUS SIGN USING AN "ALWAYS SIGNED" FLAG
//
// Format signed integer values
//
template<class Value, uint8_t _temp_size = 10>
struct Signed
{
    using value_t = Value;
	using size_t = uint16_t;

	static size_t encode( value_t _val, char* _buffer, char (&temp) [_temp_size] ) {
	    size_t bytes_written = 0;

	    if( _val < 0 ) {
	    	++bytes_written;
	    	_val *= -1;
	    	*_buffer = '-';
	    }

	    return (bytes_written + Unsigned<value_t, _temp_size>::encode(_val, _buffer+bytes_written, temp)); //TODO: DECIDE IF THE NULL TERMINATOR SHOULD BE INCLUDED HERE
	}

	static size_t encode( value_t _val, char* _buffer) {
	    char temp[_temp_size];
	    return encode(_val, _buffer, temp);
	}

};

// TODO: DECIDE HOW TO HANDLE FIXEDPOINT FORMATTING
// TODO: DECIDE HOW TO HANDLE SCIENTIFIC NOTATION, ETC.

//
// Format "real-number" values in standard decimal notation
//
template<class Value, uint8_t _digits = 5>
struct Decimal
{
    using value_t = Value;
	using size_t = uint16_t;

	static size_t encode( value_t _val, char * const _buffer ){
		char temp[24];
		size_t bytes_written = 0;

		char* _str = _buffer;
		static constexpr value_t frac_mult = meta::pow10<_digits>::value;
		const bool negative = _val < 0.0;
		_val = fabs(_val);
		const unsigned long whole = static_cast<unsigned long>(_val);
		const unsigned long fractional = static_cast<unsigned long>((_val-whole)*frac_mult);

		if(negative) {
			*_str = '-';
			++bytes_written;
			++_str;
		}

		bytes_written += Unsigned<unsigned long, 24>::encode(whole, _str, temp);
		_str = _buffer+bytes_written;
		*_str = '.'; ++_str;
		unsigned int place = static_cast<unsigned int>(frac_mult/10);
		while(fractional < place) {
			*_str = '0'; ++_str;
			place /= 10;
			++bytes_written;
		}

		if(fractional == 0){
			*_str = '\0';
			return bytes_written;
		}
		return (bytes_written + Unsigned<unsigned long, 24>::encode(fractional, _str, temp));
	}
};

} /*namespace chandra*/
#endif /*CHANDRA_FORMAT_H*/
