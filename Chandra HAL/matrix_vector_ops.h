#ifndef CHANDRA_MATRIX_VECTOR_OPS_H
#define CHANDRA_MATRIX_VECTOR_OPS_H

#include <cmath>
using namespace std;

#include "matrix.h"
#include "matrix_vectors.h"

namespace chandra
{
namespace math
{

// Matrix Multiplication
// template<typename V1, typename V2, size_t M, size_t N1, size_t N2, size_t O>
// constexpr auto operator * (const Matrix<V1, M, N1>& a, const Matrix<V2, N2, O>& b) {
//     static_assert(N1 == N2, "Attempting to multiply matricies with incompatible sizes.");
//     using return_t = Matrix<typename std::common_type<V1, V2>::type, M, O>;
//     using index_t = typename return_t::index_t;
//
//     return_t r;
//     for(index_t row = 0; row < M; ++row) {
//         for(index_t column = 0; column < O; ++column) {
//             auto accumulate = V1(0);
//             for(index_t idx = 0; idx < N1; ++idx) {
//                 accumulate += (a(row, idx) * V1(b(idx, column)));
//             }
//             r(row, column) = accumulate;
//         }
//     }
//     return r;
// }

// Element-Wise Multiplication
template<typename V1, typename V2, size_t M>
constexpr auto emul(const Matrix<V1, M, 1>& a, const Vector<V2, M>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        r(row) = a(row) * b(row);
    }
    return r;
}

template<typename V1, typename V2, size_t M>
constexpr auto emul(const Vector<V1, M>& a, const Matrix<V2, M, 1>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        r(row) = a(row) * b(row);
    }
    return r;
}

template<typename V1, typename V2, size_t M>
constexpr auto emul(const Vector<V1, M>& a, const Vector<V2, M>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        r(row) = a(row) * b(row);
    }
    return r;
}

// Scalar Multiplication
template<typename Scalar, typename V, size_t M>
constexpr auto operator * (const Scalar& s, const Vector<V, M>& A) {
    using return_t = Vector<typename std::common_type<Scalar, V>::type, M>;
    return_t r(A);
    r *= s;
    return r;
}

template<typename Scalar, typename V, size_t M>
constexpr auto operator * (const Vector<V, M>& A, const Scalar& s) {
    using return_t = Vector<typename std::common_type<Scalar, V>::type, M>;
    return_t r(A);
    r *= s;
    return r;
}

// Scalar/Vector Addition
template<typename Scalar, typename V, size_t M, bool IsColumn>
constexpr auto operator + (const Scalar& s, const Vector<V, M, IsColumn>& A) {
    using return_t = Vector<decltype(s + V()), M, IsColumn>;
    return_t r(A);
    r += s;
    return r;
}

template<typename Scalar, typename V, size_t M, bool IsColumn>
constexpr auto operator + (const Vector<V, M, IsColumn>& A, const Scalar& s) {
    using return_t = Vector<decltype(s + V()), M, IsColumn>;
    return_t r(A);
    r += s;
    return r;
}

// Matrix/Vector Addition
template<typename V1, typename V2, size_t M>
constexpr auto operator + (const Matrix<V1, M, 1>& a, const Vector<V2, M, true>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M, true>;

    return_t result(a);
    result += b;
    return result;
}

template<typename V1, typename V2, size_t M>
constexpr auto operator + (const Matrix<V1, 1, M>& a, const Vector<V2, M, false>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M, false>;

    return_t result(a);
    result += b;
    return result;
}

template<typename V1, typename V2, size_t M>
constexpr auto operator + (const Vector<V1, M, true>& a, const Matrix<V2, M, 1>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M, true>;

    return_t result(a);
    result += b;
    return result;
}

template<typename V1, typename V2, size_t M>
constexpr auto operator + (const Vector<V1, M, false>& a, const Matrix<V2, 1, M>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M, false>;

    return_t result(a);
    result += b;
    return result;
}

template<typename V1, typename V2, size_t M, bool IsColumn>
constexpr auto operator + (const Vector<V1, M, IsColumn>& a, const Vector<V2, M, IsColumn>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M, IsColumn>;

    return_t result(a);
    result += b;
    return result;
}

// Matrix/Vector Subtraction
template<typename V1, typename V2, size_t M>
constexpr auto operator - (const Matrix<V1, M, 1>& a, const Vector<V2, M>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M>;

    return_t result(a);
    result -= b;
    return result;
}

template<typename V1, typename V2, size_t M>
constexpr auto operator - (const Vector<V1, M>& a, const Matrix<V2, M, 1>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M>;

    return_t result(a);
    result -= b;
    return result;
}

template<typename V1, typename V2, size_t M>
constexpr auto operator - (const Vector<V1, M>& a, const Vector<V2, M>& b) {
    using return_t = Vector<typename std::common_type<V1, V2>::type, M>;

    return_t result(a);
    result -= b;
    return result;
}

//
// Vector Operations
//


// //  Dot Product -- Any Length of Vector
// template<typename V1, typename V2, size_t N>
// constexpr V1 dot(const Matrix<V1, N, 1>& _v1, const Matrix<V2, N, 1>& _v2) {
//     V1 sum(0);
//     for(size_t idx = 0; idx < N; ++idx) {
//         sum += (_v1(idx) * _v2(idx));
//     }
//     return sum;
// }
//
// //  Cross Product -- Vectors of Length Three
// template<typename V1, typename V2>
// constexpr auto cross(const Matrix<V1, 3, 1>& _v1, const Matrix<V2, 3, 1>& _v2) {
//     Matrix<V1, 3, 1> v;
//     v(0) = ((_v1(1)*_v2(2)) - (_v1(2)*_v2(1)));
//     v(1) = ((_v1(2)*_v2(0)) - (_v1(0)*_v2(2)));
//     v(2) = ((_v1(0)*_v2(1)) - (_v1(1)*_v2(0)));
//     return v;
// }
//
// //  Norm
// template<typename V, size_t N>
// constexpr V norm(const Matrix<V, N, 1>& _v) { return dot(_v, _v); }
//
// //  Magnitude
// template<typename V, size_t N>
// constexpr V magnitude(const Matrix<V, N, 1>& _v) { return sqrt(norm(_v)); }

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_VECTOR_OPS_H*/
