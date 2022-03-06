#ifndef CHANDRA_STREAM_H
#define CHANDRA_STREAM_H

#include "format.h"

//
// Pre-processor directives to configure the ASCII formatting
//	of floating-point numbers
//
#ifndef CHANDRA_FLOAT_FORMAT_DIGITS
#define CHANDRA_FLOAT_FORMAT_DIGITS 2
#endif

#ifndef CHANDRA_DOUBLE_FORMAT_DIGITS
#define CHANDRA_DOUBLE_FORMAT_DIGITS 4
#endif

#ifndef CHANDRA_LONG_DOUBLE_FORMAT_DIGITS
#define CHANDRA_LONG_DOUBLE_FORMAT_DIGITS 6
#endif

namespace chandra
{
//
// The stream classes define a mix-in class (Stream) that is used to add stream methods to other classes.
//	These stream methods include both ASCII and binary stream insertion operators as well as some stream
//	manipulators that can be overridden for sub-classes of Stream.
//
enum class StreamError {
	Ok
};

enum class StreamJustify {
	Left,
	Right
};

class ASCIIStreamImpl // TODO: THE SIZES OF THESE ARE NOT CLEAR.... IT SHOULD BE POSSIBLE TO CALCULATE THEM AT LEAST APPROXIMATELY FROM THE SIZE OF THE VALUES
{
	public: // TODO: USE THE RETURNED FORMAT SIZE IN THESE FUNCTIONS
		StreamError ASCIIformat(const unsigned char& _value, char* _p) {
			Unsigned<unsigned char, 3>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const signed char& _value, char* _p) {
			Signed<signed char, 4>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const unsigned short& _value, char* _p) {
			Unsigned<unsigned char, 5>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const signed short& _value, char* _p) {
			Signed<signed short, 6>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const unsigned int& _value, char* _p) {
			Unsigned<unsigned int, 10>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const signed int& _value, char* _p) {
			Signed<signed int, 11>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const unsigned long& _value, char* _p) {
			Unsigned<unsigned long, 19>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const signed long& _value, char* _p) {
			Unsigned<signed short, 20>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const float& _value, char* _p) {
			Decimal<float, CHANDRA_FLOAT_FORMAT_DIGITS>::encode(_value, _p);
			return StreamError::Ok;
		}

		StreamError ASCIIformat(const double& _value, char* _p) {
			Decimal<double, CHANDRA_DOUBLE_FORMAT_DIGITS>::encode(_value, _p);
			return StreamError::Ok;
		}

