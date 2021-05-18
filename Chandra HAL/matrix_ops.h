#ifndef CHANDRA_MATRIX_OPS_H
#define CHANDRA_MATRIX_OPS_H

#include <cmath>
using namespace std;

#include "matrix_core.h"
#include "matrix_vectors.h"

namespace chandra
{
namespace math
{
namespace method
{
struct GE {
	static const bool symmetric = false;
	static const bool positive_definite = false;
	static const bool positive_semi_definite = false;
	static const bool diagonal = false;
};
struct LDL {
	static const bool symmetric = true;
	static const bool positive_definite = false;
	static const bool positive_semi_definite = true;
	static const bool diagonal = false;
};
struct Cholesky {
	static const bool symmetric = true;
	static const bool positive_definite = true;
	static const bool positive_semi_definite = true;
	static const bool diagonal = false;
};
} /* namespace method */

// Stream Output
template<typename Stream, typename Value, size_t N, size_t M>
Stream& operator << (Stream& _stream, const chandra::math::Matrix<Value, N, M>& _val) {
	const Value epsilon{ 1e-25 };

	_stream << "[ ";

    for(int row = 0; row < N; ++row){
        for(int column = 0; column < M; ++column){
			const auto v = _val(row, column);
			_stream << ((abs(v) > epsilon) ? v : Value{ 0 });
            if(column != (M-1)) _stream << ", ";
        }
        if(row != (N-1)) _stream << ";\n";
    }
    _stream << " ]";
    return _stream;
}

template<typename Stream, typename Value, size_t N>
Stream& operator << (Stream& _stream, const chandra::math::Matrix<Value, 1, N>& _val) {
    _stream << "[ ";
    for(int column = 0; column < N; ++column){
        _stream << _val(column);
        if(column != (N-1)) _stream << ", ";
    }
    _stream << " ]";
    return _stream;
}

template<typename Stream, typename Value, size_t N>
Stream& operator << (Stream& _stream, const chandra::math::Matrix<Value, N, 1>& _val) {
    _stream << "[ ";
    for(int column = 0; column < N; ++column){
        _stream << _val(column);
        if(column != (N-1)) _stream << "; ";
    }
    _stream << " ]";
    return _stream;
}

namespace internal
{
template<typename V1, typename V2, size_t N, size_t M>
auto backwardsubstitute(Matrix<V1, N, N>& A, Matrix<V2, N, M>& b) {
    for(size_t head = N; head > 0; --head) {
		const auto idx = head - 1;
        const auto head_val = A(idx, idx);
        A(idx, idx) = V1(1);
        for(size_t row = 0; row < idx; ++row) {
            const auto scale = A(row, idx) / head_val;
            A(row, idx) = V1(0);
            for(size_t column = 0; column < M; ++column) {
                b(row, column) -= (scale * b(idx, column));
            }
        }
		for (size_t column = 0; column < M; ++column) {
			b(idx, column) /= head_val;
		}
    }
    return true;
}

template<typename V1, typename V2, size_t N, size_t M>
auto unitriangular_backwardsubstitute(const Matrix<V1, N, N>& A, Matrix<V2, N, M>& b) {
	for (size_t head = N; head > 0; --head) {
		const auto idx = head - 1;
		for (size_t row = 0; row < idx; ++row) {
			const auto scale = A(row, idx);
			for (size_t column = 0; column < M; ++column) {
				b(row, column) -= (scale * b(idx, column));
			}
		}
	}
	return true;
}

template<typename V1, typename V2, size_t N, size_t M>
auto forwardsubstitute(Matrix<V1, N, N>& A, Matrix<V2, N, M>& b) {
  for(size_t head = 0; head < N; ++head) {
      const auto head_val = A(head, head);
      A(head, head) = V1(1);
      for(size_t row = head+1; row < N; ++row) {
          const auto scale = A(row, head) / head_val;
		  A(row, head) = V1(0);
          for(size_t column = 0; column < M; ++column) {
              b(row, column) -= (scale * b(head, column));
          }
      }
	  for (size_t column = 0; column < M; ++column) {
		  b(head, column) /= head_val;
	  }
  }
    return true;
}

template<typename V1, typename V2, size_t N, size_t M>
auto unitriangular_forwardsubstitute(const Matrix<V1, N, N>& A, Matrix<V2, N, M>& b) {
	for (size_t head = 0; head < N; ++head) {
		for (size_t row = head + 1; row < N; ++row) {
			const auto scale = A(row, head);
			for (size_t column = 0; column < M; ++column) {
				b(row, column) -= (scale * b(head, column));
			}
		}
	}
	return true;
}

template<typename Value, size_t N>
struct LDLReturn
{
	Matrix<Value, N, N> L;
	Matrix<Value, N, N> D;
	Matrix<Value, N, N> Lt;
};

template<typename Value, size_t N>
struct RDRReturn
{
	Matrix<Value, N, N> Rt;
	Matrix<Value, N, N> D;
	Matrix<Value, N, N> R;
};

} /*namespace internal*/

// TODO: FIX THE CHOLESKY AND LDL DECOMPOSITIONS TO HANDLE THE
//  CONJUGATE TO MAKE IT WORK CORRECTLY WITH COMPLEX NUMBERS.  AS THEY ARE
//  THEY ARE ONLY VALID FOR REAL NUMBERS.
template<typename Value, size_t N>
Matrix<Value, N, N> cholesky(const Matrix<Value, N, N>& _A) {
	Matrix<Value, N, N> R(0);

	return R.T();
}

template<typename Value, size_t N>
internal::RDRReturn<Value, N> rdr(const Matrix<Value, N, N>& _A) {
	Matrix<Value, N, N> D(0);
	Matrix<Value, N, N> R(0);
	Matrix<Value, N, N> Rt(0);

	for (size_t i = 0; i < N; ++i) {
		for (size_t j = i; j < N; ++j) {
			if (j == i) {
				auto di = _A(i, i);
				for (size_t k = 0; k < i; ++k) di -= (R(k, i) * R(k, i) * D(k, k));
				D(i, i) = di;
				R(i, i) = 1;
				Rt(i, i) = 1;
			}
			else {
				auto rij = _A(i, j);
				for (size_t k = 0; k < i; ++k) rij -= (R(k, i) * R(k, j) * D(k, k));
				const auto r_new = rij / D(i, i);
				R(i, j) = r_new;
				Rt(j, i) = r_new;
			}
		}
	}
	return { Rt, D, R };
}

template<typename Value, size_t N>
internal::LDLReturn<Value, N> ldl(const Matrix<Value, N, N>& _A) {
	const auto results = rdr(_A);
	return { results.Rt, results.D, results.R };
}

namespace internal
{
template<typename V1, typename V2, size_t N, size_t M, typename Method = method::GE>
struct SolveImplementation
{
	static constexpr Matrix<V2, N, M> calc(const Matrix<V1, N, N> _A, Matrix<V2, N, M> b) {
		Matrix<V1, N, N> A{ _A };

		// Gaussian Elimination
		for (size_t head = 0; head < N; ++head) {
			size_t max_head = head;
			auto max_pivot = abs(A(head, head));
			for (size_t row = head + 1; row < N; ++row) {
				if (abs(A(row, head)) > max_pivot) max_head = row;
			}

			if (max_head > head) {
				for (size_t column = head; column < N + M; ++column) {
					if (column < N) {
						const auto temp = A(head, column);
						A(head, column) = A(max_head, column);
						A(max_head, column) = temp;
					}
					else {
						const auto idx = column - N;
						const auto temp = b(head, idx);
						b(head, idx) = b(max_head, idx);
						b(max_head, idx) = temp;
					}
				}
			}

			const auto value = A(head, head);
			A(head, head) = 1;

			for (size_t row = head + 1; row < N; ++row) { // Update the lower-right submatrix
				const auto scale = A(row, head) / value;
				A(row, head) = 0;
				for (size_t column = head + 1; column < N; ++column) {
					A(row, column) -= (scale * A(head, column));
				}
				for (size_t column = 0; column < M; ++column) {
					b(row, column) -= (scale * b(head, column));
				}
			}

			for (size_t column = head + 1; column < N + M; ++column) { // Update Reference Line
				if (column < N) {
					A(head, column) /= value;
				}
				else {
					b(head, column - N) /= value;
				}
			}

			A(head, head) = 1;
		}

		backwardsubstitute(A, b);

		return b;
	}
};

template<typename V1, typename V2, size_t N, size_t M>
struct SolveImplementation<V1, V2, N, M, method::LDL>
{
	static constexpr Matrix<V2, N, M> calc(const Matrix<V1, N, N> A, Matrix<V2, N, M> b) {
		const auto results = rdr(A);

		internal::unitriangular_forwardsubstitute(results.Rt, b);

		for (size_t idx = 0; idx < N; ++idx) {
			const auto scale = results.D(idx, idx);
			for (size_t column = 0; column < M; ++column) {
				b(idx, column) /= scale;
			}
		}
		internal::unitriangular_backwardsubstitute(results.R, b);

		return b;
	}
};

};

template<typename V1, typename V2, size_t N, size_t M>
auto solve(Matrix<V1, N, N> A, Matrix<V2, N, M> b) {
	return internal::SolveImplementation<V1, V2, N, M, method::GE>::calc(A, b);
}

template<typename Method, typename V1, typename V2, size_t N, size_t M>
auto solve(Matrix<V1, N, N> A, Matrix<V2, N, M> b) {
	return internal::SolveImplementation<V1, V2, N, M, Method>::calc(A, b);
}

namespace internal
{

template<typename Value, size_t N>
struct Inverter
{
	template<typename Method>
    static Matrix<Value, N, N> calc(const Matrix<Value, N, N>& _A) {
        return solve<Method>(_A, Matrix<Value, N, N>::Eye());
    }
};

template<typename Value>
struct Inverter<Value, 1>
{
	template<typename Method>
    static Matrix<Value, 1, 1> calc(const Matrix<Value, 1, 1>& _m) {
        return {Value(1.0) / _m(0)};
    }
};

template<typename Value>
struct Inverter<Value, 2>
{
	template<typename Method>
    static Matrix<Value, 2, 2> calc(const Matrix<Value, 2, 2>& _m) {
        const auto inv_det = Value(1.0) / (_m(0,0)*_m(1,1) + _m(0,1)*_m(1,0));
        const auto b00 = inv_det * _m(1,1);
        const auto b01 = inv_det * -_m(0,1);
        const auto b10 = inv_det * -_m(1,0);
        const auto b11 = inv_det * _m(0,0);
        return {b00, b01, b10, b11};
    }
};

template<typename Value>
struct Inverter<Value, 3>
{
	template<typename Method>
    static Matrix<Value, 3, 3> calc(const Matrix<Value, 3, 3>& _m) {
        const auto c0 = _m(2,2)*_m(1,1);
        const auto c1 = _m(2,1)*_m(1,2);
        const auto c2 = _m(2,2)*_m(0,1);
        const auto c3 = _m(2,1)*_m(0,2);
        const auto c4 = _m(1,2)*_m(0,1);
        const auto c5 = _m(1,1)*_m(0,2);
        const auto c6 = c0 - c1;
        const auto c7 = c3 - c2;
        const auto c8 = c4 - c5;

        const auto det = c6*_m(0,0) + c7*_m(1,0) + c8*_m(2,0);
        const auto inv_det = Value(1) / det;

        const auto b00 = inv_det * c6;
        const auto b01 = inv_det * c7;
        const auto b02 = inv_det * c8;

        const auto b10 = inv_det * (_m(2,0)*_m(1,2) - _m(2,2)*_m(1,0));
        const auto b11 = inv_det * (_m(2,2)*_m(0,0) - _m(2,0)*_m(0,2));
        const auto b12 = inv_det * (_m(1,0)*_m(0,2) - _m(1,2)*_m(0,0));

        const auto b20 = inv_det * (_m(2,1)*_m(1,0) - _m(2,0)*_m(1,1));
        const auto b21 = inv_det * (_m(2,0)*_m(0,1) - _m(2,1)*_m(0,0));
        const auto b22 = inv_det * (_m(1,1)*_m(0,0) - _m(1,0)*_m(0,1));

        return {    b00, b01, b02,
                    b10, b11, b12,
                    b20, b21, b22
        };
    }
};
} /*namespace internal*/

template<typename V, size_t N>
constexpr auto inverse(const Matrix<V, N, N>& _m) {
    return internal::Inverter<V, N>::template calc<method::GE>(_m);
}

template<typename Method, typename V, size_t N>
constexpr auto inverse(const Matrix<V, N, N> & _m) {
	return internal::Inverter<V, N>::template calc<Method>(_m);
}

// Element-Wise Multiplication
template<typename V1, typename V2, size_t M, size_t N>
constexpr auto emul(const Matrix<V1, M, N>& a, const Matrix<V2, M, N>& b) {
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, N>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        for(index_t column = 0; column < N; ++column) {
            r(row, column) = a(row, column) * b(row, column);
        }
    }
    return r;
}

// Matrix Multiplication
template<typename V1, typename V2, size_t M, size_t N1, size_t N2, size_t O>
constexpr auto operator * (const Matrix<V1, M, N1>& a, const Matrix<V2, N2, O>& b) {
    static_assert(N1 == N2, "Attempting to multiply matricies with incompatible sizes.");
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, O>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        for(index_t column = 0; column < O; ++column) {
            auto accumulate = V1(0);
            for(index_t idx = 0; idx < N1; ++idx) {
                accumulate += (a(row, idx) * V1(b(idx, column)));
            }
            r(row, column) = accumulate;
        }
    }
    return r;
}

