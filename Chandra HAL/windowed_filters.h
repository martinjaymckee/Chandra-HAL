#ifndef CHANDRA_WINDOWED_FILTERS_H
#define CHANDRA_WINDOWED_FILTERS_H

#include <chrono>

#include "meta.h"
#include "units.h"

namespace chandra
{
namespace signal
{

template<typename Value, class Clock = void>
class ExponentialWeightedAverage
{
    public:
        using value_t = Value;
        using scalar_t = scalar_of_t<value_t>;

        ExponentialWeightedAverage(const scalar_t& _w = scalar_t(0.5)) : w_(_w), v_(0) {}

        value_t v(value_t _v) {
            v_ = _v;
            return v_;
        }

        value_t v() const { return v_; }

        value_t operator() (const value_t& _v) {
            v_ += w_* (_v - v_);
            return v_;
        }

    private:
        scalar_t w_;
        value_t v_;
};

// TODO: WHEN THIS IS WORKING, SIMPLIFY IT TO GET JUST THE MEAN FILTER.
//  ALSO, LOOK INTO POSSIBLE OPTIMIZATIONS OF THE FUCTIONS TO MAKE THIS AS EFFICIENT AS POSSIBLE
//  ACTUALLY... IT MIGHT MAKE SENSE TO SUBCLASS THIS FROM THE RECURSIVE MEAN FILTER AS THAT WOULD
//  ALLOW FOR SOME OF THE HELPER FUNCTIONS TO BE INHERITED
template<typename Value, class Clock = chandra::chrono::timestamp_clock>
class RecursiveMeanVarianceFilter
{
    //
    // Note: The bias correction in this implementation is based upon that
    // outlined in NASA Technical Note D-5465:
    //  "Estimation of Variance by a Recursive Equation", M. Melvin Bruce, 1969
    //

    public:
        using value_t = Value;
        using variance_t = decltype(value_t()*value_t());
        using standard_deviation_t = Value;
        using scalar_t = scalar_of_t<value_t>;
        using duration_t = typename Clock::duration;
        template<class V>
        using frequency_t = chandra::units::Quantity<V, chandra::units::mks::Hz>;

        RecursiveMeanVarianceFilter() {
          initialize_cutoffs(1.0/5.0); // Initialize cutoff frequency to fs / 5
        }

        RecursiveMeanVarianceFilter(
          const scalar_t& _A = scalar_t(0.9),
          const scalar_t& _B = scalar_t(0.9)
        )
          : A_(_A), B_(B), v_(0)
        {
          updateCoefficients();
        }

        value_t reset(value_t _x) {
          x(_x);
          v_ = 0;
        }

        value_t x(value_t _x) {
            x_ = _x;
            return x_;
        }

        value_t x() const { return x_; }

        constexpr value_t var() const { return v_; }
        constexpr value_t std() const { return sqrt(var()); }

        template<class V>
        bool initalize_timeconstants( const auto& _tau_mean, auto& _tau_var, const frequency_t<V>& _fs ) {
          const auto tau_mean = std::chrono::duration_cast<std::chrono::microseconds>(_tau_mean);
          const auto tau_var = std::chrono::duration_cast<std::chrono::microseconds>(_tau_var);
          const auto ts = calcSampleTime(_fs.value());
          A_ = calcCoef(tau_mean.count(), ts);
          B_ = calcCoef(tau_var.count(), ts);
          updateCoefficients();
          return true;
        }

        template<class V>
        bool initalize_timeconstants( const auto& _tau, const frequency_t<V>& _fs ) {
          return timeconstants( _tau, _tau, _fs );
        }

        // ADD AN ALTERNITIVE INITIALIZAION METHOD THAT TAKES THE RATIO OF BANDWIDTH TO SAMPLING RATE
        // use: A = e^(-T/tau), ratio = T/tau, tau = -T/log(A)
        bool initialize_cutoffs(const scalar_t& _cutoff_mean, const scalar_t& _cutoff_var) {
          A_ = calcCoef(scalar_t{1}, _cutoff_mean);
          B_ = calcCoef(scalar_t{1}, _cutoff_var);
          updateCoefficients();
          return true;
        }

        bool initialize_cutoffs(const scalar_t& _cutoff) {
          return initialize_cutoffs(_cutoff, _cutoff);
        }

        template<class V>
        duration_t tau_mean(const frequency_t<V>& _fs) {
            const auto ts = calcSampleTime(_fs.value());
            return {calcTau(A_, ts)};
        }

        template<class V>
        duration_t tau_var(const frequency_t<V>& _fs) {
            const auto ts = calcSampleTime(_fs.value());
            return {calcTau(B_, ts)};
        }

        scalar_t A(scalar_t _A) {
          A_ = _A;
          updateCoefficients();
          return A_;
        }
        constexpr scalar_t A() const { return A_; }

        scalar_t B(scalar_t _B) {
          B_ = _B;
          updateCoefficients();
          return B_;
        }
        constexpr scalar_t B() const { return B_; }

        value_t operator() (const value_t& _x) {
            x_ = (A_* (x_ - _x)) + _x; // Recursive Mean Estimator
            const auto e = x_-_x;
            v_ = (B_*v_) + (D_*(e*e));
            return v_;
        }

    protected:
        constexpr scalar_t calcD(scalar_t _A, scalar_t _B) const {
          return ((scalar_t(1.0) - B_) + (scalar_t(1.0) + A_)) / scalar_t(2.0);
        }

        constexpr scalar_t calcCoef(scalar_t _tau, scalar_t _ts) const {
          return 0;
        }

        constexpr scalar_t calcTau(scalar_t _e, scalar_t _ts) const {

          return 0;
        }

        constexpr std::chrono::microseconds calcSampleTime(const scalar_t& _fs) const {
          return {scalar_t(1000000) / _fs}; // TODO: THIS IS PROBABLY GOING TO REQUIRE A DURATION CAST....
        }

        void updateCoefficients() {
          D_ = calcD(A_, B_);
        }

    private:
        scalar_t A_;
        scalar_t B_;
        scalar_t D_;
        value_t x_;
        variance_t v_;
};

} /*namespace signal*/
} /*namespace chandra*/

#endif /*CHANDRA_WINDOWED_FILTERS_H*/
