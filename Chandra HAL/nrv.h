#ifndef CHANDRA_NRV_H
#define CHANDRA_NRV_H

#include <cmath>
#include <utility>
#include <quantity_math.h>

#include <comparable.h>

namespace chandra
{
namespace math
{
namespace statistics
{

template<class Value = float, class VarianceType = decltype(std::declval<Value>() * std::declval<Value>())>
class NRV : public chandra::math::Comparable
{
  public:
    template<class V, class VT>
    friend class NRV;
    
    using value_t = Value;
    using mean_t = value_t;
    using standard_deviation_t = value_t;
    using variance_t = VarianceType;

    NRV() = default;

    NRV(mean_t _mean, standard_deviation_t _sd)
      : mean_{_mean}, variance_{_sd * _sd} {}

    NRV(mean_t _mean) : mean_{_mean}, variance_{0} {}

	static NRV Noise(standard_deviation_t _sd) { return NRV{ 0, _sd }; }
    static NRV NoiseVar(variance_t _variance) { return NRV{0, sqrt(_variance)}; }

    mean_t mean() const { return mean_; }
    mean_t mean(mean_t _mean) {
      mean_ = _mean;
      return mean_;
    }

    standard_deviation_t standard_deviation() const { return sqrt(variance_); }
    standard_deviation_t standard_deviation(standard_deviation_t _standard_deviation) {
      variance_ = _standard_deviation * _standard_deviation;
      return _standard_deviation;
    }

    variance_t variance() const { return variance_; }
    variance_t variance(variance_t _variance) {
      variance_ = _variance;
      return variance_;
    }

    template<class V>
    bool operator == (const V& _other) const {
      return mean_ == mean_t(_other.mean_);
    }

    template<class V>
    bool operator > (const V& _other) const {
      return mean_ > mean_t(_other.mean_);
    }

  private:
    mean_t mean_{0};
    variance_t variance_{1};
};

template<class Stream, class Value>
Stream& operator << (Stream& _stream, const NRV<Value>& _nrv) {
  _stream << "N(" << _nrv.mean() << ", " << _nrv.standard_deviation() << ")";
  return _stream;
}

} /*namespace statistics*/
} /*namespace math*/
} /*namespace chandra*/
#endif /*CHANDRA_NRV_H*/