// Scalar Multiplication
template<typename Scalar, typename V, size_t M, size_t N>
constexpr auto operator * (const Scalar& s, const Matrix<V, M, N>& A) {
    using return_t = Matrix<typename std::common_type<Scalar, V>::type, M, N>;
    return_t r(A);
    r *= s;
    return r;
}

template<typename Scalar, typename V, size_t M, size_t N>
constexpr auto operator * (const Matrix<V, M, N>& A, const Scalar& s) {
    using return_t = Matrix<typename std::common_type<Scalar, V>::type, M, N>;
    return_t r(A);
    r *= s;
    return r;
}


// Element-Wise Division
template<typename V1, typename V2, size_t M, size_t N>
constexpr auto ediv(const Matrix<V1, M, N>& a, const Matrix<V2, M, N>& b) {
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, N>;
    using index_t = typename return_t::index_t;

    return_t r;
    for(index_t row = 0; row < M; ++row) {
        for(index_t column = 0; column < N; ++column) {
            r(row, column) = a(row, column) / b(row, column);
        }
    }
    return r;
}

// Scalar Division
template<typename Scalar, typename V, size_t M, size_t N>
constexpr auto operator / (const Matrix<V, M, N>& A, const Scalar& s) {
    using return_t = Matrix<typename std::common_type<Scalar, V>::type, M, N>;
    return_t r(A);
    r /= s;
    return r;
}

