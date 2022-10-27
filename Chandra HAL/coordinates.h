#ifndef CHANDRA_COORDINATES_H
#define CHANDRA_COORDINATES_H

#include <cmath>

#include "geoid.h"
#include "math_ops.h"
#include "quantity_math.h"
#include "units.h"
using namespace chandra::units::mks::literals;


namespace chandra
{
namespace aero
{
namespace frames
{
using None = void;
struct Body {};
struct Geodetic {};
struct ECEF {};
struct ENU {};
struct NED {};
};

template<class Value, class AngleUnits = chandra::units::mks::rad, class LengthUnits = chandra::units::mks::m>
struct LLH
{
    using angle_t = chandra::units::Quantity<Value, AngleUnits>;
    using length_t = chandra::units::Quantity<Value, LengthUnits>;

    angle_t latitude;
    angle_t longitude;
    length_t altitude;
};

template<class Stream, class Value, class AngleUnits, class LengthUnits>
Stream& operator << (Stream& _stream, const LLH<Value, AngleUnits, LengthUnits>& _llh) {
  _stream << "LLH( " << _llh.latitude << ", " << _llh.longitude << ", ";
  _stream << _llh.altitude << " )";
  return _stream;
}

template<class Value, class LengthUnits = chandra::units::mks::m>
using ECEF = chandra::math::Vector3D<chandra::units::Quantity<Value, LengthUnits>, true, frames::ECEF>;

template<class Value, class LengthUnits = chandra::units::mks::m>
using ENU = chandra::math::Vector3D<chandra::units::Quantity<Value, LengthUnits>, true, frames::ENU>;

template<class Value, class LengthUnits = chandra::units::mks::m>
using NED = chandra::math::Vector3D<chandra::units::Quantity<Value, LengthUnits>, true, frames::NED>;


template<class Value, class AngleUnits, class LengthUnits, Datum DatumDef = Datum::WGS84>
auto LLHToECEF( const LLH<Value, AngleUnits, LengthUnits>& _llh ) -> ECEF<Value>
{
  using ellipsoid_t = chandra::aero::Ellipsoid<Value, DatumDef>;
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

template<class Value, class LengthUnits, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
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
    using ellipsoid_t = chandra::aero::Ellipsoid<Value, DatumDef>;
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


template<class V1, class V2, class LU1, class LU2, class AU, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto ECEFToENU( const ECEF<V1, LU1>& _p, const LLH<V2, LU2, AU>& _llh0 ) {
  const auto lat = chandra::math::sincos(_llh0.latitude);
  const auto lon = chandra::math::sincos(_llh0.longitude);
  const auto ecef_ref = LLHToECEF(_llh0);
  
  const auto dx = _p.x - ecef_ref.x;
  const auto dy = _p.y - ecef_ref.y;
  const auto dz = _p.z - ecef_ref.z;

  using length_t = typename ENU<V1, LU1>::value_t;
  ENU<V1, LU1> enu;
  enu.x = length_t((-lon.sin * dx) + (lon.cos * dy));
  enu.y = length_t((-lat.sin * lon.cos * dx) + (-lat.sin * lon.sin * dy) + (lat.cos * dz));
  enu.z = length_t((lat.cos * lon.cos * dx) + (lat.cos * lon.sin * dy) + (lat.sin * dz));
  return enu;
}

template<class V1, class V2, class LU1, class LU2, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto ECEFToENU( const ECEF<V1, LU1>& _p, const ECEF<V2, LU2>& _p0 ) {
  const auto llh_ref = ECEFToLLH(_p0);
  return ECEFToENU(_p, llh_ref);
}

template<class V1, class V2, class LU1, class LU2, class AU1, class AU2, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto LLHToENU( const LLH<V1, LU1, AU1>& _llh, const LLH<V2, LU2, AU2>& _llh0 ) {
  const auto ecef = LLHToECEF(_llh);
  return ECEFToENU(ecef, _llh0);
}

template<class V1, class V2, class LU1, class LU2, class AU, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto LLHToENU( const LLH<V1, LU1, AU>& _llh, const ECEF<V2, LU2>& _p0 ) {
  const auto llh_ref = ECEFToLLH(_p0);
  const auto ecef = LLHToECEF(_llh);
  return ECEFToENU(ecef, llh_ref);
}

template<class V1, class V2, class LU1, class LU2, class AU, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto ENUToECEF( const ENU<V1, LU1>& _p, const LLH<V2, LU2, AU>& _llh0 ) {
    const auto lat = chandra::math::sincos(_llh0.latitude);
    const auto lon = chandra::math::sincos(_llh0.longitude);
    const auto ecef_ref = LLHToECEF(_llh0);

    using length_t = typename ECEF<V1, LU1>::value_t;
    ECEF<V1, LU1> ecef;
    ecef.x = length_t((-lon.sin * _p.x) + (-lat.sin * lon.cos * _p.y) + (lat.cos * lon.cos * _p.z) + ecef_ref.x);
    ecef.y = length_t((lon.cos * _p.x) + (-lat.sin * lon.sin * _p.y) + (lat.cos * lon.sin * _p.z) + ecef_ref.y);
    ecef.z = length_t((lat.cos * _p.y) + (lat.sin * _p.z) + ecef_ref.z);
    return ecef;
}

template<class V1, class V2, class LU1, class LU2, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto ENUToECEF( const ENU<V1, LU1>& _p, const ECEF<V2, LU2>& _p0 ) {
  return ENUToECEF(_p, ECEFToLLH(_p0));
}

template<class V1, class V2, class LU1, class LU2, class AU, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto ENUToLLH(const ENU<V1, LU1>& _p, const LLH<V2, LU2, AU>& _llh0 ) {
  const auto ecef = ENUToECEF(_p, _llh0);
  return ECEFToLLH(ecef);
}

template<class V1, class V2, class LU1, class LU2, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto ENUToLLH( const ENU<V1, LU1>& _p, const ECEF<V2, LU2>& _p0) {
  const auto ecef = ENUToECEF(_p, _p0);
  return ECEFToLLH(ecef);
}

template<class V1, class V2, class LU1, class LU2, class AU, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto RotateECEFToENU(const ECEF<V1, LU1>& _p, const LLH<V2, LU2, AU>& _llh0) {
    const auto lat = chandra::math::sincos(_llh0.latitude);
    const auto lon = chandra::math::sincos(_llh0.longitude);
    const auto ecef_ref = LLHToECEF(_llh0);

    const auto x = _p.x;
    const auto y = _p.y;
    const auto z = _p.z;

    using value_t = typename ENU<V1, LU1>::value_t;
    ENU<V1, LU1> enu;
    enu.x = value_t((-lon.sin * x) + (lon.cos * y));
    enu.y = value_t((-lat.sin * lon.cos * x) + (-lat.sin * lon.sin * y) + (lat.cos * z));
    enu.z = value_t((lat.cos * lon.cos * x) + (lat.cos * lon.sin * y) + (lat.sin * z));

    return enu;
}

template<class V1, class V2, class LU1, class LU2, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto RotateECEFToENU(const ECEF<V1, LU1>& _p, const ECEF<V2, LU2>& _p0) {
    const auto llh_ref = ECEFToLLH(_p0);
    return RotateECEFToENU(_p, llh_ref);
}

template<class V1, class V2, class LU1, class LU2, class AU, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto RotateENUToECEF(const ENU<V1, LU1>& _p, const LLH<V2, LU2, AU>& _llh0) {
    const auto lat = chandra::math::sincos(_llh0.latitude);
    const auto lon = chandra::math::sincos(_llh0.longitude);

    const auto x = _p.x;
    const auto y = _p.y;
    const auto z = _p.z;

    using value_t = typename ECEF<V1, LU1>::value_t;
    ECEF<V1, LU1> ecef;
    ecef.x = value_t((-lon.sin * x) + (-lat.sin * lon.cos * y) + (lat.cos * lon.cos * z));
    ecef.y = value_t((lon.cos * x) + (-lat.sin * lon.sin * y) + (lat.cos * lon.sin * z));
    ecef.z = value_t((lat.cos * y) + (lat.sin * z));
    return ecef;
}

template<class V1, class V2, class LU1, class LU2, Datum DatumDef = Datum::WGS84, size_t MaxIters = 7>
auto RotateENUToECEF(const ENU<V1, LU1>& _p, const ECEF<V2, LU2>& _p0) {
    return RotateENUToECEF(_p, ECEFToLLH(_p0));
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

template<class P1, class P2, class L>
bool ENUWithinError(const P1& _p1, const P2& _p2, const L& _l) {
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
