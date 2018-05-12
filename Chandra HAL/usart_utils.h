#ifndef CHANDRA_USART_UTILS_H
#define CHANDRA_USART_UTILS_H

namespace chandra
{
namespace io
{

template <class T>
struct USARTClockStatus
{
        T clk;
        T ppm;
};

enum class Parity {
    None = 0x00,
    Even = 0x02,
    Odd = 0x03
};

namespace internal
{
template<class Value, class Timepoint>
struct TimestampedValue
{
        Value value;
        Timepoint timestamp;
        operator Value () const { return value; }
};

template<class Value, class Timepoint, bool _timestamped=false>
struct RX
{
        static Value encode(const Value& _value) { return _value; }
};


template<class Value, class Timepoint>
struct RX<Value, Timepoint, true>
{
        static TimestampedValue<Value, Timepoint> encode(const Value& _value) {
            return {_value, Timepoint::clock::now()};
        }
};
} /*namespace internal*/
} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_SART_UTILS_H*/