    StreamError ASCIIformat(const long double& _value, char* _p) {
        Decimal<double, CHANDRA_LONG_DOUBLE_FORMAT_DIGITS>::encode(_value, _p);
        return StreamError::Ok;
    }
};

class BinaryStreamImpl
{
	public:
		template<class T>
		StreamError BINformat(const T& _value, char* _p) {
			static constexpr uint8_t bytes = 8 * sizeof(T);
			// TODO: IMPLEMENT THE BINARY STREAMING HERE
			return StreamError::Ok;
		}
};

namespace impl
{
	// TODO: IMPLEMENT THE ABILITY TO CONFIGURE THE STREAM TO CHOSE ASCII OR BINARY STREAMING
} /* namespace impl */

template<class Derived>
class Stream : public ASCIIStreamImpl, public BinaryStreamImpl
{
	public:
		bool puts(const char* _p, bool _raw=false) { // TODO: THIS SHOULD REALLY USE UINT8_T....
			char c;
			while((c=*_p) != '\0'){
				if(!static_cast<Derived*>(this)->put(c, _raw)) return false;
				++_p;
			}

			return true;
		}
};

//
// Insertion operator for basic formatted insertions
// TODO: MAKE THIS WORK FOR BINARY FORMAT TOO.
template<class Derived, class T>
Derived& operator << (Stream<Derived>& _stream, const T& _value) {
	Derived& stream = static_cast<Derived&>(_stream);
    char buffer[30]; // TODO: IS THERE A BETTER PLACE TO STORE THIS OR TO CALCULATE THE SIZE OF THIS BUFFER?
    //char* p = buffer;
    stream.ASCIIformat(_value, &buffer[0]);
    stream.puts(buffer);
    return stream;
}

//
// Insertion operator to insert a single char into the stream
//
template<class Derived>
Derived& operator << (Stream<Derived>& _stream, const char& _value) {
	Derived& stream = static_cast<Derived&>(_stream);
    stream.put(_value);
    return stream;
}

//
// Insertion operator to insert c-strings into the stream
//
// template<class Derived>
// Derived& operator << (Stream<Derived>& _stream, const char* _value) {
// 	Derived& stream = static_cast<Derived&>(_stream);
//     stream.puts(_value);
//     return stream;
// }

//
// Insertion operator to insert a (null-terminated) character buffer / c-string into the stream
//
template<class Derived, size_t N>
Derived& operator << (Stream<Derived>& _stream, const char (&_buffer)[N]) {
	Derived& stream = static_cast<Derived&>(_stream);
    stream.puts(static_cast<const char*>(&_buffer[0]));
    return stream;
}

//
// Stream manipulator to command an end-of-line on the stream
//
struct eol {
	eol() {}
};

struct RawCharacterWrapper
{
	RawCharacterWrapper(char _ch) : ch(_ch) {}
	char ch;
};

struct RawStringWrapper
{
	RawStringWrapper(const char* _s) : s(_s) {}
	const char* s;
};

// TODO: CREATE A RAW STRING WRAPPER LIKE THE CHARACTER WRAPPER

static inline RawCharacterWrapper raw_c(char _ch) { return {_ch}; }

template<class Derived>
Derived& operator << (Stream<Derived>& _stream, eol) { return _stream; }

template<class Derived>
Derived& operator << (Stream<Derived>& _stream, const RawCharacterWrapper& _raw) {
	static_cast<Derived*>(&_stream)->put(_raw.ch, true);
	return *static_cast<Derived*>(&_stream);
}

template<class Derived>
Derived& operator << (Stream<Derived>& _stream, const RawStringWrapper& _raw) {
	static_cast<Derived*>(&_stream)->puts(_raw.s, true);
	return *static_cast<Derived*>(&_stream);
}

//
// Fixed-Width Manipulator
//
template<class T, uint8_t Width, StreamJustify Justified = StreamJustify::Right>
struct FixedWidthManipulator
{
	FixedWidthManipulator(const T& _value, const char& _fill = ' ') : value(_value), fill(_fill) {}

	const T& value;
	const char fill;

	static constexpr uint8_t width = Width;
	static constexpr StreamJustify justified = Justified;
};

template<uint8_t Width, class T>
FixedWidthManipulator<T, Width, StreamJustify::Right> right_fixed_width(const T& _value, const char& _fill = ' ') {
	return FixedWidthManipulator<T, Width, StreamJustify::Right>(_value, _fill);
}

template<uint8_t Width, class T>
FixedWidthManipulator<T, Width, StreamJustify::Left> left_fixed_width(const T& _value, const char& _fill = ' ') {
	return FixedWidthManipulator<T, Width, StreamJustify::Left>(_value, _fill);
}

template<class Derived, class T, uint8_t Width, StreamJustify Justified>
Derived& operator << (Stream<Derived>& _stream, const FixedWidthManipulator<T, Width, Justified>& _fw) {
	char temp[_fw.width + 1];
	Derived& stream = static_cast<Derived&>(_stream);

	stream.ASCIIformat(_fw.value, temp);
	const uint8_t format_width = cstr::length(temp);

	if(format_width < _fw.width) { // Need to fill
		const uint8_t fill_width = _fw.width - format_width;
		if(_fw.justified == StreamJustify::Left) {
			stream.puts(temp);
			for(uint8_t i = 0; i < fill_width; ++i) stream << _fw.fill;
		} else {
			for(uint8_t i = 0; i < fill_width; ++i) stream << _fw.fill;
			stream.puts(temp);
		}
	} else if (format_width > _fw.width) { // Over-full!!
		for(uint8_t i = 0; i < _fw.width; ++i) stream << '?';
	} else {
		stream.puts(temp);
	}

	return stream;
}

} /*namespace chandra*/
#endif /*CHANDRA_STREAM_H*/
