#ifndef CHANDRA_GRAVITY_H
#define CHANDRA_GRAVITY_H

#include <stddef.h>

#include "geoid.h"
#include "math_ops.h"
#include "matrix.h"
#include "quantity.h"
#include "units.h"

// TODO: ADD GRS80 TO THE GRAVITATIONAL MODELS
namespace chandra
{
namespace aero
{
struct GravityConfig
{
  protected:
    constexpr static uint32_t model_offset{10};
    constexpr static uint32_t free_air_correction_offset{0};
    constexpr static uint32_t slab_correction_offset{2};
    constexpr static uint32_t centripetal_correction_offset{3};

  public:
    constexpr static uint32_t ModelMask{0x0F<<model_offset};
    constexpr static uint32_t Standard{0x00};
    constexpr static uint32_t IGF{0x01<<model_offset};
    constexpr static uint32_t WGS84{0x02<<model_offset};

    constexpr static uint32_t FreeAirMask{0x03<<free_air_correction_offset};
    constexpr static uint32_t FreeAirCorrect{0x01<<free_air_correction_offset};
    constexpr static uint32_t ApproxFreeAirCorrect{0x02<<free_air_correction_offset};
    constexpr static uint32_t SlabMask{0x01<<slab_correction_offset};
    constexpr static uint32_t SlabCorrect{0x01<<slab_correction_offset};
    constexpr static uint32_t CentripetalMask{0x01<<centripetal_correction_offset};
    constexpr static uint32_t CentripetalCorrect{0x01<<centripetal_correction_offset};
};

namespace internal
{
template<class Value> // NOTE: THIS IS USING THE WSG84 VALUES...
struct GravitationalConstants
{
  using value_t = Value;
  using angle_t = chandra::units::mks::Q_rad<value_t>;

  constexpr static value_t G{6.67408e-11}; // Gravitational Constant
  constexpr static value_t Me{5.9722e24}; // Mass of the Earth
  constexpr static value_t Req{6378137}; // Equatorial radius of the Earth
  constexpr static value_t Rpol{6356752.3142}; // Polar radius of the Earth
  constexpr static value_t Ravg{6371008.8}; // Average radius of the Earth
  constexpr static value_t GMe{3.986004418e14}; // Product of Geocentric Gravitational Constant

  constexpr static value_t g_eq{9.7803253359}; // Gravity at the equator
  constexpr static value_t g_pol{9.8321849378}; // Gravity at the poles

  // NOTE: THIS REALLY DOES NOT BELONG IN THE "CONSTANTS" IT SHOULD BE MOVED SOMEWHERE ELSE
  //  BUT IT DEPENDS HEAVILY ON THE CONSTANTS, SO IT SHOULDN'T TAKE THEM AS PARAMETERS...
  constexpr static value_t R(angle_t _lat_rad) {
    const auto r = chandra::math::sincos(_lat_rad.value());
    const auto A = Req * r.cos;
    const auto B = Rpol * r.sin;
    const auto C = Req * A;
    const auto D = Rpol * B;
    return sqrt(((C*C)+(D*D))/((A*A)+(B*B)));
  }
};

template<class Value, uint32_t Flags = GravityConfig::Standard>
class GravityModelImpl
{
  public:
    using value_t = Value;
    using angle_t = chandra::units::mks::Q_rad<value_t>;
    using length_t = chandra::units::mks::Q_m<value_t>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<value_t>;

    explicit GravityModelImpl(angle_t, angle_t, length_t) {}

    constexpr static acceleration_t base_gravity() {
      return acceleration_t{9.80665};
    }

    constexpr bool update(angle_t, angle_t, length_t) const {
      return true;
    }
};

template<class Value>
struct GravityModelImpl<Value, GravityConfig::IGF>
{
  public:
    using value_t = Value;
    using angle_t = chandra::units::mks::Q_rad<value_t>;
    using length_t = chandra::units::mks::Q_m<value_t>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<value_t>;

    explicit GravityModelImpl(angle_t _lat, angle_t _long, length_t _h_asl) {
      update(_lat, _long, _h_asl);
    }

    constexpr acceleration_t base_gravity() const {
      return g_;
    }

    bool update(angle_t _lat, angle_t, length_t) {
      constexpr static value_t gamma{9.780327};
      constexpr static value_t beta{5.3024e-3};
      constexpr static value_t beta1{-5.8e-6};
      const value_t s = sin(_lat.value());
      const value_t s2 = sin(2*_lat.value());

      g_ = acceleration_t{gamma * (1 + (beta*(s*s)) + (beta1*(s2*s2)))};
      return true;
    }

  private:
    acceleration_t g_;
};

template<class Value>
struct GravityModelImpl<Value, GravityConfig::WGS84>
{
  public:
    using value_t = Value;
    using angle_t = chandra::units::mks::Q_rad<value_t>;
    using length_t = chandra::units::mks::Q_m<value_t>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<value_t>;
    using C = GravitationalConstants<Value>;

