#ifndef CHANDRA_BUFFER_STREAM_H
#define CHANDRA_BUFFER_STREAM_H

// #include <cstdio>
// #include <cmath>
#include <stdint.h>
// #include <string.h>

#include "circular_buffer.h"
// #include "format.h"
#include "stream.h"

namespace chandra
{
namespace io
{

template<class Value = uint8_t, size_t Capacity = 128>
class BufferStream : public Stream< BufferStream<Value, Capacity> >
{
	public:
    using value_t = Value;
    using ref_t = BufferStream<Value, Capacity>;

    BufferStream() {}

    bool put( char _ch, bool _raw = true) {
      (void) _raw;
      buffer_ << _ch;
      return true;
		}

		operator value_t() { return read(); }

		value_t read() { return value_t(buffer_); }

    auto available() const { return buffer_.available(); }

    ref_t& operator >> ( value_t& _ch ) {
      _ch = read();
      return *this;
		}

	private:
    chandra::FixedCircularBuffer<value_t, Capacity> buffer_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_VIRTUAL_SERIAL_H*/
