#ifndef CHANDRA_DIMENSION_CONVERT_H
#define CHANDRA_DIMENSION_CONVERT_H

#include <ratio>
#include <type_traits>

#include "dimensions.h"
#include "meta_types.h"

namespace chandra
{
namespace units
{
namespace internal
{

// TODO: NEED TO OPTIMIZE THE OFFSETS TO SIMPLY PASS THE VALUE IF THE OFFSET IS ZERO
template<bool Pass, typename Ratio>
struct offset_add_impl
{
        template<typename Value>
        static constexpr Value calc(const Value& _val) {
            return _val;
        }
};

template<typename Ratio>
struct offset_add_impl<false, Ratio>
{
        template<typename Value>
        static constexpr Value calc(const Value& _val) {
            return _val + ratio_cast<scalar_of_t<Value>, Ratio>::value;
        }
};

template<typename Ratio, typename Value>
constexpr auto offset_add(const Value& _val) {
    return offset_add_impl<(Ratio::num == 0), Ratio>::calc(_val);
}

template<bool Pass, typename Ratio>
struct offset_sub_impl
{
        template<typename Value>
        static constexpr Value calc(const Value& _val) {
            return _val;
        }
};

template<typename Ratio>
struct offset_sub_impl<false, Ratio>
{
        template<typename Value>
        static constexpr Value calc(const Value& _val) {
            return _val - ratio_cast<scalar_of_t<Value>, Ratio>::value;
        }
};

template<typename Ratio, typename Value>
constexpr auto offset_sub(const Value& _val) {
    return offset_sub_impl<(Ratio::num == 0), Ratio>::calc(_val);
}


template<typename T> struct TD;

// Default implementation -- for arbitrary ratio and integral values
template<typename Value, bool Integral, bool NumOne, bool DenOne, intmax_t Num, intmax_t Den>
struct convert_scale_impl
{
        static Value calc(const Value& _v) {
            cout << "\t*** Default scale -- ratio<" << Num << ", " << Den << ">\n";
            return (Num * _v) / Den;
        }
};

// Pass implementation
template<typename Value, bool Integral, bool NumOne, bool DenOne, intmax_t N>
struct convert_scale_impl<Value, Integral, NumOne, DenOne, N, N>
{
        static Value calc(const Value& _v) {
            cout << "\t*** Pass -- ratio<" << N << ", " << N << ">\n";
            return _v;
        }
};

// Multiply implementation
template<typename Value, bool Integral, intmax_t N>
struct convert_scale_impl<Value, Integral, false, true, N, 1>
{
        static Value calc(const Value& _v) {
            cout << "\t*** Multiply -- ratio<" << N << ", " << 1 << ">\n";
            return N*_v;
        }
};

// Divide implementation
template<typename Value, bool Integral, intmax_t N>
struct convert_scale_impl<Value, Integral, true, false, 1, N>
{
        static Value calc(const Value& _v) {
            cout << "\t*** Divide -- ratio<" << 1 << ", " << N << ">\n";
            return _v/N;
        }
};

// Optimized FP implementation
template<typename Value, intmax_t Num, intmax_t Den>
struct convert_scale_impl<Value, false, false, false, Num, Den>
{
        static Value calc(const Value& _v) {
            using ratio_t = std::ratio<Num, Den>;
            cout << "\t*** Optimized FP -- ratio<" << Num << ", " << Den << ">\n";
            return ratio_cast<ratio_t>(_v);
        }
};

template<typename Ratio, typename Value>
Value convert_scale(const Value& _v) {
    return convert_scale_impl<
            Value,                          // Pass in Value type
            std::is_integral<Value>::value, // Check if Value is integral
            (Ratio::num == 1),              // Check if the numerator is one
            (Ratio::den == 1),              // Check if the denominator is one
            Ratio::num,                     // Pass the numerator
            Ratio::den                      // Pass the denominator
            >::calc(_v);
}
} /*namespace internal*/

template<typename Dest, typename Src, typename Value>
constexpr Value convert(const Value& _val) {
    static_assert(
        Dest::absolute == Src::absolute,
        "Attempting to convert between relative and absolute units."
    );
    static_assert(
        dimensions::DimensionsMatch<
            typename Dest::dimensions_t,
            typename Src::dimensions_t
         >::value,
        "Attempting to convert between incommensurate dimensions."
    );

    using src_factor_t = typename Src::factor_t;
    using dest_factor_t = typename Dest::factor_t;
    return internal::offset_add<typename Dest::offset_t>(
        internal::convert_scale<dest_factor_t, src_factor_t>(
            internal::offset_sub<typename Src::offset_t>(_val)
        )
    );
}

namespace internal
{
template<typename UnitsA, typename UnitsB>
struct MultUnits
{
        static_assert(!(UnitsA::absolute || UnitsB::absolute), "Unable to multiply absolute units");
        using dims_a = typename UnitsA::dimensions_t;
        using dims_b = typename UnitsB::dimensions_t;
        using dimensions_t = decltype(dims_a()*dims_b());
        using factor_t = typename std::ratio_multiply<typename UnitsA::factor_t, typename UnitsB::factor_t>::type;
        using offset_t = std::ratio<0,1>;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "(";
            UnitsA::streamname(_stream);
            _stream << "*";
            UnitsB::streamname(_stream);
            _stream << ")";
        }
};

template<typename UnitsA, typename UnitsB>
struct DivUnits
{
        static_assert(!(UnitsA::absolute || UnitsB::absolute), "Unable to divide absolute units");
        using dims_a = typename UnitsA::dimensions_t;
        using dims_b = typename UnitsB::dimensions_t;
        using dimensions_t = decltype(dims_a()/dims_b());
        using factor_t = typename std::ratio_divide<typename UnitsA::factor_t, typename UnitsB::factor_t>::type;
        using offset_t = std::ratio<0,1>;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            UnitsA::streamname(_stream);
            _stream << "/";
            UnitsB::streamname(_stream);
        }
};
} /*namespace internal*/
} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_DIMENSION_CONVERT_H*/

