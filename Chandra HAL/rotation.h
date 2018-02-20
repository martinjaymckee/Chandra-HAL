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

// TODO: CONVERT BETWEEN DIFFERENT ROTATION FORMATS
//  -- ROTATION MATRIX
//  -- EULER ANGLE
//  -- ANGLE-AXIS
//  -- QUATERNION
//  -- ?? OTHERS

//
// Rotation Representation Conversions
//
//  To Rotation Matrix
template<typename V>
auto rotMat(const Quaternion<V>& _q){
    Matrix<V, 3, 3> r;

    return r;
}

template<typename V1, typename V2, typename V3>
auto rotMat(
        const units::Q_rad<V> _yaw,
        const units::Q_rad<V2> _pitch,
        const units::Q_rad<V3> _roll
){
    Matrix<V, 3, 3> r;

    return r;
}

//  To Quaternion

//  To Euler Angles / Other Sets???

//  To Angle-Axis


//
// Vector Operations
//

//  Angle Between
template<typename V1, typename V2, size_t N>
auto angleBetween(const Matrix<V1, N, 1>& _v1, const Matrix<V2, N, 1>& _v2) {
    const auto alpha = acos(dot(_v1, _v2)/(sqrt(norm(_v1)*norm(_v2))));
    return chandra::units::Quantity<V1, chandra::units::mks::rad>(alpha);
}

//
// Quaternion Operations
//  TODO: MODIFY TO USE THE NEW MATRIX CLASS
//  TODO: THIS NEEDS TO BE TESTED....
//
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
auto angleBetween(const Quaternion<V1>& _q1, const Quaternion<V2>& _q2) {
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

