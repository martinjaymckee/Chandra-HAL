#ifndef CHANDRA_GEOID_H
#define CHANDRA_GEOID_H

#include "units.h"

namespace chandra
{
namespace aero
{
enum class GeoidCoordinates
{
  None,
  NEU,
  ECEF
};

enum class Geoid
{
  WGS84,
  GRS80
};

namespace internal
{
template<class Derived, class Value>
class EllipsoidBase
{
public:
    using value_t = Value;
    using angular_rate_t = chandra::units::mks::Q_rad_per_s<value_t>;
    constexpr static auto a2() { return Derived::a() * Derived::a(); } // Semi-major axis squared
    constexpr static auto b2() { return Derived::b() * Derived::b(); } // Semi-minor axis squared

    constexpr static value_t e2() { return ((a2() - b2()) / a2()); } //
    constexpr static value_t e2_prime() { return ((a2() - b2()) / b2()); } //
    constexpr static value_t f() { return ((Derived::a() - Derived::b()) / Derived::a()); }  // Flattening

    constexpr static auto omega_e() { return angular_rate_t{ 7.2921151467e-5 }; }
};
} /*namespace internal*/

template<class Value, Geoid GeoidDef = Geoid::WGS84>
class Ellipsoid : public internal::EllipsoidBase<Ellipsoid<Value, GeoidDef>, Value>
{
  public:
    using value_t = Value;
    using length_t = chandra::units::mks::Q_m<value_t>;

    constexpr static length_t a() { return length_t{ 6378137 }; } // Semi-major Axis
    constexpr static length_t b() { return length_t{ 6356752.314245 }; } // Semi-minor Axis
};

template<class Value>
class Ellipsoid<Value, Geoid::GRS80>
{
public:
    using value_t = Value;
    using length_t = chandra::units::mks::Q_m<value_t>;

    constexpr static length_t a() { return length_t{ 6378137 }; } // Semi-major Axis
    constexpr static length_t b() { return length_t{ 6356752.314140347 }; } // Semi-minor Axis
};

} /*namespace aero*/
} /*namespace chandra*/

#endif /*CHANDRA_GEOID_H*/
