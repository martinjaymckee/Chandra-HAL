#ifndef CHANDRA_NRV_H
#define CHANDRA_NRV_H

#include <cmath>
#include <utility>
#include <quantity_math.h> // TODO: FIGURE OUT IF THERE'S A WAY TO PULL IN SQRT THROUGH ADL

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
    template<class MT, class VT>
    friend class NRV;

	  template<class MT, class VT, class MT2, class VT2>
	  friend auto operator / (const NRV<MT, VT>&, const NRV<MT2, VT2>&);

    template<class MT, class VT, class V>
    friend auto operator / (const NRV<MT, VT>&, const V&);

    template<class V, class MT, class VT>
    friend auto operator / (const V&, const NRV<MT, VT>&);

    template<class MT, class VT, class MT2, class VT2>
	  friend auto operator * (const NRV<MT, VT>&, const NRV<MT2, VT2>&);

    template<class MT, class VT, class V>
    friend auto operator * (const NRV<MT, VT>&, const V&);

    template<class V, class MT, class VT>
    friend auto operator * (const V&, const NRV<MT, VT>&);

    using value_t = Value;
    using mean_t = value_t;
    using standard_deviation_t = value_t;
    using variance_t = VarianceType;

    //
    // Constructors
    //
    NRV() = default;

    NRV(mean_t _mean, standard_deviation_t _sd)
      : mean_{_mean}, variance_{_sd * _sd} {}

    NRV(mean_t _mean) : mean_{_mean}, variance_{0} {}

    //  Copy-/Conversion-Constructor
    template<class MT, class VT>
    NRV(const NRV<MT, VT> _other) : mean_{_other.mean_}, variance_{_other.variance_} {}

    //  Noise-Only Constructors
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

//
// Conversion Function
//
template<class V>
auto nrv(const V& _val) -> NRV<V> {
  return {_val};
}

//
// Stream Output
//
template<class Stream, class Value>
Stream& operator << (Stream& _stream, const NRV<Value>& _nrv) {
  _stream << "N(" << _nrv.mean() << ", " << _nrv.standard_deviation() << ")";
  return _stream;
}

//
// Arithmetic
//

//
// Division
//
//  by NRV
template<class MT, class VT, class MT2, class VT2>
auto operator / (const NRV<MT, VT>& _den, const NRV<MT2, VT2>& _num) {
  static const MT den_eps{1e-9}; // HACK: THIS NEEDS TO GET THE EPS VALUE FROM SOMEWHERE ELSE

  using division_mean_t = decltype(std::declval<MT>() / std::declval<MT2>());
	NRV<division_mean_t> result;
  using division_variance_t = decltype(result.variance());
  const auto ma = _den.mean_;
  const auto mb = _num.mean_;
  result.mean_ = ma / mb;
  const auto vb = _num.variance_;
  const auto mb_2 = mb * mb;
//  if( (ma > -den_eps) and (ma < den_eps) ) {
//    result.variance_ = division_variance_t(vb / mb_2);
//  } else {
    const auto va = _den.variance_;
    const auto ma_2 = ma * ma;
    result.variance_ = division_variance_t(((ma_2 / mb_2)*((va / ma_2) + (vb / mb_2))));
//  }
	return result;
}

//  by Value
template<class MT, class VT, class V>
auto operator / (const NRV<MT, VT>& _den, const V& _num) {
	return _den / NRV<V>(_num);
}

//  of Value by NRV
template<class V, class MT, class VT>
auto operator / (const V& _den, const NRV<MT, VT>& _num) {
  return NRV<V>(_den) / _num;
}

//
// Multiplication
//
//  by NRV
template<class MT, class VT, class MT2, class VT2>
auto operator * (const NRV<MT, VT>& _op_a, const NRV<MT2, VT2>& _op_b) {
	using product_mean_t = decltype(std::declval<MT>() * std::declval<MT2>());
	NRV<product_mean_t> result;
  using product_variance_t = decltype(result.variance());
  const auto ma = _op_a.mean_;
  const auto mb = _op_b.mean_;
  result.mean_ = ma * mb;
  const auto va = _op_a.variance_;
  const auto vb = _op_b.variance_;
  const auto ma_2 = ma * ma;
  const auto mb_2 = mb * mb;
	result.variance_ = product_variance_t((va + ma_2)*(vb + mb_2)) - product_variance_t(ma_2 * mb_2);
	return result;
}

//  by Value
template<class MT, class VT, class V>
auto operator * (const NRV<MT, VT>& _op_a, const V& _op_b) {
  using product_mean_t = decltype(std::declval<MT>() * std::declval<V>());
	NRV<product_mean_t> result;
  using product_variance_t = decltype(result.variance());
  const auto ma = _op_a.mean_;
  const auto mb = _op_b;
  result.mean_ = ma * mb;
  const auto va = _op_a.variance_;
  const auto ma_2 = ma * ma;
  const auto mb_2 = mb * mb;
	result.variance_ = product_variance_t((va + ma_2)*mb_2) - product_variance_t(ma_2 * mb_2);
	return result;
}

//  NRV Division of Other Value by NRV
template<class V, class MT, class VT>
auto operator * (const V& _op_a, const NRV<MT, VT>& _op_b) {
  using product_mean_t = decltype(std::declval<V>() * std::declval<MT>());
	NRV<product_mean_t> result;
  using product_variance_t = decltype(result.variance());
  const auto ma = _op_a;
  const auto mb = _op_b.mean_;
  result.mean_ = ma * mb;
  const auto vb = _op_b.variance_;
  const auto ma_2 = ma * ma;
  const auto mb_2 = mb * mb;
	result.variance_ = product_variance_t(ma_2*(vb + mb_2)) - product_variance_t(ma_2 * mb_2);
	return result;
}

} /*namespace statistics*/
} /*namespace math*/
} /*namespace chandra*/
#endif /*CHANDRA_NRV_H*/
