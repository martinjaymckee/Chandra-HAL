#ifndef CHANDRA_MATRIX_VIEW_H
#define CHANDRA_MATRIX_VIEW_H

#include "matrix.h"

namespace chandra
{
namespace math
{

namespace internal
{

template<typename Value>
class ValueProxy
{
    public:
        using value_t = Value;

        explicit constexpr ValueProxy(value_t& _ref) : ref_(_ref) {}

        template<class V>
        constexpr ValueProxy& operator = (const V& v) {
            ref_ = v;
            return *this;
        }

        template<class V>
        constexpr ValueProxy<Value>& operator = (const ValueProxy<V>& v) {
            ref_ = v.value();
            return *this;
        }

        constexpr operator value_t() { return ref_; }

        constexpr value_t value() const { return ref_; }

    private:
        value_t& ref_;
};

template<class V1, class V2>
constexpr bool operator == (const ValueProxy<V1>& _a, const ValueProxy<V2>& _b) {
  return _a.value() == _b.value();
}

template<class V1, class V2>
constexpr bool operator != (const ValueProxy<V1>& _a, const ValueProxy<V2>& _b) {
  return _a.value() != _b.value();
}

} /*namespace internal*/

template<typename Value, size_t N>
struct Vector : public Matrix<Value, N, 1>
{
        using value_t = Value;
        using base_t = Matrix<value_t, N, 1>;
};

template<typename Value>
struct Vector<Value, 2> : public Matrix<Value, 2, 1>
{
        using value_t = Value;
        using base_t = Matrix<value_t, 2, 1>;
        using ref_t = Vector<value_t, 2>;

        constexpr Vector(const base_t& m)
            : base_t(m),
              x(this->data_[0][0]),
              y(this->data_[1][0]) {}

        constexpr Vector(const ref_t& v) : Vector(static_cast<const base_t&>(v)) {}

        internal::ValueProxy<value_t> x;
        internal::ValueProxy<value_t> y;
};

template<typename Value>
struct Vector<Value, 3> : public Matrix<Value, 3, 1>
{
        using value_t = Value;
        using base_t = Matrix<value_t, 3, 1>;
        using ref_t = Vector<value_t, 3>;

        constexpr Vector(const base_t& m)
            : base_t(m),
              x(this->data_[0][0]),
              y(this->data_[1][0]),
              z(this->data_[2][0]) {}

        constexpr Vector(const ref_t& v) : Vector(static_cast<const base_t&>(v)) {}

        internal::ValueProxy<value_t> x;
        internal::ValueProxy<value_t> y;
        internal::ValueProxy<value_t> z;
};

template<typename Value>
struct Vector<Value, 4> : public Matrix<Value, 4, 1>
{
        using value_t = Value;
        using base_t = Matrix<value_t, 4, 1>;
        using ref_t = Vector<value_t, 4>;

        constexpr Vector(const base_t& m)
            : base_t(m),
            w(this->data_[0][0]),
            x(this->data_[1][0]),
            y(this->data_[2][0]),
            z(this->data_[3][0]) {}

        constexpr Vector(const ref_t& v) : Vector(static_cast<const base_t&>(v)) {}

        internal::ValueProxy<value_t> w;
        internal::ValueProxy<value_t> x;
        internal::ValueProxy<value_t> y;
        internal::ValueProxy<value_t> z;
};

template<class Value>
using Vector2D = Vector<Value, 2>;

template<class Value>
using Vector3D = Vector<Value, 3>;

template<class Value>
using Vector4D = Vector<Value, 4>;

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_VIEW_H*/
