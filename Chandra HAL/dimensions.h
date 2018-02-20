#ifndef CHANDRA_DIMENSIONS_H
#define CHANDRA_DIMENSIONS_H

#include <type_traits>

namespace chandra
{
namespace units
{
namespace dimensions
{
//
// This library implements a slightly modified version of the SI basic quantities with the addition
//  of plane angle as per the paper, "Implications of adopting plane angle as a base quantity
//  in the SI", by: Paul Quincey and Richard J. C. Brown.  As suggested in the conclusion of the
//  paper, the purpose here is not to cause an upheval in physics circles regarding the "correct"
//  set of basic constants, but, rather, to gain the ability to catch additional dimensional
//  errors in code relating to angles.
//
// Basic Quantities are:
//  Length              - l
//  Mass                - m
//  Time                - t
//  Electric Current    - I
//  Temperature         - T
//  Amount of Substance - mol
//  Luminous Intensity  - J
//  Plane Angle         - A
//

template<int l=0, int m=0, int t=0, int I=0, int T=0, int mol=0, int J=0, int A=0>
struct Dimensions
{
    template<int l2, int m2, int t2, int I2, int T2, int mol2, int J2, int A2>
    constexpr auto operator * (Dimensions<l2, m2, t2, I2, T2, mol2, J2, A2>) {
        return Dimensions<l+l2, m+m2, t+t2, I+I2, T+T2, mol+mol2, J+J2, A+A2>();
    }

    template<int l2, int m2, int t2, int I2, int T2, int mol2, int J2, int A2>
    constexpr auto operator / (Dimensions<l2, m2, t2, I2, T2, mol2, J2, A2>) {
        return Dimensions<l-l2, m-m2, t-t2, I-I2, T-T2, mol-mol2, J-J2, A-A2>();
    }

