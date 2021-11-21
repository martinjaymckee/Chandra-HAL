#ifndef CHANDRA_RATIO_UTILS_H
#define CHANDRA_RATIO_UTILS_H

#include <ratio>

#include <meta_math.h>

namespace chandra
{

	template<class R>
	using ratio_square = std::ratio_multiply<R, R>;

	template<class R>
	using ratio_int_sqrt = std::ratio<chandra::meta::sqrt<intmax_t>(static_cast<std::intmax_t>((R::num + R::den) / R::den)), 1>;

namespace internal {
	using ratio_zero = ratio<0>;
	using ratio_one = ratio<1>;

	template <typename R>
	struct IsPerfectSquare {
	protected:
		const static intmax_t DenSqrt_ = chandra::meta::sqrt<intmax_t>(R::den);
		const static intmax_t NumSqrt_ = chandra::meta::sqrt<intmax_t>(R::num);

	public:
		const static bool value = DenSqrt_ * DenSqrt_ == R::den && NumSqrt_ * NumSqrt_ == R::num;
		using Sqrt = ratio<NumSqrt_, DenSqrt_>;
	};

	// Represents sqrt(P)-Q.
	template <typename Tp, typename Tq>
	struct Remainder {
		using P = Tp;
		using Q = Tq;
	};

	// Represents 1/R = I + Rem where R is a Remainder.
	template <typename R>
	struct Reciprocal {
	protected:
		using P_ = typename R::P;
		using Q_ = typename R::Q;
		using Den_ = std::ratio_subtract<P_, chandra::ratio_square<Q_>>;
		using A_ = std::ratio_divide<Q_, Den_>;
		using B_ = std::ratio_divide<P_, chandra::ratio_square<Den_>>;
		using C_ = std::ratio_multiply<B_, chandra::ratio_square<std::ratio<A_::den>>>;

	public:
		using I = std::ratio_divide<std::ratio_add<std::ratio<A_::num>, chandra::ratio_int_sqrt<C_>>, std::ratio<A_::den>>;
		using Rem = Remainder<B_, ratio_subtract<I, A_>>;
	};

	// Expands sqrt(R) to continued fraction:
	// f(x)=C1+1/(C2+1/(C3+1/(...+1/(Cn+x)))) = (U*x+V)/(W*x+1) and sqrt(R)=f(Rem).
	// The error |f(Rem)-V| = |(U-W*V)x/(W*x+1)| <= |U-W*V|*Rem <= |U-W*V|/I' where
	// I' is the integer part of reciprocal of Rem.
	template <typename R, intmax_t N>
	struct ContinuedFraction {
		template <typename T>
		using Abs_ = typename conditional<ratio_less<T, ratio_zero>::value, ratio_subtract<ratio_zero, T>, T>::type;

		using Last_ = ContinuedFraction<R, N - 1>;
		using Reciprocal_ = Reciprocal<typename Last_::Rem>;
		using Rem = typename Reciprocal_::Rem;
		using I_ = typename Reciprocal_::I;
		using Den_ = ratio_add<typename Last_::W, I_>;
		using U = ratio_divide<typename Last_::V, Den_>;
		using V = ratio_divide<ratio_add<typename Last_::U, ratio_multiply<typename Last_::V, I_>>, Den_>;
		using W = ratio_divide<ratio_one, Den_>;
		using Error = Abs_<ratio_divide<ratio_subtract<U, ratio_multiply<V, W>>, typename Reciprocal<Rem>::I>>;
	};

	template <typename R>
	struct ContinuedFraction<R, 1> {
		using U = ratio_one;
		using V = chandra::ratio_int_sqrt<R>; // ratio<Integer<R>::value>;
		using W = ratio_zero;
		using Rem = Remainder<R, V>;
		using Error = ratio_divide<ratio_one, typename Reciprocal<Rem>::I>;
	};

	template <typename R, typename Eps, intmax_t N = 1, typename Enabled = void>
	struct Sqrt_ : Sqrt_<R, Eps, N + 1> {};

	template <typename R, typename Eps, intmax_t N>
	struct Sqrt_<R, Eps, N, typename enable_if<ratio_less_equal<typename ContinuedFraction<R, N>::Error, Eps>::value>::type> {
		using type = typename ContinuedFraction<R, N>::V;
	};

	template <typename R, typename Eps, typename Enabled = void>
	struct ratio_sqrt_impl {
		static_assert(std::ratio_greater_equal<R, internal::ratio_zero>::value, "R can't be negative");
	};

	template <typename R, typename Eps>
	struct ratio_sqrt_impl<R, Eps, typename std::enable_if<std::ratio_greater_equal<R, internal::ratio_zero>::value&& internal::IsPerfectSquare<R>::value>::type> {
		using type = typename internal::IsPerfectSquare<R>::Sqrt;
	};

	template <typename R, typename Eps>
	struct ratio_sqrt_impl<R, Eps, typename std::enable_if<(ratio_greater_equal<R, internal::ratio_zero>::value && !internal::IsPerfectSquare<R>::value)>::type> : internal::Sqrt_<R, Eps> {};

} /* namespace internal */

template<class R, class Eps>
using ratio_sqrt = typename internal::ratio_sqrt_impl<R, Eps>::type;

} /* namespace chandra */

#endif /* CHANDRA_RATIO_UTILS_H */
