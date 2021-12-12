#ifndef CHANDRA_ARITHMETIC_H
#define CHANDRA_ARITHMETIC_H

#include<type_traits>
#include<utility>

namespace chandra
{
namespace math
{
namespace detail
{
template<class OpA, class OpB>
struct default_sum_type
{
  using type = decltype(std::declval<OpA>() + std::declval<OpB>());
};

template<class OpA, class OpB>
struct default_difference_type
{
  using type = decltype(std::declval<OpA>() - std::declval<OpB>());
};

template<class OpA, class OpB>
struct default_product_type
{
  using type = decltype(std::declval<OpA>() * std::declval<OpB>());
};

template<class Den, class Num>
struct default_division_type
{
  using type = decltype(std::declval<Den>() / std::declval<Num>());
};

} /*namespace detail*/

template<class Derived, class DivisionType = detail::default_division_type, class IsValidOperand = std::is_convertible>
class Divisible
{
  public:
    template<class Den, class Num>
    using division_type = typename DivisionType<Den, Num>::type;

    template<
      class Upper,
      class ReturnType = division_type<Upper, Derived>,
      class is_convertible = typename std::enable_if<IsValidOperand<Derived, Lower>::value, ReturnType>::type
    >
    friend auto operator / (const Derived& _num, const Lower& _den) {
      using return_t = division_type<Derived, Lower>;
      
      return return_t{};
    }

    // template<
    //   class Upper,
    //   class ReturnType = division_type<Upper, Derived>,
    //   class is_convertible = typename std::enable_if<IsValidOperand<Upper, Lower>::value, ReturnType>::type
    // >
    // friend auto operator / (const Upper& _num, const Derived& _den) {
    //   using return_t = division_type<Upper, Derived>;
    //   return return_t{};
    // }

    template<
      class Lower,
      class ReturnType = division_type<Derived, Lower>,
      class is_convertible = typename std::enable_if<IsValidOperand<Derived, Lower>::value, ReturnType>::type
    >
    Derived& operator /= (const Lower& _den) {
      static_assert(std::is_same(Derived, return_t), "Division-Assignment which results in a different type is not allowed");
      *this = *this / _den;
      return *this;
    }
};

}
}

#endif /* CHANDRA_ARITHMETIC_H */