    constexpr auto inv() {
        return Dimensions<-l, -m, -t, -I, -T, -mol, -J, -A>();
    }
};

template<typename A, typename B>
class DimensionsMatch
{
    public:
        constexpr static bool value = std::is_same<A, B>::value;
};

namespace internal
{
template<typename Stream>
constexpr void pushDimension(Stream& _stream, const char* _symbol, int _n){
    if(_n == 0) return;
    if(_n != 1) _stream << '(';
    _stream << _symbol;
    if(_n != 1) {
        _stream << '^' << _n << ')';
    }
}
}

template<typename Stream, int l, int m, int t, int I, int T, int mol, int J, int A>
Stream& operator << (Stream& _stream, const Dimensions<l, m, t, I, T, mol, J, A>) {
    internal::pushDimension(_stream, "m", m);
    internal::pushDimension(_stream, "l", l);
    internal::pushDimension(_stream, "t", t);
    internal::pushDimension(_stream, "I", I);
    internal::pushDimension(_stream, "T", T);
    internal::pushDimension(_stream, "mol", mol);
    internal::pushDimension(_stream, "J", J);
    internal::pushDimension(_stream, "A", A);

    return _stream;
}

// Declaring the Basic Dimensions
using Unitless = Dimensions<>;
using Length = Dimensions<1>;
using Mass = Dimensions<0, 1>;
using Time = Dimensions<0, 0, 1>;
using ElectricCurrent = Dimensions<0, 0, 0, 1>;
using Temperature = Dimensions<0, 0, 0, 0, 1>;
using Amount = Dimensions<0, 0, 0, 0, 0, 1>;
using LuminousIntensity = Dimensions<0, 0, 0, 0, 0, 0, 1>;
using PlaneAngle = Dimensions<0, 0, 0, 0, 0, 0, 0, 1>;
using SolidAngle = Unitless; // Note: It may make sense to make this a basic dimension....

// Helper Dimensions
namespace internal
{
using Time2 = decltype(Time() * Time());
using Time3 = decltype(Time2() * Time());
using Time4 = decltype(Time2() * Time2());
using Time5 = decltype(Time3() * Time2());
using Time6 = decltype(Time3() * Time3());
using ElectricCurrent2 = decltype(ElectricCurrent() * ElectricCurrent());
}

// Declaration of Derived Dimensions
using Abasement = decltype(Length() * Time());
using Area = decltype(Length() * Length());
using AbsorbedDoseRate = decltype(Area() / internal::Time3());
using Acceleration = decltype(Length() / internal::Time2());
using AngularAcceleration = decltype(PlaneAngle() / internal::Time2());
using AngularMomentum = decltype(Mass() * Area() / Time());
using AngularVelocity = decltype(PlaneAngle() / Time());
using AreaDensity = decltype(Mass() / Area());
using Capacitance = decltype(internal::Time4() * internal::ElectricCurrent2() / Mass() / Area());
using CatalyticActivity = decltype(Amount() / Time());
using Volume = decltype(Length() * Length() * Length());
using CatalyticActivityConcentration = decltype(CatalyticActivity() / Volume());
using ChemicalPotential = decltype(Mass() * Area() / internal::Time2() / Amount());
using Crackle = decltype(Length() / internal::Time5());
using CurrentDensity = decltype(ElectricCurrent() / Area());
using DoseEquivalent = decltype(Area() / internal::Time2());
using DynamicViscosity = decltype(Mass() / Length() / Time());
using ElectricCharge = decltype(Time() * ElectricCurrent());
using ElectricChargeDensity = decltype(ElectricCharge() / Volume());
using ElectricDisplacement = decltype(ElectricCharge() / Area());
using ElectricFieldStrength = decltype(Mass() * Length() / internal::Time3() / ElectricCurrent());
using ElectricalConductance =
    decltype(internal::ElectricCurrent2() * internal::Time3() / Area() / Mass());
using ElectricalConductivity = decltype(ElectricalConductance() / Length());
using ElectricPotential = decltype(Mass() * Area() / ElectricCurrent() / internal::Time2());
using ElectricalResistance = decltype(ElectricalConductance().inv());
using ElectricalResistivity = decltype(ElectricalConductivity().inv());
using Energy = decltype(Mass() * Area() / internal::Time2());
using Heat = Energy;
using EnergyDensity = decltype(Energy() / Volume());
using Entropy = decltype(Energy() / Temperature());
using Force = decltype(Mass() * Acceleration());
using Frequency = decltype(Time().inv());
using HeatCapacity = decltype(Heat() / Temperature());
using HeatFluxDensity = decltype(Mass() / internal::Time3());
using LuminousFlux = LuminousIntensity;
using Illuminance = decltype(LuminousFlux() / Area());
using Impedance = decltype(Energy() / Time() / internal::ElectricCurrent2());
using Impulse = decltype(Mass() * Length() / Time());
using Inductance = decltype(Energy() / internal::ElectricCurrent2());
using Intensity = decltype(Mass() / internal::Time3());
using Irradiance = Intensity;
using Jerk = decltype(Length() / internal::Time3());
using Jounce = decltype(Length() / internal::Time4());
using Snap = Jounce;
using LinearDensity = decltype(Mass() / Length());
using MachNumver = Dimensions<>;
using MagneticFieldStrength = decltype(Length() / ElectricCurrent());
using MagneticFlux = decltype(Mass() * Area() / internal::Time2() / ElectricCurrent());
using MagneticFluxDensity = decltype(MagneticFlux() / Area());
using Magnetization = decltype(ElectricCurrent() / Length());
using MassFraction = Unitless;
using Density = decltype(Mass() / Volume());
using MolarConcentration = decltype(Amount() / Volume());
using MolarEnergy = decltype(Energy() / Amount());
using MolarEntropy = decltype(Entropy() / Amount());
using MolarHeatCapacity = decltype(HeatCapacity() / Amount());
using MomentOfInertia = decltype(Mass() * Area());
using Momentum = decltype(Mass() * Length() / Time());
using Permeability = decltype(Mass() * Length() / internal::Time2() / internal::ElectricCurrent2());
using Permittivity = decltype(internal::Time4() * internal::ElectricCurrent2() / Mass() / Volume());
using Power = decltype(Mass() * Area() / internal::Time3());
using Pressure = decltype(Mass() / Length() / internal::Time2());
using Pop = decltype(Length() / internal::Time6());
using Activity = Frequency;
using Dose = decltype(Area() / internal::Time2());
using Radiance = decltype(Mass() / internal::Time3());
using RadiantIntensity = decltype(Mass() * Area() / internal::Time3());
using ReactionRate = decltype(Amount() / Volume() / Time());
using RefractiveIndex = Unitless;
using Speed = decltype(Length() / Time());
using Velocity = Speed;
using SpecificEnergy = decltype(Energy() / Mass());
using SpecificHeatCapacity = decltype(Area() / internal::Time2() / Temperature());
using SpecificVolume = decltype(Volume() / Mass());
using Spin = decltype(Mass() * Area() / Time());
using Strain = Unitless;
using Stress = decltype(Mass() / Length() / internal::Time2());
using SurfaceTension = decltype(Mass() / internal::Time2());
using ThermalConductivity = decltype(Mass() * Length() / internal::Time3() / Temperature());
// TODO: DETERMINE IF TORQUE SHOULD CONTAIN ANGLE
using Torque = decltype(Mass() * Area() / internal::Time2());
using Wavelength = Length;
using Wavenumber = decltype(Wavelength().inv());
using Wavevector = Wavenumber;
using Weight = Force;
using Work = Energy;
using YoungsModulus = decltype(Mass() / Length() / internal::Time2());

} /*namespace dimensions*/
} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_DIMENSIONS_H*/

