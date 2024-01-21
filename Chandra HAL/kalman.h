#ifndef CHANDRA_KALMAN_H
#define CHANDRA_KALMAN_H

#include <matrix.h>
#include <matrix_ops.h>

namespace chandra
{
namespace control
{
namespace detail
{
// Base for state variables
template<class Value, size_t StateSize>
class KalmanFilterStateBase
{
	public:
		using state_t = chandra::math::Matrix<Value, StateSize, 1>;
		using state_transition_t = chandra::math::Matrix<Value, StateSize, StateSize>;
		using state_covariance_t = chandra::math::Matrix<Value, StateSize, StateSize>;

		state_t X_prior;
		state_t X_post;
		state_transition_t F;
		state_covariance_t P_prior;
		state_covariance_t P_post;
		state_covariance_t Q = state_covariance_t::Eye();
};

// Base for measurement variables
template<class Value, size_t StateSize, size_t MeasurementSize>
class KalmanFilterMeasurementBase
{
	public:
		using measurement_t = chandra::math::Matrix<Value, MeasurementSize, 1>;
		using observation_model_t = chandra::math::Matrix<Value, MeasurementSize, StateSize>;
		using measurement_covariance_t = chandra::math::Matrix<Value, MeasurementSize, MeasurementSize>;
		using measurement_gain_t = chandra::math::Matrix<Value, StateSize, MeasurementSize>;

		observation_model_t H;
		measurement_covariance_t R = measurement_covariance_t::Eye();
		measurement_covariance_t S;
		measurement_gain_t K;
		measurement_t y;
};

// Base for input variables
template<class Value, size_t StateSize, size_t InputSize>
class KalmanFilterInputBase
{
	public:
		using input_t = chandra::math::Matrix<Value, InputSize, 1>;
		using control_model_t = chandra::math::Matrix<Value, StateSize, InputSize>;

		control_model_t B;
};

// Base for calculation core
//	With Inputs
template<class Value, uint8_t StateSize, uint8_t MeasurementSize, size_t InputSize>
class KalmanFilterBase
	: public KalmanFilterStateBase<Value, StateSize>,
	public KalmanFilterMeasurementBase<Value, StateSize, MeasurementSize>,
	public KalmanFilterInputBase<Value, StateSize, InputSize>
{
	public:
		using input_t = typename KalmanFilterInputBase<Value, StateSize, InputSize>::input_t;
		using measurement_t = typename KalmanFilterMeasurementBase<Value, StateSize, MeasurementSize>::measurement_t;
		using state_t = typename KalmanFilterStateBase<Value, StateSize>::state_t;
		using state_covariance_t = typename KalmanFilterStateBase<Value, StateSize>::state_covariance_t;

		void predict(const input_t& u) {
			this->X_prior = (this->F * this->X_post) + (this->B * u);
			this->P_prior = (this->F * this->P_post * this->F.T()) + this->Q;
			return;
		}

		void measure(const measurement_t& z) {
			this->y = z - (this->H * this->X_prior);
			return;
		}

		void gain_update() {
			this->S = (this->H * this->P_prior * this->H.T()) + this->R;
			this->K = this->P_prior * this->H.T() * chandra::math::inverse(this->S);
			return;
		}

		state_t correct() {
			constexpr static state_covariance_t I = state_covariance_t::Eye();
			this->X_post = this->X_prior + (this->K * this->y);
			this->P_post = (I - (this->K * this->H)) * this->P_prior;
			return this->X_post;
		}

		state_t update(const input_t& u, const measurement_t& z, const bool& do_gain=true) {
			predict(u);
			measure(z);
			if(do_gain) gain_update();
			return correct();
		}
};

// Without Inputs
template<class Value, uint8_t StateSize, uint8_t MeasurementSize>
class KalmanFilterBase<Value, StateSize, MeasurementSize, 0>
	: public KalmanFilterStateBase<Value, StateSize>,
	public KalmanFilterMeasurementBase<Value, StateSize, MeasurementSize>
{
public:
	using measurement_t = typename KalmanFilterMeasurementBase<Value, StateSize, MeasurementSize>::measurement_t;
	using state_t = typename KalmanFilterStateBase<Value, StateSize>::state_t;
	using state_covariance_t = typename KalmanFilterStateBase<Value, StateSize>::state_covariance_t;
	using measurement_gain_t = typename KalmanFilterMeasurementBase<Value, StateSize, MeasurementSize>::measurement_gain_t;

	void predict() {
		this->X_prior = (this->F * this->X_post);
		this->P_prior = (this->F * this->P_post * this->F.T()) + this->Q;
		return;
	}

	void measure(const measurement_t& z) {
		this->y = z - (this->H * this->X_prior);
		return;
	}

	void gain_update(const bool& use_inverse = true) {
		if (use_inverse) {
			this->S = (this->H * this->P_prior * this->H.T()) + this->R;
			this->K = this->P_prior * this->H.T() * chandra::math::inverse(this->S);
		} else {
			const auto b = (this->H * this->P_prior);
			this->S = (b * this->H.T() + this->R);
			this->K = (chandra::math::solve<chandra::math::method::LDL>(this->S, b)).T();
		}
		return;
	}

	state_t correct() {
		const static state_covariance_t I = state_covariance_t::Eye();
		this->X_post = this->X_prior + (this->K * this->y);
		this->P_post = (I - (this->K * this->H)) * this->P_prior;
		return this->X_post;
	}

	state_t update(const measurement_t& z, const bool& do_gain = true) {
		predict();
		measure(z);
		if (do_gain) gain_update(false);
		return correct();
	}
};
} /*namespace detail*/

template<class Value, uint8_t StateSize, uint8_t MeasurementSize, uint8_t InputSize=0>
class KalmanFilter : public detail::KalmanFilterBase<Value, StateSize, MeasurementSize, InputSize>
{
	public:
		using base_t = detail::KalmanFilterBase<Value, StateSize, MeasurementSize, InputSize>;
		using state_t = typename base_t::state_t;
		using state_covariance_t = typename base_t::state_covariance_t;
		using measurement_t = typename base_t::measurement_t;

		constexpr void init(const state_t& X0, const state_covariance_t& P0) {
			this->X_prior = X0;
			this->X_post = X0;
			this->P_prior = P0;
			this->P_post = P0;
			return;
		}

		constexpr void init(const state_t& X0) {
			const state_covariance_t P0(1); // TODO: MAKE THIS DO SOMETHING BETTER
			init(X0, P0);
		}

		// For calculating post-fit residual
		measurement_t residual(const measurement_t& z) {
			return z - (this->H * this->X_post);
		}
};

} /*namespace control*/
} /*namespace chandra*/

#endif /*CHANDRA_KALMAN_H*/
