#ifndef CHANDRA_MATRIX_VIEW_H
#define CHANDRA_MATRIX_VIEW_H

#include "matrix.h"

namespace chandra
{
namespace math
{

namespace internal
{

template<typename Value, size_t Rows, size_t Columns>
class VectorWrapper
{
    public:
        using matrix_t = Matrix<Value, Rows, Columns>;

        constexpr VectorWrapper() {}
        constexpr VectorWrapper(const matrix_t& _src) : vec(_src) {}
        constexpr VectorWrapper(const VectorWrapper& _other) : vec(_other.vec) {}

        constexpr operator matrix_t&() const { return vec; }
        constexpr operator matrix_t&() { return vec; }

    protected:
        matrix_t vec; // TODO: DECIDE IF THIS SHOULD BE A REFERENCE OR A VALUE....
};

template<typename Value>
class ValueProxy
{
    public:
        using value_t = Value;

        explicit constexpr ValueProxy(value_t& _ref) : ref_(_ref) {}

        constexpr ValueProxy& operator = (auto v) {
            ref_ = v;
            return *this;
        }

        constexpr operator value_t() { return ref_; }

    private:
        value_t& ref_;
};
} /*namespace internal*/

template<typename Value>
struct Vector2D : public internal::VectorWrapper<Value, 2, 1>
{
        using base_t = internal::VectorWrapper<Value, 2, 1>;
        using matrix_t = typename base_t::matrix_t;

        constexpr Vector2D(const matrix_t& m)
            : base_t(m),
              x(this->vec(0)),
              y(this->vec(1)) {}

        internal::ValueProxy<Value> x;
        internal::ValueProxy<Value> y;
};

template<typename Value>
struct Vector3D : public internal::VectorWrapper<Value, 3, 1>
{
        using base_t = internal::VectorWrapper<Value, 3, 1>;
        using matrix_t = typename base_t::matrix_t;

        constexpr Vector3D(const matrix_t& m)
            : base_t(m),
              x(this->vec(0)),
              y(this->vec(1)),
              z(this->vec(2)) {}

        internal::ValueProxy<Value> x;
        internal::ValueProxy<Value> y;
        internal::ValueProxy<Value> z;
};

template<typename Value>
struct Vector4D : public internal::VectorWrapper<Value, 4, 1>
{
        using base_t = internal::VectorWrapper<Value, 4, 1>;
        using matrix_t = typename base_t::matrix_t;

        constexpr Vector4D(const matrix_t& m)
            : base_t(m),
              w(this->vec(0)),
              x(this->vec(1)),
              y(this->vec(2)),
              z(this->vec(3)) {}

        internal::ValueProxy<Value> w;
        internal::ValueProxy<Value> x;
        internal::ValueProxy<Value> y;
        internal::ValueProxy<Value> z;
};

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_VIEW_H*/

