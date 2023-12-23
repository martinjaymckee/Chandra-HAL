#ifndef CHANDRA_MATRIX_VECTOR_OPS_H
#define CHANDRA_MATRIX_VECTOR_OPS_H

#include <cmath>
using namespace std;

#include "matrix.h"
#include "matrix_vectors.h"
#include "quantity_math.h"
#include "units.h"

namespace chandra
{
namespace math
{

// Element-Wise Multiplication
template<typename V1, typename V2, size_t M, bool IC, class Frame>
constexpr auto emul(const Matrix<V1, M, 1>& a, const Vector<V2, M, IC, Frame>& b) {
    using return_t = Vector<decltype(V1()*V2()), M, IC, Frame>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        r(row) = a(row) * b(row);
    }
    return r;
}

template<typename V1, typename V2, size_t M, bool IC, class Frame>
constexpr auto emul(const Vector<V1, M, IC, Frame>& a, const Matrix<V2, M, 1>& b) {
    using return_t = Vector<decltype(V1() * V2()), M, IC, Frame>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        r(row) = a(row) * b(row);
    }
    return r;
}

template<typename V1, typename V2, size_t M, bool IC, class Frame>
constexpr auto emul(const Vector<V1, M, IC, Frame>& a, const Vector<V2, M, IC, Frame>& b) {
    using return_t = Vector<decltype(V1()* V2()), M, IC, Frame>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        r(row) = a(row) * b(row);
    }
    return r;
}

// Scalar Multiplication
template<typename Scalar, typename V, size_t M, bool IsColumn, class Frame>
constexpr auto operator * (const Scalar& s, const Vector<V, M, IsColumn, Frame>& A) {
    using return_t = Vector<decltype(s * V()), M, IsColumn, Frame>;
    return_t r;
    for (size_t idx = 0; idx < M; ++idx) {
        r(idx) = s * A(idx);
    }
    return r;
}

template<typename Scalar, typename V, size_t M, bool IsColumn>
constexpr auto operator * (const Vector<V, M, IsColumn>& A, const Scalar& s) {
    return s * A;
    //using return_t = Vector<decltype(s + V()), M, IsColumn>;
    //return_t r;
    //for (size_t idx = 0; idx < M; ++idx) {
    //    r(idx) = A(idx) + s;
    //}
    //return r;
}

// Matrix/ColumnVector Multiplication
template<typename V1, size_t M, size_t N, typename V2, class Frame>
constexpr auto operator * (const Matrix<V1, M, N>& _A, const Vector<V2, N, true, Frame>& _v) {
    using value_t = decltype(V1() * V2());
    using return_t = Vector<value_t, N, true, Frame>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        auto accumulate = value_t{0};
        for(index_t idx = 0; idx < N; ++idx) {
            accumulate += (_A(row, idx) * _v(idx));
        }
        r(row) = accumulate;
    }
    return r;
}

/*
template<typename Scalar, typename V, size_t M, bool IC, class Frame>
constexpr auto operator * (const Scalar& s, const Vector<V, M, IC, Frame>& A) {
    using return_t = Vector<decltype(V() * s), M, IC, Frame>;
    return_t r(A);
    r *= s;
    return r;
}

template<typename Scalar, typename V, size_t M, bool IC, class Frame>
constexpr auto operator * (const Vector<V, M, IC, Frame>& A, const Scalar& s) {
    using return_t = Vector<decltype(V() * s), M, IC, Frame>;
    return_t r(A);
    r *= s;
    return r;
}
*/

// Scalar Division
template<typename Scalar, typename V, size_t M, bool IC, class Frame>
constexpr auto operator / (const Vector<V, M, IC, Frame>& A, const Scalar& s) {
    using return_t = Vector<decltype(V() / s), M, IC, Frame>;
    return_t r;
    for(size_t idx = 0; idx < M; ++idx) {
      r(idx) = A(idx) / s;
    }
    return r;
}

// Scalar/Vector Addition
template<typename Scalar, typename V, size_t M, bool IsColumn, class Frame>
constexpr auto operator + (const Scalar& s, const Vector<V, M, IsColumn, Frame>& A) {
    using return_t = Vector<decltype(s + V()), M, IsColumn, Frame>;
    return_t r;
    for (size_t idx = 0; idx < M; ++idx) {
        r(idx) = A(idx) + s;
    }
    return r;
}

template<typename Scalar, typename V, size_t M, bool IsColumn, class Frame>
constexpr auto operator + (const Vector<V, M, IsColumn, Frame>& A, const Scalar& s) {
    return s + A;
}

// Matrix/Vector Addition
template<typename V1, typename V2, size_t M, class Frame>
constexpr auto operator + (const Matrix<V1, M, 1>& a, const Vector<V2, M, true, Frame>& b) {
    using return_t = Vector<decltype(V1() + V2()), M, true, Frame>;
    return_t result;
    for (size_t idx = 0; idx < M; ++idx) {
        result(idx) = a(idx) + b(idx);
    }
    return result;
}

template<typename V1, typename V2, size_t M, class Frame>
constexpr auto operator + (const Matrix<V1, 1, M>& a, const Vector<V2, M, false, Frame>& b) {
    using return_t = Vector<decltype(V1() + V2()), M, false, Frame>;
    return_t result;
    for (size_t idx = 0; idx < M; ++idx) {
        result(idx) = a(idx) + b(idx);
    }
    return result;
}

