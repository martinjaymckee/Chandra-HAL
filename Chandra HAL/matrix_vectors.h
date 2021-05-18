#ifndef CHANDRA_MATRIX_VIEW_H
#define CHANDRA_MATRIX_VIEW_H

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
} /* namespace internal */

//
// Vector Implementations
//
template<class Value, size_t N, bool IsColumn = true>
class Vector {};

template<class Value, bool IsColumn>
class Vector<Value, 2, IsColumn> : public Matrix<Value, IsColumn ? 2 : 1, IsColumn ? 1 : 2>
{
  public:
    using value_t = Value;
    using base_t = Matrix<Value, IsColumn ? 2 : 1, IsColumn ? 1 : 2>;

    Vector()
      : base_t{},
		x(internal::vector_reference<IsColumn>(this->data_, 0)),
		y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    Vector(const Vector& _other)
      : base_t{_other},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    template<class V>
    Vector(const Matrix<V, base_t::rows, base_t::columns>& _other)
      : base_t{_other},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)) {}

    value_t& x;
    value_t& y;
};

template<class Value, bool IsColumn>
class Vector<Value, 3, IsColumn> : public Matrix<Value, IsColumn ? 3 : 1, IsColumn ? 1 : 3>
{
  public:
    using value_t = Value;
    using base_t = Matrix<Value, IsColumn ? 3 : 1, IsColumn ? 1 : 3>;

    Vector()
      : base_t{},
        x(internal::vector_reference<IsColumn>(this->data_, 0)),
        y(internal::vector_reference<IsColumn>(this->data_, 1)),
        z(internal::vector_reference<IsColumn>(this->data_, 2)) {}

    Vector(const Vector& _other)
      : base_t{_other},
    		x(internal::vector_reference<IsColumn>(this->data_, 0)),
    		y(internal::vector_reference<IsColumn>(this->data_, 1)),
    		z(internal::vector_reference<IsColumn>(this->data_, 2)) {}

    template<class V>
    Vector(const Matrix<V, base_t::rows, base_t::columns>& _other)
      : base_t{_other},
    		x(internal::vector_reference<IsColumn>(this->data_, 0)),
    		y(internal::vector_reference<IsColumn>(this->data_, 1)),
    		z(internal::vector_reference<IsColumn>(this->data_, 2)) {}

    value_t& x;
    value_t& y;
    value_t& z;
};

template<class Value, bool IsColumn>
class Vector<Value, 4, IsColumn> : public Matrix<Value, IsColumn ? 4 : 1, IsColumn ? 1 : 4>
{
  public:
    using value_t = Value;
    using base_t = Matrix<Value, IsColumn ? 4 : 1, IsColumn ? 1 : 4>;

    Vector()
      : base_t{},
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}

    Vector(const Vector& _other)
      : base_t{_other},
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}

    template<class V>
    Vector(const Matrix<V, base_t::rows, base_t::columns>& _other)
      : base_t{_other},
        w(internal::vector_reference<IsColumn>(this->data_, 0)),
        x(internal::vector_reference<IsColumn>(this->data_, 1)),
        y(internal::vector_reference<IsColumn>(this->data_, 2)),
        z(internal::vector_reference<IsColumn>(this->data_, 3)) {}



    value_t& w;
    value_t& x;
    value_t& y;
    value_t& z;
};


//
// Vector Aliases
//
template<class Value, bool IsColumn = true>
using Vector2D = Vector<Value, 2, IsColumn>;

template<class Value>
using RowVector2D = Vector2D<Value, false>;

template<class Value>
using ColumnVector2D = Vector2D<Value, true>;

template<class Value, bool IsColumn = true>
using Vector3D = Vector<Value, 3, IsColumn>;

template<class Value>
using RowVector3D = Vector3D<Value, false>;

template<class Value>
using ColumnVector3D = Vector3D<Value, true>;

template<class Value, bool IsColumn = true>
using Vector4D = Vector<Value, 4, IsColumn>;

template<class Value>
using RowVector4D = Vector4D<Value, false>;

template<class Value>
using ColumnVector4D = Vector4D<Value, true>;

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_VIEW_H*/
