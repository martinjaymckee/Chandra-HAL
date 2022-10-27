#ifndef CHANDRA_MATRIX_VIEW_H
#define CHANDRA_MATRIX_VIEW_H

#include <initializer_list>
#include <utility>

#include "matrix_core.h"

namespace chandra
{
namespace math
{
namespace internal
{
template<class Value, size_t Rows, size_t Columns, bool IsColumn=true>
struct VectorReferenceImpl
{
  static constexpr Value& exec(Value (&_data)[Rows][Columns], const size_t& _idx) {
    return _data[_idx][0];
  }
};

template<class Value, size_t Rows, size_t Columns>
struct VectorReferenceImpl<Value, Rows, Columns, false>
{
  static constexpr Value& exec(Value (&_data)[Rows][Columns], const size_t& _idx) {
    return _data[0][_idx];
  }
};

template<bool IsColumn, class Value, size_t Rows, size_t Columns>
constexpr Value& vector_reference(Value (&_data)[Rows][Columns], const size_t& _idx) {
  return VectorReferenceImpl<Value, Rows, Columns, IsColumn>::exec(_data, _idx);
}

template<class Value, size_t N, bool IsColumn>
using VectorMatrixStorage = Matrix<Value, IsColumn ? N : 1, IsColumn ? 1 : N>;

} /* namespace internal */

//
// Vector Implementations
//
template<class Value, size_t N, bool IsColumn = true, class Frame = void>
class Vector {
  public:
    constexpr Vector() {
      static_assert((N == 1) or (N >= 5), "This size vector is undefined.");
    }
};

template<class Value, bool IsColumn, class Frame>
class Vector<Value, 2, IsColumn, Frame> : public internal::VectorMatrixStorage<Value, 2, IsColumn>
{
  public:
    using frame_t = Frame;
    using value_t = Value;
    using matrix_t = internal::VectorMatrixStorage<Value, 2, IsColumn>;
    using ref_t = Vector<Value, 2, IsColumn, Frame>;

    constexpr Vector()
      : matrix_t{},
		x(internal::vector_reference<IsColumn>(this->data_, 0)),
		y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    constexpr Vector(std::initializer_list<value_t> _values)
        : matrix_t{_values},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    constexpr Vector(const Vector& _other)
      : matrix_t{_other},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    template<class V>
    constexpr Vector(const Matrix<V, matrix_t::rows, matrix_t::columns>& _other)
      : matrix_t{_other},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    constexpr ref_t& operator = (const ref_t& _other) {
      x = _other(0);
      y = _other(1);
      return *this;
    }

    template<class V>
    constexpr ref_t& operator = (const Matrix<V, matrix_t::rows, matrix_t::columns>& _other) {
      x = _other(0);
      y = _other(1);
      return *this;
    }

    template<class V>
    constexpr ref_t& operator = (const Vector<V, 2, IsColumn, Frame>& _other) {
        x = _other(0);
        y = _other(1);
        return *this;
    }

    //  Transpose
    constexpr auto T() const {
        return Vector<value_t, 2, !IsColumn, frame_t>{ x, y };
    }

    value_t& x;
    value_t& y;
};

template<class Value, bool IsColumn, class Frame>
class Vector<Value, 3, IsColumn, Frame> : public internal::VectorMatrixStorage<Value, 3, IsColumn>
{
  public:
    using frame_t = Frame;
    using value_t = Value;
    using base_t = internal::VectorMatrixStorage<Value, 3, IsColumn>;
    using matrix_t = internal::VectorMatrixStorage<Value, 3, IsColumn>;
    using ref_t = Vector<Value, 3, IsColumn, Frame>;

    constexpr Vector()
      : base_t{},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)),
        z(internal::vector_reference<IsColumn>(this->data_, 2)) {}

