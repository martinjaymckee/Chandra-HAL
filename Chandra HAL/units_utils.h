#ifndef CHANDRA_DIMENSION_CONVERT_H
#define CHANDRA_DIMENSION_CONVERT_H

#include <ratio>
#include <type_traits>
#include <utility>

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
            return _val + ratio_cast<Ratio>(Value{1});
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
            return _val - ratio_cast<Ratio>(Value{1});
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
//            cout << "\t*** Default scale -- ratio<" << Num << ", " << Den << ">\n";
            return (Num * _v) / Den;
        }
};

// Pass implementation
template<typename Value, bool Integral, bool NumOne, bool DenOne, intmax_t N>
struct convert_scale_impl<Value, Integral, NumOne, DenOne, N, N>
{
        static Value calc(const Value& _v) {
//            cout << "\t*** Pass -- ratio<" << N << ", " << N << ">\n";
            return _v;
        }
};

// Multiply implementation
template<typename Value, bool Integral, intmax_t N>
struct convert_scale_impl<Value, Integral, false, true, N, 1>
{
        static Value calc(const Value& _v) {
//            cout << "\t*** Multiply -- ratio<" << N << ", " << 1 << ">\n";
            return N*_v;
        }
};

// Divide implementation
template<typename Value, bool Integral, intmax_t N>
struct convert_scale_impl<Value, Integral, true, false, 1, N>
{
        static Value calc(const Value& _v) {
//            cout << "\t*** Divide -- ratio<" << 1 << ", " << N << ">\n";
            return _v/N;
        }
};

//template<typename T> struct TD;

// Optimized FP implementation
template<typename Value, intmax_t Num, intmax_t Den>
struct convert_scale_impl<Value, false, false, false, Num, Den>
{
        static Value calc(const Value& _v) {
            using ratio_t = std::ratio<Num, Den>;
//            cout << "\t*** Optimized FP -- ratio<" << Num << ", " << Den << ">\n";
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

template<typename Value, typename Dest, typename Src, typename V2>
constexpr Value convert(const V2& _val) {
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
    using convert_factor_t = std::ratio<
        src_factor_t::num*dest_factor_t::den,
        src_factor_t::den*dest_factor_t::num
    >; // TODO: TEST THIS

    return internal::offset_add<typename Dest::offset_t>(
        internal::convert_scale<convert_factor_t>(
            internal::offset_sub<typename Src::offset_t>(static_cast<Value>(_val))
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

template<typename Dims, typename Factor, size_t Exp>
struct PowUnitsImpl
{
    using child_t = PowUnitsImpl<Dims, Factor, Exp-1>;
    using dimensions_t = decltype(Dims()*typename child_t::dimensions_t());
    using factor_t = typename std::ratio_multiply<Factor, typename child_t::factor_t>::type;
};

template<typename Dims, typename Factor>
struct PowUnitsImpl<Dims, Factor, 1>
{
    using dimensions_t = Dims;
    using factor_t = Factor;
};

template<typename Dims, typename Factor>
struct PowUnitsImpl<Dims, Factor, 0>
{
    using dimensions_t = chandra::units::dimensions::Unitless;
    using factor_t = std::ratio<1,1>;
};

template<typename Units, size_t Exp>
struct PowUnits
{
        static_assert(!Units::absolute, "Unable to raise absolute units to a power");
        using impl_t = PowUnitsImpl<typename Units::dimensions_t, typename Units::factor_t, Exp>;
        using dimensions_t = typename impl_t::dimensions_t;
        using factor_t = typename impl_t::factor_t;
        using offset_t = std::ratio<0,1>;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            Units::streamname(_stream);
            _stream << "^";
            _stream << Exp;
        }
};

template<typename Units>
struct SqrtUnits
{
    static_assert(!Units::absolute, "Unable to take square root of absolute units");
    using dims_a = typename Units::dimensions_t;
    using dimensions_t = decltype(std::declval<dims_a>().sqrt());
    using factor_t = typename Units::factor_t;
    using offset_t = std::ratio<0,1>;
    static constexpr bool absolute = false;
    template<typename Stream>
    static void streamname(Stream& _stream) {
        Units::streamname(_stream);
        _stream << "^1/2";
    }
};
} /*namespace internal*/

// TODO: THERE SHOULD BE A WAY TO CONSTRAIN THE UNITS TYPE TO SOMETHING THAT
//  IS A LENGTH, MASS, ETC. IN THESE SORTS OF FUNCTIONS
template<
  typename L,
  typename is_L = typename std::is_same<typename L::dimensions_t, chandra::units::dimensions::Length>
>
using areaFrom = internal::PowUnits<L, 2>;

template<
  typename L,
  typename is_L = typename std::is_same<typename L::dimensions_t, chandra::units::dimensions::Length>
>
using volumeFrom = internal::PowUnits<L, 3>;

template<
  typename M, typename L,
  typename is_M = typename std::is_same<typename M::dimensions_t, chandra::units::dimensions::Mass>::type,
  typename is_L = typename std::is_same<typename L::dimensions_t, chandra::units::dimensions::Length>::type
>
using densityFrom = internal::DivUnits<M, volumeFrom<L>>;

template<typename L, typename T>
using velocityFrom = internal::DivUnits<L, T>;

template<typename L, typename T>
using accelerationFrom = internal::DivUnits<L, internal::PowUnits<T, 2>>;

template<typename F, typename L>
using pressureFrom = internal::DivUnits<F, areaFrom<L>>;

template<typename U>
using sqrtOf = internal::SqrtUnits<U>;
} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_DIMENSION_CONVERT_H*/
