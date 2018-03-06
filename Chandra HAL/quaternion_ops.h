#ifndef CHANDRA_QUATERNION_OPS_H
#define CHANDRA_QUATERNION_OPS_H

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

//  Derivitive
template<typename V1, typename V2>
// TODO: CHANGE TO TAKE AN ANGULAR VELOCITY QUANTITY
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