    explicit GravityModelImpl(angle_t _lat, angle_t _long, length_t _h_asl) {
      update(_lat, _long, _h_asl);
    }

    constexpr acceleration_t base_gravity() const {
      return g_;
    }

    bool update(angle_t _lat, angle_t, length_t _h_asl) {
      constexpr static value_t e2{value_t{1} - ((C::Rpol/C::Req)*(C::Rpol/C::Req))};
      constexpr static value_t k{((C::Rpol*C::g_pol)-(C::Req*C::g_eq))/(C::Req*C::g_eq)};
      const auto s{sin(_lat.value())};
      const auto s2{s*s};
      g_ = acceleration_t{C::g_eq * ((1 + (k*s2)) / sqrt(1 - (e2*s2)))};
      return true;
    }

  private:
    acceleration_t g_{0};
};

template<class Value, uint32_t Flags>
class FreeAirCorrectionImpl // Disabled Free-Air Correction
{
  public:
    using angle_t = chandra::units::mks::Q_rad<Value>;
    using length_t = chandra::units::mks::Q_m<Value>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<Value>;

    FreeAirCorrectionImpl(angle_t) {}

    acceleration_t magnitude(length_t) const {
      return acceleration_t{0};
    }

    bool update(angle_t) {
      return true;
    }
};

template<class Value>
class FreeAirCorrectionImpl<Value, GravityConfig::ApproxFreeAirCorrect>
{
  public:
    using angle_t = chandra::units::mks::Q_rad<Value>;
    using length_t = chandra::units::mks::Q_m<Value>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<Value>;
    using C = GravitationalConstants<Value>;

    FreeAirCorrectionImpl(angle_t _lat) { update(_lat); }

    auto magnitude(length_t _h_asl) const {
      const auto dg{-3.086e-6*_h_asl.value()};
      return acceleration_t{dg};
    }

    bool update(angle_t) {
      return true;
    }

  private:
    angle_t lat_;
};

template<class Value>
class FreeAirCorrectionImpl<Value, GravityConfig::FreeAirCorrect>
{
  public:
    using angle_t = chandra::units::mks::Q_rad<Value>;
    using length_t = chandra::units::mks::Q_m<Value>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<Value>;
    using value_t = Value;
    using C = GravitationalConstants<value_t>;

    FreeAirCorrectionImpl(angle_t _lat) { update(_lat); }

    auto magnitude(length_t _h_asl) const {
      const auto Rtot{R_ + _h_asl.value()};
      const auto dg{(C::GMe / (Rtot * Rtot)) - g_ref_};
      return acceleration_t{dg};
    }

    bool update(angle_t _lat) {
      R_ = C::R(_lat);
      R_2_ = R_ * R_;
      g_ref_ = C::GMe / R_2_;
      return true;
    }

  private:
    value_t R_;
    value_t R_2_;
    value_t g_ref_;
};

template<class Value, uint32_t SlabEnable>
class SlabImpl
{
  public:
    using value_t = Value;
    using length_t = chandra::units::mks::Q_m<value_t>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<value_t>;

    SlabImpl(length_t) {}

    auto magnitude() {
      return acceleration_t{0};
    }

    bool update(length_t _thickness) {
      return true;
    }

  private:

};

template<class Value, uint32_t CentripetalEnable>
class CentripetalImpl
{
  public:
    using value_t = Value;
    using angle_t = chandra::units::mks::Q_rad<value_t>;
    using length_t = chandra::units::mks::Q_m<value_t>;
    using acceleration_t = chandra::units::mks::Q_m_per_s2<value_t>;

    CentripetalImpl(angle_t, length_t) {}

    auto magnitude() {
      return acceleration_t{0};
    }

    bool update(angle_t, length_t) {
      return true;
    }

  private:

};

// TODO: LOAD THE GEOID CONSTANTS ON CONSTRUCTION AND PASS THEM TO THE IMPLEMENTATIONS ON
//  CORRECT() CALLS.
//
// TODO: FIGURE OUT HOW TO HANDLE VECTOR DIRECTION CORRECTION???
//  THIS NEEDS TO TAKE VECTORS INTO ACCOUNT FOR BOTH OUTPUT OF THE MAIN VECTOR AND THE CENTRIPETAL
//  CORRECTION....
//
// TODO: FIGURE OUT IF IT SHOULD BE POSSIBLE TO CALCULATE WITH A DIFFERENT SLAB DENSITY.  IF SO
//  THEN IT SHOULD ALSO BE POSSIBLE TO CHANGE THE DIMENSIONS AS WITH THE OTHER DIMENSIONS....
template<
  class Value,
  uint32_t Flags = GravityConfig::ApproxFreeAirCorrect,
  class AngleUnits = chandra::units::mks::rad,
  class LengthUnits = chandra::units::mks::m,
  class AccelerationUnits = chandra::units::mks::m_per_s2
>
class ScalarGravityImpl
{
  public:
    using value_t = Value;
    using angle_t = chandra::units::Quantity<value_t, AngleUnits>;
    using length_t = chandra::units::Quantity<value_t, LengthUnits>;
    using acceleration_t = chandra::units::Quantity<value_t, AccelerationUnits>;

