#ifndef CHANDRA_AIR_H
#define CHANDRA_AIR_H

#include <cmath>

#include "horners.h"
#include "quantity.h"
#include "units.h"

// TODO: EVENTUALLY INCLUDE CORRECTION TO THE STANDARD VALUES BASED ON CALBRATION PRESSURE/TEMPERATURE/ALTITUDE
//  THIS CAN BY ADDING A TEMPERATURE DELTA (FOR TEMPERATURE ONLY).  PRESSURE, DENSITY, ETC ARE SUPPOSED
//  TO REMAIN UNCHANGED.  FIGURE OUT IF THERE IS ANOTHER WAY TO HANDLE THIS.
//  SOME INTERESTIG RELATED INFORMATION ARE THE MILITARY SPECIFICATIONS: MIL-STD-210C AND MIL-HDBK-310
//  WHICH OUTLINE CLIMATE CONDITIONS FOR PERFORMACE REQUIREMENTS.

// ADD CALCULATIO OF CORRECTION FOR CALORICALLY IMPERFECT GAS -- https://www.grc.nasa.gov/WWW/BGH/realspec.html

namespace chandra
{
namespace aero
{

template<class Value=float>
class Air
{
  public:
    using length_units = chandra::units::mks::m;
    using mass_units = chandra::units::mks::kg;
    using time_units = chandra::units::mks::s;
    using pressure_units = chandra::units::mks::Pa;
    using temperature_units = chandra::units::mks::K;

    using volume_units = chandra::units::volumeFrom<length_units>;
    using density_units = chandra::units::densityFrom<mass_units, length_units>;
    using velocity_units = chandra::units::velocityFrom<length_units, time_units>;
    using acceleration_units = chandra::units::accelerationFrom<length_units, time_units>;
    using dynamic_viscosity_units = mass_units;
    using kinematic_viscosity_units = mass_units;
    using thermal_conductivity_units = mass_units;

    using length_t = chandra::units::Quantity<Value, length_units>;
    using density_t = chandra::units::Quantity<Value, density_units>;
    using pressure_t = chandra::units::Quantity<Value, pressure_units>;
    using temperature_t = chandra::units::Quantity<Value, temperature_units>;
    using acceleration_t = chandra::units::Quantity<Value, acceleration_units>;
    using dynamic_viscosity_t = chandra::units::Quantity<Value, dynamic_viscosity_units>;
    using kinematic_viscosity_t = chandra::units::Quantity<Value, kinematic_viscosity_units>;
    using thermal_conductivity_t = chandra::units::Quantity<Value, thermal_conductivity_units>;

    // CALCULATE:
    //  PRESSURE (USING IDEAL GAS LAWS)
    //  DENSITY (USING IDEAL GAS LAWS)

    //  RATIO OF SPECIFIC HEATS (GAMMA)
    constexpr Value gamma(const temperature_t& _T) const {
      constexpr const Value C[] = {
          -1.27486493e-13,
          4.95701726e-10,
          -6.45129609e-07,
          2.38253065e-04,
          1.37472658
      };

      return chandra::math::HornersMethod<Value>(C, _T.value());
    }

    //  SPECIFIC HEAT (Cp and Cv) (relative to T and relative to T and P)
    //  Cv(T) = Cp(T) / gamma(T)

    //  DYNAMIC/KINEMATIC VISCOSITY
    constexpr dynamic_viscosity_t mu(const temperature_t& _T) const {
      const Value beta = 1.458e-6; // kg / (s*m*k^1/2)
      const Value S = 110.4; // Sutherland's Constant (K)
      const Value T = _T.value();
      return dynamic_viscosity_t{static_cast<Value>((beta * std::pow(T, 3.0/2.0))/(T + S))}; // TODO: SEE IF THERE IS A WAY TO OPTIMIZE THIS
    }

    constexpr kinematic_viscosity_t eta(const temperature_t& _T, const density_t& _rho) const {
      return kinematic_viscosity_t{static_cast<Value>(mu(_T).value() / _rho.value())};
    }



    //  THERMAL CONDUCTIVITY

    //  SPEED OF SOUND

    //  ETC.

};

} /* namespace aero */
} /* namespace chandra */

#endif /*CHANDRA_AIR_H*/
