#ifndef CHANDRA_ROTATION_H
#define CHANDRA_ROTATION_H

#include "matrix.h"
#include "matrix_ops.h"
#include "quaternion.h"
#include "quaternion_ops.h"
#include "quantity.h"
#include "units.h"

namespace chandra
{
namespace math
{
//
// Unless otherwise specified, the implementations in this file are taken from the paper,
//  "Representing Attitude: Euler Angles, Unit Quaternions, and Rotation Vectors", written by
//  James Diebel.
//

template<typename Value>
class TaitBryan
{
    public:
        using value_t = Value;
        using angle_t = units::mks::Q_rad<value_t>;

        TaitBryan() : roll(0), pitch(0), yaw(0) {}
        TaitBryan(
                const angle_t& _roll,
                const angle_t& _pitch = angle_t(0),
                const angle_t& _yaw = angle_t(0) )
            : roll(_roll), pitch(_pitch), yaw(_yaw) {}

        angle_t roll;
        angle_t pitch;
        angle_t yaw;
};

template<typename Stream, typename Value>
Stream& operator << (Stream& _stream, TaitBryan<Value> _tb) {
    _stream << "TaitBryan( roll = " << _tb.roll;
    _stream << ", pitch = " << _tb.pitch;
    _stream << ", yaw = " << _tb.yaw << " )";
    return _stream;
}

// TODO: CONVERT BETWEEN DIFFERENT ROTATION FORMATS
//  -- ROTATION MATRIX
//  -- EULER ANGLE
//  -- ANGLE-AXIS
//  -- QUATERNION
//  -- ?? OTHERS

//
// Rotation Representation Conversions
//
//  To Direction Cosine Matrix - dcm(...)
//      -> From Quaternion
template<typename V>
constexpr auto dcm(const Quaternion<V>& _q){
    const auto w2 = _q.w*_q.w;
    const auto x2 = _q.x*_q.x;
    const auto y2 = _q.y*_q.y;
    const auto z2 = _q.z*_q.z;
    const auto wx = _q.w*_q.x;
    const auto wy = _q.w*_q.y;
    const auto wz = _q.w*_q.z;
    const auto xy = _q.x*_q.y;
    const auto xz = _q.x*_q.z;
    const auto yz = _q.y*_q.z;

    Matrix<V, 3, 3> M;
    M(0, 0) = w2+x2-y2-z2;
    M(0, 1) = 2*(xy+wz);
    M(0, 2) = 2*(xz-wy);

    M(1, 0) = 2*(xy-wz);
    M(1, 1) = w2-x2+y2-z2;
    M(1, 2) = 2*(yz+wx);

    M(2, 0) = 2*(xz+wy);
    M(2, 1) = 2*(yz-wx);
    M(2, 2) = w2-x2-y2+z2;
    return M;
}

//      -> From Tait-Bryan Angles
template<typename V>
constexpr auto dcm(const TaitBryan<V>& _tb) {
    using value_t = V;
    const value_t sr = sin(_tb.roll.value());
    const value_t cr = cos(_tb.roll.value());
    const value_t sp = sin(_tb.pitch.value());
    const value_t cp = cos(_tb.pitch.value());
    const value_t sy = sin(_tb.yaw.value());
    const value_t cy = cos(_tb.yaw.value());

    Matrix<value_t, 3, 3> M;
    M(0, 0) = cp*cy;
    M(0, 1) = cp*sy;
    M(0, 2) = -sp;

    M(1, 0) = sr*sp*cy - cr*sy;
    M(1, 1) = sr*sp*sy + cr*cy;
    M(1, 2) = cp*sr;

    M(2, 0) = cr*sp*cy + sr*sy;
    M(2, 1) = cr*sp*sy - sr*cy;
    M(2, 2) = cp*cr;
    return M;
}

//      -> Tait-Bryan (Independent Angles)
template <typename V1, typename V2, typename V3>
constexpr auto dcm(
        units::mks::Q_rad<V1> _roll,
        units::mks::Q_rad<V2> _pitch,
        units::mks::Q_rad<V3> _yaw)
{
    return dcm(TaitBryan<V1>(_roll, _pitch, _yaw));
}

//  To Quaternion - quat(...)
//      -> From Tait-Bryan Angles
template<typename V>
constexpr auto quat(const TaitBryan<V>& _tb) {
    using value_t = V;
    const value_t half_roll = _tb.roll.value() / 2.0;
    const value_t half_pitch = _tb.pitch.value() / 2.0;
    const value_t half_yaw = _tb.yaw.value() / 2.0;
    const value_t sr = sin(half_roll);
    const value_t cr = cos(half_roll);
    const value_t sp = sin(half_pitch);
    const value_t cp = cos(half_pitch);
    const value_t sy = sin(half_yaw);
    const value_t cy = cos(half_yaw);
    const auto w = cr*cp*cy + sr*sp*sy;
    const auto x = sr*cp*cy - cr*sp*sy;
    const auto y = cr*sp*cy + sr*cp*sy;
    const auto z = cr*cp*sy - sr*sp*cy;
    return Quaternion<V>(w, x, y, z);
}

//      -> Tait-Bryan (Independent Angles)
template <typename V1, typename V2, typename V3>
constexpr auto quat(
        units::mks::Q_rad<V1> _roll,
        units::mks::Q_rad<V2> _pitch,
        units::mks::Q_rad<V3> _yaw)
{
    return quat(TaitBryan<V1>(_roll, _pitch, _yaw));
}

//      -> Direction Cosine Matrix
template <typename V>
constexpr auto quat(const Matrix<V, 3, 3>& _M) {
// Implementation based upon that found in,
//      "Converting a Rotation Matrix to a Quaternion"
//      By: Mike Day, Insominac Games
    constexpr V one(1);
    V w = 0;
    V x = 0;
    V y = 0;
    V z = 0;
    V t = 0;

    if(_M(2, 2) < 0) {
        if(_M(0, 0) > _M(1, 1)) {
            t = one + _M(0, 0) - _M(1, 1) - _M(2, 2);
            w = _M(1, 2) - _M(2, 1);
            x = t;
            y = _M(0, 1) + _M(1, 0);
            z = _M(2, 0) + _M(0, 2);
        } else {
            t = one - _M(0, 0) + _M(1, 1) - _M(2, 2);
            w = _M(2, 0) - _M(0, 2);
            x = _M(0, 1) + _M(1, 0);
            y = t;
            z = _M(1, 2) + _M(2, 1);
        }
    } else {
        if(_M(0, 0) < -_M(1, 1)) {
            t = one - _M(0, 0) - _M(1, 1) + _M(2, 2);
            w = _M(0, 1) - _M(1, 0);
            x = _M(2, 0) + _M(0, 2);
            y = _M(1, 2) + _M(2, 1);
            z = t;
        } else {
            t = one + _M(0, 0) + _M(1, 1) + _M(2, 2);
            w = t;
            x = _M(1, 2) - _M(2, 1);
            y = _M(2, 0) - _M(0, 2);
            z = _M(0, 1) - _M(1, 0);
        }
    }
    const auto s = 0.5 / sqrt(t);
    return Quaternion<V>(s*w, s*x, s*y, s*z);
}

//  To Tait Bryan
//      -> Independent Angles
template <typename V1, typename V2, typename V3>
 constexpr auto taitbryan(
        units::mks::Q_rad<V1> _roll,
        units::mks::Q_rad<V2> _pitch,
        units::mks::Q_rad<V3> _yaw)
{
    return TaitBryan<V1>{_roll, _pitch, _yaw};
}

