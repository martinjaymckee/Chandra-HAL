#ifndef CHANDRA_HORNERS_METHOD_H
#define CHANDRA_HORNERS_METHOD_H

#include <type_traits>

namespace chandra
{
namespace math
{
namespace internal
{
template<typename Value, size_t N>
struct HornersMethodImpl
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[N], const V2& x) {
      (void) c;
      (void) x;
      return 0;
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 1>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[1], const V2&) {
      return c[0];
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 2>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[2], const V2& x) {
      return c[0]*x + c[1];
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 3>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[3], const V2& x) {
      return x*(c[0]*x + c[1]) + c[2];
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 4>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[4], const V2& x) {
      return x*(x*(c[0]*x + c[1]) + c[2]) + c[3];
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 5>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[5], const V2& x) {
      return x*(x*(x*(c[0]*x + c[1]) + c[2]) + c[3]) + c[4];
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 6>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[6], const V2& x) {
      return x*(x*(x*(x*(c[0]*x + c[1]) + c[2]) + c[3]) + c[4]) + c[5];
    }
};

template<typename Value>
struct HornersMethodImpl<Value, 7>
{
    template<typename V1, typename V2>
    constexpr static Value exec(const V1 (&c)[7], const V2& x) {
      return x*(x*(x*(x*(x*(c[0]*x+c[1])+c[2])+c[3])+c[4])+c[5])+c[6];
    }
};

} /*namespace internal*/

template<typename V1, typename V2, size_t N>
auto HornersMethod(const V1 (&c)[N], const V2& x) {
  using Value = typename std::common_type<V1, V2>::type;
  return internal::HornersMethodImpl<Value, N>::exec(c, x);
}

} /*namespace math*/
} /*namespace chandra*/
#endif /*CHANDRA_HORNERS_METHOD_H*/
