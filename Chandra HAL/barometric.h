#ifndef CHANDRA_BAROMETRIC_H
#define CHANDRA_BAROMETRIC_H

#include "units.h"

namespace chandra
{
namespace drivers
{
  namespace internal
  {
  template<class Value, class BaseUnits>
  struct BaseBarometricProxyImpl
  {
      using scalar_t = Value;

      template<class... Args>
      BaseBarometricProxyImpl(Args...) {}

      auto set_odr(const units::Quantity<scalar_t, units::mks::Hz>&) {
        return units::Quantity<scalar_t, units::mks::Hz>(0);
      }

      auto get_odr() {
        return units::Quantity<scalar_t, units::mks::Hz>(0);
      }

      auto set_osr(const uint16_t&) {
        return 0;
      }

      auto get_osr() {
        return 0;
      }

      auto set_lpf(const units::Quantity<scalar_t, units::mks::Hz>&) {
        return units::Quantity<scalar_t, units::mks::Hz>(0);
      }

      auto get_lpf() {
        return units::Quantity<scalar_t, units::mks::Hz>(0);
      }
  };
  } /*namespace internal*/

  template<typename Derived, typename Value, typename PressureUnits, typename TempUnits, typename PressureImpl, typename TempImpl>
  class Barometric
  {
      public:
          using scalar_t = Value;
          using value_t = Value;

      protected:
          template<typename BaseUnits, typename Impl>
          class Proxy : public Impl
          {
              public:
                  template<class... Args>
                  Proxy(Derived& _owner, const value_t& _v, Args... args)
                      : Impl(args...), owner_(_owner), v(_v) {}

                  //
                  // Conversion and Transformation
                  //
                  template<typename V, typename U>
                  auto offset(const units::Quantity<V, U>& _v) {
                      const auto new_o = chandra::units::convert<BaseUnits, U>(_v.value());
                      o = new_o;
                      return o;
                  }

                  auto offset() const {
                      return units::Quantity<value_t, BaseUnits>{o};
                  }

                  auto quantity() const {
                      return units::Quantity<value_t, BaseUnits>{v+o};
                  }

                  auto operator () () const { return quantity(); }

                  auto datarate(units::Quantity<scalar_t, units::mks::Hz> _odr) {
                      return units::Quantity<scalar_t, units::mks::Hz>(this->set_odr(_odr.value()));
                  }

                  auto datarate() {
                      return units::Quantity<scalar_t, units::mks::Hz>(this->get_odr());
                  }

                  auto oversampling(const uint16_t& _osr) {
                      return this->set_osr(_osr);
                  }

                  auto oversampling() {
                      return this->get_osr();
                  }

                  auto lowpass(units::Quantity<scalar_t, units::mks::Hz> _freq) {
                      return units::Quantity<scalar_t, units::mks::Hz>(this->set_lpf(_freq.value()));
                  }

                  auto lowpass() {
                      return units::Quantity<scalar_t, units::mks::Hz>(this->get_lpf());
                  }

              protected:
                  Derived& owner_;
                  const value_t& v;
                  value_t o;
          };

      protected:
        value_t pressure_raw_;
        value_t temperature_raw_;

      public:
          template<typename... Args>
          Barometric(Args... args)
            : pressure{static_cast<Derived&>(*this), pressure_raw_, args...},
              temperature{static_cast<Derived&>(*this), temperature_raw_, args...} {}

          uint8_t id() const { return 0xFF; }

          //bool init()
          //bool initialized() const
          //bool reset()
          //status_t calibrate(bool blocking=false)
          //bool calibrated() const
          //status_t update()
          //bool valid()
          //degC setSelfHeating(const degC& Tinit)
          //degC setSelfHeating() // use current temperature
          //degC Tinit()
          //degC Tselfheating()

          Proxy<PressureUnits, PressureImpl> pressure;
          Proxy<TempUnits, TempImpl> temperature;
  };


// TODO: IMPLEMENT ALTITUDE CALCULATOR FUNCTIONS
// TODO: THESE NEED TO BE TESTED....
// template<typename Value, typename Interface, typename Conversion>
// Value isaAltitude(const Barometric<Value, Interface, Conversion>& _baro, const auto& p0 = 1015.0) {
//     const auto e = Value(1.0) / Value(5.255);
//     const auto C = Value(44330.0);
//     const auto r = _baro.status();
//     return C * ( Value(1.0) - pow(r.pressure / p0, e));
// }
//
// template<typename Value, typename Interface, typename Conversion>
// Value hypsometricAltitude(const Barometric<Value, Interface, Conversion>& _baro,
//                           const auto& p0 = 1015.0, const auto& L = 0.0065) {
//     const auto e = Value(1.0) / Value(5.255);
//     const auto r = _baro.status();
//     return (r.temperature / L)* (pow(p0 / r.pressure, e));
// }

// TODO: THERE SHOULD ALSO BE SOME COMPENSATED PRESSURE/TEMPERATURE CALCULATION
//  FUNCTIONS TO ALLOW FOR BARO CALIBRATION AS THINGS MOVE FORWARD

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_BAROMETRIC_H*/
