#ifndef CHANDRA_QUATERNION_OPS_H
#define CHANDRA_QUATERNION_OPS_H

#include <cmath>

#include "quantity.h" // NOTE: THIS IS ONLY NEEDED FOR IMPLEMENTING THE INTEGRATE METHOD IN SUCH A WAY THAT QUANTITIES ARE USABLE...
                      //  I NEED TO FIGURE OUT IF THIS MAKES SENSE
#include "units.h"

namespace chandra
{
namespace math
{

//
// Arithmetic Operations
//

//  Norm
template<class T>
constexpr T norm(const Quaternion<T>& _q){ return (_q.w*_q.w) + (_q.x*_q.x) + (_q.y*_q.y) + (_q.z*_q.z); }

//  Modulus
template<class T>
constexpr T modulus(const Quaternion<T>& _q) { return sqrt(norm(_q)); }

//  Complex Conjugate
template<class T>
constexpr Quaternion<T> conj(const Quaternion<T>& _q) { return Quaternion<T>(_q.w, -_q.x, -_q.y, -_q.z); }

//  Inverse
template<class T>
constexpr Quaternion<T> inv(const Quaternion<T>& _q) {
    const auto n = norm(_q);
    return Quaternion<T>(_q.w/n, -_q.x/n, -_q.y/n, -_q.z/n);
}

//  Unit Quaternion
template<class T>
constexpr Quaternion<T> unit(const Quaternion<T>& _q) {
    return _q.normalized();
}

//  Addition
template<class T1, class T2>
constexpr Quaternion<T1> operator + (const Quaternion<T1>& _q, const Quaternion<T2>& _r) {
    auto q = Quaternion<T1>(_q);
    q += _r;
    return q;
}

//  Subtraction
template<class T1, class T2>
constexpr Quaternion<T1> operator - (const Quaternion<T1>& _q, const Quaternion<T2>& _r) {
    auto q = Quaternion<T1>(_q);
    q -= _r;
    return q;
}

//  Multiplication
//      Quaternion
template<class T1, class T2>
constexpr Quaternion<T1> operator * (const Quaternion<T1>& _q, const Quaternion<T2>& _r) {
    auto q = Quaternion<T1>(_q);
    q *= _r;
    return q;
}

//      Scalar
template<class T1, class T2>
constexpr Quaternion<T1> operator * (const Quaternion<T1>& _q, const T2& _r) {
    auto q = Quaternion<T1>(_q);
    q *= _r;
    return q;
}

template<class T1, class T2>
constexpr Quaternion<T2> operator * (const T1& _c, const Quaternion<T2>& _q) {
    auto q = Quaternion<T2>(_q);
    q *= _c;
    return q;
}

//  Division
//      Quaternion
template<class T1, class T2>
constexpr Quaternion<T1> operator / (const Quaternion<T1>& _q, const Quaternion<T2>& _r) {
    auto q = Quaternion<T1>(_q);
    q /= _r;
    return q;
}

//      Scalar
template<class T1, class T2>
constexpr Quaternion<T1> operator / (const Quaternion<T1>& _q, const T2& _r) {
    auto q = Quaternion<T1>(_q);
    q /= _r;
    return q;
}

//  Dot Product
template<class T1, class T2>
constexpr auto dot(const Quaternion<T1>& _qa, const Quaternion<T2>& _qb) {
  return (_qa.w * _qb.w) + (_qa.x * _qb.x) + (_qa.y * _qb.y) + (_qa.z * _qb.z);
}

//  Derivitive
template<typename V1, typename V2>
constexpr Quaternion<V1> deriv(const Quaternion<V1>& _q, const Matrix<V2, 3, 1>& _w_dot)
{
    constexpr V1 half(0.5);
    Quaternion<V1> dq;
    dq.w = -half * (_w_dot(0)*_q.x + _w_dot(1)*_q.y + _w_dot(2)*_q.z);
    dq.x = half * (_w_dot(0)*_q.w + _w_dot(1)*_q.z - _w_dot(2)*_q.y);
    dq.y = half * (_w_dot(1)*_q.w + _w_dot(2)*_q.x - _w_dot(0)*_q.z);
    dq.z = half * (_w_dot(2)*_q.w + _w_dot(0)*_q.y - _w_dot(1)*_q.x);
    return dq;
}


//  Integral
/*template<class V1, class TimeType, class V2>
constexpr auto integrate(const Quaternion<V1>& _q, const TimeType& _dt, const Matrix<V2, 3, 1>& _w_dot)
{
  using scalar_t = typename chandra::scalar_of<V2>::type;
  const Matrix<scalar_t, 3, 1> w_dot{
    chandra::units::scalar_cast(_w_dot(0)), // TODO: THIS SHOULD NOT USE THE UNITS NAMESPACE UNLESS ABSOLUTELY NECESSARY....
    chandra::units::scalar_cast(_w_dot(1)),
    chandra::units::scalar_cast(_w_dot(2))
  };
  const auto q_rot = Quaternion<V1>::Pure(w_dot);
  const auto dt = chandra::units::scalar_cast(_dt);
  return _q + ( dt * deriv(_q, w_dot));
}*/


template<class V1, class TimeType, class V2>
constexpr auto integrate(const Quaternion<V1>& _q, const TimeType& _dt, const Matrix<V2, 3, 1>& _w_dot)
{
  using scalar_t = typename chandra::scalar_of<V2>::type;
  const Matrix<scalar_t, 3, 1> w_dot{
    chandra::units::scalar_cast(_w_dot(0)), // TODO: THIS SHOULD NOT USE THE UNITS NAMESPACE UNLESS ABSOLUTELY NECESSARY....
    chandra::units::scalar_cast(_w_dot(1)),
    chandra::units::scalar_cast(_w_dot(2))
  };
  const auto dt = chandra::units::scalar_cast(_dt);
  const auto mag = chandra::math::magnitude(w_dot);
  const auto theta = chandra::units::scalar_cast(dt*mag);
  const auto axis = w_dot / mag;
  const auto qr = Quaternion<V1>::AngleAxis(theta, axis);
  const auto qn = _q * qr;
  if(mag > 0.01) {
    const auto a = 10;
  }
  return qn;
}

template<class V1, class TimeType, class V2, bool IC, class Frame>
constexpr auto integrate(const Quaternion<V1>& _q, const TimeType& _dt, const Vector<V2, 3, IC, Frame>& _w_dot)
{
  const Matrix<V2, 3, 1> w_dot{_w_dot(0), _w_dot(1), _w_dot(2)};
  return integrate(_q, _dt, w_dot);
}

template<class V>
constexpr auto offsetAngle(const Quaternion<V>& _q) {
  V w = _q.w;
  if(w > V{1}) w = V{1};
  if(w < V{-1}) w = V{-1};
  return chandra::units::mks::Q_rad<V>{2 * std::acos(_q.w)};
}

template<class V1, class V2, class V3>
const auto slerp(const V1& _t, const Quaternion<V2>& _qa, const Quaternion<V3>& _qb) {
    const auto theta = std::acos(dot(_qa, _qb));
    return ((_qa * std::sin((1-_t) * theta)) + (_qb * std::sin(_t * theta))) / std::sin(theta);
}

} /*namespace math*/
} /*namespace chandra*/

//
// I/O Functions
//
template<typename Stream, typename T>
Stream& operator << (Stream& _stream, const chandra::math::Quaternion<T>& _q) {
    _stream << "( " << _q.w;
    _stream << ", " << _q.x;
    _stream << ", " << _q.y;
    _stream << ", " << _q.z;
    _stream << " )";
    return _stream;
}

#endif /*CHANDRA_QUATERNION_OPS_H*/
