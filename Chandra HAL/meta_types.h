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

template<typename Value, typename Ratio>
struct ratio_cast
{
        static constexpr Value value = static_cast<Value>(Ratio::num) / Ratio::den;
};

// TODO: NEED TO IMPLEMENT THE RATIO CAST IN IAMB SO THAT FIXED-POINT VALUES ARE USABLE IN QUANTITIES....
} /*namespace chandra*/
#endif /*CHANDRA_META_TYPES_H*/

