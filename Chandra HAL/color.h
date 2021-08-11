#ifndef CHANDRA_COLOR_H
#define CHANDRA_COLOR_H

namespace chandra
{
namespace color
{

enum class ColorSpace
{
  RGB,
  XYZ,
  HSV,
  LHC
};

template<class T=uint8_t>
struct Color
{
  Color(const T& gray=0) : r(gray), g(gray), b(gray) {}

  Color(const T& _r, const T& _g, const T& _b)
    : r(_r), g(_g), b(_b) {}

  template<class T2>
  Color(const Color<T2>& _other)
    : r(static_cast<T>(_other.r)),
    g(static_cast<T>(_other.g)),
    b(static_cast<T>(_other.b)) {}

  template<class T2>
  Color<T>& operator = (const T2& _gray) {
    r = static_cast<T>(_gray);
    g = static_cast<T>(_gray);
    b = static_cast<T>(_gray);
    return *this;
  }

  template<class T2>
  Color<T>& operator = (const Color<T2>& _other) {
    r = static_cast<T>(_other.r);
    g = static_cast<T>(_other.g);
    b = static_cast<T>(_other.b);
    return *this;
  }

  T r;
  T g;
  T b;
};


template<class T, class Q, class R, class Calc=uint32_t>
auto int_lerp(const T& _weight, const Color<Q>& _a, const Color<R>& _b, const Calc& _scale=Calc{256}) {
  using return_value_t = typename std::common_type<Q, R>::type;
  const Calc weight_a{_weight};
  const Calc weight_b{(_scale - 1) - _weight};
	const auto red{((weight_a*_a.r) + (weight_b*_b.r)) / _scale};
	const auto green{((weight_a*_a.g) + (weight_b*_b.g)) / _scale};
	const auto blue{((weight_a*_a.b) + (weight_b*_b.b)) / _scale};
	return Color<return_value_t>(
    static_cast<return_value_t>(red),
    static_cast<return_value_t>(green),
    static_cast<return_value_t>(blue)
  );
}

} /*namespace color*/
} /*namespace chandra*/

#endif /*CHANDRA_COLOR_H*/