 //     -> Quaternion
template <typename V>
constexpr auto taitbryan(const Quaternion<V>& _q) {
    using value_t = V;
    using angle_t = typename TaitBryan<value_t>::angle_t;
    const auto w2 = _q.w*_q.w;
    const auto x2 = _q.x*_q.x;
    const auto y2 = _q.y*_q.y;
    const auto z2 = _q.z*_q.z;
    TaitBryan<value_t> tb;
    tb.roll = angle_t(atan2(2*(_q.y*_q.z + _q.w*_q.x), w2-x2-y2+z2));
    tb.pitch = angle_t(-asin(2*(_q.x*_q.z - _q.w*_q.y)));
    tb.yaw = angle_t(atan2(2*(_q.x*_q.y + _q.w*_q.z), w2+x2-y2-z2));
    return tb;
/*    constexpr value_t half_pi(3.141592635/2.0);

    const auto pitch_val = asin(2 * (_q.w*_q.y - _q.x*_q.z)); // TODO: CHECK WHY THIS DOESN'T WORK WITH THE NEGATIVE ON PITCH
    const auto w2 = _q.w*_q.w;
    const auto x2 = _q.x*_q.x;
    const auto y2 = _q.y*_q.y;
    const auto z2 = _q.z*_q.z;
    TaitBryan<value_t> tb;

    if(pitch_val == half_pi or pitch_val == -half_pi) {
        tb.roll = angle_t(0);
        if(pitch_val == half_pi) {
            tb.yaw = angle_t(-2 * atan2(_q.w, _q.x));
        } else { // pitch = -pi/2 rad
            tb.yaw = angle_t(2 * atan2(_q.x, _q.w));
        }
    } else {
        tb.roll = angle_t(atan2(2*(_q.w*_q.z + _q.x*_q.y), w2+x2-y2-z2));
        tb.yaw = angle_t(atan2(2*(_q.w*_q.x + _q.y*_q.z), w2-x2-y2+z2));
    }
    tb.pitch = angle_t(pitch_val);

    return tb;
*/
}

//      -> Direction Cosine Matrix
template<typename V>
constexpr auto taitbryan(const Matrix<V, 3, 3>& _M) {
    using value_t = V;
    using angle_t = typename TaitBryan<value_t>::angle_t;
    TaitBryan<value_t> tb;

    tb.roll = angle_t(atan2(_M(1, 2), _M(2, 2)));
    tb.pitch = angle_t(-asin(_M(0, 2)));
    tb.yaw = angle_t(atan2(_M(0, 1), _M(0, 0)));

    return tb;
}

//  To Angle-Axis


//
// Vector Operations
//

//  Angle Between
template<typename V1, typename V2, size_t N>
constexpr auto angleBetween(const Matrix<V1, N, 1>& _v1, const Matrix<V2, N, 1>& _v2) {
    const auto alpha = acos(dot(_v1, _v2)/(sqrt(norm(_v1)*norm(_v2))));
    return chandra::units::mks::Q_rad<V1>(alpha);
}

//
// Rotations
//
// By Direction Cosine Matrix
template<typename V1, typename V2>
constexpr auto rotate(const Matrix<V1, 3, 1>& _v, const Matrix<V2, 3, 3>& _M) {
    return _M * _v;
}

//  By Quaternion
template<typename V1, typename V2>
constexpr auto rotate(const Matrix<V1, 3, 1>& _v, const Quaternion<V2>& _q) {
    Matrix<V1, 3, 1> v;

    constexpr V1 one(1);
    constexpr V1 two(2);

    const auto D1 = two * (_q.x * _q.x);
    const auto D2 = two * (_q.y * _q.y);
    const auto D3 = two * (_q.z * _q.z);

    const auto Q01 = _q.w * _q.x;
    const auto Q02 = _q.w * _q.y;
    const auto Q03 = _q.w * _q.z;
    const auto Q12 = _q.x * _q.y;
    const auto Q13 = _q.x * _q.z;
    const auto Q23 = _q.y * _q.z;

    v(0) = (_v(0)*(one-D2-D3)) + (two * ((_v(1)*(Q12+Q03)) + (_v(2)*(Q13-Q02))));
    v(1) = (_v(1)*(one-D1-D3)) + (two * ((_v(0)*(Q12-Q03)) + (_v(2)*(Q23+Q01))));
    v(2) = (_v(2)*(one-D1-D2)) + (two * ((_v(0)*(Q13+Q02)) + (_v(1)*(Q23-Q01))));

    return v;
}

// TODO: THIS NEEDS TO RETURN AN ANGLE QUANTITY
template<typename V1, typename V2>
constexpr auto angleBetween(const Quaternion<V1>& _q1, const Quaternion<V2>& _q2) {
    constexpr V1 pi(3.14159);

    const auto N = (_q1.w*_q2.w) + (_q1.x*_q2.x) + (_q1.y*_q2.y) + (_q1.z*_q2.z);
    const auto D = norm(_q1)*norm(_q2);
    const auto alpha = 2 * acos(N/D);
//    const auto z = _q1 * inv(_q2);
//    const auto alpha = 2 * acos(z.w);

    if(alpha > pi) return chandra::units::Quantity<V1, chandra::units::mks::rad>(alpha - pi);
    else if(alpha < -pi) return chandra::units::Quantity<V1, chandra::units::mks::rad>(alpha + pi);
    return chandra::units::Quantity<V1, chandra::units::mks::rad>(alpha);
}

} /*namespace math*/
} /*namespace chandra*/

#endif /*MATRIX_H*/