  protected:
    using model_impl_t = internal::GravityModelImpl<value_t, (Flags & GravityConfig::ModelMask)>;
    using free_air_impl_t = internal::FreeAirCorrectionImpl<value_t, (Flags & GravityConfig::FreeAirMask)>;
    using slab_impl_t = internal::SlabImpl<value_t, (Flags & GravityConfig::SlabMask)>;
    using centripetal_impl_t = internal::CentripetalImpl<value_t, (Flags & GravityConfig::CentripetalMask)>;

  public:
    explicit ScalarGravityImpl(angle_t _lat, angle_t _long, length_t _h_asl)
      : model_impl_{_lat, _long, _h_asl},
        free_air_impl_{_lat},
        slab_impl_{_h_asl},
        centripetal_impl_{_lat, _h_asl},
        lat_{_lat},
        long_{_long},
        h_asl_{_h_asl}
    {
      update_surface_gravity();
    }

    explicit ScalarGravityImpl(angle_t _lat, angle_t _long)
      : ScalarGravityImpl(_lat, _long, length_t{0}) {}

    explicit ScalarGravityImpl(angle_t _lat, length_t _h_asl)
      : ScalarGravityImpl(_lat, angle_t{0}, _h_asl) {}

    explicit ScalarGravityImpl(angle_t _lat)
      : ScalarGravityImpl(_lat, length_t{0}) {}

    explicit ScalarGravityImpl()
      : ScalarGravityImpl(angle_t{0}, angle_t{0}, length_t{0}) {}

    bool position(angle_t _lat, angle_t _long, length_t _h_asl) {
      h_asl_ = _h_asl;
      lat_ = _lat;
      long_ = _long;
      model_impl_.update(lat_, long_, h_asl_);
      free_air_impl_.update(lat_);
      centripetal_impl_.update(lat_, h_asl_);
      update_surface_gravity();
      return true;
    }

    bool position(angle_t _lat, angle_t _long) {
      return position(_lat, _long, h_asl_);
    }

    angle_t latitude() const { return lat_; }
    angle_t latitude(angle_t _lat) {
      lat_ = _lat;
      position(lat_, long_);
      return lat_;
    }

    angle_t longitude() const { return long_; }
    angle_t longitude(angle_t _long) {
      long_ = _long;
      position(lat_, long_);
      return long_;
    }

    length_t height_asl() const { return h_asl_; }
    length_t height_asl(length_t _h_asl) {
      h_asl_ = _h_asl;
      model_impl_.update(lat_, h_asl_);
      slab_impl_.update(lat_, h_asl_);
      update_surface_gravity();
      return h_asl_;
    }

    auto g0() const {
      return g_surface_;
    }

    auto gh_agl(length_t _agl) const {
      return gh_asl(_agl + h_asl_);
    }

    auto gh_asl(length_t _asl) const {
      return g0() + free_air_impl_.magnitude(_asl);
    }

  protected:
    auto update_surface_gravity() {
      const auto g0 = model_impl_.base_gravity();
      const auto gs = slab_impl_.magnitude();
      const auto gc = centripetal_impl_.magnitude();
      g_surface_ = g0 + gs + gc;
      // TODO: THE PROJECTION OF THE CENTRIPETAL CORRECTION NEEDS TO BE CALCULATED AND APPLIED.
    }

    model_impl_t model_impl_;
    free_air_impl_t free_air_impl_;
    slab_impl_t slab_impl_;
    centripetal_impl_t centripetal_impl_;
    angle_t lat_;
    angle_t long_;
    length_t h_asl_;
    acceleration_t g_surface_;
};

template<
  class Value,
  chandra::aero::GeoidCoordinates VectorCoordinates = chandra::aero::GeoidCoordinates::None,
  uint32_t Flags = GravityConfig::ApproxFreeAirCorrect,
  class AngleUnits = chandra::units::mks::rad,
  class LengthUnits = chandra::units::mks::m,
  class AccelerationUnits = chandra::units::mks::m_per_s2
>
class VectorGravityImpl : public ScalarGravityImpl<Value, Flags, AngleUnits, LengthUnits, AccelerationUnits>
{
  public:
    using base_t = ScalarGravityImpl<Value, Flags, AngleUnits, LengthUnits, AccelerationUnits>;
    using value_t = typename base_t::value_t;
    using angle_t = typename base_t::angle_t;
    using length_t = typename base_t::length_t;
    using acceleration_t = typename base_t::acceleration_t;
    using vector_t = chandra::math::Matrix<acceleration_t, 3, 1>;