    constexpr Vector(std::initializer_list<value_t> _values)
        : matrix_t{ _values },
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)),
        z(internal::vector_reference<IsColumn>(this->data_, 2)) {}

    constexpr Vector(const Vector& _other)
      : base_t{_other},
    		x(internal::vector_reference<IsColumn>(this->data_, 0)),
    		y(internal::vector_reference<IsColumn>(this->data_, 1)),
    		z(internal::vector_reference<IsColumn>(this->data_, 2)) {}

    template<class V>
    constexpr Vector(const Matrix<V, matrix_t::rows, matrix_t::columns>& _other)
      : base_t{_other},
    		x(internal::vector_reference<IsColumn>(this->data_, 0)),
    		y(internal::vector_reference<IsColumn>(this->data_, 1)),
    		z(internal::vector_reference<IsColumn>(this->data_, 2)) {
        }

    constexpr ref_t& operator = (const ref_t& _other) {
      x = _other(0);
      y = _other(1);
      z = _other(2);
      return *this;
    }

    template<class V>
    constexpr ref_t& operator = (const Matrix<V, matrix_t::rows, matrix_t::columns>& _other) {
      x = _other(0);
      y = _other(1);
      z = _other(2);
      return *this;
    }

    template<class V>
    constexpr ref_t& operator = (const Vector<V, 3, IsColumn, Frame>& _other) {
        x = _other(0);
        y = _other(1);
        z = _other(2);
        return *this;
    }

    //  Transpose
    constexpr auto T() const {
        return Vector<value_t, 3, !IsColumn, frame_t>{ x, y, z };
    }

    value_t& x;
    value_t& y;
    value_t& z;
};

template<class Value, bool IsColumn, class Frame>
class Vector<Value, 4, IsColumn, Frame> : public internal::VectorMatrixStorage<Value, 4, IsColumn>
{
  public:
    using frame_t = Frame;
    using value_t = Value;
    using matrix_t = internal::VectorMatrixStorage<Value, 4, IsColumn>;
    using ref_t = Vector<Value, 4, IsColumn, Frame>;

    constexpr Vector()
      : matrix_t{},
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}

    constexpr Vector(std::initializer_list<value_t> _values)
        : matrix_t{ _values },
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}

    constexpr Vector(const Vector& _other)
      : matrix_t{_other},
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}

    template<class V>
    constexpr Vector(const Matrix<V, matrix_t::rows, matrix_t::columns>& _other)
      : matrix_t{_other},
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}

    constexpr ref_t& operator = (const ref_t& _other) {
      w = _other(0);
      x = _other(1);
      y = _other(2);
      z = _other(3);
      return *this;
    }

    template<class V>
    constexpr ref_t& operator = (const Matrix<V, matrix_t::rows, matrix_t::columns>& _other) {
      w = _other(0);
      x = _other(1);
      y = _other(2);
      z = _other(3);
      return *this;
    }

    template<class V>
    constexpr ref_t& operator = (const Vector<V, 4, IsColumn, Frame>& _other) {
        w = _other(0);
        x = _other(1);
        y = _other(2);
        z = _other(3);
        return *this;
    }

    //  Transpose
    constexpr auto T() const {
        return Vector<value_t, 4, !IsColumn, frame_t>{ {w, x, y, z} };
    }

    value_t& w;
    value_t& x;
    value_t& y;
    value_t& z;
};

//
// Vector Aliases
//
template<class Value, bool IsColumn = true, class Frame = void>
using Vector2D = Vector<Value, 2, IsColumn, Frame>;

template<class Value, class Frame = void>
using RowVector2D = Vector2D<Value, false, Frame>;

template<class Value, class Frame = void>
using ColumnVector2D = Vector2D<Value, true, Frame>;

template<class Value, bool IsColumn = true, class Frame = void>
using Vector3D = Vector<Value, 3, IsColumn, Frame>;

template<class Value, class Frame = void>
using RowVector3D = Vector3D<Value, false, Frame>;

template<class Value, class Frame = void>
using ColumnVector3D = Vector3D<Value, true, Frame>;

template<class Value, bool IsColumn = true, class Frame = void>
using Vector4D = Vector<Value, 4, IsColumn, Frame>;

template<class Value, class Frame = void>
using RowVector4D = Vector4D<Value, false, Frame>;

template<class Value, class Frame = void>
using ColumnVector4D = Vector4D<Value, true, Frame>;

//
// Conversion to vector type
//
template<class Value, size_t Rows, size_t Columns>
auto as_vector(const Matrix<Value, Rows, Columns>& _m) {
  static constexpr bool is_column = (Columns == 1);
  static constexpr size_t N = is_column ? Rows : Columns;
  static_assert((Rows == 1) || (Columns == 1), "Matrix is not shaped as a vector");
  return Vector<Value, N, is_column>{_m};
}

template<class Value, size_t N, bool IsColumn>
auto as_vector(const Vector<Value, N, IsColumn>& _v) {
  return Vector<Value, N, IsColumn>{_v};
}

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_VIEW_H*/
