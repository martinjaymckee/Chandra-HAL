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

        ExponentialWeightedAverage(const scalar_t& _w = scalar_t(0.5)) : w_(_w), x_(0) {}

        value_t x(value_t _x) {
            x_ = _x;
            return x_;
        }

        value_t x() const { return x_; }

        value_t operator() (const value_t& _x) {
            x_ += w_* (_x - x_);
            return x_;
        }

    private:
        scalar_t w_;
        value_t x_;
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

        // RecursiveMeanVarianceFilter() {
        //   initialize_cutoffs(1.0/5.0); // Initialize cutoff frequency to fs / 5
        // }

        RecursiveMeanVarianceFilter(
          const scalar_t& _a = scalar_t(0.9),
          const scalar_t& _b = scalar_t(0.9)
        )
          : a_(_a), b_(_b), v_(0)
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

        template<class MeanType, class VarType, class V>
        bool initalize_timeconstants( const MeanType& _tau_mean, const VarType& _tau_var, const frequency_t<V>& _fs ) {
          const auto tau_mean = std::chrono::duration_cast<std::chrono::microseconds>(_tau_mean);
          const auto tau_var = std::chrono::duration_cast<std::chrono::microseconds>(_tau_var);
          const auto ts = calcSampleTime(_fs.value());
          a_ = calcCoef(tau_mean.count(), ts);
          b_ = calcCoef(tau_var.count(), ts);
          updateCoefficients();
          return true;
        }

        template<class TauType, class V>
        bool initalize_timeconstants( const TauType& _tau, const frequency_t<V>& _fs ) {
          return timeconstants( _tau, _tau, _fs );
        }

        // ADD AN ALTERNITIVE INITIALIZAION METHOD THAT TAKES THE RATIO OF BANDWIDTH TO SAMPLING RATE
        // use: A = e^(-T/tau), ratio = T/tau, tau = -T/log(A)
        bool initialize_cutoffs(const scalar_t& _cutoff_mean, const scalar_t& _cutoff_var) {
          a_ = calcCoef(scalar_t{1}, _cutoff_mean);
          b_ = calcCoef(scalar_t{1}, _cutoff_var);
          updateCoefficients();
          return true;
        }

        bool initialize_cutoffs(const scalar_t& _cutoff) {
          return initialize_cutoffs(_cutoff, _cutoff);
        }

        template<class V>
        duration_t tau_mean(const frequency_t<V>& _fs) {
            const auto ts = calcSampleTime(_fs.value());
            return {calcTau(a_, ts)};
        }

        template<class V>
        duration_t tau_var(const frequency_t<V>& _fs) {
            const auto ts = calcSampleTime(_fs.value());
            return {calcTau(b_, ts)};
        }

        scalar_t a(scalar_t _a) {
          a_ = _a;
          updateCoefficients();
          return a_;
        }
        constexpr scalar_t a() const { return a_; }

        scalar_t b(scalar_t _b) {
          b_ = _b;
          updateCoefficients();
          return b_;
        }
        constexpr scalar_t b() const { return b_; }

        constexpr variance_t operator() (const value_t& _x) {
          if(initialized_) {
            x_ = (a_* (x_ - _x)) + _x; // Recursive Mean Estimator
            const auto e = x_-_x;
            v_ = (b_*v_) + (d_*(e*e));
          } else {
            x_ = _x;
            v_ = variance_t{0};
            initialized_ = true;
          }
            return v_;
        }

    protected:
        constexpr scalar_t calcD(scalar_t _a, scalar_t _b) const {
          return ((scalar_t(1.0) - _b) + (scalar_t(1.0) + _a)) / scalar_t(2.0);
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
          d_ = calcD(a_, b_);
        }

    private:
        bool initialized_ = false;
        scalar_t a_;
        scalar_t b_;
        scalar_t d_;
        value_t x_;
        variance_t v_;
};

} /*namespace signal*/
} /*namespace chandra*/

#endif /*CHANDRA_WINDOWED_FILTERS_H*/
