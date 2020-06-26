#ifndef CHANDRA_ATMOSPHERE_H
#define CHANDRA_ATMOSPHERE_H

#include "quantity.h"
#include "units.h"

// TODO: EVENTUALLY INCLUDE CORRECTION TO THE STANDARD VALUES BASED ON CALBRATION PRESSURE/TEMPERATURE/ALTITUDE
//  THIS CAN BY ADDING A TEMPERATURE DELTA (FOR TEMPERATURE ONLY).  PRESSURE, DENSITY, ETC ARE SUPPOSED
//  TO REMAIN UNCHANGED.  FIGURE OUT IF THERE IS ANOTHER WAY TO HANDLE THIS.
//  SOME INTERESTIG RELATED INFORMATION ARE THE MILITARY SPECIFICATIONS: MIL-STD-210C AND MIL-HDBK-310
//  WHICH OUTLINE CLIMATE CONDITIONS FOR PERFORMACE REQUIREMENTS.
// MODELS TO ADD: CIRA-86, NRLMSISE-00, JB2009
namespace chandra
{
namespace aero
{

enum class AtmosphereModel {
  US,
  ISA,
  ICAO
  // Add Interface to EARTH-GRAM 2016?, etc.
};

namespace internal
{

template<
  typename Value,
  typename LengthUnits,
  typename MassUnits,
  typename TimeUnits,
  typename PressureUnits,
  typename TemperatureUnits
>
struct AtmosphereBase
{
  using volume_units = chandra::units::volumeFrom<LengthUnits>;
  using density_units = chandra::units::densityFrom<MassUnits, LengthUnits>;
  using gas_constant_units = chandra::units::internal::DivUnits<
                                chandra::units::mks::J,
                                chandra::units::internal::MultUnits<chandra::units::mks::mol, chandra::units::mks::K>
                              >;
  using molar_mass_units = chandra::units::internal::DivUnits<chandra::units::mks::kg, chandra::units::mks::mol>;
  using acceleration_units = chandra::units::mks::m_per_s2;
  using lapse_rate_units = chandra::units::internal::DivUnits<TemperatureUnits, LengthUnits>;

  using gas_constant_t = chandra::units::Quantity<Value, gas_constant_units>;
  using molar_mass_t = chandra::units::Quantity<Value, molar_mass_units>;

  using length_t = chandra::units::Quantity<Value, LengthUnits>;
  using density_t = chandra::units::Quantity<Value, density_units>;
  using pressure_t = chandra::units::Quantity<Value, PressureUnits>;
  using temperature_t = chandra::units::Quantity<Value, TemperatureUnits>;
  using acceleration_t = chandra::units::Quantity<Value, acceleration_units>;
  using lapse_rate_t = chandra::units::Quantity<Value, lapse_rate_units>;


  using length_dims = typename LengthUnits::dimensions_t;
  using density_dims = typename density_units::dimensions_t;
  using pressure_dims = typename PressureUnits::dimensions_t;
  using temperature_dims = typename TemperatureUnits::dimensions_t;

  struct Properties
  {
      length_t h;
      density_t rho;
      pressure_t P;
      temperature_t T;
      density_t rhob;
      pressure_t Pb;
      temperature_t Tb;
      lapse_rate_t L;
  };

  struct Parameters
  {
    gas_constant_t Rstar;
    molar_mass_t M;
    acceleration_t g0;
  };

  struct AtmosphereLayer
  {
    length_t hb;
    pressure_t Pb;
    temperature_t Tb;
    density_t rhob;
    lapse_rate_t Lb;
  };

  protected:
    template<size_t N>
    constexpr const AtmosphereLayer& altitudeLayer(const AtmosphereLayer (&layers)[N], const length_t& h) const {
      if(h < layers[1].hb) return layers[0];
      for(size_t i=1; i < N; ++i) {
        if(h > layers[i].hb) return layers[i];
      }
      return layers[N-1];
    }

