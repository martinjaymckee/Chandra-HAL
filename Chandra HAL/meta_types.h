#ifndef CHANDRA_META_TYPES_H
#define CHANDRA_META_TYPES_H

#include "matrix.h"
namespace chandra
{

template<typename Value>
struct scalar_of
{
        using type = Value;
};

template<typename Value, size_t N, size_t M>
struct scalar_of<math::Matrix<Value, N, M>>
{
        using type = Value;
};

template<typename Value>
using scalar_of_t = typename scalar_of<Value>::type;

template<typename Ratio, typename Value>
Value ratio_cast(const Value& v) {
    cout << "\t*** Default Ratio Cast\n";
    return (v * Ratio::num) / Ratio::den;
}

#if defined(__USING_IAMB__)
template<typename Ratio, typename S, size_t F, typename C>
auto ratio_cast(const iamb::FixedPoint<S, F, C>& v) {
    using value_t = iamb::FixedPoint<S, F, C>;
    cout << "\t*** Iamb Ratio Cast!\n";
    return v * value_t::IntDiv(Ratio::num, Ratio::den);
}
#endif

} /*namespace chandra*/
#endif /*CHANDRA_META_TYPES_H*/