// Matrix Addition
template<typename V1, typename V2, size_t M, size_t N>
constexpr auto operator + (const Matrix<V1, M, N>& a, const Matrix<V2, M, N>& b) {
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, N>;

    return_t result(a);
    result += b;
    return result;
}

// Scalar Addition
template<typename V1, typename V2, size_t M, size_t N>
constexpr auto operator + (const Matrix<V1, M, N>& a, const V2& b) {
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, N>;

    return_t result(a);
    result += b;
    return result;
}

// Matrix Subtraction
template<typename V1, typename V2, size_t M, size_t N>
constexpr auto operator - (const Matrix<V1, M, N>& a, const Matrix<V2, M, N>& b) {
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, N>;

    return_t result(a);
    result -= b;
    return result;
}

// Scalar Subtraction
template<typename V1, typename V2, size_t M, size_t N>
constexpr auto operator - (const Matrix<V1, M, N>& a, const V2& b) {
    using return_t = Matrix<typename std::common_type<V1, V2>::type, M, N>;

    return_t result(a);
    result -= b;
    return result;
}

//
// Vector Operations
//


//  Dot Product -- Any Length of Vector
template<typename V1, typename V2, size_t N>
constexpr V1 dot(const Matrix<V1, N, 1>& _v1, const Matrix<V2, N, 1>& _v2) {
    V1 sum(0);
    for(size_t idx = 0; idx < N; ++idx) {
        sum += (_v1(idx) * _v2(idx));
    }
    return sum;
}

//  Cross Product -- Vectors of Length Three
template<typename V1, typename V2>
constexpr auto cross(const Matrix<V1, 3, 1>& _v1, const Matrix<V2, 3, 1>& _v2) {
    Matrix<V1, 3, 1> v;
    v(0) = ((_v1(1)*_v2(2)) - (_v1(2)*_v2(1)));
    v(1) = ((_v1(2)*_v2(0)) - (_v1(0)*_v2(2)));
    v(2) = ((_v1(0)*_v2(1)) - (_v1(1)*_v2(0)));
    return v;
}

//  Norm
template<typename V, size_t N>
constexpr V norm(const Matrix<V, N, 1>& _v) { return dot(_v, _v); }

//  Magnitude
template<typename V, size_t N>
constexpr V magnitude(const Matrix<V, N, 1>& _v) { return sqrt(norm(_v)); }

} /*namespace math*/
} /*namespace chandra*/

#endif /*CHANDRA_MATRIX_OPS_H*/
