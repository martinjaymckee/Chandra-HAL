#ifndef CHANDRA_COORDINATES_H
#define CHANDRA_COORDINATES_H

#include <cmath>

#include "geoid.h"
#include "math_ops.h"
#include "quantity_math.h"
#include "units.h"
using namespace chandra::units::mks::literals;

template<class T>
struct TD;

namespace chandra
{
namespace aero
{

template<class Value, class AngleUnits = chandra::units::mks::rad, class LengthUnits = chandra::units::mks::m>
struct LLH
{
    using angle_t = chandra::units::Quantity<Value, AngleUnits>;
    using length_t = chandra::units::Quantity<Value, LengthUnits>;

    angle_t latitude;
    angle_t longitude;
    length_t altitude;
};


template<class Value, class LengthUnits = chandra::units::mks::m>
struct ECEF
{
    using length_t = chandra::units::Quantity<Value, LengthUnits>;

    length_t x;
    length_t y;
    length_t z;
};

template<class Value, class AngleUnits, class LengthUnits, Geoid GeoidDef = Geoid::WGS84>
auto LLHToECEF( const LLH<Value, AngleUnits, LengthUnits>& _llh ) -> ECEF<Value>
{
  using ellipsoid_t = chandra::aero::Ellipsoid<Value, GeoidDef>;
  using angle_t = chandra::units::mks::Q_rad<Value>;
  ECEF<Value, LengthUnits> xyz;
  const auto r = chandra::math::sincos<Value>(angle_t{_llh.latitude}.value());
  const auto q = chandra::math::sincos<Value>(angle_t{_llh.longitude}.value());
  const auto N = ellipsoid_t::a() / (std::sqrt(Value{1} - ellipsoid_t::e2() * (r.sin * r.sin)));
  xyz.x = (N + _llh.altitude) * r.cos * q.cos;
  xyz.y = (N + _llh.altitude) * r.cos * q.sin;
  xyz.z = ((Value{ 1 } - ellipsoid_t::e2()) * N + _llh.altitude) * r.sin;
  return xyz;
}

namespace internal
{
template<class Ellipsoid, class Length, class V, class AngleUnits>
Length calcN(const chandra::units::Quantity<V, AngleUnits>& _lat) {
    const auto s = sin(_lat);
    return Length{Ellipsoid::a() / std::sqrt(1 - Ellipsoid::e2()*(s*s))};
}
} /*namespace internal*/

template<class Value, class LengthUnits, Geoid GeoidDef = Geoid::WGS84, size_t MaxIters = 5>
auto ECEFToLLH(
        const ECEF<Value, LengthUnits>& _ecef, 
        const chandra::units::mks::Q_m<Value>& _h_thresh = 1e-4_m_
    ) -> LLH<Value>
{
    //
    // Note: This is using a Newton-Raphson algorithm to do the transformation.
    //  It may make sense to implement another algorithm for greater efficiency;
    //  however, I don't have a test version of any other algorithms running
    //  properly yet. So, there's no particular rush.
    //
    using ellipsoid_t = chandra::aero::Ellipsoid<Value, GeoidDef>;
    using rads_t = chandra::units::mks::Q_rad<Value>;
    using meter_t = chandra::units::mks::Q_m<Value>;
    LLH<Value, chandra::units::mks::rad, LengthUnits> llh;

    const auto x = meter_t(_ecef.x);
    const auto y = meter_t(_ecef.y);
    const auto z = meter_t(_ecef.z);
    llh.longitude = rads_t(std::atan2(y, x));
    const auto p = std::sqrt((x * x) + (y * y));
    const bool pole = (abs(x) < 1e-8_m_) || (abs(y) < 1e-8_m_);
    llh.latitude = pole ? rads_t(90_deg_ * ((z > 0_m_) ? 1 : -1)) : rads_t(atan2(p, z));
    meter_t altitude_last;

    for (size_t iter = 0; iter < MaxIters; ++iter) {
        const auto N = internal::calcN<ellipsoid_t, meter_t>(llh.latitude);
        llh.altitude = meter_t((p / std::cos(llh.latitude.value())) - N);

        if (!pole) {
            llh.latitude = rads_t(std::atan( (z / p) * (1 / (1 - ellipsoid_t::e2() * (N / (N + llh.altitude))))));
        }

        if (iter > 0) {
           const auto dh = abs(llh.altitude - altitude_last);
            if (dh <= _h_thresh) break;
        }

        altitude_last = llh.altitude;
    }

    return llh;
}


namespace utils
{
template<class P1, class P2, class L>
bool ECEFWithinError(const P1& _p1, const P2& _p2, const L& _l) {
    const auto dx = (_p1.x > _p2.x) ? _p1.x - _p2.x : _p2.x - _p1.x;
    const auto dy = (_p1.y > _p2.y) ? _p1.y - _p2.y : _p2.y - _p1.y;
    const auto dz = (_p1.z > _p2.z) ? _p1.z - _p2.z : _p2.z - _p1.z;

    return (dx <= _l) && (dy <= _l) && (dz <= _l);
}

template<class P1, class P2, class A, class L>
bool LLHWithinError(const P1& _p1, const P2& _p2, const A& _a, const L& _l) {
    const auto dLat = (_p1.latitude > _p2.latitude) ? _p1.latitude - _p2.latitude : _p2.latitude - _p1.latitude;
    const auto dLon = (_p1.longitude > _p2.longitude) ? _p1.longitude - _p2.longitude : _p2.longitude - _p1.longitude;
    const auto dAlt = (_p1.altitude > _p2.altitude) ? _p1.altitude - _p2.altitude : _p2.altitude - _p1.altitude;

    return (dLat <= _a) && (dLon <= _a) && (dAlt <= _l);
}

// TODO: DEFINE LLH WITHIN ERROR USING ONLY A LENGTH THRESHOLD AND CALCULATING THE ANGLE THRESHOLD SEPARATELY FOR LATITUDE AND LONGITUDE
} /*namespace utils*/
} /*namespace aero*/
} /*namespace chandra*/

#endif /*CHANDRA_COORDINATES_H*/
