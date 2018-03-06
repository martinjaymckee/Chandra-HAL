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

template<bool Integral, bool Simple, bool Pass, intmax_t Num, intmax_t Den>
struct convert_scale_impl
{
        template<typename Value>
        static constexpr auto calc(const Value& _val) {
            TD<std::ratio<Num,Den>> simple;
            return (Num*_val) / Den;
        }
};

template<intmax_t Num, intmax_t Den>
struct convert_scale_impl<false, false, false, Num, Den>
{
        template<typename Value>
        static constexpr auto calc(const Value& _val) {
            TD<std::ratio<Num,Den>> floating;
            using ratio_t = std::ratio<Num, Den>;
            using scalar_t = scalar_of_t<Value>;
            constexpr auto factor = ratio_cast<scalar_t, ratio_t>::value;
            return factor * _val;
        }
};

template<bool Integral, intmax_t Num>
struct convert_scale_impl<Integral, true, false, Num, 1>
{
        template<typename Value>
        static constexpr auto calc(const Value& _val) {
            TD<std::ratio<Num,1>> mult;
            return Num*_val;
        }
};

template<bool Integral, intmax_t Den>
struct convert_scale_impl<Integral, true, false, 1, Den>
{
        template<typename Value>
        static constexpr auto calc(const Value& _val) {
            TD<std::ratio<1,Den>> div;
            return _val/Den;
        }
};

template<bool Integral, bool Simple, intmax_t N>
struct convert_scale_impl<Integral, Simple, true, N, N>
{
        template<typename Value>
        static constexpr auto calc(const Value& _val) {
            TD<std::ratio<N,N>> pass;
            return _val;
        }
};

template<typename Dest, typename Src, typename Value>
constexpr auto convert_scale(const Value& _val) {
    using convert_ratio_t = std::ratio<Dest::den*Src::num, Dest::num*Src::den>;
    TD<convert_ratio_t> convert;
    return convert_scale_impl<
            !std::is_integral<scalar_of_t<Value>>::value,
            (convert_ratio_t::num == 1 || convert_ratio_t::den == 1),
            (convert_ratio_t::num == convert_ratio_t::den),
            convert_ratio_t::num,
            convert_ratio_t::den
        >::calc(_val);
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

