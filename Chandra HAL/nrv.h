#ifndef CHANDRA_NRV_H
#define CHANDRA_NRV_H

#include <cmath>
#include <utility>

namespace chandra
{
namespace math
{
namespace statistics
{

template<class Value = float>
class NRV
{
  public:
    using value_t = Value;
    using mean_t = value_t;
    using standard_deviation_t = value_t;
    using variance_t = decltype(std::declval<standard_deviation_t>() * std::declval<standard_deviation_t>());

    NRV() = default;

    NRV(mean_t _mean, variance_t _variance)
      : mean_{_mean}, variance_{_variance} {}

    NRV(mean_t _mean) : mean_{_mean}, variance_{0} {}


    static NRV Noise(variance_t _variance) { return NRV{0, _variance}; }
    static NRV NoiseSd(standard_deviation_t _variance) { return NRV{0, _variance}; }

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