    using base_t::base_t; // Inherit the constructors

    auto vec_g0() const {
      return vec_g_;
    }

    auto vec_gh_asl(length_t _h_asl) const {
      return vec_g_;
    }

    auto vec_gh_agl(length_t _h_agl) const {
      return vec_g_;
    }

  protected:
    // auto update_surface_gravity() {
    //   const auto g0 = model_impl_.base_gravity();
    //   const auto gs = slab_impl_.magnitude();
    //   const auto gc = centripetal_impl_.magnitude();
    //   g_surface_ = g0 + gb + gs;
    //   // TODO: THE PROJECTION OF THE CENTRIPETAL CORRECTION NEEDS TO BE CALCULATED AND APPLIED.
    // }

    vector_t vec_g_;
};

template<
  class Value,
  chandra::aero::GeoidCoordinates VectorCoordinates,
  uint32_t Flags,
  class AngleUnits,
  class LengthUnits,
  class AccelerationUnits
>
struct SelectGravityImpl
{
  using type = VectorGravityImpl<Value, VectorCoordinates, Flags, AngleUnits, LengthUnits, AccelerationUnits>;
};

template<
  class Value,
  uint32_t Flags,
  class AngleUnits,
  class LengthUnits,
  class AccelerationUnits
>
struct SelectGravityImpl<Value, chandra::aero::GeoidCoordinates::None, Flags, AngleUnits, LengthUnits, AccelerationUnits>
{
  using type = ScalarGravityImpl<Value, Flags, AngleUnits, LengthUnits, AccelerationUnits>;
};

} /*namespace internal*/

template<
  class Value,
  chandra::aero::GeoidCoordinates VectorCoordinates = chandra::aero::GeoidCoordinates::None,
  uint32_t Flags = GravityConfig::ApproxFreeAirCorrect,
  class AngleUnits = chandra::units::mks::rad,
  class LengthUnits = chandra::units::mks::m,
  class AccelerationUnits = chandra::units::mks::m_per_s2
>
class Gravity :public internal::SelectGravityImpl<
    Value, VectorCoordinates, Flags, AngleUnits, LengthUnits, AccelerationUnits
  >::type
{
public:
  using base_t = typename internal::SelectGravityImpl<
      Value, VectorCoordinates, Flags, AngleUnits, LengthUnits, AccelerationUnits
    >::type;
  using base_t::base_t;
};

template<
  class Value,
  chandra::aero::GeoidCoordinates VectorCoordinates = chandra::aero::GeoidCoordinates::None,
  uint32_t AdditionalFlags = 0,
  class AngleUnits = chandra::units::mks::rad,
  class LengthUnits = chandra::units::mks::m,
  class AccelerationUnits = chandra::units::mks::m_per_s2
>
using StandardGravity = Gravity<
                          Value,
                          VectorCoordinates,
                          AdditionalFlags | GravityConfig::FreeAirCorrect,
                          AngleUnits,
                          LengthUnits,AccelerationUnits
                        >;

template<
  class Value,
  chandra::aero::GeoidCoordinates VectorCoordinates = chandra::aero::GeoidCoordinates::None,
  uint32_t AdditionalFlags = 0,
  class AngleUnits = chandra::units::mks::rad,
  class LengthUnits = chandra::units::mks::m,
  class AccelerationUnits = chandra::units::mks::m_per_s2
>
using IGFGravity = Gravity<
                      Value,
                      VectorCoordinates,
                      AdditionalFlags | GravityConfig::IGF | GravityConfig::SlabCorrect | GravityConfig::CentripetalCorrect | GravityConfig::FreeAirCorrect,
                      AngleUnits,
                      LengthUnits,
                      AccelerationUnits
                    >;

template<
  class Value,
  chandra::aero::GeoidCoordinates VectorCoordinates = chandra::aero::GeoidCoordinates::None,
  uint32_t AdditionalFlags = 0,
  class AngleUnits = chandra::units::mks::rad,
  class LengthUnits = chandra::units::mks::m,
  class AccelerationUnits = chandra::units::mks::m_per_s2
>
using WGS84Gravity = Gravity<
                      Value,
                      VectorCoordinates,
                      AdditionalFlags | GravityConfig::WGS84 | GravityConfig::SlabCorrect | GravityConfig::CentripetalCorrect | GravityConfig::FreeAirCorrect,
                      AngleUnits,
                      LengthUnits,
                      AccelerationUnits
                    >;
} /*namespace aero*/
} /*namespace chandra*/

#endif /*namespace chandra*/