    template<size_t N>
    constexpr const AtmosphereLayer& densityLayer(const AtmosphereLayer (&layers)[N], const density_t& rho) const {
      if(rho > layers[1].rhob) return layers[0];
      for(size_t i=1; i < N; ++i) {
        if(rho < layers[i].rhob) return layers[i];
      }
      return layers[N-1];
    }

    template<size_t N>
    constexpr const AtmosphereLayer& pressureLayer(const AtmosphereLayer (&layers)[N], const pressure_t& P) const {
      if(P > layers[1].Pb) return layers[0];
      for(size_t i=1; i < N; ++i) {
        if(P < layers[i].Pb) return layers[i];
      }
      return layers[N-1];
    }
};

template<
  typename Value,
  AtmosphereModel Model,
  typename LengthUnits,
  typename MassUnits,
  typename TimeUnits,
  typename PressureUnits,
  typename TemperatureUnits
>
class AtmosphereImpl
  : public AtmosphereBase<
                            Value,
                            LengthUnits,
                            MassUnits,
                            TimeUnits,
                            PressureUnits,
                            TemperatureUnits
                          >
{

};

//
// US Standard Atmosphere
//
template<
  typename Value,
  typename LengthUnits,
  typename MassUnits,
  typename TimeUnits,
  typename PressureUnits,
  typename TemperatureUnits
>
class AtmosphereImpl<Value, AtmosphereModel::US, LengthUnits, MassUnits, TimeUnits, PressureUnits, TemperatureUnits>
  : public AtmosphereBase<
                            Value,
                            LengthUnits,
                            MassUnits,
                            TimeUnits,
                            PressureUnits,
                            TemperatureUnits
                          >
{
  public:
    using base_t = AtmosphereBase<
                              Value,
                              LengthUnits,
                              MassUnits,
                              TimeUnits,
                              PressureUnits,
                              TemperatureUnits
                            >;

    using length_t = typename base_t::length_t;
    using density_t = typename base_t::density_t;
    using pressure_t = typename base_t::pressure_t;
    using temperature_t = typename base_t::temperature_t;
    using lapse_rate_t = typename base_t::lapse_rate_t;
    using gas_constant_t = typename base_t::gas_constant_t;
    using molar_mass_t = typename base_t::molar_mass_t;
    using acceleration_t = typename base_t::acceleration_t;

  protected:
    const typename base_t::AtmosphereLayer layers_[7] = {
      {length_t{0}, pressure_t{101325.00}, temperature_t{288.15}, density_t{1.225}, lapse_rate_t{-0.0065}},
      {length_t{11000}, pressure_t{22632.10}, temperature_t{216.65}, density_t{0.36391}, lapse_rate_t{0}},
      {length_t{20000}, pressure_t{5474.89}, temperature_t{216.65}, density_t{0.08803}, lapse_rate_t{0.001}},
      {length_t{32000}, pressure_t{868.02}, temperature_t{228.65}, density_t{0.01322}, lapse_rate_t{0.0028}},
      {length_t{47000}, pressure_t{110.91}, temperature_t{270.65}, density_t{0.00143}, lapse_rate_t{0}},
      {length_t{51000}, pressure_t{66.94}, temperature_t{270.65}, density_t{0.00086}, lapse_rate_t{-0.0028}},
      {length_t{71000}, pressure_t{3.96}, temperature_t{214.65}, density_t{0.000064}, lapse_rate_t{-0.002}}
    };

    const Value Rstar_{8.3144598};
    const Value M_{0.0289644};
    const Value g0_{9.80665};
};

} /* namespace internal*/


template<
  class Value=float,
  AtmosphereModel Model = AtmosphereModel::US,
  typename LengthUnits = chandra::units::mks::m,
  typename MassUnits = chandra::units::mks::kg,
  typename TimeUnits = chandra::units::mks::s,
  typename PressureUnits = chandra::units::mks::Pa,
  typename TemperatureUnits = chandra::units::mks::K
>
class Atmosphere
  : public internal::AtmosphereImpl<
                                      Value,
                                      Model,
                                      LengthUnits,
                                      MassUnits,
                                      TimeUnits,
                                      PressureUnits,
                                      TemperatureUnits
                                    >
{
  public:
    using base_t = internal::AtmosphereImpl<
                                              Value,
                                              Model,
                                              LengthUnits,
                                              MassUnits,
                                              TimeUnits,
                                              PressureUnits,
                                              TemperatureUnits
                                            >;

    using length_t = typename base_t::length_t;
    using density_t = typename base_t::density_t;
    using pressure_t = typename base_t::pressure_t;
    using temperature_t = typename base_t::temperature_t;

    using length_dims = typename length_t::units_t::dimensions_t;
    using density_dims = typename density_t::units_t::dimensions_t;
    using pressure_dims = typename pressure_t::units_t::dimensions_t;
    using temperature_dims = typename temperature_t::units_t::dimensions_t;

    using Properties = typename base_t::Properties;

    Atmosphere() : exp_1_((this->g0_*this->M_)/this->Rstar_), exp_2_(this->Rstar_/(this->g0_*this->M_)) {}

    template<typename V, typename Units>
    constexpr length_t altitude(const chandra::units::Quantity<V, Units>& _v) const {
      return altitudeImpl(_v, typename Units::dimensions_t());
    }

    template<typename V, typename Units>
    constexpr density_t density(const chandra::units::Quantity<V, Units>& _v) const {
      return densityImpl(_v, typename Units::dimensions_t());
    }

    template<typename V, typename Units>
    constexpr pressure_t pressure(const chandra::units::Quantity<V, Units>& _v) const {
      return pressureImpl(_v, typename Units::dimensions_t());
    }

    template<typename V, typename Units>
    constexpr temperature_t temperature(const chandra::units::Quantity<V, Units>& _v) const {
      return temperatureImpl(_v, typename Units::dimensions_t());
    }

    template<typename V, typename Units>
    constexpr typename base_t::Properties properties(const chandra::units::Quantity<V, Units>& _v) const {
      return propertiesImpl(_v, typename Units::dimensions_t());
    }

    constexpr length_t geometricToGeopotential(const length_t& _h) const {
      return _h; // TODO: IMPLEMENT THIS!!!
    }

    constexpr length_t geopotentialToGeometric(const length_t& _h) const {
      return _h; // TODO: IMPLEMENT THIS!!!
    }

    constexpr typename base_t::Parameters parameters() const {
      return {
        typename base_t::gas_constant_t{this->Rstar_},
        typename base_t::molar_mass_t{this->M_},
        typename base_t::acceleration_t{this->g0_}
      };
    };

  protected:
    //
    // Altitude Calculation
    //
    constexpr length_t pToH(const pressure_t _P, const typename base_t::AtmosphereLayer& layer) const {
      const auto P = _P.value();
      const auto Pb = layer.Pb.value();
      const auto Tb = layer.Tb.value();
      const auto Lb = layer.Lb.value();
      const auto hb = layer.hb.value();
      const auto one = Value{1};

      if(Lb != 0) {
        return length_t{static_cast<Value>(hb + ((Tb/Lb)*((one/std::pow((P/Pb), (Lb*exp_2_)))-one)))};
      }
      return length_t{static_cast<Value>(hb - (std::log(P/Pb)*(exp_2_*Tb)))};
    }

    constexpr length_t rhoToH(const density_t _rho, const typename base_t::AtmosphereLayer& layer) const {
      const auto rho = _rho.value();
      const auto rhob = layer.rhob.value();
      const auto Tb = layer.Tb.value();
      const auto Lb = layer.Lb.value();
      const auto hb = layer.hb.value();
      const auto one = Value{1};

      if(Lb != 0) {
        return length_t{static_cast<Value>(hb + ((Tb/Lb)*((one/std::pow((rho/rhob), (one/(one+(exp_1_/Lb)))))-one)))};
      }
      return length_t{static_cast<Value>(hb - (std::log(rho/rhob)*(exp_2_*Tb)))};
    }

    template<typename V, typename Units>
    constexpr length_t altitudeImpl(const chandra::units::Quantity<V, Units>& _v, const pressure_dims&) const {
      return pToH(_v, this->pressureLayer(this->layers_, _v));
    }

    template<typename V, typename Units>
    constexpr length_t altitudeImpl(const chandra::units::Quantity<V, Units>& _v, const density_dims&) const {
      return rhoToH(_v, this->densityLayer(this->layers_, _v));
    }

    //
    // Density Calculation
    //
    constexpr density_t hToRho(const length_t _h, const typename base_t::AtmosphereLayer& layer) const {
      const auto h = _h.value();
      const auto rhob = layer.rhob.value();
      const auto Tb = layer.Tb.value();
      const auto Lb = layer.Lb.value();
      const auto hb = layer.hb.value();
      if(Lb != 0) {
        return density_t{static_cast<Value>(rhob * std::pow((Tb / (Tb + (Lb*(h - hb)))), (Value{1} + (exp_1_/Lb))))};
      }
      return density_t{static_cast<Value>(rhob * std::exp((-exp_1_(h - hb))/Tb))};
    }

    template<typename V, typename Units>
    constexpr density_t densityImpl(const chandra::units::Quantity<V, Units>& _v, const pressure_dims&) const {
      const typename base_t::AtmosphereLayer& layer = this->densityLayer(this->layers_, _v);
      const length_t h = rhoToH(_v, layer);
      return hToRho(h, layer);
    }

    template<typename V, typename Units>
    constexpr density_t densityImpl(const chandra::units::Quantity<V, Units>& _v, const length_dims&) const {
      return hToRho(_v, this->densityLayer(this->layers_, _v));
    }

    //
    // Pressure Calculation
    //
    constexpr pressure_t hToP(const length_t _h, const typename base_t::AtmosphereLayer& layer) const {
      const auto h = _h.value();
      const auto Pb = layer.Pb.value();
      const auto Tb = layer.Tb.value();
      const auto Lb = layer.Lb.value();
      const auto hb = layer.hb.value();
      if(Lb != 0) {
        return pressure_t{static_cast<Value>(Pb * std::pow((Tb / (Tb + (Lb*(h - hb)))), (exp_1_/Lb)))};
      }
      return pressure_t{static_cast<Value>(Pb * std::exp((-exp_1_*(h - hb))/Tb))};
    }

    template<typename V, typename Units>
    constexpr pressure_t pressureImpl(const chandra::units::Quantity<V, Units>& _v, const density_dims&) const {
      const typename base_t::AtmosphereLayer& layer = this->densityLayer(this->layers_, _v);
      const length_t h = pToH(_v, layer);
      return hToP(h, layer);
    }

    template<typename V, typename Units>
    constexpr pressure_t pressureImpl(const chandra::units::Quantity<V, Units>& _v, const length_dims&) const {
      return hToP(_v, this->altitudeLayer(this->layers_, _v));
    }

    //
    // Temperature Calculation
    //
    constexpr temperature_t hToT(const length_t _h, const typename base_t::AtmosphereLayer& layer) const {
      const auto h = _h.value();
      const auto Tb = layer.Tb.value();
      const auto Lb = layer.Lb.value();
      const auto hb = layer.hb.value();
      return temperature_t{(Lb * (h - hb)) + Tb};
    }

    template<typename V, typename Units>
    constexpr temperature_t temperatureImpl(const chandra::units::Quantity<V, Units>& _v, const length_dims&) const {
      return hToT(_v, this->altitudeLayer(this->layers_, _v));
    }

    //
    // Full Properties Calculation
    //
    template<typename V, typename Units>
    constexpr Properties propertiesImpl(const chandra::units::Quantity<V, Units>& _v, const length_dims&) const {
      return Properties{};
    }

    template<typename V, typename Units>
    constexpr Properties propertiesImpl(const chandra::units::Quantity<V, Units>& _v, const density_dims&) const {
      return Properties{};
    }

    template<typename V, typename Units>
    constexpr Properties propertiesImpl(const chandra::units::Quantity<V, Units>& _v, const pressure_dims&) const {
      return Properties{};
    }

    const Value exp_1_;
    const Value exp_2_;
};

} /* namespace aero */
} /* namespace chandra */

#endif /*CHANDRA_ATMOSPHERE_H*/