template<typename V1, typename V2, size_t M, class Frame>
constexpr auto operator + (const Vector<V1, M, true, Frame>& a, const Matrix<V2, M, 1>& b) {
    using return_t = Vector<decltype(V1() + V2()), M, true, Frame>;
    return_t result;
    for (size_t idx = 0; idx < M; ++idx) {
        result(idx) = a(idx) + b(idx);
    }
    return result;
}

template<typename V1, typename V2, size_t M, class Frame>
constexpr auto operator + (const Vector<V1, M, false, Frame>& a, const Matrix<V2, 1, M>& b) {
    using return_t = Vector<decltype(V1() + V2()), M, false, Frame>;
    return_t result;
    for (size_t idx = 0; idx < M; ++idx) {
        result(idx) = a(idx) + b(idx);
    }
    return result;
}

template<typename V1, typename V2, size_t M, bool IsColumn, class Frame>
constexpr auto operator + (const Vector<V1, M, IsColumn, Frame>& a, const Vector<V2, M, IsColumn, Frame>& b) {
    using return_t = Vector<decltype(V1() + V2()), M, IsColumn>;
    return_t result;
    for (size_t idx = 0; idx < M; ++idx) {
        result(idx) = a(idx) + b(idx);
    }
    return result;
}

// Matrix/Vector Subtraction
template<typename V1, typename V2, size_t M, bool IC, class Frame>
constexpr auto operator - (const Matrix<V1, M, 1>& a, const Vector<V2, M, IC, Frame>& b) {
    using return_t = Vector<decltype(V1() - V2()), M, IC, Frame>;
    return_t result;
    for(size_t idx = 0; idx < M; ++idx) {
      result(idx) = a(idx) - b(idx);
    }
    return result;
}

template<typename V1, typename V2, size_t M, bool IC, class Frame>
constexpr auto operator - (const Vector<V1, M, IC, Frame>& a, const Matrix<V2, M, 1>& b) {
    using return_t = Vector<decltype(V1() - V2()), M, IC, Frame>;
    return_t result;
    for(size_t idx = 0; idx < M; ++idx) {
      result(idx) = a(idx) - b(idx);
    }
    return result;
}

template<typename V1, typename V2, size_t M, bool IC, class Frame>
constexpr auto operator - (const Vector<V1, M, IC, Frame>& a, const Vector<V2, M, IC, Frame>& b) {
    using return_t = Vector<decltype(V1() - V2()), M, IC, Frame>;
    return_t result;
    for(size_t idx = 0; idx < M; ++idx) {
      result(idx) = a(idx) - b(idx);
    }
    return result;
}

//
// Vector Operations
//


//  Dot Product -- Any Length of 1-dimensional Vector
template<typename V1, typename V2, size_t N, bool IsColumn, class Frame>
constexpr auto dot(const Vector<V1, N, IsColumn, Frame>& _v1, const Vector<V2, N, IsColumn, Frame>& _v2) {
    using result_t = decltype(std::declval<V1>()* std::declval<V2>());
    auto sum = result_t(0);
    for (size_t idx = 0; idx < N; ++idx) {
        sum += result_t(_v1(idx) * _v2(idx));
    }

    return sum;
}

//  Cross Product -- Vectors of Length Three
template<typename V1, typename V2, size_t N, bool IsColumn, typename Frame>
constexpr auto cross(const Vector<V1, N, IsColumn, Frame>& _v1, const Vector<V2, N, IsColumn, Frame>& _v2) {
    using result_t = decltype(std::declval<V1>()* std::declval<V1>());
    Vector<result_t, N, IsColumn, Frame> v;
    v(0) = result_t((_v1(1) * _v2(2)) - (_v1(2) * _v2(1)));
    v(1) = result_t((_v1(2) * _v2(0)) - (_v1(0) * _v2(2)));
    v(2) = result_t((_v1(0) * _v2(1)) - (_v1(1) * _v2(0)));
    return v;
}

//  Norm
template<class V, size_t N, bool IsColumn, class Frame>
constexpr auto norm(const Vector<V, N, IsColumn, Frame>& _v) {
    auto sum = V(0) * V(0);
    for (size_t idx = 0; idx < N; ++idx) {
        sum += (_v(idx) * _v(idx));
    }

    return sum;
}

//  Magnitude
template<class V, size_t N, bool IsColumn, class Frame>
constexpr V magnitude(const Vector<V, N, IsColumn, Frame>& _v) {
  return V{sqrt(norm(_v))};
}

// Direction Vector
template<class V, size_t N, bool IsColumn, class Frame>
constexpr auto direction(const Vector<V, N, IsColumn, Frame>& _v) {
  using scalar_t = typename chandra::scalar_of<V>::type;
  using result_t = Vector<scalar_t, N, IsColumn, Frame>;
  result_t v;
  for (size_t idx = 0; idx < N; ++idx) {
      v(idx) = chandra::units::scalar_cast(_v(idx));
  }
  return v / chandra::math::magnitude(v);
}

// Unit Vector
template<class V, size_t N, bool IsColumn, class Frame>
constexpr auto unit(const Vector<V, N, IsColumn, Frame>& _v) {
    using result_t = Vector<V, N, IsColumn, Frame>;
    result_t v;
    return v / chandra::units::scalar_cast(chandra::math::magnitude(v));
}

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_VECTOR_OPS_H*/
