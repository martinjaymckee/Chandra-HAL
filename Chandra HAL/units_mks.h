
#ifndef CHANDRA_MKS_UNITS_H
#define CHANDRA_MKS_UNITS_H

#include <ratio>

#include "dimensions.h"
#include "quantity.h"

namespace chandra
{
namespace units
{
namespace mks
{
//
// Overview of Units in mks System
//
//	Mass Pg = 1e+12 
//	Mass Tg = 1e+09 
//	Mass Gg = 1e+06 
//	Mass Mg = 1000 
//	Mass kg = 1 
//	Mass hg = 0.1 
//	Mass dag = 0.01 
//	Mass g = 0.001 
//	Mass dg = 0.0001 
//	Mass cg = 1e-05 
//	Mass mg = 1e-06 
//	Mass ug = 1e-09 
//	Mass ng = 1e-12 
//	Mass slug = 6854 
//	Mass TN = 1e+12 
//	Mass GN = 1e+09 
//	Mass MN = 1e+06 
//	Mass kN = 1000 
//	Mass hN = 100 
//	Mass daN = 10 
//	Mass N = 1 
//	Mass dN = 0.1 
//	Mass cN = 0.01 
//	Mass mN = 0.001 
//	Mass uN = 1e-06 
//	Mass nN = 1e-09 
//	Mass pN = 1e-12 
//	Mass Tgf = 9.807e+09 
//	Mass Ggf = 9.807e+06 
//	Mass Mgf = 9807 
//	Mass kgf = 9.807 
//	Mass hgf = 0.9807 
//	Mass dagf = 0.09807 
//	Mass gf = 0.009807 
//	Mass dgf = 0.0009807 
//	Mass cgf = 9.807e-05 
//	Mass mgf = 9.807e-06 
//	Mass ugf = 9.807e-09 
//	Mass ngf = 9.807e-12 
//	Mass lb = 0.2248 
//	Mass pdl = 7.231 
//	Length Tm = 1e+12 
//	Length Gm = 1e+09 
//	Length Mm = 1e+06 
//	Length km = 1000 
//	Length hm = 100 
//	Length dam = 10 
//	Length m = 1 
//	Length dm = 0.1 
//	Length cm = 0.01 
//	Length mm = 0.001 
//	Length um = 1e-06 
//	Length nm = 1e-09 
//	Length pm = 1e-12 
//	Length mi = 1609 
//	Length yd = 0.9144 
//	Length ft = 0.3048 
//	Length in = 0.0254 
//	Area Tm2 = 1e+12 
//	Area Gm2 = 1e+09 
//	Area Mm2 = 1e+06 
//	Area km2 = 1000 
//	Area hm2 = 100 
//	Area dam2 = 10 
//	Area m2 = 1 
//	Area dm2 = 0.1 
//	Area cm2 = 0.01 
//	Area mm2 = 0.001 
//	Area um2 = 1e-06 
//	Area nm2 = 1e-09 
//	Area pm2 = 1e-12 
//	Area mi2 = 2.59e+06 
//	Area yd2 = 0.8361 
//	Area ft2 = 0.0929 
//	Area in2 = 0.0006452 
//	Volume Tm3 = 1e+12 
//	Volume Gm3 = 1e+09 
//	Volume Mm3 = 1e+06 
//	Volume km3 = 1000 
//	Volume hm3 = 100 
//	Volume dam3 = 10 
//	Volume m3 = 1 
//	Volume dm3 = 0.1 
//	Volume cm3 = 0.01 
//	Volume mm3 = 0.001 
//	Volume um3 = 1e-06 
//	Volume nm3 = 1e-09 
//	Volume pm3 = 1e-12 
//	Volume mi3 = 4.168e+09 
//	Volume yd3 = 0.7646 
//	Volume ft3 = 0.02832 
//	Volume in3 = 1.639e-05 
//	Amount mol = 1 
//	Density Pg_per_m3 = 1e+12 
//	Density Tg_per_m3 = 1e+09 
//	Density Gg_per_m3 = 1e+06 
//	Density Mg_per_m3 = 1000 
//	Density kg_per_m3 = 1 
//	Density hg_per_m3 = 0.1 
//	Density dag_per_m3 = 0.01 
//	Density g_per_m3 = 0.001 
//	Density dg_per_m3 = 0.0001 
//	Density cg_per_m3 = 1e-05 
//	Density mg_per_m3 = 1e-06 
//	Density ug_per_m3 = 1e-09 
//	Density ng_per_m3 = 1e-12 
//	Density Gg_per_cc = 1e+12 
//	Density Mg_per_cc = 1e+09 
//	Density kg_per_cc = 1e+06 
//	Density hg_per_cc = 1e+05 
//	Density dag_per_cc = 1e+04 
//	Density g_per_cc = 1000 
//	Density dg_per_cc = 100 
//	Density cg_per_cc = 10 
//	Density mg_per_cc = 1 
//	Density ug_per_cc = 0.001 
//	Density ng_per_cc = 1e-06 
//	Density pg_per_cc = 1e-09 
//	Density fg_per_cc = 1e-12 
//	Energy TJ = 1e+12 
//	Energy GJ = 1e+09 
//	Energy MJ = 1e+06 
//	Energy kJ = 1000 
//	Energy hJ = 100 
//	Energy daJ = 10 
//	Energy J = 1 
//	Energy dJ = 0.1 
//	Energy cJ = 0.01 
//	Energy mJ = 0.001 
//	Energy uJ = 1e-06 
//	Energy nJ = 1e-09 
//	Energy pJ = 1e-12 
//	Energy ft_lbf = 0.7376 
//	Energy BTU = 0.0009478 
//	Energy kWh = 2.778e-07 
//	Time Ts = 1e+12 
//	Time Gs = 1e+09 
//	Time Ms = 1e+06 
//	Time ks = 1000 
//	Time hs = 100 
//	Time das = 10 
//	Time s = 1 
//	Time ds = 0.1 
//	Time cs = 0.01 
//	Time ms = 0.001 
//	Time us = 1e-06 
//	Time ns = 1e-09 
//	Time ps = 1e-12 
//	Time min = 60 
//	Time hr = 3600 
//	Time day = 8.64e+04 
//	Frequency THz = 1e+12 
//	Frequency GHz = 1e+09 
//	Frequency MHz = 1e+06 
//	Frequency kHz = 1000 
//	Frequency hHz = 100 
//	Frequency daHz = 10 
//	Frequency Hz = 1 
//	Frequency dHz = 0.1 
//	Frequency cHz = 0.01 
//	Frequency mHz = 0.001 
//	Frequency uHz = 1e-06 
//	Frequency nHz = 1e-09 
//	Frequency pHz = 1e-12 
//	Velocity Tm_per_s = 1e+12 
//	Velocity Gm_per_s = 1e+09 
//	Velocity Mm_per_s = 1e+06 
//	Velocity km_per_s = 1000 
//	Velocity hm_per_s = 100 
//	Velocity dam_per_s = 10 
//	Velocity m_per_s = 1 
//	Velocity dm_per_s = 0.1 
//	Velocity cm_per_s = 0.01 
//	Velocity mm_per_s = 0.001 
//	Velocity um_per_s = 1e-06 
//	Velocity nm_per_s = 1e-09 
//	Velocity pm_per_s = 1e-12 
//	Velocity kmph = 0.36 
//	Velocity mph = 0.447 
//	Velocity kt = 0.5144 
//	Velocity mi_per_s = 1609 
//	Velocity yd_per_s = 0.9144 
//	Velocity fps = 0.3048 
//	Velocity in_per_s = 0.0254 
//	Acceleration Tm_per_s2 = 1e+12 
//	Acceleration Gm_per_s2 = 1e+09 
//	Acceleration Mm_per_s2 = 1e+06 
//	Acceleration km_per_s2 = 1000 
//	Acceleration hm_per_s2 = 100 
//	Acceleration dam_per_s2 = 10 
//	Acceleration m_per_s2 = 1 
//	Acceleration dm_per_s2 = 0.1 
//	Acceleration cm_per_s2 = 0.01 
//	Acceleration mm_per_s2 = 0.001 
//	Acceleration um_per_s2 = 1e-06 
//	Acceleration nm_per_s2 = 1e-09 
//	Acceleration pm_per_s2 = 1e-12 
//	Acceleration mi_per_s2 = 1609 
//	Acceleration yd_per_s2 = 0.9144 
//	Acceleration ft_per_s2 = 0.3048 
//	Acceleration in_per_s2 = 0.0254 
//	Acceleration Ggees = 9.807e+09 
//	Acceleration Mgees = 9.807e+06 
//	Acceleration kgees = 9807 
//	Acceleration hgees = 980.7 
//	Acceleration dagees = 98.07 
//	Acceleration gees = 9.807 
//	Acceleration dgees = 0.9807 
//	Acceleration cgees = 0.09807 
//	Acceleration mgees = 0.009807 
//	Acceleration ugees = 9.807e-06 
//	Acceleration ngees = 9.807e-09 
//	Acceleration pgees = 9.807e-12 
//	Jerk Tm_per_s3 = 1e+12 
//	Jerk Gm_per_s3 = 1e+09 
//	Jerk Mm_per_s3 = 1e+06 
//	Jerk km_per_s3 = 1000 
//	Jerk hm_per_s3 = 100 
//	Jerk dam_per_s3 = 10 
//	Jerk m_per_s3 = 1 
//	Jerk dm_per_s3 = 0.1 
//	Jerk cm_per_s3 = 0.01 
//	Jerk mm_per_s3 = 0.001 
//	Jerk um_per_s3 = 1e-06 
//	Jerk nm_per_s3 = 1e-09 
//	Jerk pm_per_s3 = 1e-12 
//	Jerk mi_per_s3 = 1609 
//	Jerk yd_per_s3 = 0.9144 
//	Jerk ft_per_s3 = 0.3048 
//	Jerk in_per_s3 = 0.0254 
//	Jerk Ggees_per_s = 9.807e+09 
//	Jerk Mgees_per_s = 9.807e+06 
//	Jerk kgees_per_s = 9807 
//	Jerk hgees_per_s = 980.7 
//	Jerk dagees_per_s = 98.07 
//	Jerk gees_per_s = 9.807 
//	Jerk dgees_per_s = 0.9807 
//	Jerk cgees_per_s = 0.09807 
//	Jerk mgees_per_s = 0.009807 
//	Jerk ugees_per_s = 9.807e-06 
//	Jerk ngees_per_s = 9.807e-09 
//	Jerk pgees_per_s = 9.807e-12 
//	PlaneAngle rad = 1 
//	PlaneAngle rev = 0.3183 
//	PlaneAngle deg = 0.01745 
//	PlaneAngle grad = 0.01571 
//	AngularVelocity rad_per_s = 1 
//	AngularVelocity rev_per_s = 0.3183 
//	AngularVelocity deg_per_s = 0.01745 
//	AngularVelocity grad_per_s = 0.01571 
//	AngularVelocity rpm = 0.005305 
//	AngularAcceleration rad_per_s2 = 1 
//	AngularAcceleration rev_per_s2 = 0.3183 
//	AngularAcceleration deg_per_s2 = 0.01745 
//	AngularAcceleration grad_per_s2 = 0.01571 
//	Temperature TdegC = 1e+12 
//	Temperature TdegC_abs = 1e+12 
//	Temperature GdegC = 1e+09 
//	Temperature GdegC_abs = 1e+09 
//	Temperature MdegC = 1e+06 
//	Temperature MdegC_abs = 1e+06 
//	Temperature kdegC = 1000 
//	Temperature kdegC_abs = 1000 
//	Temperature hdegC = 100 
//	Temperature hdegC_abs = 100 
//	Temperature dadegC = 10 
//	Temperature dadegC_abs = 10 
//	Temperature degC = 1 
//	Temperature degC_abs = 1 
//	Temperature ddegC = 0.1 
//	Temperature ddegC_abs = 0.1 
//	Temperature cdegC = 0.01 
//	Temperature cdegC_abs = 0.01 
//	Temperature mdegC = 0.001 
//	Temperature mdegC_abs = 0.001 
//	Temperature udegC = 1e-06 
//	Temperature udegC_abs = 1e-06 
//	Temperature ndegC = 1e-09 
//	Temperature ndegC_abs = 1e-09 
//	Temperature pdegC = 1e-12 
//	Temperature pdegC_abs = 1e-12 
//	Temperature TK = 1e+12 @ -273.15
//	Temperature TK_abs = 1e+12 @ -273.15
//	Temperature GK = 1e+09 @ -273.15
//	Temperature GK_abs = 1e+09 @ -273.15
//	Temperature MK = 1e+06 @ -273.15
//	Temperature MK_abs = 1e+06 @ -273.15
//	Temperature kK = 1000 @ -273.15
//	Temperature kK_abs = 1000 @ -273.15
//	Temperature hK = 100 @ -273.15
//	Temperature hK_abs = 100 @ -273.15
//	Temperature daK = 10 @ -273.15
//	Temperature daK_abs = 10 @ -273.15
//	Temperature K = 1 @ -273.15
//	Temperature K_abs = 1 @ -273.15
//	Temperature dK = 0.1 @ -273.15
//	Temperature dK_abs = 0.1 @ -273.15
//	Temperature cK = 0.01 @ -273.15
//	Temperature cK_abs = 0.01 @ -273.15
//	Temperature mK = 0.001 @ -273.15
//	Temperature mK_abs = 0.001 @ -273.15
//	Temperature uK = 1e-06 @ -273.15
//	Temperature uK_abs = 1e-06 @ -273.15
//	Temperature nK = 1e-09 @ -273.15
//	Temperature nK_abs = 1e-09 @ -273.15
//	Temperature pK = 1e-12 @ -273.15
//	Temperature pK_abs = 1e-12 @ -273.15
//	Temperature GdegF = 5.556e+08 @ 32.00
//	Temperature GdegF_abs = 5.556e+08 @ 32.00
//	Temperature MdegF = 5.556e+05 @ 32.00
//	Temperature MdegF_abs = 5.556e+05 @ 32.00
//	Temperature kdegF = 555.6 @ 32.00
//	Temperature kdegF_abs = 555.6 @ 32.00
//	Temperature hdegF = 55.56 @ 32.00
//	Temperature hdegF_abs = 55.56 @ 32.00
//	Temperature dadegF = 5.556 @ 32.00
//	Temperature dadegF_abs = 5.556 @ 32.00
//	Temperature degF = 0.5556 @ 32.00
//	Temperature degF_abs = 0.5556 @ 32.00
//	Temperature ddegF = 0.05556 @ 32.00
//	Temperature ddegF_abs = 0.05556 @ 32.00
//	Temperature cdegF = 0.005556 @ 32.00
//	Temperature cdegF_abs = 0.005556 @ 32.00
//	Temperature mdegF = 0.0005556 @ 32.00
//	Temperature mdegF_abs = 0.0005556 @ 32.00
//	Temperature udegF = 5.556e-07 @ 32.00
//	Temperature udegF_abs = 5.556e-07 @ 32.00
//	Temperature ndegF = 5.556e-10 @ 32.00
//	Temperature ndegF_abs = 5.556e-10 @ 32.00
//	Temperature pdegF = 1e-12 @ 32.00
//	Temperature pdegF_abs = 1e-12 @ 32.00
//	Temperature GdegRa = 5.556e+08 @ -459.67
//	Temperature GdegRa_abs = 5.556e+08 @ -459.67
//	Temperature MdegRa = 5.556e+05 @ -459.67
//	Temperature MdegRa_abs = 5.556e+05 @ -459.67
//	Temperature kdegRa = 555.6 @ -459.67
//	Temperature kdegRa_abs = 555.6 @ -459.67
//	Temperature hdegRa = 55.56 @ -459.67
//	Temperature hdegRa_abs = 55.56 @ -459.67
//	Temperature dadegRa = 5.556 @ -459.67
//	Temperature dadegRa_abs = 5.556 @ -459.67
//	Temperature degRa = 0.5556 @ -459.67
//	Temperature degRa_abs = 0.5556 @ -459.67
//	Temperature ddegRa = 0.05556 @ -459.67
//	Temperature ddegRa_abs = 0.05556 @ -459.67
//	Temperature cdegRa = 0.005556 @ -459.67
//	Temperature cdegRa_abs = 0.005556 @ -459.67
//	Temperature mdegRa = 0.0005556 @ -459.67
//	Temperature mdegRa_abs = 0.0005556 @ -459.67
//	Temperature udegRa = 5.556e-07 @ -459.67
//	Temperature udegRa_abs = 5.556e-07 @ -459.67
//	Temperature ndegRa = 5.556e-10 @ -459.67
//	Temperature ndegRa_abs = 5.556e-10 @ -459.67
//	Temperature pdegRa = 1e-12 @ -459.67
//	Temperature pdegRa_abs = 1e-12 @ -459.67
//	MagneticFlux TT = 1e+12 
//	MagneticFlux GT = 1e+09 
//	MagneticFlux MT = 1e+06 
//	MagneticFlux kT = 1000 
//	MagneticFlux hT = 100 
//	MagneticFlux daT = 10 
//	MagneticFlux T = 1 
//	MagneticFlux dT = 0.1 
//	MagneticFlux cT = 0.01 
//	MagneticFlux mT = 0.001 
//	MagneticFlux uT = 1e-06 
//	MagneticFlux nT = 1e-09 
//	MagneticFlux pT = 1e-12 
//	MagneticFlux PG = 1e+11 
//	MagneticFlux TG = 1e+08 
//	MagneticFlux GG = 1e+05 
//	MagneticFlux MG = 100 
//	MagneticFlux kG = 0.1 
//	MagneticFlux hG = 0.01 
//	MagneticFlux daG = 0.001 
//	MagneticFlux G = 0.0001 
//	MagneticFlux dG = 1e-05 
//	MagneticFlux cG = 1e-06 
//	MagneticFlux mG = 1e-07 
//	MagneticFlux uG = 1e-10 
//	Pressure TPa = 1e+12 
//	Pressure GPa = 1e+09 
//	Pressure MPa = 1e+06 
//	Pressure kPa = 1000 
//	Pressure hPa = 100 
//	Pressure daPa = 10 
//	Pressure Pa = 1 
//	Pressure dPa = 0.1 
//	Pressure cPa = 0.01 
//	Pressure mPa = 0.001 
//	Pressure uPa = 1e-06 
//	Pressure nPa = 1e-09 
//	Pressure pPa = 1e-12 
//	Pressure Mbar = 1e+11 
//	Pressure kbar = 1e+08 
//	Pressure hbar = 1e+07 
//	Pressure dabar = 1e+06 
//	Pressure bar = 1e+05 
//	Pressure dbar = 1e+04 
//	Pressure cbar = 1000 
//	Pressure mbar = 100 
//	Pressure ubar = 0.1 
//	Pressure nbar = 0.0001 
//	Pressure pbar = 1e-07 
//	Pressure fbar = 1e-10 
//	Pressure psi = 6895 
//	Pressure atm = 1.013e+05 
//	Pressure torr = 133.3 
//	ElectricPotential TV = 1e+12 
//	ElectricPotential GV = 1e+09 
//	ElectricPotential MV = 1e+06 
//	ElectricPotential kV = 1000 
//	ElectricPotential hV = 100 
//	ElectricPotential daV = 10 
//	ElectricPotential V = 1 
//	ElectricPotential dV = 0.1 
//	ElectricPotential cV = 0.01 
//	ElectricPotential mV = 0.001 
//	ElectricPotential uV = 1e-06 
//	ElectricPotential nV = 1e-09 
//	ElectricPotential pV = 1e-12 
//	ElectricCurrent TA = 1e+12 
//	ElectricCurrent GA = 1e+09 
//	ElectricCurrent MA = 1e+06 
//	ElectricCurrent kA = 1000 
//	ElectricCurrent hA = 100 
//	ElectricCurrent daA = 10 
//	ElectricCurrent A = 1 
//	ElectricCurrent dA = 0.1 
//	ElectricCurrent cA = 0.01 
//	ElectricCurrent mA = 0.001 
//	ElectricCurrent uA = 1e-06 
//	ElectricCurrent nA = 1e-09 
//	ElectricCurrent pA = 1e-12 
//	ElectricalResistance Pohm = 1e+12 
//	ElectricalResistance Tohm = 1e+09 
//	ElectricalResistance Gohm = 1e+06 
//	ElectricalResistance Mohm = 1000 
//	ElectricalResistance kohm = 1 
//	ElectricalResistance hohm = 0.1 
//	ElectricalResistance daohm = 0.01 
//	ElectricalResistance ohm = 0.001 
//	ElectricalResistance dohm = 0.0001 
//	ElectricalResistance cohm = 1e-05 
//	ElectricalResistance mohm = 1e-06 
//	ElectricalResistance uohm = 1e-09 
//	ElectricalResistance nohm = 1e-12 
//	ElectricalConductance GS = 1e+12 
//	ElectricalConductance MS = 1e+09 
//	ElectricalConductance kS = 1e+06 
//	ElectricalConductance hS = 1e+05 
//	ElectricalConductance daS = 1e+04 
//	ElectricalConductance S = 1000 
//	ElectricalConductance dS = 100 
//	ElectricalConductance cS = 10 
//	ElectricalConductance mS = 1 
//	ElectricalConductance uS = 0.001 
//	ElectricalConductance nS = 1e-06 
//	ElectricalConductance pS = 1e-09 
//	ElectricalConductance fS = 1e-12 
//	Capacitance GF = 1e+12 
//	Capacitance MF = 1e+09 
//	Capacitance kF = 1e+06 
//	Capacitance hF = 1e+05 
//	Capacitance daF = 1e+04 
//	Capacitance F = 1000 
//	Capacitance dF = 100 
//	Capacitance cF = 10 
//	Capacitance mF = 1 
//	Capacitance uF = 0.001 
//	Capacitance nF = 1e-06 
//	Capacitance pF = 1e-09 
//	Capacitance fF = 1e-12 
//	Inductance PH = 1e+12 
//	Inductance TH = 1e+09 
//	Inductance GH = 1e+06 
//	Inductance MH = 1000 
//	Inductance kH = 1 
//	Inductance hH = 0.1 
//	Inductance daH = 0.01 
//	Inductance H = 0.001 
//	Inductance dH = 0.0001 
//	Inductance cH = 1e-05 
//	Inductance mH = 1e-06 
//	Inductance uH = 1e-09 
//	Inductance nH = 1e-12 



//
// Unit "Pg"
//
    struct Pg
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pg";
        }
    };
    template<typename Value = long double>
    using Q_Pg = units::Quantity<Value, Pg>;
    namespace literals
    {
        static inline Q_Pg<long double> operator "" _Pg_ (long double _v) {
            return Q_Pg<long double>(_v); }
        static inline Q_Pg<long double> operator "" _Pg_ (unsigned long long int _v) {
            return Q_Pg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tg"
//
    struct Tg
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tg";
        }
    };
    template<typename Value = long double>
    using Q_Tg = units::Quantity<Value, Tg>;
    namespace literals
    {
        static inline Q_Tg<long double> operator "" _Tg_ (long double _v) {
            return Q_Tg<long double>(_v); }
        static inline Q_Tg<long double> operator "" _Tg_ (unsigned long long int _v) {
            return Q_Tg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gg"
//
    struct Gg
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gg";
        }
    };
    template<typename Value = long double>
    using Q_Gg = units::Quantity<Value, Gg>;
    namespace literals
    {
        static inline Q_Gg<long double> operator "" _Gg_ (long double _v) {
            return Q_Gg<long double>(_v); }
        static inline Q_Gg<long double> operator "" _Gg_ (unsigned long long int _v) {
            return Q_Gg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mg"
//
    struct Mg
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mg";
        }
    };
    template<typename Value = long double>
    using Q_Mg = units::Quantity<Value, Mg>;
    namespace literals
    {
        static inline Q_Mg<long double> operator "" _Mg_ (long double _v) {
            return Q_Mg<long double>(_v); }
        static inline Q_Mg<long double> operator "" _Mg_ (unsigned long long int _v) {
            return Q_Mg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kg"
//
    struct kg
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kg";
        }
    };
    template<typename Value = long double>
    using Q_kg = units::Quantity<Value, kg>;
    namespace literals
    {
        static inline Q_kg<long double> operator "" _kg_ (long double _v) {
            return Q_kg<long double>(_v); }
        static inline Q_kg<long double> operator "" _kg_ (unsigned long long int _v) {
            return Q_kg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hg"
//
    struct hg
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hg";
        }
    };
    template<typename Value = long double>
    using Q_hg = units::Quantity<Value, hg>;
    namespace literals
    {
        static inline Q_hg<long double> operator "" _hg_ (long double _v) {
            return Q_hg<long double>(_v); }
        static inline Q_hg<long double> operator "" _hg_ (unsigned long long int _v) {
            return Q_hg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dag"
//
    struct dag
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dag;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dag";
        }
    };
    template<typename Value = long double>
    using Q_dag = units::Quantity<Value, dag>;
    namespace literals
    {
        static inline Q_dag<long double> operator "" _dag_ (long double _v) {
            return Q_dag<long double>(_v); }
        static inline Q_dag<long double> operator "" _dag_ (unsigned long long int _v) {
            return Q_dag<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "g"
//
    struct g
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = g;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "g";
        }
    };
    template<typename Value = long double>
    using Q_g = units::Quantity<Value, g>;
    namespace literals
    {
        static inline Q_g<long double> operator "" _g_ (long double _v) {
            return Q_g<long double>(_v); }
        static inline Q_g<long double> operator "" _g_ (unsigned long long int _v) {
            return Q_g<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dg"
//
    struct dg
    {
        using factor_t = std::ratio<1, 10000>; // approx. 0.0001
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dg";
        }
    };
    template<typename Value = long double>
    using Q_dg = units::Quantity<Value, dg>;
    namespace literals
    {
        static inline Q_dg<long double> operator "" _dg_ (long double _v) {
            return Q_dg<long double>(_v); }
        static inline Q_dg<long double> operator "" _dg_ (unsigned long long int _v) {
            return Q_dg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cg"
//
    struct cg
    {
        using factor_t = std::ratio<1, 100000>; // approx. 1e-05
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cg";
        }
    };
    template<typename Value = long double>
    using Q_cg = units::Quantity<Value, cg>;
    namespace literals
    {
        static inline Q_cg<long double> operator "" _cg_ (long double _v) {
            return Q_cg<long double>(_v); }
        static inline Q_cg<long double> operator "" _cg_ (unsigned long long int _v) {
            return Q_cg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mg"
//
    struct mg
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mg";
        }
    };
    template<typename Value = long double>
    using Q_mg = units::Quantity<Value, mg>;
    namespace literals
    {
        static inline Q_mg<long double> operator "" _mg_ (long double _v) {
            return Q_mg<long double>(_v); }
        static inline Q_mg<long double> operator "" _mg_ (unsigned long long int _v) {
            return Q_mg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ug"
//
    struct ug
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ug;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ug";
        }
    };
    template<typename Value = long double>
    using Q_ug = units::Quantity<Value, ug>;
    namespace literals
    {
        static inline Q_ug<long double> operator "" _ug_ (long double _v) {
            return Q_ug<long double>(_v); }
        static inline Q_ug<long double> operator "" _ug_ (unsigned long long int _v) {
            return Q_ug<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ng"
//
    struct ng
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ng;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ng";
        }
    };
    template<typename Value = long double>
    using Q_ng = units::Quantity<Value, ng>;
    namespace literals
    {
        static inline Q_ng<long double> operator "" _ng_ (long double _v) {
            return Q_ng<long double>(_v); }
        static inline Q_ng<long double> operator "" _ng_ (unsigned long long int _v) {
            return Q_ng<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "slug"
//
    struct slug
    {
        using factor_t = std::ratio<4283756, 625>; // approx. 6854.01
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = slug;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "slug";
        }
    };
    template<typename Value = long double>
    using Q_slug = units::Quantity<Value, slug>;
    namespace literals
    {
        static inline Q_slug<long double> operator "" _slug_ (long double _v) {
            return Q_slug<long double>(_v); }
        static inline Q_slug<long double> operator "" _slug_ (unsigned long long int _v) {
            return Q_slug<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TN"
//
    struct TN
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TN";
        }
    };
    template<typename Value = long double>
    using Q_TN = units::Quantity<Value, TN>;
    namespace literals
    {
        static inline Q_TN<long double> operator "" _TN_ (long double _v) {
            return Q_TN<long double>(_v); }
        static inline Q_TN<long double> operator "" _TN_ (unsigned long long int _v) {
            return Q_TN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GN"
//
    struct GN
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GN";
        }
    };
    template<typename Value = long double>
    using Q_GN = units::Quantity<Value, GN>;
    namespace literals
    {
        static inline Q_GN<long double> operator "" _GN_ (long double _v) {
            return Q_GN<long double>(_v); }
        static inline Q_GN<long double> operator "" _GN_ (unsigned long long int _v) {
            return Q_GN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MN"
//
    struct MN
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MN";
        }
    };
    template<typename Value = long double>
    using Q_MN = units::Quantity<Value, MN>;
    namespace literals
    {
        static inline Q_MN<long double> operator "" _MN_ (long double _v) {
            return Q_MN<long double>(_v); }
        static inline Q_MN<long double> operator "" _MN_ (unsigned long long int _v) {
            return Q_MN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kN"
//
    struct kN
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kN";
        }
    };
    template<typename Value = long double>
    using Q_kN = units::Quantity<Value, kN>;
    namespace literals
    {
        static inline Q_kN<long double> operator "" _kN_ (long double _v) {
            return Q_kN<long double>(_v); }
        static inline Q_kN<long double> operator "" _kN_ (unsigned long long int _v) {
            return Q_kN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hN"
//
    struct hN
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hN";
        }
    };
    template<typename Value = long double>
    using Q_hN = units::Quantity<Value, hN>;
    namespace literals
    {
        static inline Q_hN<long double> operator "" _hN_ (long double _v) {
            return Q_hN<long double>(_v); }
        static inline Q_hN<long double> operator "" _hN_ (unsigned long long int _v) {
            return Q_hN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daN"
//
    struct daN
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daN";
        }
    };
    template<typename Value = long double>
    using Q_daN = units::Quantity<Value, daN>;
    namespace literals
    {
        static inline Q_daN<long double> operator "" _daN_ (long double _v) {
            return Q_daN<long double>(_v); }
        static inline Q_daN<long double> operator "" _daN_ (unsigned long long int _v) {
            return Q_daN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "N"
//
    struct N
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = N;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "N";
        }
    };
    template<typename Value = long double>
    using Q_N = units::Quantity<Value, N>;
    namespace literals
    {
        static inline Q_N<long double> operator "" _N_ (long double _v) {
            return Q_N<long double>(_v); }
        static inline Q_N<long double> operator "" _N_ (unsigned long long int _v) {
            return Q_N<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dN"
//
    struct dN
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dN";
        }
    };
    template<typename Value = long double>
    using Q_dN = units::Quantity<Value, dN>;
    namespace literals
    {
        static inline Q_dN<long double> operator "" _dN_ (long double _v) {
            return Q_dN<long double>(_v); }
        static inline Q_dN<long double> operator "" _dN_ (unsigned long long int _v) {
            return Q_dN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cN"
//
    struct cN
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cN";
        }
    };
    template<typename Value = long double>
    using Q_cN = units::Quantity<Value, cN>;
    namespace literals
    {
        static inline Q_cN<long double> operator "" _cN_ (long double _v) {
            return Q_cN<long double>(_v); }
        static inline Q_cN<long double> operator "" _cN_ (unsigned long long int _v) {
            return Q_cN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mN"
//
    struct mN
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mN";
        }
    };
    template<typename Value = long double>
    using Q_mN = units::Quantity<Value, mN>;
    namespace literals
    {
        static inline Q_mN<long double> operator "" _mN_ (long double _v) {
            return Q_mN<long double>(_v); }
        static inline Q_mN<long double> operator "" _mN_ (unsigned long long int _v) {
            return Q_mN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uN"
//
    struct uN
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uN";
        }
    };
    template<typename Value = long double>
    using Q_uN = units::Quantity<Value, uN>;
    namespace literals
    {
        static inline Q_uN<long double> operator "" _uN_ (long double _v) {
            return Q_uN<long double>(_v); }
        static inline Q_uN<long double> operator "" _uN_ (unsigned long long int _v) {
            return Q_uN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nN"
//
    struct nN
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nN";
        }
    };
    template<typename Value = long double>
    using Q_nN = units::Quantity<Value, nN>;
    namespace literals
    {
        static inline Q_nN<long double> operator "" _nN_ (long double _v) {
            return Q_nN<long double>(_v); }
        static inline Q_nN<long double> operator "" _nN_ (unsigned long long int _v) {
            return Q_nN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pN"
//
    struct pN
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pN;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pN";
        }
    };
    template<typename Value = long double>
    using Q_pN = units::Quantity<Value, pN>;
    namespace literals
    {
        static inline Q_pN<long double> operator "" _pN_ (long double _v) {
            return Q_pN<long double>(_v); }
        static inline Q_pN<long double> operator "" _pN_ (unsigned long long int _v) {
            return Q_pN<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tgf"
//
    struct Tgf
    {
        using factor_t = std::ratio<9806650000, 1>; // approx. 9.80665e+09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tgf";
        }
    };
    template<typename Value = long double>
    using Q_Tgf = units::Quantity<Value, Tgf>;
    namespace literals
    {
        static inline Q_Tgf<long double> operator "" _Tgf_ (long double _v) {
            return Q_Tgf<long double>(_v); }
        static inline Q_Tgf<long double> operator "" _Tgf_ (unsigned long long int _v) {
            return Q_Tgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Ggf"
//
    struct Ggf
    {
        using factor_t = std::ratio<9806650, 1>; // approx. 9.80665e+06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ggf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ggf";
        }
    };
    template<typename Value = long double>
    using Q_Ggf = units::Quantity<Value, Ggf>;
    namespace literals
    {
        static inline Q_Ggf<long double> operator "" _Ggf_ (long double _v) {
            return Q_Ggf<long double>(_v); }
        static inline Q_Ggf<long double> operator "" _Ggf_ (unsigned long long int _v) {
            return Q_Ggf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mgf"
//
    struct Mgf
    {
        using factor_t = std::ratio<196133, 20>; // approx. 9806.65
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mgf";
        }
    };
    template<typename Value = long double>
    using Q_Mgf = units::Quantity<Value, Mgf>;
    namespace literals
    {
        static inline Q_Mgf<long double> operator "" _Mgf_ (long double _v) {
            return Q_Mgf<long double>(_v); }
        static inline Q_Mgf<long double> operator "" _Mgf_ (unsigned long long int _v) {
            return Q_Mgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kgf"
//
    struct kgf
    {
        using factor_t = std::ratio<196133, 20000>; // approx. 9.80665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kgf";
        }
    };
    template<typename Value = long double>
    using Q_kgf = units::Quantity<Value, kgf>;
    namespace literals
    {
        static inline Q_kgf<long double> operator "" _kgf_ (long double _v) {
            return Q_kgf<long double>(_v); }
        static inline Q_kgf<long double> operator "" _kgf_ (unsigned long long int _v) {
            return Q_kgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hgf"
//
    struct hgf
    {
        using factor_t = std::ratio<196133, 200000>; // approx. 0.980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hgf";
        }
    };
    template<typename Value = long double>
    using Q_hgf = units::Quantity<Value, hgf>;
    namespace literals
    {
        static inline Q_hgf<long double> operator "" _hgf_ (long double _v) {
            return Q_hgf<long double>(_v); }
        static inline Q_hgf<long double> operator "" _hgf_ (unsigned long long int _v) {
            return Q_hgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dagf"
//
    struct dagf
    {
        using factor_t = std::ratio<196133, 2000000>; // approx. 0.0980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dagf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dagf";
        }
    };
    template<typename Value = long double>
    using Q_dagf = units::Quantity<Value, dagf>;
    namespace literals
    {
        static inline Q_dagf<long double> operator "" _dagf_ (long double _v) {
            return Q_dagf<long double>(_v); }
        static inline Q_dagf<long double> operator "" _dagf_ (unsigned long long int _v) {
            return Q_dagf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "gf"
//
    struct gf
    {
        using factor_t = std::ratio<196133, 20000000>; // approx. 0.00980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = gf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "gf";
        }
    };
    template<typename Value = long double>
    using Q_gf = units::Quantity<Value, gf>;
    namespace literals
    {
        static inline Q_gf<long double> operator "" _gf_ (long double _v) {
            return Q_gf<long double>(_v); }
        static inline Q_gf<long double> operator "" _gf_ (unsigned long long int _v) {
            return Q_gf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dgf"
//
    struct dgf
    {
        using factor_t = std::ratio<196133, 200000000>; // approx. 0.000980665
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dgf";
        }
    };
    template<typename Value = long double>
    using Q_dgf = units::Quantity<Value, dgf>;
    namespace literals
    {
        static inline Q_dgf<long double> operator "" _dgf_ (long double _v) {
            return Q_dgf<long double>(_v); }
        static inline Q_dgf<long double> operator "" _dgf_ (unsigned long long int _v) {
            return Q_dgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cgf"
//
    struct cgf
    {
        using factor_t = std::ratio<196133, 2000000000>; // approx. 9.80665e-05
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cgf";
        }
    };
    template<typename Value = long double>
    using Q_cgf = units::Quantity<Value, cgf>;
    namespace literals
    {
        static inline Q_cgf<long double> operator "" _cgf_ (long double _v) {
            return Q_cgf<long double>(_v); }
        static inline Q_cgf<long double> operator "" _cgf_ (unsigned long long int _v) {
            return Q_cgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mgf"
//
    struct mgf
    {
        using factor_t = std::ratio<196133, 20000000000>; // approx. 9.80665e-06
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mgf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mgf";
        }
    };
    template<typename Value = long double>
    using Q_mgf = units::Quantity<Value, mgf>;
    namespace literals
    {
        static inline Q_mgf<long double> operator "" _mgf_ (long double _v) {
            return Q_mgf<long double>(_v); }
        static inline Q_mgf<long double> operator "" _mgf_ (unsigned long long int _v) {
            return Q_mgf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ugf"
//
    struct ugf
    {
        using factor_t = std::ratio<8563, 873182993173>; // approx. 9.80665e-09
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ugf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ugf";
        }
    };
    template<typename Value = long double>
    using Q_ugf = units::Quantity<Value, ugf>;
    namespace literals
    {
        static inline Q_ugf<long double> operator "" _ugf_ (long double _v) {
            return Q_ugf<long double>(_v); }
        static inline Q_ugf<long double> operator "" _ugf_ (unsigned long long int _v) {
            return Q_ugf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ngf"
//
    struct ngf
    {
        using factor_t = std::ratio<5, 509858106489>; // approx. 9.80665e-12
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ngf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ngf";
        }
    };
    template<typename Value = long double>
    using Q_ngf = units::Quantity<Value, ngf>;
    namespace literals
    {
        static inline Q_ngf<long double> operator "" _ngf_ (long double _v) {
            return Q_ngf<long double>(_v); }
        static inline Q_ngf<long double> operator "" _ngf_ (unsigned long long int _v) {
            return Q_ngf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "lb"
//
    struct lb
    {
        using factor_t = std::ratio<11241, 50000>; // approx. 0.22482
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = lb;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "lb";
        }
    };
    template<typename Value = long double>
    using Q_lb = units::Quantity<Value, lb>;
    namespace literals
    {
        static inline Q_lb<long double> operator "" _lb_ (long double _v) {
            return Q_lb<long double>(_v); }
        static inline Q_lb<long double> operator "" _lb_ (unsigned long long int _v) {
            return Q_lb<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdl"
//
    struct pdl
    {
        using factor_t = std::ratio<66175, 9152>; // approx. 7.23066
        using dimensions_t = dimensions::Mass;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pdl;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdl";
        }
    };
    template<typename Value = long double>
    using Q_pdl = units::Quantity<Value, pdl>;
    namespace literals
    {
        static inline Q_pdl<long double> operator "" _pdl_ (long double _v) {
            return Q_pdl<long double>(_v); }
        static inline Q_pdl<long double> operator "" _pdl_ (unsigned long long int _v) {
            return Q_pdl<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tm"
//
    struct Tm
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm";
        }
    };
    template<typename Value = long double>
    using Q_Tm = units::Quantity<Value, Tm>;
    namespace literals
    {
        static inline Q_Tm<long double> operator "" _Tm_ (long double _v) {
            return Q_Tm<long double>(_v); }
        static inline Q_Tm<long double> operator "" _Tm_ (unsigned long long int _v) {
            return Q_Tm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gm"
//
    struct Gm
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm";
        }
    };
    template<typename Value = long double>
    using Q_Gm = units::Quantity<Value, Gm>;
    namespace literals
    {
        static inline Q_Gm<long double> operator "" _Gm_ (long double _v) {
            return Q_Gm<long double>(_v); }
        static inline Q_Gm<long double> operator "" _Gm_ (unsigned long long int _v) {
            return Q_Gm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mm"
//
    struct Mm
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm";
        }
    };
    template<typename Value = long double>
    using Q_Mm = units::Quantity<Value, Mm>;
    namespace literals
    {
        static inline Q_Mm<long double> operator "" _Mm_ (long double _v) {
            return Q_Mm<long double>(_v); }
        static inline Q_Mm<long double> operator "" _Mm_ (unsigned long long int _v) {
            return Q_Mm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "km"
//
    struct km
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km";
        }
    };
    template<typename Value = long double>
    using Q_km = units::Quantity<Value, km>;
    namespace literals
    {
        static inline Q_km<long double> operator "" _km_ (long double _v) {
            return Q_km<long double>(_v); }
        static inline Q_km<long double> operator "" _km_ (unsigned long long int _v) {
            return Q_km<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hm"
//
    struct hm
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm";
        }
    };
    template<typename Value = long double>
    using Q_hm = units::Quantity<Value, hm>;
    namespace literals
    {
        static inline Q_hm<long double> operator "" _hm_ (long double _v) {
            return Q_hm<long double>(_v); }
        static inline Q_hm<long double> operator "" _hm_ (unsigned long long int _v) {
            return Q_hm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dam"
//
    struct dam
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam";
        }
    };
    template<typename Value = long double>
    using Q_dam = units::Quantity<Value, dam>;
    namespace literals
    {
        static inline Q_dam<long double> operator "" _dam_ (long double _v) {
            return Q_dam<long double>(_v); }
        static inline Q_dam<long double> operator "" _dam_ (unsigned long long int _v) {
            return Q_dam<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "m"
//
    struct m
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m";
        }
    };
    template<typename Value = long double>
    using Q_m = units::Quantity<Value, m>;
    namespace literals
    {
        static inline Q_m<long double> operator "" _m_ (long double _v) {
            return Q_m<long double>(_v); }
        static inline Q_m<long double> operator "" _m_ (unsigned long long int _v) {
            return Q_m<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dm"
//
    struct dm
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm";
        }
    };
    template<typename Value = long double>
    using Q_dm = units::Quantity<Value, dm>;
    namespace literals
    {
        static inline Q_dm<long double> operator "" _dm_ (long double _v) {
            return Q_dm<long double>(_v); }
        static inline Q_dm<long double> operator "" _dm_ (unsigned long long int _v) {
            return Q_dm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cm"
//
    struct cm
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm";
        }
    };
    template<typename Value = long double>
    using Q_cm = units::Quantity<Value, cm>;
    namespace literals
    {
        static inline Q_cm<long double> operator "" _cm_ (long double _v) {
            return Q_cm<long double>(_v); }
        static inline Q_cm<long double> operator "" _cm_ (unsigned long long int _v) {
            return Q_cm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mm"
//
    struct mm
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm";
        }
    };
    template<typename Value = long double>
    using Q_mm = units::Quantity<Value, mm>;
    namespace literals
    {
        static inline Q_mm<long double> operator "" _mm_ (long double _v) {
            return Q_mm<long double>(_v); }
        static inline Q_mm<long double> operator "" _mm_ (unsigned long long int _v) {
            return Q_mm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "um"
//
    struct um
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = um;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "um";
        }
    };
    template<typename Value = long double>
    using Q_um = units::Quantity<Value, um>;
    namespace literals
    {
        static inline Q_um<long double> operator "" _um_ (long double _v) {
            return Q_um<long double>(_v); }
        static inline Q_um<long double> operator "" _um_ (unsigned long long int _v) {
            return Q_um<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nm"
//
    struct nm
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nm";
        }
    };
    template<typename Value = long double>
    using Q_nm = units::Quantity<Value, nm>;
    namespace literals
    {
        static inline Q_nm<long double> operator "" _nm_ (long double _v) {
            return Q_nm<long double>(_v); }
        static inline Q_nm<long double> operator "" _nm_ (unsigned long long int _v) {
            return Q_nm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pm"
//
    struct pm
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pm";
        }
    };
    template<typename Value = long double>
    using Q_pm = units::Quantity<Value, pm>;
    namespace literals
    {
        static inline Q_pm<long double> operator "" _pm_ (long double _v) {
            return Q_pm<long double>(_v); }
        static inline Q_pm<long double> operator "" _pm_ (unsigned long long int _v) {
            return Q_pm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mi"
//
    struct mi
    {
        using factor_t = std::ratio<201168, 125>; // approx. 1609.34
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi";
        }
    };
    template<typename Value = long double>
    using Q_mi = units::Quantity<Value, mi>;
    namespace literals
    {
        static inline Q_mi<long double> operator "" _mi_ (long double _v) {
            return Q_mi<long double>(_v); }
        static inline Q_mi<long double> operator "" _mi_ (unsigned long long int _v) {
            return Q_mi<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "yd"
//
    struct yd
    {
        using factor_t = std::ratio<1143, 1250>; // approx. 0.9144
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd";
        }
    };
    template<typename Value = long double>
    using Q_yd = units::Quantity<Value, yd>;
    namespace literals
    {
        static inline Q_yd<long double> operator "" _yd_ (long double _v) {
            return Q_yd<long double>(_v); }
        static inline Q_yd<long double> operator "" _yd_ (unsigned long long int _v) {
            return Q_yd<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ft"
//
    struct ft
    {
        using factor_t = std::ratio<381, 1250>; // approx. 0.3048
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft";
        }
    };
    template<typename Value = long double>
    using Q_ft = units::Quantity<Value, ft>;
    namespace literals
    {
        static inline Q_ft<long double> operator "" _ft_ (long double _v) {
            return Q_ft<long double>(_v); }
        static inline Q_ft<long double> operator "" _ft_ (unsigned long long int _v) {
            return Q_ft<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "in"
//
    struct in
    {
        using factor_t = std::ratio<127, 5000>; // approx. 0.0254
        using dimensions_t = dimensions::Length;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in";
        }
    };
    template<typename Value = long double>
    using Q_in = units::Quantity<Value, in>;
    namespace literals
    {
        static inline Q_in<long double> operator "" _in_ (long double _v) {
            return Q_in<long double>(_v); }
        static inline Q_in<long double> operator "" _in_ (unsigned long long int _v) {
            return Q_in<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tm2"
//
    struct Tm2
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm2";
        }
    };
    template<typename Value = long double>
    using Q_Tm2 = units::Quantity<Value, Tm2>;
    namespace literals
    {
        static inline Q_Tm2<long double> operator "" _Tm2_ (long double _v) {
            return Q_Tm2<long double>(_v); }
        static inline Q_Tm2<long double> operator "" _Tm2_ (unsigned long long int _v) {
            return Q_Tm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gm2"
//
    struct Gm2
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm2";
        }
    };
    template<typename Value = long double>
    using Q_Gm2 = units::Quantity<Value, Gm2>;
    namespace literals
    {
        static inline Q_Gm2<long double> operator "" _Gm2_ (long double _v) {
            return Q_Gm2<long double>(_v); }
        static inline Q_Gm2<long double> operator "" _Gm2_ (unsigned long long int _v) {
            return Q_Gm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mm2"
//
    struct Mm2
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm2";
        }
    };
    template<typename Value = long double>
    using Q_Mm2 = units::Quantity<Value, Mm2>;
    namespace literals
    {
        static inline Q_Mm2<long double> operator "" _Mm2_ (long double _v) {
            return Q_Mm2<long double>(_v); }
        static inline Q_Mm2<long double> operator "" _Mm2_ (unsigned long long int _v) {
            return Q_Mm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "km2"
//
    struct km2
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km2";
        }
    };
    template<typename Value = long double>
    using Q_km2 = units::Quantity<Value, km2>;
    namespace literals
    {
        static inline Q_km2<long double> operator "" _km2_ (long double _v) {
            return Q_km2<long double>(_v); }
        static inline Q_km2<long double> operator "" _km2_ (unsigned long long int _v) {
            return Q_km2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hm2"
//
    struct hm2
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm2";
        }
    };
    template<typename Value = long double>
    using Q_hm2 = units::Quantity<Value, hm2>;
    namespace literals
    {
        static inline Q_hm2<long double> operator "" _hm2_ (long double _v) {
            return Q_hm2<long double>(_v); }
        static inline Q_hm2<long double> operator "" _hm2_ (unsigned long long int _v) {
            return Q_hm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dam2"
//
    struct dam2
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam2";
        }
    };
    template<typename Value = long double>
    using Q_dam2 = units::Quantity<Value, dam2>;
    namespace literals
    {
        static inline Q_dam2<long double> operator "" _dam2_ (long double _v) {
            return Q_dam2<long double>(_v); }
        static inline Q_dam2<long double> operator "" _dam2_ (unsigned long long int _v) {
            return Q_dam2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "m2"
//
    struct m2
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m2";
        }
    };
    template<typename Value = long double>
    using Q_m2 = units::Quantity<Value, m2>;
    namespace literals
    {
        static inline Q_m2<long double> operator "" _m2_ (long double _v) {
            return Q_m2<long double>(_v); }
        static inline Q_m2<long double> operator "" _m2_ (unsigned long long int _v) {
            return Q_m2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dm2"
//
    struct dm2
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm2";
        }
    };
    template<typename Value = long double>
    using Q_dm2 = units::Quantity<Value, dm2>;
    namespace literals
    {
        static inline Q_dm2<long double> operator "" _dm2_ (long double _v) {
            return Q_dm2<long double>(_v); }
        static inline Q_dm2<long double> operator "" _dm2_ (unsigned long long int _v) {
            return Q_dm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cm2"
//
    struct cm2
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm2";
        }
    };
    template<typename Value = long double>
    using Q_cm2 = units::Quantity<Value, cm2>;
    namespace literals
    {
        static inline Q_cm2<long double> operator "" _cm2_ (long double _v) {
            return Q_cm2<long double>(_v); }
        static inline Q_cm2<long double> operator "" _cm2_ (unsigned long long int _v) {
            return Q_cm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mm2"
//
    struct mm2
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm2";
        }
    };
    template<typename Value = long double>
    using Q_mm2 = units::Quantity<Value, mm2>;
    namespace literals
    {
        static inline Q_mm2<long double> operator "" _mm2_ (long double _v) {
            return Q_mm2<long double>(_v); }
        static inline Q_mm2<long double> operator "" _mm2_ (unsigned long long int _v) {
            return Q_mm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "um2"
//
    struct um2
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = um2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "um2";
        }
    };
    template<typename Value = long double>
    using Q_um2 = units::Quantity<Value, um2>;
    namespace literals
    {
        static inline Q_um2<long double> operator "" _um2_ (long double _v) {
            return Q_um2<long double>(_v); }
        static inline Q_um2<long double> operator "" _um2_ (unsigned long long int _v) {
            return Q_um2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nm2"
//
    struct nm2
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nm2";
        }
    };
    template<typename Value = long double>
    using Q_nm2 = units::Quantity<Value, nm2>;
    namespace literals
    {
        static inline Q_nm2<long double> operator "" _nm2_ (long double _v) {
            return Q_nm2<long double>(_v); }
        static inline Q_nm2<long double> operator "" _nm2_ (unsigned long long int _v) {
            return Q_nm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pm2"
//
    struct pm2
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pm2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pm2";
        }
    };
    template<typename Value = long double>
    using Q_pm2 = units::Quantity<Value, pm2>;
    namespace literals
    {
        static inline Q_pm2<long double> operator "" _pm2_ (long double _v) {
            return Q_pm2<long double>(_v); }
        static inline Q_pm2<long double> operator "" _pm2_ (unsigned long long int _v) {
            return Q_pm2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mi2"
//
    struct mi2
    {
        using factor_t = std::ratio<23309893, 9>; // approx. 2.58999e+06
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi2";
        }
    };
    template<typename Value = long double>
    using Q_mi2 = units::Quantity<Value, mi2>;
    namespace literals
    {
        static inline Q_mi2<long double> operator "" _mi2_ (long double _v) {
            return Q_mi2<long double>(_v); }
        static inline Q_mi2<long double> operator "" _mi2_ (unsigned long long int _v) {
            return Q_mi2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "yd2"
//
    struct yd2
    {
        using factor_t = std::ratio<1306449, 1562500>; // approx. 0.836127
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd2";
        }
    };
    template<typename Value = long double>
    using Q_yd2 = units::Quantity<Value, yd2>;
    namespace literals
    {
        static inline Q_yd2<long double> operator "" _yd2_ (long double _v) {
            return Q_yd2<long double>(_v); }
        static inline Q_yd2<long double> operator "" _yd2_ (unsigned long long int _v) {
            return Q_yd2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ft2"
//
    struct ft2
    {
        using factor_t = std::ratio<145161, 1562500>; // approx. 0.092903
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft2";
        }
    };
    template<typename Value = long double>
    using Q_ft2 = units::Quantity<Value, ft2>;
    namespace literals
    {
        static inline Q_ft2<long double> operator "" _ft2_ (long double _v) {
            return Q_ft2<long double>(_v); }
        static inline Q_ft2<long double> operator "" _ft2_ (unsigned long long int _v) {
            return Q_ft2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "in2"
//
    struct in2
    {
        using factor_t = std::ratio<16129, 25000000>; // approx. 0.00064516
        using dimensions_t = dimensions::Area;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in2";
        }
    };
    template<typename Value = long double>
    using Q_in2 = units::Quantity<Value, in2>;
    namespace literals
    {
        static inline Q_in2<long double> operator "" _in2_ (long double _v) {
            return Q_in2<long double>(_v); }
        static inline Q_in2<long double> operator "" _in2_ (unsigned long long int _v) {
            return Q_in2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tm3"
//
    struct Tm3
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm3";
        }
    };
    template<typename Value = long double>
    using Q_Tm3 = units::Quantity<Value, Tm3>;
    namespace literals
    {
        static inline Q_Tm3<long double> operator "" _Tm3_ (long double _v) {
            return Q_Tm3<long double>(_v); }
        static inline Q_Tm3<long double> operator "" _Tm3_ (unsigned long long int _v) {
            return Q_Tm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gm3"
//
    struct Gm3
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm3";
        }
    };
    template<typename Value = long double>
    using Q_Gm3 = units::Quantity<Value, Gm3>;
    namespace literals
    {
        static inline Q_Gm3<long double> operator "" _Gm3_ (long double _v) {
            return Q_Gm3<long double>(_v); }
        static inline Q_Gm3<long double> operator "" _Gm3_ (unsigned long long int _v) {
            return Q_Gm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mm3"
//
    struct Mm3
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm3";
        }
    };
    template<typename Value = long double>
    using Q_Mm3 = units::Quantity<Value, Mm3>;
    namespace literals
    {
        static inline Q_Mm3<long double> operator "" _Mm3_ (long double _v) {
            return Q_Mm3<long double>(_v); }
        static inline Q_Mm3<long double> operator "" _Mm3_ (unsigned long long int _v) {
            return Q_Mm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "km3"
//
    struct km3
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km3";
        }
    };
    template<typename Value = long double>
    using Q_km3 = units::Quantity<Value, km3>;
    namespace literals
    {
        static inline Q_km3<long double> operator "" _km3_ (long double _v) {
            return Q_km3<long double>(_v); }
        static inline Q_km3<long double> operator "" _km3_ (unsigned long long int _v) {
            return Q_km3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hm3"
//
    struct hm3
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm3";
        }
    };
    template<typename Value = long double>
    using Q_hm3 = units::Quantity<Value, hm3>;
    namespace literals
    {
        static inline Q_hm3<long double> operator "" _hm3_ (long double _v) {
            return Q_hm3<long double>(_v); }
        static inline Q_hm3<long double> operator "" _hm3_ (unsigned long long int _v) {
            return Q_hm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dam3"
//
    struct dam3
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam3";
        }
    };
    template<typename Value = long double>
    using Q_dam3 = units::Quantity<Value, dam3>;
    namespace literals
    {
        static inline Q_dam3<long double> operator "" _dam3_ (long double _v) {
            return Q_dam3<long double>(_v); }
        static inline Q_dam3<long double> operator "" _dam3_ (unsigned long long int _v) {
            return Q_dam3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "m3"
//
    struct m3
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m3";
        }
    };
    template<typename Value = long double>
    using Q_m3 = units::Quantity<Value, m3>;
    namespace literals
    {
        static inline Q_m3<long double> operator "" _m3_ (long double _v) {
            return Q_m3<long double>(_v); }
        static inline Q_m3<long double> operator "" _m3_ (unsigned long long int _v) {
            return Q_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dm3"
//
    struct dm3
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm3";
        }
    };
    template<typename Value = long double>
    using Q_dm3 = units::Quantity<Value, dm3>;
    namespace literals
    {
        static inline Q_dm3<long double> operator "" _dm3_ (long double _v) {
            return Q_dm3<long double>(_v); }
        static inline Q_dm3<long double> operator "" _dm3_ (unsigned long long int _v) {
            return Q_dm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cm3"
//
    struct cm3
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm3";
        }
    };
    template<typename Value = long double>
    using Q_cm3 = units::Quantity<Value, cm3>;
    namespace literals
    {
        static inline Q_cm3<long double> operator "" _cm3_ (long double _v) {
            return Q_cm3<long double>(_v); }
        static inline Q_cm3<long double> operator "" _cm3_ (unsigned long long int _v) {
            return Q_cm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mm3"
//
    struct mm3
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm3";
        }
    };
    template<typename Value = long double>
    using Q_mm3 = units::Quantity<Value, mm3>;
    namespace literals
    {
        static inline Q_mm3<long double> operator "" _mm3_ (long double _v) {
            return Q_mm3<long double>(_v); }
        static inline Q_mm3<long double> operator "" _mm3_ (unsigned long long int _v) {
            return Q_mm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "um3"
//
    struct um3
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = um3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "um3";
        }
    };
    template<typename Value = long double>
    using Q_um3 = units::Quantity<Value, um3>;
    namespace literals
    {
        static inline Q_um3<long double> operator "" _um3_ (long double _v) {
            return Q_um3<long double>(_v); }
        static inline Q_um3<long double> operator "" _um3_ (unsigned long long int _v) {
            return Q_um3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nm3"
//
    struct nm3
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nm3";
        }
    };
    template<typename Value = long double>
    using Q_nm3 = units::Quantity<Value, nm3>;
    namespace literals
    {
        static inline Q_nm3<long double> operator "" _nm3_ (long double _v) {
            return Q_nm3<long double>(_v); }
        static inline Q_nm3<long double> operator "" _nm3_ (unsigned long long int _v) {
            return Q_nm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pm3"
//
    struct pm3
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pm3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pm3";
        }
    };
    template<typename Value = long double>
    using Q_pm3 = units::Quantity<Value, pm3>;
    namespace literals
    {
        static inline Q_pm3<long double> operator "" _pm3_ (long double _v) {
            return Q_pm3<long double>(_v); }
        static inline Q_pm3<long double> operator "" _pm3_ (unsigned long long int _v) {
            return Q_pm3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mi3"
//
    struct mi3
    {
        using factor_t = std::ratio<37513636429, 9>; // approx. 4.16818e+09
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi3";
        }
    };
    template<typename Value = long double>
    using Q_mi3 = units::Quantity<Value, mi3>;
    namespace literals
    {
        static inline Q_mi3<long double> operator "" _mi3_ (long double _v) {
            return Q_mi3<long double>(_v); }
        static inline Q_mi3<long double> operator "" _mi3_ (unsigned long long int _v) {
            return Q_mi3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "yd3"
//
    struct yd3
    {
        using factor_t = std::ratio<1493271207, 1953125000>; // approx. 0.764555
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd3";
        }
    };
    template<typename Value = long double>
    using Q_yd3 = units::Quantity<Value, yd3>;
    namespace literals
    {
        static inline Q_yd3<long double> operator "" _yd3_ (long double _v) {
            return Q_yd3<long double>(_v); }
        static inline Q_yd3<long double> operator "" _yd3_ (unsigned long long int _v) {
            return Q_yd3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ft3"
//
    struct ft3
    {
        using factor_t = std::ratio<55306341, 1953125000>; // approx. 0.0283168
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft3";
        }
    };
    template<typename Value = long double>
    using Q_ft3 = units::Quantity<Value, ft3>;
    namespace literals
    {
        static inline Q_ft3<long double> operator "" _ft3_ (long double _v) {
            return Q_ft3<long double>(_v); }
        static inline Q_ft3<long double> operator "" _ft3_ (unsigned long long int _v) {
            return Q_ft3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "in3"
//
    struct in3
    {
        using factor_t = std::ratio<2048383, 125000000000>; // approx. 1.63871e-05
        using dimensions_t = dimensions::Volume;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in3";
        }
    };
    template<typename Value = long double>
    using Q_in3 = units::Quantity<Value, in3>;
    namespace literals
    {
        static inline Q_in3<long double> operator "" _in3_ (long double _v) {
            return Q_in3<long double>(_v); }
        static inline Q_in3<long double> operator "" _in3_ (unsigned long long int _v) {
            return Q_in3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mol"
//
    struct mol
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Amount;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mol;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mol";
        }
    };
    template<typename Value = long double>
    using Q_mol = units::Quantity<Value, mol>;
    namespace literals
    {
        static inline Q_mol<long double> operator "" _mol_ (long double _v) {
            return Q_mol<long double>(_v); }
        static inline Q_mol<long double> operator "" _mol_ (unsigned long long int _v) {
            return Q_mol<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Pg_per_m3"
//
    struct Pg_per_m3
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_Pg_per_m3 = units::Quantity<Value, Pg_per_m3>;
    namespace literals
    {
        static inline Q_Pg_per_m3<long double> operator "" _Pg_per_m3_ (long double _v) {
            return Q_Pg_per_m3<long double>(_v); }
        static inline Q_Pg_per_m3<long double> operator "" _Pg_per_m3_ (unsigned long long int _v) {
            return Q_Pg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tg_per_m3"
//
    struct Tg_per_m3
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_Tg_per_m3 = units::Quantity<Value, Tg_per_m3>;
    namespace literals
    {
        static inline Q_Tg_per_m3<long double> operator "" _Tg_per_m3_ (long double _v) {
            return Q_Tg_per_m3<long double>(_v); }
        static inline Q_Tg_per_m3<long double> operator "" _Tg_per_m3_ (unsigned long long int _v) {
            return Q_Tg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gg_per_m3"
//
    struct Gg_per_m3
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_Gg_per_m3 = units::Quantity<Value, Gg_per_m3>;
    namespace literals
    {
        static inline Q_Gg_per_m3<long double> operator "" _Gg_per_m3_ (long double _v) {
            return Q_Gg_per_m3<long double>(_v); }
        static inline Q_Gg_per_m3<long double> operator "" _Gg_per_m3_ (unsigned long long int _v) {
            return Q_Gg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mg_per_m3"
//
    struct Mg_per_m3
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_Mg_per_m3 = units::Quantity<Value, Mg_per_m3>;
    namespace literals
    {
        static inline Q_Mg_per_m3<long double> operator "" _Mg_per_m3_ (long double _v) {
            return Q_Mg_per_m3<long double>(_v); }
        static inline Q_Mg_per_m3<long double> operator "" _Mg_per_m3_ (unsigned long long int _v) {
            return Q_Mg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kg_per_m3"
//
    struct kg_per_m3
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_kg_per_m3 = units::Quantity<Value, kg_per_m3>;
    namespace literals
    {
        static inline Q_kg_per_m3<long double> operator "" _kg_per_m3_ (long double _v) {
            return Q_kg_per_m3<long double>(_v); }
        static inline Q_kg_per_m3<long double> operator "" _kg_per_m3_ (unsigned long long int _v) {
            return Q_kg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hg_per_m3"
//
    struct hg_per_m3
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_hg_per_m3 = units::Quantity<Value, hg_per_m3>;
    namespace literals
    {
        static inline Q_hg_per_m3<long double> operator "" _hg_per_m3_ (long double _v) {
            return Q_hg_per_m3<long double>(_v); }
        static inline Q_hg_per_m3<long double> operator "" _hg_per_m3_ (unsigned long long int _v) {
            return Q_hg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dag_per_m3"
//
    struct dag_per_m3
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dag_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dag_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_dag_per_m3 = units::Quantity<Value, dag_per_m3>;
    namespace literals
    {
        static inline Q_dag_per_m3<long double> operator "" _dag_per_m3_ (long double _v) {
            return Q_dag_per_m3<long double>(_v); }
        static inline Q_dag_per_m3<long double> operator "" _dag_per_m3_ (unsigned long long int _v) {
            return Q_dag_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "g_per_m3"
//
    struct g_per_m3
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = g_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "g_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_g_per_m3 = units::Quantity<Value, g_per_m3>;
    namespace literals
    {
        static inline Q_g_per_m3<long double> operator "" _g_per_m3_ (long double _v) {
            return Q_g_per_m3<long double>(_v); }
        static inline Q_g_per_m3<long double> operator "" _g_per_m3_ (unsigned long long int _v) {
            return Q_g_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dg_per_m3"
//
    struct dg_per_m3
    {
        using factor_t = std::ratio<1, 10000>; // approx. 0.0001
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_dg_per_m3 = units::Quantity<Value, dg_per_m3>;
    namespace literals
    {
        static inline Q_dg_per_m3<long double> operator "" _dg_per_m3_ (long double _v) {
            return Q_dg_per_m3<long double>(_v); }
        static inline Q_dg_per_m3<long double> operator "" _dg_per_m3_ (unsigned long long int _v) {
            return Q_dg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cg_per_m3"
//
    struct cg_per_m3
    {
        using factor_t = std::ratio<1, 100000>; // approx. 1e-05
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_cg_per_m3 = units::Quantity<Value, cg_per_m3>;
    namespace literals
    {
        static inline Q_cg_per_m3<long double> operator "" _cg_per_m3_ (long double _v) {
            return Q_cg_per_m3<long double>(_v); }
        static inline Q_cg_per_m3<long double> operator "" _cg_per_m3_ (unsigned long long int _v) {
            return Q_cg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mg_per_m3"
//
    struct mg_per_m3
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mg_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mg_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_mg_per_m3 = units::Quantity<Value, mg_per_m3>;
    namespace literals
    {
        static inline Q_mg_per_m3<long double> operator "" _mg_per_m3_ (long double _v) {
            return Q_mg_per_m3<long double>(_v); }
        static inline Q_mg_per_m3<long double> operator "" _mg_per_m3_ (unsigned long long int _v) {
            return Q_mg_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ug_per_m3"
//
    struct ug_per_m3
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ug_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ug_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_ug_per_m3 = units::Quantity<Value, ug_per_m3>;
    namespace literals
    {
        static inline Q_ug_per_m3<long double> operator "" _ug_per_m3_ (long double _v) {
            return Q_ug_per_m3<long double>(_v); }
        static inline Q_ug_per_m3<long double> operator "" _ug_per_m3_ (unsigned long long int _v) {
            return Q_ug_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ng_per_m3"
//
    struct ng_per_m3
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ng_per_m3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ng_per_m3";
        }
    };
    template<typename Value = long double>
    using Q_ng_per_m3 = units::Quantity<Value, ng_per_m3>;
    namespace literals
    {
        static inline Q_ng_per_m3<long double> operator "" _ng_per_m3_ (long double _v) {
            return Q_ng_per_m3<long double>(_v); }
        static inline Q_ng_per_m3<long double> operator "" _ng_per_m3_ (unsigned long long int _v) {
            return Q_ng_per_m3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gg_per_cc"
//
    struct Gg_per_cc
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_Gg_per_cc = units::Quantity<Value, Gg_per_cc>;
    namespace literals
    {
        static inline Q_Gg_per_cc<long double> operator "" _Gg_per_cc_ (long double _v) {
            return Q_Gg_per_cc<long double>(_v); }
        static inline Q_Gg_per_cc<long double> operator "" _Gg_per_cc_ (unsigned long long int _v) {
            return Q_Gg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mg_per_cc"
//
    struct Mg_per_cc
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_Mg_per_cc = units::Quantity<Value, Mg_per_cc>;
    namespace literals
    {
        static inline Q_Mg_per_cc<long double> operator "" _Mg_per_cc_ (long double _v) {
            return Q_Mg_per_cc<long double>(_v); }
        static inline Q_Mg_per_cc<long double> operator "" _Mg_per_cc_ (unsigned long long int _v) {
            return Q_Mg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kg_per_cc"
//
    struct kg_per_cc
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_kg_per_cc = units::Quantity<Value, kg_per_cc>;
    namespace literals
    {
        static inline Q_kg_per_cc<long double> operator "" _kg_per_cc_ (long double _v) {
            return Q_kg_per_cc<long double>(_v); }
        static inline Q_kg_per_cc<long double> operator "" _kg_per_cc_ (unsigned long long int _v) {
            return Q_kg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hg_per_cc"
//
    struct hg_per_cc
    {
        using factor_t = std::ratio<100000, 1>; // approx. 100000
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_hg_per_cc = units::Quantity<Value, hg_per_cc>;
    namespace literals
    {
        static inline Q_hg_per_cc<long double> operator "" _hg_per_cc_ (long double _v) {
            return Q_hg_per_cc<long double>(_v); }
        static inline Q_hg_per_cc<long double> operator "" _hg_per_cc_ (unsigned long long int _v) {
            return Q_hg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dag_per_cc"
//
    struct dag_per_cc
    {
        using factor_t = std::ratio<10000, 1>; // approx. 10000
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dag_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dag_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_dag_per_cc = units::Quantity<Value, dag_per_cc>;
    namespace literals
    {
        static inline Q_dag_per_cc<long double> operator "" _dag_per_cc_ (long double _v) {
            return Q_dag_per_cc<long double>(_v); }
        static inline Q_dag_per_cc<long double> operator "" _dag_per_cc_ (unsigned long long int _v) {
            return Q_dag_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "g_per_cc"
//
    struct g_per_cc
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = g_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "g_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_g_per_cc = units::Quantity<Value, g_per_cc>;
    namespace literals
    {
        static inline Q_g_per_cc<long double> operator "" _g_per_cc_ (long double _v) {
            return Q_g_per_cc<long double>(_v); }
        static inline Q_g_per_cc<long double> operator "" _g_per_cc_ (unsigned long long int _v) {
            return Q_g_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dg_per_cc"
//
    struct dg_per_cc
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_dg_per_cc = units::Quantity<Value, dg_per_cc>;
    namespace literals
    {
        static inline Q_dg_per_cc<long double> operator "" _dg_per_cc_ (long double _v) {
            return Q_dg_per_cc<long double>(_v); }
        static inline Q_dg_per_cc<long double> operator "" _dg_per_cc_ (unsigned long long int _v) {
            return Q_dg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cg_per_cc"
//
    struct cg_per_cc
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_cg_per_cc = units::Quantity<Value, cg_per_cc>;
    namespace literals
    {
        static inline Q_cg_per_cc<long double> operator "" _cg_per_cc_ (long double _v) {
            return Q_cg_per_cc<long double>(_v); }
        static inline Q_cg_per_cc<long double> operator "" _cg_per_cc_ (unsigned long long int _v) {
            return Q_cg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mg_per_cc"
//
    struct mg_per_cc
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_mg_per_cc = units::Quantity<Value, mg_per_cc>;
    namespace literals
    {
        static inline Q_mg_per_cc<long double> operator "" _mg_per_cc_ (long double _v) {
            return Q_mg_per_cc<long double>(_v); }
        static inline Q_mg_per_cc<long double> operator "" _mg_per_cc_ (unsigned long long int _v) {
            return Q_mg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ug_per_cc"
//
    struct ug_per_cc
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ug_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ug_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_ug_per_cc = units::Quantity<Value, ug_per_cc>;
    namespace literals
    {
        static inline Q_ug_per_cc<long double> operator "" _ug_per_cc_ (long double _v) {
            return Q_ug_per_cc<long double>(_v); }
        static inline Q_ug_per_cc<long double> operator "" _ug_per_cc_ (unsigned long long int _v) {
            return Q_ug_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ng_per_cc"
//
    struct ng_per_cc
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ng_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ng_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_ng_per_cc = units::Quantity<Value, ng_per_cc>;
    namespace literals
    {
        static inline Q_ng_per_cc<long double> operator "" _ng_per_cc_ (long double _v) {
            return Q_ng_per_cc<long double>(_v); }
        static inline Q_ng_per_cc<long double> operator "" _ng_per_cc_ (unsigned long long int _v) {
            return Q_ng_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pg_per_cc"
//
    struct pg_per_cc
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_pg_per_cc = units::Quantity<Value, pg_per_cc>;
    namespace literals
    {
        static inline Q_pg_per_cc<long double> operator "" _pg_per_cc_ (long double _v) {
            return Q_pg_per_cc<long double>(_v); }
        static inline Q_pg_per_cc<long double> operator "" _pg_per_cc_ (unsigned long long int _v) {
            return Q_pg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "fg_per_cc"
//
    struct fg_per_cc
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Density;
        using offset_t = std::ratio<0, 1>;
        using relative_t = fg_per_cc;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "fg_per_cc";
        }
    };
    template<typename Value = long double>
    using Q_fg_per_cc = units::Quantity<Value, fg_per_cc>;
    namespace literals
    {
        static inline Q_fg_per_cc<long double> operator "" _fg_per_cc_ (long double _v) {
            return Q_fg_per_cc<long double>(_v); }
        static inline Q_fg_per_cc<long double> operator "" _fg_per_cc_ (unsigned long long int _v) {
            return Q_fg_per_cc<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TJ"
//
    struct TJ
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TJ";
        }
    };
    template<typename Value = long double>
    using Q_TJ = units::Quantity<Value, TJ>;
    namespace literals
    {
        static inline Q_TJ<long double> operator "" _TJ_ (long double _v) {
            return Q_TJ<long double>(_v); }
        static inline Q_TJ<long double> operator "" _TJ_ (unsigned long long int _v) {
            return Q_TJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GJ"
//
    struct GJ
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GJ";
        }
    };
    template<typename Value = long double>
    using Q_GJ = units::Quantity<Value, GJ>;
    namespace literals
    {
        static inline Q_GJ<long double> operator "" _GJ_ (long double _v) {
            return Q_GJ<long double>(_v); }
        static inline Q_GJ<long double> operator "" _GJ_ (unsigned long long int _v) {
            return Q_GJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MJ"
//
    struct MJ
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MJ";
        }
    };
    template<typename Value = long double>
    using Q_MJ = units::Quantity<Value, MJ>;
    namespace literals
    {
        static inline Q_MJ<long double> operator "" _MJ_ (long double _v) {
            return Q_MJ<long double>(_v); }
        static inline Q_MJ<long double> operator "" _MJ_ (unsigned long long int _v) {
            return Q_MJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kJ"
//
    struct kJ
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kJ";
        }
    };
    template<typename Value = long double>
    using Q_kJ = units::Quantity<Value, kJ>;
    namespace literals
    {
        static inline Q_kJ<long double> operator "" _kJ_ (long double _v) {
            return Q_kJ<long double>(_v); }
        static inline Q_kJ<long double> operator "" _kJ_ (unsigned long long int _v) {
            return Q_kJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hJ"
//
    struct hJ
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hJ";
        }
    };
    template<typename Value = long double>
    using Q_hJ = units::Quantity<Value, hJ>;
    namespace literals
    {
        static inline Q_hJ<long double> operator "" _hJ_ (long double _v) {
            return Q_hJ<long double>(_v); }
        static inline Q_hJ<long double> operator "" _hJ_ (unsigned long long int _v) {
            return Q_hJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daJ"
//
    struct daJ
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daJ";
        }
    };
    template<typename Value = long double>
    using Q_daJ = units::Quantity<Value, daJ>;
    namespace literals
    {
        static inline Q_daJ<long double> operator "" _daJ_ (long double _v) {
            return Q_daJ<long double>(_v); }
        static inline Q_daJ<long double> operator "" _daJ_ (unsigned long long int _v) {
            return Q_daJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "J"
//
    struct J
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = J;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "J";
        }
    };
    template<typename Value = long double>
    using Q_J = units::Quantity<Value, J>;
    namespace literals
    {
        static inline Q_J<long double> operator "" _J_ (long double _v) {
            return Q_J<long double>(_v); }
        static inline Q_J<long double> operator "" _J_ (unsigned long long int _v) {
            return Q_J<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dJ"
//
    struct dJ
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dJ";
        }
    };
    template<typename Value = long double>
    using Q_dJ = units::Quantity<Value, dJ>;
    namespace literals
    {
        static inline Q_dJ<long double> operator "" _dJ_ (long double _v) {
            return Q_dJ<long double>(_v); }
        static inline Q_dJ<long double> operator "" _dJ_ (unsigned long long int _v) {
            return Q_dJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cJ"
//
    struct cJ
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cJ";
        }
    };
    template<typename Value = long double>
    using Q_cJ = units::Quantity<Value, cJ>;
    namespace literals
    {
        static inline Q_cJ<long double> operator "" _cJ_ (long double _v) {
            return Q_cJ<long double>(_v); }
        static inline Q_cJ<long double> operator "" _cJ_ (unsigned long long int _v) {
            return Q_cJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mJ"
//
    struct mJ
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mJ";
        }
    };
    template<typename Value = long double>
    using Q_mJ = units::Quantity<Value, mJ>;
    namespace literals
    {
        static inline Q_mJ<long double> operator "" _mJ_ (long double _v) {
            return Q_mJ<long double>(_v); }
        static inline Q_mJ<long double> operator "" _mJ_ (unsigned long long int _v) {
            return Q_mJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uJ"
//
    struct uJ
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uJ";
        }
    };
    template<typename Value = long double>
    using Q_uJ = units::Quantity<Value, uJ>;
    namespace literals
    {
        static inline Q_uJ<long double> operator "" _uJ_ (long double _v) {
            return Q_uJ<long double>(_v); }
        static inline Q_uJ<long double> operator "" _uJ_ (unsigned long long int _v) {
            return Q_uJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nJ"
//
    struct nJ
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nJ";
        }
    };
    template<typename Value = long double>
    using Q_nJ = units::Quantity<Value, nJ>;
    namespace literals
    {
        static inline Q_nJ<long double> operator "" _nJ_ (long double _v) {
            return Q_nJ<long double>(_v); }
        static inline Q_nJ<long double> operator "" _nJ_ (unsigned long long int _v) {
            return Q_nJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pJ"
//
    struct pJ
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pJ;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pJ";
        }
    };
    template<typename Value = long double>
    using Q_pJ = units::Quantity<Value, pJ>;
    namespace literals
    {
        static inline Q_pJ<long double> operator "" _pJ_ (long double _v) {
            return Q_pJ<long double>(_v); }
        static inline Q_pJ<long double> operator "" _pJ_ (unsigned long long int _v) {
            return Q_pJ<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ft_lbf"
//
    struct ft_lbf
    {
        using factor_t = std::ratio<5000, 6779>; // approx. 0.737572
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft_lbf;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft_lbf";
        }
    };
    template<typename Value = long double>
    using Q_ft_lbf = units::Quantity<Value, ft_lbf>;
    namespace literals
    {
        static inline Q_ft_lbf<long double> operator "" _ft_lbf_ (long double _v) {
            return Q_ft_lbf<long double>(_v); }
        static inline Q_ft_lbf<long double> operator "" _ft_lbf_ (unsigned long long int _v) {
            return Q_ft_lbf<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "BTU"
//
    struct BTU
    {
        using factor_t = std::ratio<50, 52753>; // approx. 0.000947813
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = BTU;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "BTU";
        }
    };
    template<typename Value = long double>
    using Q_BTU = units::Quantity<Value, BTU>;
    namespace literals
    {
        static inline Q_BTU<long double> operator "" _BTU_ (long double _v) {
            return Q_BTU<long double>(_v); }
        static inline Q_BTU<long double> operator "" _BTU_ (unsigned long long int _v) {
            return Q_BTU<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kWh"
//
    struct kWh
    {
        using factor_t = std::ratio<1, 3600000>; // approx. 2.77778e-07
        using dimensions_t = dimensions::Energy;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kWh;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kWh";
        }
    };
    template<typename Value = long double>
    using Q_kWh = units::Quantity<Value, kWh>;
    namespace literals
    {
        static inline Q_kWh<long double> operator "" _kWh_ (long double _v) {
            return Q_kWh<long double>(_v); }
        static inline Q_kWh<long double> operator "" _kWh_ (unsigned long long int _v) {
            return Q_kWh<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Ts"
//
    struct Ts
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ts;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ts";
        }
    };
    template<typename Value = long double>
    using Q_Ts = units::Quantity<Value, Ts>;
    namespace literals
    {
        static inline Q_Ts<long double> operator "" _Ts_ (long double _v) {
            return Q_Ts<long double>(_v); }
        static inline Q_Ts<long double> operator "" _Ts_ (unsigned long long int _v) {
            return Q_Ts<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gs"
//
    struct Gs
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gs;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gs";
        }
    };
    template<typename Value = long double>
    using Q_Gs = units::Quantity<Value, Gs>;
    namespace literals
    {
        static inline Q_Gs<long double> operator "" _Gs_ (long double _v) {
            return Q_Gs<long double>(_v); }
        static inline Q_Gs<long double> operator "" _Gs_ (unsigned long long int _v) {
            return Q_Gs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Ms"
//
    struct Ms
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ms;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ms";
        }
    };
    template<typename Value = long double>
    using Q_Ms = units::Quantity<Value, Ms>;
    namespace literals
    {
        static inline Q_Ms<long double> operator "" _Ms_ (long double _v) {
            return Q_Ms<long double>(_v); }
        static inline Q_Ms<long double> operator "" _Ms_ (unsigned long long int _v) {
            return Q_Ms<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ks"
//
    struct ks
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ks;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ks";
        }
    };
    template<typename Value = long double>
    using Q_ks = units::Quantity<Value, ks>;
    namespace literals
    {
        static inline Q_ks<long double> operator "" _ks_ (long double _v) {
            return Q_ks<long double>(_v); }
        static inline Q_ks<long double> operator "" _ks_ (unsigned long long int _v) {
            return Q_ks<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hs"
//
    struct hs
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hs;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hs";
        }
    };
    template<typename Value = long double>
    using Q_hs = units::Quantity<Value, hs>;
    namespace literals
    {
        static inline Q_hs<long double> operator "" _hs_ (long double _v) {
            return Q_hs<long double>(_v); }
        static inline Q_hs<long double> operator "" _hs_ (unsigned long long int _v) {
            return Q_hs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "das"
//
    struct das
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = das;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "das";
        }
    };
    template<typename Value = long double>
    using Q_das = units::Quantity<Value, das>;
    namespace literals
    {
        static inline Q_das<long double> operator "" _das_ (long double _v) {
            return Q_das<long double>(_v); }
        static inline Q_das<long double> operator "" _das_ (unsigned long long int _v) {
            return Q_das<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "s"
//
    struct s
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "s";
        }
    };
    template<typename Value = long double>
    using Q_s = units::Quantity<Value, s>;
    namespace literals
    {
        static inline Q_s<long double> operator "" _s_ (long double _v) {
            return Q_s<long double>(_v); }
        static inline Q_s<long double> operator "" _s_ (unsigned long long int _v) {
            return Q_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ds"
//
    struct ds
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ds;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ds";
        }
    };
    template<typename Value = long double>
    using Q_ds = units::Quantity<Value, ds>;
    namespace literals
    {
        static inline Q_ds<long double> operator "" _ds_ (long double _v) {
            return Q_ds<long double>(_v); }
        static inline Q_ds<long double> operator "" _ds_ (unsigned long long int _v) {
            return Q_ds<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cs"
//
    struct cs
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cs;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cs";
        }
    };
    template<typename Value = long double>
    using Q_cs = units::Quantity<Value, cs>;
    namespace literals
    {
        static inline Q_cs<long double> operator "" _cs_ (long double _v) {
            return Q_cs<long double>(_v); }
        static inline Q_cs<long double> operator "" _cs_ (unsigned long long int _v) {
            return Q_cs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ms"
//
    struct ms
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ms;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ms";
        }
    };
    template<typename Value = long double>
    using Q_ms = units::Quantity<Value, ms>;
    namespace literals
    {
        static inline Q_ms<long double> operator "" _ms_ (long double _v) {
            return Q_ms<long double>(_v); }
        static inline Q_ms<long double> operator "" _ms_ (unsigned long long int _v) {
            return Q_ms<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "us"
//
    struct us
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = us;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "us";
        }
    };
    template<typename Value = long double>
    using Q_us = units::Quantity<Value, us>;
    namespace literals
    {
        static inline Q_us<long double> operator "" _us_ (long double _v) {
            return Q_us<long double>(_v); }
        static inline Q_us<long double> operator "" _us_ (unsigned long long int _v) {
            return Q_us<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ns"
//
    struct ns
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ns;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ns";
        }
    };
    template<typename Value = long double>
    using Q_ns = units::Quantity<Value, ns>;
    namespace literals
    {
        static inline Q_ns<long double> operator "" _ns_ (long double _v) {
            return Q_ns<long double>(_v); }
        static inline Q_ns<long double> operator "" _ns_ (unsigned long long int _v) {
            return Q_ns<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ps"
//
    struct ps
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ps;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ps";
        }
    };
    template<typename Value = long double>
    using Q_ps = units::Quantity<Value, ps>;
    namespace literals
    {
        static inline Q_ps<long double> operator "" _ps_ (long double _v) {
            return Q_ps<long double>(_v); }
        static inline Q_ps<long double> operator "" _ps_ (unsigned long long int _v) {
            return Q_ps<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "min"
//
    struct min
    {
        using factor_t = std::ratio<60, 1>; // approx. 60
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = min;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "min";
        }
    };
    template<typename Value = long double>
    using Q_min = units::Quantity<Value, min>;
    namespace literals
    {
        static inline Q_min<long double> operator "" _min_ (long double _v) {
            return Q_min<long double>(_v); }
        static inline Q_min<long double> operator "" _min_ (unsigned long long int _v) {
            return Q_min<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hr"
//
    struct hr
    {
        using factor_t = std::ratio<3600, 1>; // approx. 3600
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hr;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hr";
        }
    };
    template<typename Value = long double>
    using Q_hr = units::Quantity<Value, hr>;
    namespace literals
    {
        static inline Q_hr<long double> operator "" _hr_ (long double _v) {
            return Q_hr<long double>(_v); }
        static inline Q_hr<long double> operator "" _hr_ (unsigned long long int _v) {
            return Q_hr<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "day"
//
    struct day
    {
        using factor_t = std::ratio<86400, 1>; // approx. 86400
        using dimensions_t = dimensions::Time;
        using offset_t = std::ratio<0, 1>;
        using relative_t = day;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "day";
        }
    };
    template<typename Value = long double>
    using Q_day = units::Quantity<Value, day>;
    namespace literals
    {
        static inline Q_day<long double> operator "" _day_ (long double _v) {
            return Q_day<long double>(_v); }
        static inline Q_day<long double> operator "" _day_ (unsigned long long int _v) {
            return Q_day<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "THz"
//
    struct THz
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = THz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "THz";
        }
    };
    template<typename Value = long double>
    using Q_THz = units::Quantity<Value, THz>;
    namespace literals
    {
        static inline Q_THz<long double> operator "" _THz_ (long double _v) {
            return Q_THz<long double>(_v); }
        static inline Q_THz<long double> operator "" _THz_ (unsigned long long int _v) {
            return Q_THz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GHz"
//
    struct GHz
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GHz";
        }
    };
    template<typename Value = long double>
    using Q_GHz = units::Quantity<Value, GHz>;
    namespace literals
    {
        static inline Q_GHz<long double> operator "" _GHz_ (long double _v) {
            return Q_GHz<long double>(_v); }
        static inline Q_GHz<long double> operator "" _GHz_ (unsigned long long int _v) {
            return Q_GHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MHz"
//
    struct MHz
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MHz";
        }
    };
    template<typename Value = long double>
    using Q_MHz = units::Quantity<Value, MHz>;
    namespace literals
    {
        static inline Q_MHz<long double> operator "" _MHz_ (long double _v) {
            return Q_MHz<long double>(_v); }
        static inline Q_MHz<long double> operator "" _MHz_ (unsigned long long int _v) {
            return Q_MHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kHz"
//
    struct kHz
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kHz";
        }
    };
    template<typename Value = long double>
    using Q_kHz = units::Quantity<Value, kHz>;
    namespace literals
    {
        static inline Q_kHz<long double> operator "" _kHz_ (long double _v) {
            return Q_kHz<long double>(_v); }
        static inline Q_kHz<long double> operator "" _kHz_ (unsigned long long int _v) {
            return Q_kHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hHz"
//
    struct hHz
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hHz";
        }
    };
    template<typename Value = long double>
    using Q_hHz = units::Quantity<Value, hHz>;
    namespace literals
    {
        static inline Q_hHz<long double> operator "" _hHz_ (long double _v) {
            return Q_hHz<long double>(_v); }
        static inline Q_hHz<long double> operator "" _hHz_ (unsigned long long int _v) {
            return Q_hHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daHz"
//
    struct daHz
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daHz";
        }
    };
    template<typename Value = long double>
    using Q_daHz = units::Quantity<Value, daHz>;
    namespace literals
    {
        static inline Q_daHz<long double> operator "" _daHz_ (long double _v) {
            return Q_daHz<long double>(_v); }
        static inline Q_daHz<long double> operator "" _daHz_ (unsigned long long int _v) {
            return Q_daHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Hz"
//
    struct Hz
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Hz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Hz";
        }
    };
    template<typename Value = long double>
    using Q_Hz = units::Quantity<Value, Hz>;
    namespace literals
    {
        static inline Q_Hz<long double> operator "" _Hz_ (long double _v) {
            return Q_Hz<long double>(_v); }
        static inline Q_Hz<long double> operator "" _Hz_ (unsigned long long int _v) {
            return Q_Hz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dHz"
//
    struct dHz
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dHz";
        }
    };
    template<typename Value = long double>
    using Q_dHz = units::Quantity<Value, dHz>;
    namespace literals
    {
        static inline Q_dHz<long double> operator "" _dHz_ (long double _v) {
            return Q_dHz<long double>(_v); }
        static inline Q_dHz<long double> operator "" _dHz_ (unsigned long long int _v) {
            return Q_dHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cHz"
//
    struct cHz
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cHz";
        }
    };
    template<typename Value = long double>
    using Q_cHz = units::Quantity<Value, cHz>;
    namespace literals
    {
        static inline Q_cHz<long double> operator "" _cHz_ (long double _v) {
            return Q_cHz<long double>(_v); }
        static inline Q_cHz<long double> operator "" _cHz_ (unsigned long long int _v) {
            return Q_cHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mHz"
//
    struct mHz
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mHz";
        }
    };
    template<typename Value = long double>
    using Q_mHz = units::Quantity<Value, mHz>;
    namespace literals
    {
        static inline Q_mHz<long double> operator "" _mHz_ (long double _v) {
            return Q_mHz<long double>(_v); }
        static inline Q_mHz<long double> operator "" _mHz_ (unsigned long long int _v) {
            return Q_mHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uHz"
//
    struct uHz
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uHz";
        }
    };
    template<typename Value = long double>
    using Q_uHz = units::Quantity<Value, uHz>;
    namespace literals
    {
        static inline Q_uHz<long double> operator "" _uHz_ (long double _v) {
            return Q_uHz<long double>(_v); }
        static inline Q_uHz<long double> operator "" _uHz_ (unsigned long long int _v) {
            return Q_uHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nHz"
//
    struct nHz
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nHz";
        }
    };
    template<typename Value = long double>
    using Q_nHz = units::Quantity<Value, nHz>;
    namespace literals
    {
        static inline Q_nHz<long double> operator "" _nHz_ (long double _v) {
            return Q_nHz<long double>(_v); }
        static inline Q_nHz<long double> operator "" _nHz_ (unsigned long long int _v) {
            return Q_nHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pHz"
//
    struct pHz
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Frequency;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pHz;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pHz";
        }
    };
    template<typename Value = long double>
    using Q_pHz = units::Quantity<Value, pHz>;
    namespace literals
    {
        static inline Q_pHz<long double> operator "" _pHz_ (long double _v) {
            return Q_pHz<long double>(_v); }
        static inline Q_pHz<long double> operator "" _pHz_ (unsigned long long int _v) {
            return Q_pHz<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tm_per_s"
//
    struct Tm_per_s
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Tm_per_s = units::Quantity<Value, Tm_per_s>;
    namespace literals
    {
        static inline Q_Tm_per_s<long double> operator "" _Tm_per_s_ (long double _v) {
            return Q_Tm_per_s<long double>(_v); }
        static inline Q_Tm_per_s<long double> operator "" _Tm_per_s_ (unsigned long long int _v) {
            return Q_Tm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gm_per_s"
//
    struct Gm_per_s
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Gm_per_s = units::Quantity<Value, Gm_per_s>;
    namespace literals
    {
        static inline Q_Gm_per_s<long double> operator "" _Gm_per_s_ (long double _v) {
            return Q_Gm_per_s<long double>(_v); }
        static inline Q_Gm_per_s<long double> operator "" _Gm_per_s_ (unsigned long long int _v) {
            return Q_Gm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mm_per_s"
//
    struct Mm_per_s
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Mm_per_s = units::Quantity<Value, Mm_per_s>;
    namespace literals
    {
        static inline Q_Mm_per_s<long double> operator "" _Mm_per_s_ (long double _v) {
            return Q_Mm_per_s<long double>(_v); }
        static inline Q_Mm_per_s<long double> operator "" _Mm_per_s_ (unsigned long long int _v) {
            return Q_Mm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "km_per_s"
//
    struct km_per_s
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km_per_s";
        }
    };
    template<typename Value = long double>
    using Q_km_per_s = units::Quantity<Value, km_per_s>;
    namespace literals
    {
        static inline Q_km_per_s<long double> operator "" _km_per_s_ (long double _v) {
            return Q_km_per_s<long double>(_v); }
        static inline Q_km_per_s<long double> operator "" _km_per_s_ (unsigned long long int _v) {
            return Q_km_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hm_per_s"
//
    struct hm_per_s
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_hm_per_s = units::Quantity<Value, hm_per_s>;
    namespace literals
    {
        static inline Q_hm_per_s<long double> operator "" _hm_per_s_ (long double _v) {
            return Q_hm_per_s<long double>(_v); }
        static inline Q_hm_per_s<long double> operator "" _hm_per_s_ (unsigned long long int _v) {
            return Q_hm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dam_per_s"
//
    struct dam_per_s
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dam_per_s = units::Quantity<Value, dam_per_s>;
    namespace literals
    {
        static inline Q_dam_per_s<long double> operator "" _dam_per_s_ (long double _v) {
            return Q_dam_per_s<long double>(_v); }
        static inline Q_dam_per_s<long double> operator "" _dam_per_s_ (unsigned long long int _v) {
            return Q_dam_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "m_per_s"
//
    struct m_per_s
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m_per_s";
        }
    };
    template<typename Value = long double>
    using Q_m_per_s = units::Quantity<Value, m_per_s>;
    namespace literals
    {
        static inline Q_m_per_s<long double> operator "" _m_per_s_ (long double _v) {
            return Q_m_per_s<long double>(_v); }
        static inline Q_m_per_s<long double> operator "" _m_per_s_ (unsigned long long int _v) {
            return Q_m_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dm_per_s"
//
    struct dm_per_s
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dm_per_s = units::Quantity<Value, dm_per_s>;
    namespace literals
    {
        static inline Q_dm_per_s<long double> operator "" _dm_per_s_ (long double _v) {
            return Q_dm_per_s<long double>(_v); }
        static inline Q_dm_per_s<long double> operator "" _dm_per_s_ (unsigned long long int _v) {
            return Q_dm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cm_per_s"
//
    struct cm_per_s
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_cm_per_s = units::Quantity<Value, cm_per_s>;
    namespace literals
    {
        static inline Q_cm_per_s<long double> operator "" _cm_per_s_ (long double _v) {
            return Q_cm_per_s<long double>(_v); }
        static inline Q_cm_per_s<long double> operator "" _cm_per_s_ (unsigned long long int _v) {
            return Q_cm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mm_per_s"
//
    struct mm_per_s
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_mm_per_s = units::Quantity<Value, mm_per_s>;
    namespace literals
    {
        static inline Q_mm_per_s<long double> operator "" _mm_per_s_ (long double _v) {
            return Q_mm_per_s<long double>(_v); }
        static inline Q_mm_per_s<long double> operator "" _mm_per_s_ (unsigned long long int _v) {
            return Q_mm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "um_per_s"
//
    struct um_per_s
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = um_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "um_per_s";
        }
    };
    template<typename Value = long double>
    using Q_um_per_s = units::Quantity<Value, um_per_s>;
    namespace literals
    {
        static inline Q_um_per_s<long double> operator "" _um_per_s_ (long double _v) {
            return Q_um_per_s<long double>(_v); }
        static inline Q_um_per_s<long double> operator "" _um_per_s_ (unsigned long long int _v) {
            return Q_um_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nm_per_s"
//
    struct nm_per_s
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_nm_per_s = units::Quantity<Value, nm_per_s>;
    namespace literals
    {
        static inline Q_nm_per_s<long double> operator "" _nm_per_s_ (long double _v) {
            return Q_nm_per_s<long double>(_v); }
        static inline Q_nm_per_s<long double> operator "" _nm_per_s_ (unsigned long long int _v) {
            return Q_nm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pm_per_s"
//
    struct pm_per_s
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pm_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pm_per_s";
        }
    };
    template<typename Value = long double>
    using Q_pm_per_s = units::Quantity<Value, pm_per_s>;
    namespace literals
    {
        static inline Q_pm_per_s<long double> operator "" _pm_per_s_ (long double _v) {
            return Q_pm_per_s<long double>(_v); }
        static inline Q_pm_per_s<long double> operator "" _pm_per_s_ (unsigned long long int _v) {
            return Q_pm_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kmph"
//
    struct kmph
    {
        using factor_t = std::ratio<9, 25>; // approx. 0.36
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kmph;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kmph";
        }
    };
    template<typename Value = long double>
    using Q_kmph = units::Quantity<Value, kmph>;
    namespace literals
    {
        static inline Q_kmph<long double> operator "" _kmph_ (long double _v) {
            return Q_kmph<long double>(_v); }
        static inline Q_kmph<long double> operator "" _kmph_ (unsigned long long int _v) {
            return Q_kmph<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mph"
//
    struct mph
    {
        using factor_t = std::ratio<8711, 19486>; // approx. 0.447039
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mph;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mph";
        }
    };
    template<typename Value = long double>
    using Q_mph = units::Quantity<Value, mph>;
    namespace literals
    {
        static inline Q_mph<long double> operator "" _mph_ (long double _v) {
            return Q_mph<long double>(_v); }
        static inline Q_mph<long double> operator "" _mph_ (unsigned long long int _v) {
            return Q_mph<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kt"
//
    struct kt
    {
        using factor_t = std::ratio<643, 1250>; // approx. 0.5144
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kt;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kt";
        }
    };
    template<typename Value = long double>
    using Q_kt = units::Quantity<Value, kt>;
    namespace literals
    {
        static inline Q_kt<long double> operator "" _kt_ (long double _v) {
            return Q_kt<long double>(_v); }
        static inline Q_kt<long double> operator "" _kt_ (unsigned long long int _v) {
            return Q_kt<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mi_per_s"
//
    struct mi_per_s
    {
        using factor_t = std::ratio<201168, 125>; // approx. 1609.34
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi_per_s";
        }
    };
    template<typename Value = long double>
    using Q_mi_per_s = units::Quantity<Value, mi_per_s>;
    namespace literals
    {
        static inline Q_mi_per_s<long double> operator "" _mi_per_s_ (long double _v) {
            return Q_mi_per_s<long double>(_v); }
        static inline Q_mi_per_s<long double> operator "" _mi_per_s_ (unsigned long long int _v) {
            return Q_mi_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "yd_per_s"
//
    struct yd_per_s
    {
        using factor_t = std::ratio<1143, 1250>; // approx. 0.9144
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd_per_s";
        }
    };
    template<typename Value = long double>
    using Q_yd_per_s = units::Quantity<Value, yd_per_s>;
    namespace literals
    {
        static inline Q_yd_per_s<long double> operator "" _yd_per_s_ (long double _v) {
            return Q_yd_per_s<long double>(_v); }
        static inline Q_yd_per_s<long double> operator "" _yd_per_s_ (unsigned long long int _v) {
            return Q_yd_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "fps"
//
    struct fps
    {
        using factor_t = std::ratio<381, 1250>; // approx. 0.3048
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = fps;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "fps";
        }
    };
    template<typename Value = long double>
    using Q_fps = units::Quantity<Value, fps>;
    namespace literals
    {
        static inline Q_fps<long double> operator "" _fps_ (long double _v) {
            return Q_fps<long double>(_v); }
        static inline Q_fps<long double> operator "" _fps_ (unsigned long long int _v) {
            return Q_fps<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "in_per_s"
//
    struct in_per_s
    {
        using factor_t = std::ratio<127, 5000>; // approx. 0.0254
        using dimensions_t = dimensions::Velocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in_per_s";
        }
    };
    template<typename Value = long double>
    using Q_in_per_s = units::Quantity<Value, in_per_s>;
    namespace literals
    {
        static inline Q_in_per_s<long double> operator "" _in_per_s_ (long double _v) {
            return Q_in_per_s<long double>(_v); }
        static inline Q_in_per_s<long double> operator "" _in_per_s_ (unsigned long long int _v) {
            return Q_in_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tm_per_s2"
//
    struct Tm_per_s2
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Tm_per_s2 = units::Quantity<Value, Tm_per_s2>;
    namespace literals
    {
        static inline Q_Tm_per_s2<long double> operator "" _Tm_per_s2_ (long double _v) {
            return Q_Tm_per_s2<long double>(_v); }
        static inline Q_Tm_per_s2<long double> operator "" _Tm_per_s2_ (unsigned long long int _v) {
            return Q_Tm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gm_per_s2"
//
    struct Gm_per_s2
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Gm_per_s2 = units::Quantity<Value, Gm_per_s2>;
    namespace literals
    {
        static inline Q_Gm_per_s2<long double> operator "" _Gm_per_s2_ (long double _v) {
            return Q_Gm_per_s2<long double>(_v); }
        static inline Q_Gm_per_s2<long double> operator "" _Gm_per_s2_ (unsigned long long int _v) {
            return Q_Gm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mm_per_s2"
//
    struct Mm_per_s2
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_Mm_per_s2 = units::Quantity<Value, Mm_per_s2>;
    namespace literals
    {
        static inline Q_Mm_per_s2<long double> operator "" _Mm_per_s2_ (long double _v) {
            return Q_Mm_per_s2<long double>(_v); }
        static inline Q_Mm_per_s2<long double> operator "" _Mm_per_s2_ (unsigned long long int _v) {
            return Q_Mm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "km_per_s2"
//
    struct km_per_s2
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_km_per_s2 = units::Quantity<Value, km_per_s2>;
    namespace literals
    {
        static inline Q_km_per_s2<long double> operator "" _km_per_s2_ (long double _v) {
            return Q_km_per_s2<long double>(_v); }
        static inline Q_km_per_s2<long double> operator "" _km_per_s2_ (unsigned long long int _v) {
            return Q_km_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hm_per_s2"
//
    struct hm_per_s2
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_hm_per_s2 = units::Quantity<Value, hm_per_s2>;
    namespace literals
    {
        static inline Q_hm_per_s2<long double> operator "" _hm_per_s2_ (long double _v) {
            return Q_hm_per_s2<long double>(_v); }
        static inline Q_hm_per_s2<long double> operator "" _hm_per_s2_ (unsigned long long int _v) {
            return Q_hm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dam_per_s2"
//
    struct dam_per_s2
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_dam_per_s2 = units::Quantity<Value, dam_per_s2>;
    namespace literals
    {
        static inline Q_dam_per_s2<long double> operator "" _dam_per_s2_ (long double _v) {
            return Q_dam_per_s2<long double>(_v); }
        static inline Q_dam_per_s2<long double> operator "" _dam_per_s2_ (unsigned long long int _v) {
            return Q_dam_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "m_per_s2"
//
    struct m_per_s2
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_m_per_s2 = units::Quantity<Value, m_per_s2>;
    namespace literals
    {
        static inline Q_m_per_s2<long double> operator "" _m_per_s2_ (long double _v) {
            return Q_m_per_s2<long double>(_v); }
        static inline Q_m_per_s2<long double> operator "" _m_per_s2_ (unsigned long long int _v) {
            return Q_m_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dm_per_s2"
//
    struct dm_per_s2
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_dm_per_s2 = units::Quantity<Value, dm_per_s2>;
    namespace literals
    {
        static inline Q_dm_per_s2<long double> operator "" _dm_per_s2_ (long double _v) {
            return Q_dm_per_s2<long double>(_v); }
        static inline Q_dm_per_s2<long double> operator "" _dm_per_s2_ (unsigned long long int _v) {
            return Q_dm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cm_per_s2"
//
    struct cm_per_s2
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_cm_per_s2 = units::Quantity<Value, cm_per_s2>;
    namespace literals
    {
        static inline Q_cm_per_s2<long double> operator "" _cm_per_s2_ (long double _v) {
            return Q_cm_per_s2<long double>(_v); }
        static inline Q_cm_per_s2<long double> operator "" _cm_per_s2_ (unsigned long long int _v) {
            return Q_cm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mm_per_s2"
//
    struct mm_per_s2
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_mm_per_s2 = units::Quantity<Value, mm_per_s2>;
    namespace literals
    {
        static inline Q_mm_per_s2<long double> operator "" _mm_per_s2_ (long double _v) {
            return Q_mm_per_s2<long double>(_v); }
        static inline Q_mm_per_s2<long double> operator "" _mm_per_s2_ (unsigned long long int _v) {
            return Q_mm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "um_per_s2"
//
    struct um_per_s2
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = um_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "um_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_um_per_s2 = units::Quantity<Value, um_per_s2>;
    namespace literals
    {
        static inline Q_um_per_s2<long double> operator "" _um_per_s2_ (long double _v) {
            return Q_um_per_s2<long double>(_v); }
        static inline Q_um_per_s2<long double> operator "" _um_per_s2_ (unsigned long long int _v) {
            return Q_um_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nm_per_s2"
//
    struct nm_per_s2
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_nm_per_s2 = units::Quantity<Value, nm_per_s2>;
    namespace literals
    {
        static inline Q_nm_per_s2<long double> operator "" _nm_per_s2_ (long double _v) {
            return Q_nm_per_s2<long double>(_v); }
        static inline Q_nm_per_s2<long double> operator "" _nm_per_s2_ (unsigned long long int _v) {
            return Q_nm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pm_per_s2"
//
    struct pm_per_s2
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pm_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pm_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_pm_per_s2 = units::Quantity<Value, pm_per_s2>;
    namespace literals
    {
        static inline Q_pm_per_s2<long double> operator "" _pm_per_s2_ (long double _v) {
            return Q_pm_per_s2<long double>(_v); }
        static inline Q_pm_per_s2<long double> operator "" _pm_per_s2_ (unsigned long long int _v) {
            return Q_pm_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mi_per_s2"
//
    struct mi_per_s2
    {
        using factor_t = std::ratio<201168, 125>; // approx. 1609.34
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_mi_per_s2 = units::Quantity<Value, mi_per_s2>;
    namespace literals
    {
        static inline Q_mi_per_s2<long double> operator "" _mi_per_s2_ (long double _v) {
            return Q_mi_per_s2<long double>(_v); }
        static inline Q_mi_per_s2<long double> operator "" _mi_per_s2_ (unsigned long long int _v) {
            return Q_mi_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "yd_per_s2"
//
    struct yd_per_s2
    {
        using factor_t = std::ratio<1143, 1250>; // approx. 0.9144
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_yd_per_s2 = units::Quantity<Value, yd_per_s2>;
    namespace literals
    {
        static inline Q_yd_per_s2<long double> operator "" _yd_per_s2_ (long double _v) {
            return Q_yd_per_s2<long double>(_v); }
        static inline Q_yd_per_s2<long double> operator "" _yd_per_s2_ (unsigned long long int _v) {
            return Q_yd_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ft_per_s2"
//
    struct ft_per_s2
    {
        using factor_t = std::ratio<381, 1250>; // approx. 0.3048
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_ft_per_s2 = units::Quantity<Value, ft_per_s2>;
    namespace literals
    {
        static inline Q_ft_per_s2<long double> operator "" _ft_per_s2_ (long double _v) {
            return Q_ft_per_s2<long double>(_v); }
        static inline Q_ft_per_s2<long double> operator "" _ft_per_s2_ (unsigned long long int _v) {
            return Q_ft_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "in_per_s2"
//
    struct in_per_s2
    {
        using factor_t = std::ratio<127, 5000>; // approx. 0.0254
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_in_per_s2 = units::Quantity<Value, in_per_s2>;
    namespace literals
    {
        static inline Q_in_per_s2<long double> operator "" _in_per_s2_ (long double _v) {
            return Q_in_per_s2<long double>(_v); }
        static inline Q_in_per_s2<long double> operator "" _in_per_s2_ (unsigned long long int _v) {
            return Q_in_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Ggees"
//
    struct Ggees
    {
        using factor_t = std::ratio<9806650000, 1>; // approx. 9.80665e+09
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ggees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ggees";
        }
    };
    template<typename Value = long double>
    using Q_Ggees = units::Quantity<Value, Ggees>;
    namespace literals
    {
        static inline Q_Ggees<long double> operator "" _Ggees_ (long double _v) {
            return Q_Ggees<long double>(_v); }
        static inline Q_Ggees<long double> operator "" _Ggees_ (unsigned long long int _v) {
            return Q_Ggees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mgees"
//
    struct Mgees
    {
        using factor_t = std::ratio<9806650, 1>; // approx. 9.80665e+06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mgees";
        }
    };
    template<typename Value = long double>
    using Q_Mgees = units::Quantity<Value, Mgees>;
    namespace literals
    {
        static inline Q_Mgees<long double> operator "" _Mgees_ (long double _v) {
            return Q_Mgees<long double>(_v); }
        static inline Q_Mgees<long double> operator "" _Mgees_ (unsigned long long int _v) {
            return Q_Mgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kgees"
//
    struct kgees
    {
        using factor_t = std::ratio<196133, 20>; // approx. 9806.65
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kgees";
        }
    };
    template<typename Value = long double>
    using Q_kgees = units::Quantity<Value, kgees>;
    namespace literals
    {
        static inline Q_kgees<long double> operator "" _kgees_ (long double _v) {
            return Q_kgees<long double>(_v); }
        static inline Q_kgees<long double> operator "" _kgees_ (unsigned long long int _v) {
            return Q_kgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hgees"
//
    struct hgees
    {
        using factor_t = std::ratio<196133, 200>; // approx. 980.665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hgees";
        }
    };
    template<typename Value = long double>
    using Q_hgees = units::Quantity<Value, hgees>;
    namespace literals
    {
        static inline Q_hgees<long double> operator "" _hgees_ (long double _v) {
            return Q_hgees<long double>(_v); }
        static inline Q_hgees<long double> operator "" _hgees_ (unsigned long long int _v) {
            return Q_hgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dagees"
//
    struct dagees
    {
        using factor_t = std::ratio<78159, 797>; // approx. 98.0665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dagees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dagees";
        }
    };
    template<typename Value = long double>
    using Q_dagees = units::Quantity<Value, dagees>;
    namespace literals
    {
        static inline Q_dagees<long double> operator "" _dagees_ (long double _v) {
            return Q_dagees<long double>(_v); }
        static inline Q_dagees<long double> operator "" _dagees_ (unsigned long long int _v) {
            return Q_dagees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "gees"
//
    struct gees
    {
        using factor_t = std::ratio<51024, 5203>; // approx. 9.80665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = gees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "gees";
        }
    };
    template<typename Value = long double>
    using Q_gees = units::Quantity<Value, gees>;
    namespace literals
    {
        static inline Q_gees<long double> operator "" _gees_ (long double _v) {
            return Q_gees<long double>(_v); }
        static inline Q_gees<long double> operator "" _gees_ (unsigned long long int _v) {
            return Q_gees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dgees"
//
    struct dgees
    {
        using factor_t = std::ratio<6695, 6827>; // approx. 0.980665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dgees";
        }
    };
    template<typename Value = long double>
    using Q_dgees = units::Quantity<Value, dgees>;
    namespace literals
    {
        static inline Q_dgees<long double> operator "" _dgees_ (long double _v) {
            return Q_dgees<long double>(_v); }
        static inline Q_dgees<long double> operator "" _dgees_ (unsigned long long int _v) {
            return Q_dgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cgees"
//
    struct cgees
    {
        using factor_t = std::ratio<8739, 89113>; // approx. 0.0980665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cgees";
        }
    };
    template<typename Value = long double>
    using Q_cgees = units::Quantity<Value, cgees>;
    namespace literals
    {
        static inline Q_cgees<long double> operator "" _cgees_ (long double _v) {
            return Q_cgees<long double>(_v); }
        static inline Q_cgees<long double> operator "" _cgees_ (unsigned long long int _v) {
            return Q_cgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mgees"
//
    struct mgees
    {
        using factor_t = std::ratio<740, 75459>; // approx. 0.00980665
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mgees";
        }
    };
    template<typename Value = long double>
    using Q_mgees = units::Quantity<Value, mgees>;
    namespace literals
    {
        static inline Q_mgees<long double> operator "" _mgees_ (long double _v) {
            return Q_mgees<long double>(_v); }
        static inline Q_mgees<long double> operator "" _mgees_ (unsigned long long int _v) {
            return Q_mgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ugees"
//
    struct ugees
    {
        using factor_t = std::ratio<66, 6730127>; // approx. 9.80665e-06
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ugees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ugees";
        }
    };
    template<typename Value = long double>
    using Q_ugees = units::Quantity<Value, ugees>;
    namespace literals
    {
        static inline Q_ugees<long double> operator "" _ugees_ (long double _v) {
            return Q_ugees<long double>(_v); }
        static inline Q_ugees<long double> operator "" _ugees_ (unsigned long long int _v) {
            return Q_ugees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ngees"
//
    struct ngees
    {
        using factor_t = std::ratio<7, 713801349>; // approx. 9.80665e-09
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ngees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ngees";
        }
    };
    template<typename Value = long double>
    using Q_ngees = units::Quantity<Value, ngees>;
    namespace literals
    {
        static inline Q_ngees<long double> operator "" _ngees_ (long double _v) {
            return Q_ngees<long double>(_v); }
        static inline Q_ngees<long double> operator "" _ngees_ (unsigned long long int _v) {
            return Q_ngees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pgees"
//
    struct pgees
    {
        using factor_t = std::ratio<5, 509858106489>; // approx. 9.80665e-12
        using dimensions_t = dimensions::Acceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pgees;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pgees";
        }
    };
    template<typename Value = long double>
    using Q_pgees = units::Quantity<Value, pgees>;
    namespace literals
    {
        static inline Q_pgees<long double> operator "" _pgees_ (long double _v) {
            return Q_pgees<long double>(_v); }
        static inline Q_pgees<long double> operator "" _pgees_ (unsigned long long int _v) {
            return Q_pgees<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tm_per_s3"
//
    struct Tm_per_s3
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Tm_per_s3 = units::Quantity<Value, Tm_per_s3>;
    namespace literals
    {
        static inline Q_Tm_per_s3<long double> operator "" _Tm_per_s3_ (long double _v) {
            return Q_Tm_per_s3<long double>(_v); }
        static inline Q_Tm_per_s3<long double> operator "" _Tm_per_s3_ (unsigned long long int _v) {
            return Q_Tm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gm_per_s3"
//
    struct Gm_per_s3
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Gm_per_s3 = units::Quantity<Value, Gm_per_s3>;
    namespace literals
    {
        static inline Q_Gm_per_s3<long double> operator "" _Gm_per_s3_ (long double _v) {
            return Q_Gm_per_s3<long double>(_v); }
        static inline Q_Gm_per_s3<long double> operator "" _Gm_per_s3_ (unsigned long long int _v) {
            return Q_Gm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mm_per_s3"
//
    struct Mm_per_s3
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_Mm_per_s3 = units::Quantity<Value, Mm_per_s3>;
    namespace literals
    {
        static inline Q_Mm_per_s3<long double> operator "" _Mm_per_s3_ (long double _v) {
            return Q_Mm_per_s3<long double>(_v); }
        static inline Q_Mm_per_s3<long double> operator "" _Mm_per_s3_ (unsigned long long int _v) {
            return Q_Mm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "km_per_s3"
//
    struct km_per_s3
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = km_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "km_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_km_per_s3 = units::Quantity<Value, km_per_s3>;
    namespace literals
    {
        static inline Q_km_per_s3<long double> operator "" _km_per_s3_ (long double _v) {
            return Q_km_per_s3<long double>(_v); }
        static inline Q_km_per_s3<long double> operator "" _km_per_s3_ (unsigned long long int _v) {
            return Q_km_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hm_per_s3"
//
    struct hm_per_s3
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_hm_per_s3 = units::Quantity<Value, hm_per_s3>;
    namespace literals
    {
        static inline Q_hm_per_s3<long double> operator "" _hm_per_s3_ (long double _v) {
            return Q_hm_per_s3<long double>(_v); }
        static inline Q_hm_per_s3<long double> operator "" _hm_per_s3_ (unsigned long long int _v) {
            return Q_hm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dam_per_s3"
//
    struct dam_per_s3
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dam_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dam_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_dam_per_s3 = units::Quantity<Value, dam_per_s3>;
    namespace literals
    {
        static inline Q_dam_per_s3<long double> operator "" _dam_per_s3_ (long double _v) {
            return Q_dam_per_s3<long double>(_v); }
        static inline Q_dam_per_s3<long double> operator "" _dam_per_s3_ (unsigned long long int _v) {
            return Q_dam_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "m_per_s3"
//
    struct m_per_s3
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = m_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "m_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_m_per_s3 = units::Quantity<Value, m_per_s3>;
    namespace literals
    {
        static inline Q_m_per_s3<long double> operator "" _m_per_s3_ (long double _v) {
            return Q_m_per_s3<long double>(_v); }
        static inline Q_m_per_s3<long double> operator "" _m_per_s3_ (unsigned long long int _v) {
            return Q_m_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dm_per_s3"
//
    struct dm_per_s3
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_dm_per_s3 = units::Quantity<Value, dm_per_s3>;
    namespace literals
    {
        static inline Q_dm_per_s3<long double> operator "" _dm_per_s3_ (long double _v) {
            return Q_dm_per_s3<long double>(_v); }
        static inline Q_dm_per_s3<long double> operator "" _dm_per_s3_ (unsigned long long int _v) {
            return Q_dm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cm_per_s3"
//
    struct cm_per_s3
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_cm_per_s3 = units::Quantity<Value, cm_per_s3>;
    namespace literals
    {
        static inline Q_cm_per_s3<long double> operator "" _cm_per_s3_ (long double _v) {
            return Q_cm_per_s3<long double>(_v); }
        static inline Q_cm_per_s3<long double> operator "" _cm_per_s3_ (unsigned long long int _v) {
            return Q_cm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mm_per_s3"
//
    struct mm_per_s3
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_mm_per_s3 = units::Quantity<Value, mm_per_s3>;
    namespace literals
    {
        static inline Q_mm_per_s3<long double> operator "" _mm_per_s3_ (long double _v) {
            return Q_mm_per_s3<long double>(_v); }
        static inline Q_mm_per_s3<long double> operator "" _mm_per_s3_ (unsigned long long int _v) {
            return Q_mm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "um_per_s3"
//
    struct um_per_s3
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = um_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "um_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_um_per_s3 = units::Quantity<Value, um_per_s3>;
    namespace literals
    {
        static inline Q_um_per_s3<long double> operator "" _um_per_s3_ (long double _v) {
            return Q_um_per_s3<long double>(_v); }
        static inline Q_um_per_s3<long double> operator "" _um_per_s3_ (unsigned long long int _v) {
            return Q_um_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nm_per_s3"
//
    struct nm_per_s3
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_nm_per_s3 = units::Quantity<Value, nm_per_s3>;
    namespace literals
    {
        static inline Q_nm_per_s3<long double> operator "" _nm_per_s3_ (long double _v) {
            return Q_nm_per_s3<long double>(_v); }
        static inline Q_nm_per_s3<long double> operator "" _nm_per_s3_ (unsigned long long int _v) {
            return Q_nm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pm_per_s3"
//
    struct pm_per_s3
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pm_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pm_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_pm_per_s3 = units::Quantity<Value, pm_per_s3>;
    namespace literals
    {
        static inline Q_pm_per_s3<long double> operator "" _pm_per_s3_ (long double _v) {
            return Q_pm_per_s3<long double>(_v); }
        static inline Q_pm_per_s3<long double> operator "" _pm_per_s3_ (unsigned long long int _v) {
            return Q_pm_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mi_per_s3"
//
    struct mi_per_s3
    {
        using factor_t = std::ratio<201168, 125>; // approx. 1609.34
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mi_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mi_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_mi_per_s3 = units::Quantity<Value, mi_per_s3>;
    namespace literals
    {
        static inline Q_mi_per_s3<long double> operator "" _mi_per_s3_ (long double _v) {
            return Q_mi_per_s3<long double>(_v); }
        static inline Q_mi_per_s3<long double> operator "" _mi_per_s3_ (unsigned long long int _v) {
            return Q_mi_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "yd_per_s3"
//
    struct yd_per_s3
    {
        using factor_t = std::ratio<1143, 1250>; // approx. 0.9144
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = yd_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "yd_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_yd_per_s3 = units::Quantity<Value, yd_per_s3>;
    namespace literals
    {
        static inline Q_yd_per_s3<long double> operator "" _yd_per_s3_ (long double _v) {
            return Q_yd_per_s3<long double>(_v); }
        static inline Q_yd_per_s3<long double> operator "" _yd_per_s3_ (unsigned long long int _v) {
            return Q_yd_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ft_per_s3"
//
    struct ft_per_s3
    {
        using factor_t = std::ratio<381, 1250>; // approx. 0.3048
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ft_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ft_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_ft_per_s3 = units::Quantity<Value, ft_per_s3>;
    namespace literals
    {
        static inline Q_ft_per_s3<long double> operator "" _ft_per_s3_ (long double _v) {
            return Q_ft_per_s3<long double>(_v); }
        static inline Q_ft_per_s3<long double> operator "" _ft_per_s3_ (unsigned long long int _v) {
            return Q_ft_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "in_per_s3"
//
    struct in_per_s3
    {
        using factor_t = std::ratio<127, 5000>; // approx. 0.0254
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = in_per_s3;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "in_per_s3";
        }
    };
    template<typename Value = long double>
    using Q_in_per_s3 = units::Quantity<Value, in_per_s3>;
    namespace literals
    {
        static inline Q_in_per_s3<long double> operator "" _in_per_s3_ (long double _v) {
            return Q_in_per_s3<long double>(_v); }
        static inline Q_in_per_s3<long double> operator "" _in_per_s3_ (unsigned long long int _v) {
            return Q_in_per_s3<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Ggees_per_s"
//
    struct Ggees_per_s
    {
        using factor_t = std::ratio<9806650000, 1>; // approx. 9.80665e+09
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Ggees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Ggees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Ggees_per_s = units::Quantity<Value, Ggees_per_s>;
    namespace literals
    {
        static inline Q_Ggees_per_s<long double> operator "" _Ggees_per_s_ (long double _v) {
            return Q_Ggees_per_s<long double>(_v); }
        static inline Q_Ggees_per_s<long double> operator "" _Ggees_per_s_ (unsigned long long int _v) {
            return Q_Ggees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mgees_per_s"
//
    struct Mgees_per_s
    {
        using factor_t = std::ratio<9806650, 1>; // approx. 9.80665e+06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_Mgees_per_s = units::Quantity<Value, Mgees_per_s>;
    namespace literals
    {
        static inline Q_Mgees_per_s<long double> operator "" _Mgees_per_s_ (long double _v) {
            return Q_Mgees_per_s<long double>(_v); }
        static inline Q_Mgees_per_s<long double> operator "" _Mgees_per_s_ (unsigned long long int _v) {
            return Q_Mgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kgees_per_s"
//
    struct kgees_per_s
    {
        using factor_t = std::ratio<196133, 20>; // approx. 9806.65
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_kgees_per_s = units::Quantity<Value, kgees_per_s>;
    namespace literals
    {
        static inline Q_kgees_per_s<long double> operator "" _kgees_per_s_ (long double _v) {
            return Q_kgees_per_s<long double>(_v); }
        static inline Q_kgees_per_s<long double> operator "" _kgees_per_s_ (unsigned long long int _v) {
            return Q_kgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hgees_per_s"
//
    struct hgees_per_s
    {
        using factor_t = std::ratio<196133, 200>; // approx. 980.665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_hgees_per_s = units::Quantity<Value, hgees_per_s>;
    namespace literals
    {
        static inline Q_hgees_per_s<long double> operator "" _hgees_per_s_ (long double _v) {
            return Q_hgees_per_s<long double>(_v); }
        static inline Q_hgees_per_s<long double> operator "" _hgees_per_s_ (unsigned long long int _v) {
            return Q_hgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dagees_per_s"
//
    struct dagees_per_s
    {
        using factor_t = std::ratio<78159, 797>; // approx. 98.0665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dagees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dagees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dagees_per_s = units::Quantity<Value, dagees_per_s>;
    namespace literals
    {
        static inline Q_dagees_per_s<long double> operator "" _dagees_per_s_ (long double _v) {
            return Q_dagees_per_s<long double>(_v); }
        static inline Q_dagees_per_s<long double> operator "" _dagees_per_s_ (unsigned long long int _v) {
            return Q_dagees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "gees_per_s"
//
    struct gees_per_s
    {
        using factor_t = std::ratio<51024, 5203>; // approx. 9.80665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = gees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "gees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_gees_per_s = units::Quantity<Value, gees_per_s>;
    namespace literals
    {
        static inline Q_gees_per_s<long double> operator "" _gees_per_s_ (long double _v) {
            return Q_gees_per_s<long double>(_v); }
        static inline Q_gees_per_s<long double> operator "" _gees_per_s_ (unsigned long long int _v) {
            return Q_gees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dgees_per_s"
//
    struct dgees_per_s
    {
        using factor_t = std::ratio<6695, 6827>; // approx. 0.980665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_dgees_per_s = units::Quantity<Value, dgees_per_s>;
    namespace literals
    {
        static inline Q_dgees_per_s<long double> operator "" _dgees_per_s_ (long double _v) {
            return Q_dgees_per_s<long double>(_v); }
        static inline Q_dgees_per_s<long double> operator "" _dgees_per_s_ (unsigned long long int _v) {
            return Q_dgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cgees_per_s"
//
    struct cgees_per_s
    {
        using factor_t = std::ratio<8739, 89113>; // approx. 0.0980665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_cgees_per_s = units::Quantity<Value, cgees_per_s>;
    namespace literals
    {
        static inline Q_cgees_per_s<long double> operator "" _cgees_per_s_ (long double _v) {
            return Q_cgees_per_s<long double>(_v); }
        static inline Q_cgees_per_s<long double> operator "" _cgees_per_s_ (unsigned long long int _v) {
            return Q_cgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mgees_per_s"
//
    struct mgees_per_s
    {
        using factor_t = std::ratio<740, 75459>; // approx. 0.00980665
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_mgees_per_s = units::Quantity<Value, mgees_per_s>;
    namespace literals
    {
        static inline Q_mgees_per_s<long double> operator "" _mgees_per_s_ (long double _v) {
            return Q_mgees_per_s<long double>(_v); }
        static inline Q_mgees_per_s<long double> operator "" _mgees_per_s_ (unsigned long long int _v) {
            return Q_mgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ugees_per_s"
//
    struct ugees_per_s
    {
        using factor_t = std::ratio<66, 6730127>; // approx. 9.80665e-06
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ugees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ugees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_ugees_per_s = units::Quantity<Value, ugees_per_s>;
    namespace literals
    {
        static inline Q_ugees_per_s<long double> operator "" _ugees_per_s_ (long double _v) {
            return Q_ugees_per_s<long double>(_v); }
        static inline Q_ugees_per_s<long double> operator "" _ugees_per_s_ (unsigned long long int _v) {
            return Q_ugees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ngees_per_s"
//
    struct ngees_per_s
    {
        using factor_t = std::ratio<7, 713801349>; // approx. 9.80665e-09
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ngees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ngees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_ngees_per_s = units::Quantity<Value, ngees_per_s>;
    namespace literals
    {
        static inline Q_ngees_per_s<long double> operator "" _ngees_per_s_ (long double _v) {
            return Q_ngees_per_s<long double>(_v); }
        static inline Q_ngees_per_s<long double> operator "" _ngees_per_s_ (unsigned long long int _v) {
            return Q_ngees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pgees_per_s"
//
    struct pgees_per_s
    {
        using factor_t = std::ratio<5, 509858106489>; // approx. 9.80665e-12
        using dimensions_t = dimensions::Jerk;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pgees_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pgees_per_s";
        }
    };
    template<typename Value = long double>
    using Q_pgees_per_s = units::Quantity<Value, pgees_per_s>;
    namespace literals
    {
        static inline Q_pgees_per_s<long double> operator "" _pgees_per_s_ (long double _v) {
            return Q_pgees_per_s<long double>(_v); }
        static inline Q_pgees_per_s<long double> operator "" _pgees_per_s_ (unsigned long long int _v) {
            return Q_pgees_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rad"
//
    struct rad
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rad;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rad";
        }
    };
    template<typename Value = long double>
    using Q_rad = units::Quantity<Value, rad>;
    namespace literals
    {
        static inline Q_rad<long double> operator "" _rad_ (long double _v) {
            return Q_rad<long double>(_v); }
        static inline Q_rad<long double> operator "" _rad_ (unsigned long long int _v) {
            return Q_rad<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rev"
//
    struct rev
    {
        using factor_t = std::ratio<31831, 100000>; // approx. 0.31831
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rev;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rev";
        }
    };
    template<typename Value = long double>
    using Q_rev = units::Quantity<Value, rev>;
    namespace literals
    {
        static inline Q_rev<long double> operator "" _rev_ (long double _v) {
            return Q_rev<long double>(_v); }
        static inline Q_rev<long double> operator "" _rev_ (unsigned long long int _v) {
            return Q_rev<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "deg"
//
    struct deg
    {
        using factor_t = std::ratio<1092, 62567>; // approx. 0.0174533
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = deg;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "deg";
        }
    };
    template<typename Value = long double>
    using Q_deg = units::Quantity<Value, deg>;
    namespace literals
    {
        static inline Q_deg<long double> operator "" _deg_ (long double _v) {
            return Q_deg<long double>(_v); }
        static inline Q_deg<long double> operator "" _deg_ (unsigned long long int _v) {
            return Q_deg<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "grad"
//
    struct grad
    {
        using factor_t = std::ratio<1497, 95302>; // approx. 0.015708
        using dimensions_t = dimensions::PlaneAngle;
        using offset_t = std::ratio<0, 1>;
        using relative_t = grad;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "grad";
        }
    };
    template<typename Value = long double>
    using Q_grad = units::Quantity<Value, grad>;
    namespace literals
    {
        static inline Q_grad<long double> operator "" _grad_ (long double _v) {
            return Q_grad<long double>(_v); }
        static inline Q_grad<long double> operator "" _grad_ (unsigned long long int _v) {
            return Q_grad<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rad_per_s"
//
    struct rad_per_s
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rad_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rad_per_s";
        }
    };
    template<typename Value = long double>
    using Q_rad_per_s = units::Quantity<Value, rad_per_s>;
    namespace literals
    {
        static inline Q_rad_per_s<long double> operator "" _rad_per_s_ (long double _v) {
            return Q_rad_per_s<long double>(_v); }
        static inline Q_rad_per_s<long double> operator "" _rad_per_s_ (unsigned long long int _v) {
            return Q_rad_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rev_per_s"
//
    struct rev_per_s
    {
        using factor_t = std::ratio<31831, 100000>; // approx. 0.31831
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rev_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rev_per_s";
        }
    };
    template<typename Value = long double>
    using Q_rev_per_s = units::Quantity<Value, rev_per_s>;
    namespace literals
    {
        static inline Q_rev_per_s<long double> operator "" _rev_per_s_ (long double _v) {
            return Q_rev_per_s<long double>(_v); }
        static inline Q_rev_per_s<long double> operator "" _rev_per_s_ (unsigned long long int _v) {
            return Q_rev_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "deg_per_s"
//
    struct deg_per_s
    {
        using factor_t = std::ratio<1092, 62567>; // approx. 0.0174533
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = deg_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "deg_per_s";
        }
    };
    template<typename Value = long double>
    using Q_deg_per_s = units::Quantity<Value, deg_per_s>;
    namespace literals
    {
        static inline Q_deg_per_s<long double> operator "" _deg_per_s_ (long double _v) {
            return Q_deg_per_s<long double>(_v); }
        static inline Q_deg_per_s<long double> operator "" _deg_per_s_ (unsigned long long int _v) {
            return Q_deg_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "grad_per_s"
//
    struct grad_per_s
    {
        using factor_t = std::ratio<1497, 95302>; // approx. 0.015708
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = grad_per_s;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "grad_per_s";
        }
    };
    template<typename Value = long double>
    using Q_grad_per_s = units::Quantity<Value, grad_per_s>;
    namespace literals
    {
        static inline Q_grad_per_s<long double> operator "" _grad_per_s_ (long double _v) {
            return Q_grad_per_s<long double>(_v); }
        static inline Q_grad_per_s<long double> operator "" _grad_per_s_ (unsigned long long int _v) {
            return Q_grad_per_s<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rpm"
//
    struct rpm
    {
        using factor_t = std::ratio<2323, 437875>; // approx. 0.00530517
        using dimensions_t = dimensions::AngularVelocity;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rpm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rpm";
        }
    };
    template<typename Value = long double>
    using Q_rpm = units::Quantity<Value, rpm>;
    namespace literals
    {
        static inline Q_rpm<long double> operator "" _rpm_ (long double _v) {
            return Q_rpm<long double>(_v); }
        static inline Q_rpm<long double> operator "" _rpm_ (unsigned long long int _v) {
            return Q_rpm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rad_per_s2"
//
    struct rad_per_s2
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rad_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rad_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_rad_per_s2 = units::Quantity<Value, rad_per_s2>;
    namespace literals
    {
        static inline Q_rad_per_s2<long double> operator "" _rad_per_s2_ (long double _v) {
            return Q_rad_per_s2<long double>(_v); }
        static inline Q_rad_per_s2<long double> operator "" _rad_per_s2_ (unsigned long long int _v) {
            return Q_rad_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "rev_per_s2"
//
    struct rev_per_s2
    {
        using factor_t = std::ratio<31831, 100000>; // approx. 0.31831
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = rev_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "rev_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_rev_per_s2 = units::Quantity<Value, rev_per_s2>;
    namespace literals
    {
        static inline Q_rev_per_s2<long double> operator "" _rev_per_s2_ (long double _v) {
            return Q_rev_per_s2<long double>(_v); }
        static inline Q_rev_per_s2<long double> operator "" _rev_per_s2_ (unsigned long long int _v) {
            return Q_rev_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "deg_per_s2"
//
    struct deg_per_s2
    {
        using factor_t = std::ratio<1092, 62567>; // approx. 0.0174533
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = deg_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "deg_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_deg_per_s2 = units::Quantity<Value, deg_per_s2>;
    namespace literals
    {
        static inline Q_deg_per_s2<long double> operator "" _deg_per_s2_ (long double _v) {
            return Q_deg_per_s2<long double>(_v); }
        static inline Q_deg_per_s2<long double> operator "" _deg_per_s2_ (unsigned long long int _v) {
            return Q_deg_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "grad_per_s2"
//
    struct grad_per_s2
    {
        using factor_t = std::ratio<1497, 95302>; // approx. 0.015708
        using dimensions_t = dimensions::AngularAcceleration;
        using offset_t = std::ratio<0, 1>;
        using relative_t = grad_per_s2;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "grad_per_s2";
        }
    };
    template<typename Value = long double>
    using Q_grad_per_s2 = units::Quantity<Value, grad_per_s2>;
    namespace literals
    {
        static inline Q_grad_per_s2<long double> operator "" _grad_per_s2_ (long double _v) {
            return Q_grad_per_s2<long double>(_v); }
        static inline Q_grad_per_s2<long double> operator "" _grad_per_s2_ (unsigned long long int _v) {
            return Q_grad_per_s2<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TdegC"
//
    struct TdegC
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TdegC";
        }
    };
    template<typename Value = long double>
    using Q_TdegC = units::Quantity<Value, TdegC>;
    namespace literals
    {
        static inline Q_TdegC<long double> operator "" _TdegC_ (long double _v) {
            return Q_TdegC<long double>(_v); }
        static inline Q_TdegC<long double> operator "" _TdegC_ (unsigned long long int _v) {
            return Q_TdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TdegC_abs"
//
    struct TdegC_abs
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_TdegC_abs = units::Quantity<Value, TdegC_abs>;
    namespace literals
    {
        static inline Q_TdegC_abs<long double> operator "" _TdegC_abs_ (long double _v) {
            return Q_TdegC_abs<long double>(_v); }
        static inline Q_TdegC_abs<long double> operator "" _TdegC_abs_ (unsigned long long int _v) {
            return Q_TdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GdegC"
//
    struct GdegC
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GdegC";
        }
    };
    template<typename Value = long double>
    using Q_GdegC = units::Quantity<Value, GdegC>;
    namespace literals
    {
        static inline Q_GdegC<long double> operator "" _GdegC_ (long double _v) {
            return Q_GdegC<long double>(_v); }
        static inline Q_GdegC<long double> operator "" _GdegC_ (unsigned long long int _v) {
            return Q_GdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GdegC_abs"
//
    struct GdegC_abs
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_GdegC_abs = units::Quantity<Value, GdegC_abs>;
    namespace literals
    {
        static inline Q_GdegC_abs<long double> operator "" _GdegC_abs_ (long double _v) {
            return Q_GdegC_abs<long double>(_v); }
        static inline Q_GdegC_abs<long double> operator "" _GdegC_abs_ (unsigned long long int _v) {
            return Q_GdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MdegC"
//
    struct MdegC
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MdegC";
        }
    };
    template<typename Value = long double>
    using Q_MdegC = units::Quantity<Value, MdegC>;
    namespace literals
    {
        static inline Q_MdegC<long double> operator "" _MdegC_ (long double _v) {
            return Q_MdegC<long double>(_v); }
        static inline Q_MdegC<long double> operator "" _MdegC_ (unsigned long long int _v) {
            return Q_MdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MdegC_abs"
//
    struct MdegC_abs
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_MdegC_abs = units::Quantity<Value, MdegC_abs>;
    namespace literals
    {
        static inline Q_MdegC_abs<long double> operator "" _MdegC_abs_ (long double _v) {
            return Q_MdegC_abs<long double>(_v); }
        static inline Q_MdegC_abs<long double> operator "" _MdegC_abs_ (unsigned long long int _v) {
            return Q_MdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kdegC"
//
    struct kdegC
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kdegC";
        }
    };
    template<typename Value = long double>
    using Q_kdegC = units::Quantity<Value, kdegC>;
    namespace literals
    {
        static inline Q_kdegC<long double> operator "" _kdegC_ (long double _v) {
            return Q_kdegC<long double>(_v); }
        static inline Q_kdegC<long double> operator "" _kdegC_ (unsigned long long int _v) {
            return Q_kdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kdegC_abs"
//
    struct kdegC_abs
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_kdegC_abs = units::Quantity<Value, kdegC_abs>;
    namespace literals
    {
        static inline Q_kdegC_abs<long double> operator "" _kdegC_abs_ (long double _v) {
            return Q_kdegC_abs<long double>(_v); }
        static inline Q_kdegC_abs<long double> operator "" _kdegC_abs_ (unsigned long long int _v) {
            return Q_kdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hdegC"
//
    struct hdegC
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hdegC";
        }
    };
    template<typename Value = long double>
    using Q_hdegC = units::Quantity<Value, hdegC>;
    namespace literals
    {
        static inline Q_hdegC<long double> operator "" _hdegC_ (long double _v) {
            return Q_hdegC<long double>(_v); }
        static inline Q_hdegC<long double> operator "" _hdegC_ (unsigned long long int _v) {
            return Q_hdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hdegC_abs"
//
    struct hdegC_abs
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_hdegC_abs = units::Quantity<Value, hdegC_abs>;
    namespace literals
    {
        static inline Q_hdegC_abs<long double> operator "" _hdegC_abs_ (long double _v) {
            return Q_hdegC_abs<long double>(_v); }
        static inline Q_hdegC_abs<long double> operator "" _hdegC_abs_ (unsigned long long int _v) {
            return Q_hdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dadegC"
//
    struct dadegC
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dadegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dadegC";
        }
    };
    template<typename Value = long double>
    using Q_dadegC = units::Quantity<Value, dadegC>;
    namespace literals
    {
        static inline Q_dadegC<long double> operator "" _dadegC_ (long double _v) {
            return Q_dadegC<long double>(_v); }
        static inline Q_dadegC<long double> operator "" _dadegC_ (unsigned long long int _v) {
            return Q_dadegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dadegC_abs"
//
    struct dadegC_abs
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dadegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dadegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_dadegC_abs = units::Quantity<Value, dadegC_abs>;
    namespace literals
    {
        static inline Q_dadegC_abs<long double> operator "" _dadegC_abs_ (long double _v) {
            return Q_dadegC_abs<long double>(_v); }
        static inline Q_dadegC_abs<long double> operator "" _dadegC_abs_ (unsigned long long int _v) {
            return Q_dadegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "degC"
//
    struct degC
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = degC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "degC";
        }
    };
    template<typename Value = long double>
    using Q_degC = units::Quantity<Value, degC>;
    namespace literals
    {
        static inline Q_degC<long double> operator "" _degC_ (long double _v) {
            return Q_degC<long double>(_v); }
        static inline Q_degC<long double> operator "" _degC_ (unsigned long long int _v) {
            return Q_degC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "degC_abs"
//
    struct degC_abs
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = degC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "degC_abs";
        }
    };
    template<typename Value = long double>
    using Q_degC_abs = units::Quantity<Value, degC_abs>;
    namespace literals
    {
        static inline Q_degC_abs<long double> operator "" _degC_abs_ (long double _v) {
            return Q_degC_abs<long double>(_v); }
        static inline Q_degC_abs<long double> operator "" _degC_abs_ (unsigned long long int _v) {
            return Q_degC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ddegC"
//
    struct ddegC
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ddegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ddegC";
        }
    };
    template<typename Value = long double>
    using Q_ddegC = units::Quantity<Value, ddegC>;
    namespace literals
    {
        static inline Q_ddegC<long double> operator "" _ddegC_ (long double _v) {
            return Q_ddegC<long double>(_v); }
        static inline Q_ddegC<long double> operator "" _ddegC_ (unsigned long long int _v) {
            return Q_ddegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ddegC_abs"
//
    struct ddegC_abs
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ddegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ddegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_ddegC_abs = units::Quantity<Value, ddegC_abs>;
    namespace literals
    {
        static inline Q_ddegC_abs<long double> operator "" _ddegC_abs_ (long double _v) {
            return Q_ddegC_abs<long double>(_v); }
        static inline Q_ddegC_abs<long double> operator "" _ddegC_abs_ (unsigned long long int _v) {
            return Q_ddegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cdegC"
//
    struct cdegC
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cdegC";
        }
    };
    template<typename Value = long double>
    using Q_cdegC = units::Quantity<Value, cdegC>;
    namespace literals
    {
        static inline Q_cdegC<long double> operator "" _cdegC_ (long double _v) {
            return Q_cdegC<long double>(_v); }
        static inline Q_cdegC<long double> operator "" _cdegC_ (unsigned long long int _v) {
            return Q_cdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cdegC_abs"
//
    struct cdegC_abs
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_cdegC_abs = units::Quantity<Value, cdegC_abs>;
    namespace literals
    {
        static inline Q_cdegC_abs<long double> operator "" _cdegC_abs_ (long double _v) {
            return Q_cdegC_abs<long double>(_v); }
        static inline Q_cdegC_abs<long double> operator "" _cdegC_abs_ (unsigned long long int _v) {
            return Q_cdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mdegC"
//
    struct mdegC
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mdegC";
        }
    };
    template<typename Value = long double>
    using Q_mdegC = units::Quantity<Value, mdegC>;
    namespace literals
    {
        static inline Q_mdegC<long double> operator "" _mdegC_ (long double _v) {
            return Q_mdegC<long double>(_v); }
        static inline Q_mdegC<long double> operator "" _mdegC_ (unsigned long long int _v) {
            return Q_mdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mdegC_abs"
//
    struct mdegC_abs
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_mdegC_abs = units::Quantity<Value, mdegC_abs>;
    namespace literals
    {
        static inline Q_mdegC_abs<long double> operator "" _mdegC_abs_ (long double _v) {
            return Q_mdegC_abs<long double>(_v); }
        static inline Q_mdegC_abs<long double> operator "" _mdegC_abs_ (unsigned long long int _v) {
            return Q_mdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "udegC"
//
    struct udegC
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = udegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "udegC";
        }
    };
    template<typename Value = long double>
    using Q_udegC = units::Quantity<Value, udegC>;
    namespace literals
    {
        static inline Q_udegC<long double> operator "" _udegC_ (long double _v) {
            return Q_udegC<long double>(_v); }
        static inline Q_udegC<long double> operator "" _udegC_ (unsigned long long int _v) {
            return Q_udegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "udegC_abs"
//
    struct udegC_abs
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = udegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "udegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_udegC_abs = units::Quantity<Value, udegC_abs>;
    namespace literals
    {
        static inline Q_udegC_abs<long double> operator "" _udegC_abs_ (long double _v) {
            return Q_udegC_abs<long double>(_v); }
        static inline Q_udegC_abs<long double> operator "" _udegC_abs_ (unsigned long long int _v) {
            return Q_udegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ndegC"
//
    struct ndegC
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ndegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ndegC";
        }
    };
    template<typename Value = long double>
    using Q_ndegC = units::Quantity<Value, ndegC>;
    namespace literals
    {
        static inline Q_ndegC<long double> operator "" _ndegC_ (long double _v) {
            return Q_ndegC<long double>(_v); }
        static inline Q_ndegC<long double> operator "" _ndegC_ (unsigned long long int _v) {
            return Q_ndegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ndegC_abs"
//
    struct ndegC_abs
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ndegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ndegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_ndegC_abs = units::Quantity<Value, ndegC_abs>;
    namespace literals
    {
        static inline Q_ndegC_abs<long double> operator "" _ndegC_abs_ (long double _v) {
            return Q_ndegC_abs<long double>(_v); }
        static inline Q_ndegC_abs<long double> operator "" _ndegC_abs_ (unsigned long long int _v) {
            return Q_ndegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdegC"
//
    struct pdegC
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pdegC;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdegC";
        }
    };
    template<typename Value = long double>
    using Q_pdegC = units::Quantity<Value, pdegC>;
    namespace literals
    {
        static inline Q_pdegC<long double> operator "" _pdegC_ (long double _v) {
            return Q_pdegC<long double>(_v); }
        static inline Q_pdegC<long double> operator "" _pdegC_ (unsigned long long int _v) {
            return Q_pdegC<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdegC_abs"
//
    struct pdegC_abs
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pdegC;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdegC_abs";
        }
    };
    template<typename Value = long double>
    using Q_pdegC_abs = units::Quantity<Value, pdegC_abs>;
    namespace literals
    {
        static inline Q_pdegC_abs<long double> operator "" _pdegC_abs_ (long double _v) {
            return Q_pdegC_abs<long double>(_v); }
        static inline Q_pdegC_abs<long double> operator "" _pdegC_abs_ (unsigned long long int _v) {
            return Q_pdegC_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TK"
//
    struct TK
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = TK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TK";
        }
    };
    template<typename Value = long double>
    using Q_TK = units::Quantity<Value, TK>;
    namespace literals
    {
        static inline Q_TK<long double> operator "" _TK_ (long double _v) {
            return Q_TK<long double>(_v); }
        static inline Q_TK<long double> operator "" _TK_ (unsigned long long int _v) {
            return Q_TK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TK_abs"
//
    struct TK_abs
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = TK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TK_abs";
        }
    };
    template<typename Value = long double>
    using Q_TK_abs = units::Quantity<Value, TK_abs>;
    namespace literals
    {
        static inline Q_TK_abs<long double> operator "" _TK_abs_ (long double _v) {
            return Q_TK_abs<long double>(_v); }
        static inline Q_TK_abs<long double> operator "" _TK_abs_ (unsigned long long int _v) {
            return Q_TK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GK"
//
    struct GK
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = GK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GK";
        }
    };
    template<typename Value = long double>
    using Q_GK = units::Quantity<Value, GK>;
    namespace literals
    {
        static inline Q_GK<long double> operator "" _GK_ (long double _v) {
            return Q_GK<long double>(_v); }
        static inline Q_GK<long double> operator "" _GK_ (unsigned long long int _v) {
            return Q_GK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GK_abs"
//
    struct GK_abs
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = GK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GK_abs";
        }
    };
    template<typename Value = long double>
    using Q_GK_abs = units::Quantity<Value, GK_abs>;
    namespace literals
    {
        static inline Q_GK_abs<long double> operator "" _GK_abs_ (long double _v) {
            return Q_GK_abs<long double>(_v); }
        static inline Q_GK_abs<long double> operator "" _GK_abs_ (unsigned long long int _v) {
            return Q_GK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MK"
//
    struct MK
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = MK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MK";
        }
    };
    template<typename Value = long double>
    using Q_MK = units::Quantity<Value, MK>;
    namespace literals
    {
        static inline Q_MK<long double> operator "" _MK_ (long double _v) {
            return Q_MK<long double>(_v); }
        static inline Q_MK<long double> operator "" _MK_ (unsigned long long int _v) {
            return Q_MK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MK_abs"
//
    struct MK_abs
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = MK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MK_abs";
        }
    };
    template<typename Value = long double>
    using Q_MK_abs = units::Quantity<Value, MK_abs>;
    namespace literals
    {
        static inline Q_MK_abs<long double> operator "" _MK_abs_ (long double _v) {
            return Q_MK_abs<long double>(_v); }
        static inline Q_MK_abs<long double> operator "" _MK_abs_ (unsigned long long int _v) {
            return Q_MK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kK"
//
    struct kK
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = kK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kK";
        }
    };
    template<typename Value = long double>
    using Q_kK = units::Quantity<Value, kK>;
    namespace literals
    {
        static inline Q_kK<long double> operator "" _kK_ (long double _v) {
            return Q_kK<long double>(_v); }
        static inline Q_kK<long double> operator "" _kK_ (unsigned long long int _v) {
            return Q_kK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kK_abs"
//
    struct kK_abs
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = kK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kK_abs";
        }
    };
    template<typename Value = long double>
    using Q_kK_abs = units::Quantity<Value, kK_abs>;
    namespace literals
    {
        static inline Q_kK_abs<long double> operator "" _kK_abs_ (long double _v) {
            return Q_kK_abs<long double>(_v); }
        static inline Q_kK_abs<long double> operator "" _kK_abs_ (unsigned long long int _v) {
            return Q_kK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hK"
//
    struct hK
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = hK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hK";
        }
    };
    template<typename Value = long double>
    using Q_hK = units::Quantity<Value, hK>;
    namespace literals
    {
        static inline Q_hK<long double> operator "" _hK_ (long double _v) {
            return Q_hK<long double>(_v); }
        static inline Q_hK<long double> operator "" _hK_ (unsigned long long int _v) {
            return Q_hK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hK_abs"
//
    struct hK_abs
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = hK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hK_abs";
        }
    };
    template<typename Value = long double>
    using Q_hK_abs = units::Quantity<Value, hK_abs>;
    namespace literals
    {
        static inline Q_hK_abs<long double> operator "" _hK_abs_ (long double _v) {
            return Q_hK_abs<long double>(_v); }
        static inline Q_hK_abs<long double> operator "" _hK_abs_ (unsigned long long int _v) {
            return Q_hK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daK"
//
    struct daK
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = daK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daK";
        }
    };
    template<typename Value = long double>
    using Q_daK = units::Quantity<Value, daK>;
    namespace literals
    {
        static inline Q_daK<long double> operator "" _daK_ (long double _v) {
            return Q_daK<long double>(_v); }
        static inline Q_daK<long double> operator "" _daK_ (unsigned long long int _v) {
            return Q_daK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daK_abs"
//
    struct daK_abs
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = daK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daK_abs";
        }
    };
    template<typename Value = long double>
    using Q_daK_abs = units::Quantity<Value, daK_abs>;
    namespace literals
    {
        static inline Q_daK_abs<long double> operator "" _daK_abs_ (long double _v) {
            return Q_daK_abs<long double>(_v); }
        static inline Q_daK_abs<long double> operator "" _daK_abs_ (unsigned long long int _v) {
            return Q_daK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "K"
//
    struct K
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = K;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "K";
        }
    };
    template<typename Value = long double>
    using Q_K = units::Quantity<Value, K>;
    namespace literals
    {
        static inline Q_K<long double> operator "" _K_ (long double _v) {
            return Q_K<long double>(_v); }
        static inline Q_K<long double> operator "" _K_ (unsigned long long int _v) {
            return Q_K<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "K_abs"
//
    struct K_abs
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = K;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "K_abs";
        }
    };
    template<typename Value = long double>
    using Q_K_abs = units::Quantity<Value, K_abs>;
    namespace literals
    {
        static inline Q_K_abs<long double> operator "" _K_abs_ (long double _v) {
            return Q_K_abs<long double>(_v); }
        static inline Q_K_abs<long double> operator "" _K_abs_ (unsigned long long int _v) {
            return Q_K_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dK"
//
    struct dK
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = dK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dK";
        }
    };
    template<typename Value = long double>
    using Q_dK = units::Quantity<Value, dK>;
    namespace literals
    {
        static inline Q_dK<long double> operator "" _dK_ (long double _v) {
            return Q_dK<long double>(_v); }
        static inline Q_dK<long double> operator "" _dK_ (unsigned long long int _v) {
            return Q_dK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dK_abs"
//
    struct dK_abs
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = dK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dK_abs";
        }
    };
    template<typename Value = long double>
    using Q_dK_abs = units::Quantity<Value, dK_abs>;
    namespace literals
    {
        static inline Q_dK_abs<long double> operator "" _dK_abs_ (long double _v) {
            return Q_dK_abs<long double>(_v); }
        static inline Q_dK_abs<long double> operator "" _dK_abs_ (unsigned long long int _v) {
            return Q_dK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cK"
//
    struct cK
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = cK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cK";
        }
    };
    template<typename Value = long double>
    using Q_cK = units::Quantity<Value, cK>;
    namespace literals
    {
        static inline Q_cK<long double> operator "" _cK_ (long double _v) {
            return Q_cK<long double>(_v); }
        static inline Q_cK<long double> operator "" _cK_ (unsigned long long int _v) {
            return Q_cK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cK_abs"
//
    struct cK_abs
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = cK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cK_abs";
        }
    };
    template<typename Value = long double>
    using Q_cK_abs = units::Quantity<Value, cK_abs>;
    namespace literals
    {
        static inline Q_cK_abs<long double> operator "" _cK_abs_ (long double _v) {
            return Q_cK_abs<long double>(_v); }
        static inline Q_cK_abs<long double> operator "" _cK_abs_ (unsigned long long int _v) {
            return Q_cK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mK"
//
    struct mK
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = mK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mK";
        }
    };
    template<typename Value = long double>
    using Q_mK = units::Quantity<Value, mK>;
    namespace literals
    {
        static inline Q_mK<long double> operator "" _mK_ (long double _v) {
            return Q_mK<long double>(_v); }
        static inline Q_mK<long double> operator "" _mK_ (unsigned long long int _v) {
            return Q_mK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mK_abs"
//
    struct mK_abs
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = mK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mK_abs";
        }
    };
    template<typename Value = long double>
    using Q_mK_abs = units::Quantity<Value, mK_abs>;
    namespace literals
    {
        static inline Q_mK_abs<long double> operator "" _mK_abs_ (long double _v) {
            return Q_mK_abs<long double>(_v); }
        static inline Q_mK_abs<long double> operator "" _mK_abs_ (unsigned long long int _v) {
            return Q_mK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uK"
//
    struct uK
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = uK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uK";
        }
    };
    template<typename Value = long double>
    using Q_uK = units::Quantity<Value, uK>;
    namespace literals
    {
        static inline Q_uK<long double> operator "" _uK_ (long double _v) {
            return Q_uK<long double>(_v); }
        static inline Q_uK<long double> operator "" _uK_ (unsigned long long int _v) {
            return Q_uK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uK_abs"
//
    struct uK_abs
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = uK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uK_abs";
        }
    };
    template<typename Value = long double>
    using Q_uK_abs = units::Quantity<Value, uK_abs>;
    namespace literals
    {
        static inline Q_uK_abs<long double> operator "" _uK_abs_ (long double _v) {
            return Q_uK_abs<long double>(_v); }
        static inline Q_uK_abs<long double> operator "" _uK_abs_ (unsigned long long int _v) {
            return Q_uK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nK"
//
    struct nK
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = nK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nK";
        }
    };
    template<typename Value = long double>
    using Q_nK = units::Quantity<Value, nK>;
    namespace literals
    {
        static inline Q_nK<long double> operator "" _nK_ (long double _v) {
            return Q_nK<long double>(_v); }
        static inline Q_nK<long double> operator "" _nK_ (unsigned long long int _v) {
            return Q_nK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nK_abs"
//
    struct nK_abs
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = nK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nK_abs";
        }
    };
    template<typename Value = long double>
    using Q_nK_abs = units::Quantity<Value, nK_abs>;
    namespace literals
    {
        static inline Q_nK_abs<long double> operator "" _nK_abs_ (long double _v) {
            return Q_nK_abs<long double>(_v); }
        static inline Q_nK_abs<long double> operator "" _nK_abs_ (unsigned long long int _v) {
            return Q_nK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pK"
//
    struct pK
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = pK;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pK";
        }
    };
    template<typename Value = long double>
    using Q_pK = units::Quantity<Value, pK>;
    namespace literals
    {
        static inline Q_pK<long double> operator "" _pK_ (long double _v) {
            return Q_pK<long double>(_v); }
        static inline Q_pK<long double> operator "" _pK_ (unsigned long long int _v) {
            return Q_pK<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pK_abs"
//
    struct pK_abs
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-5463, 20>;
        using relative_t = pK;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pK_abs";
        }
    };
    template<typename Value = long double>
    using Q_pK_abs = units::Quantity<Value, pK_abs>;
    namespace literals
    {
        static inline Q_pK_abs<long double> operator "" _pK_abs_ (long double _v) {
            return Q_pK_abs<long double>(_v); }
        static inline Q_pK_abs<long double> operator "" _pK_abs_ (unsigned long long int _v) {
            return Q_pK_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GdegF"
//
    struct GdegF
    {
        using factor_t = std::ratio<5000000000, 9>; // approx. 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = GdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GdegF";
        }
    };
    template<typename Value = long double>
    using Q_GdegF = units::Quantity<Value, GdegF>;
    namespace literals
    {
        static inline Q_GdegF<long double> operator "" _GdegF_ (long double _v) {
            return Q_GdegF<long double>(_v); }
        static inline Q_GdegF<long double> operator "" _GdegF_ (unsigned long long int _v) {
            return Q_GdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GdegF_abs"
//
    struct GdegF_abs
    {
        using factor_t = std::ratio<5000000000, 9>; // approx. 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = GdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_GdegF_abs = units::Quantity<Value, GdegF_abs>;
    namespace literals
    {
        static inline Q_GdegF_abs<long double> operator "" _GdegF_abs_ (long double _v) {
            return Q_GdegF_abs<long double>(_v); }
        static inline Q_GdegF_abs<long double> operator "" _GdegF_abs_ (unsigned long long int _v) {
            return Q_GdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MdegF"
//
    struct MdegF
    {
        using factor_t = std::ratio<5000000, 9>; // approx. 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = MdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MdegF";
        }
    };
    template<typename Value = long double>
    using Q_MdegF = units::Quantity<Value, MdegF>;
    namespace literals
    {
        static inline Q_MdegF<long double> operator "" _MdegF_ (long double _v) {
            return Q_MdegF<long double>(_v); }
        static inline Q_MdegF<long double> operator "" _MdegF_ (unsigned long long int _v) {
            return Q_MdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MdegF_abs"
//
    struct MdegF_abs
    {
        using factor_t = std::ratio<5000000, 9>; // approx. 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = MdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_MdegF_abs = units::Quantity<Value, MdegF_abs>;
    namespace literals
    {
        static inline Q_MdegF_abs<long double> operator "" _MdegF_abs_ (long double _v) {
            return Q_MdegF_abs<long double>(_v); }
        static inline Q_MdegF_abs<long double> operator "" _MdegF_abs_ (unsigned long long int _v) {
            return Q_MdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kdegF"
//
    struct kdegF
    {
        using factor_t = std::ratio<5000, 9>; // approx. 555.556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = kdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kdegF";
        }
    };
    template<typename Value = long double>
    using Q_kdegF = units::Quantity<Value, kdegF>;
    namespace literals
    {
        static inline Q_kdegF<long double> operator "" _kdegF_ (long double _v) {
            return Q_kdegF<long double>(_v); }
        static inline Q_kdegF<long double> operator "" _kdegF_ (unsigned long long int _v) {
            return Q_kdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kdegF_abs"
//
    struct kdegF_abs
    {
        using factor_t = std::ratio<5000, 9>; // approx. 555.556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = kdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_kdegF_abs = units::Quantity<Value, kdegF_abs>;
    namespace literals
    {
        static inline Q_kdegF_abs<long double> operator "" _kdegF_abs_ (long double _v) {
            return Q_kdegF_abs<long double>(_v); }
        static inline Q_kdegF_abs<long double> operator "" _kdegF_abs_ (unsigned long long int _v) {
            return Q_kdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hdegF"
//
    struct hdegF
    {
        using factor_t = std::ratio<500, 9>; // approx. 55.5556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = hdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hdegF";
        }
    };
    template<typename Value = long double>
    using Q_hdegF = units::Quantity<Value, hdegF>;
    namespace literals
    {
        static inline Q_hdegF<long double> operator "" _hdegF_ (long double _v) {
            return Q_hdegF<long double>(_v); }
        static inline Q_hdegF<long double> operator "" _hdegF_ (unsigned long long int _v) {
            return Q_hdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hdegF_abs"
//
    struct hdegF_abs
    {
        using factor_t = std::ratio<500, 9>; // approx. 55.5556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = hdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_hdegF_abs = units::Quantity<Value, hdegF_abs>;
    namespace literals
    {
        static inline Q_hdegF_abs<long double> operator "" _hdegF_abs_ (long double _v) {
            return Q_hdegF_abs<long double>(_v); }
        static inline Q_hdegF_abs<long double> operator "" _hdegF_abs_ (unsigned long long int _v) {
            return Q_hdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dadegF"
//
    struct dadegF
    {
        using factor_t = std::ratio<50, 9>; // approx. 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = dadegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dadegF";
        }
    };
    template<typename Value = long double>
    using Q_dadegF = units::Quantity<Value, dadegF>;
    namespace literals
    {
        static inline Q_dadegF<long double> operator "" _dadegF_ (long double _v) {
            return Q_dadegF<long double>(_v); }
        static inline Q_dadegF<long double> operator "" _dadegF_ (unsigned long long int _v) {
            return Q_dadegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dadegF_abs"
//
    struct dadegF_abs
    {
        using factor_t = std::ratio<50, 9>; // approx. 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = dadegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dadegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_dadegF_abs = units::Quantity<Value, dadegF_abs>;
    namespace literals
    {
        static inline Q_dadegF_abs<long double> operator "" _dadegF_abs_ (long double _v) {
            return Q_dadegF_abs<long double>(_v); }
        static inline Q_dadegF_abs<long double> operator "" _dadegF_abs_ (unsigned long long int _v) {
            return Q_dadegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "degF"
//
    struct degF
    {
        using factor_t = std::ratio<5, 9>; // approx. 0.555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = degF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "degF";
        }
    };
    template<typename Value = long double>
    using Q_degF = units::Quantity<Value, degF>;
    namespace literals
    {
        static inline Q_degF<long double> operator "" _degF_ (long double _v) {
            return Q_degF<long double>(_v); }
        static inline Q_degF<long double> operator "" _degF_ (unsigned long long int _v) {
            return Q_degF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "degF_abs"
//
    struct degF_abs
    {
        using factor_t = std::ratio<5, 9>; // approx. 0.555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = degF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "degF_abs";
        }
    };
    template<typename Value = long double>
    using Q_degF_abs = units::Quantity<Value, degF_abs>;
    namespace literals
    {
        static inline Q_degF_abs<long double> operator "" _degF_abs_ (long double _v) {
            return Q_degF_abs<long double>(_v); }
        static inline Q_degF_abs<long double> operator "" _degF_abs_ (unsigned long long int _v) {
            return Q_degF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ddegF"
//
    struct ddegF
    {
        using factor_t = std::ratio<1, 18>; // approx. 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = ddegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ddegF";
        }
    };
    template<typename Value = long double>
    using Q_ddegF = units::Quantity<Value, ddegF>;
    namespace literals
    {
        static inline Q_ddegF<long double> operator "" _ddegF_ (long double _v) {
            return Q_ddegF<long double>(_v); }
        static inline Q_ddegF<long double> operator "" _ddegF_ (unsigned long long int _v) {
            return Q_ddegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ddegF_abs"
//
    struct ddegF_abs
    {
        using factor_t = std::ratio<1, 18>; // approx. 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = ddegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ddegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_ddegF_abs = units::Quantity<Value, ddegF_abs>;
    namespace literals
    {
        static inline Q_ddegF_abs<long double> operator "" _ddegF_abs_ (long double _v) {
            return Q_ddegF_abs<long double>(_v); }
        static inline Q_ddegF_abs<long double> operator "" _ddegF_abs_ (unsigned long long int _v) {
            return Q_ddegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cdegF"
//
    struct cdegF
    {
        using factor_t = std::ratio<1, 180>; // approx. 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = cdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cdegF";
        }
    };
    template<typename Value = long double>
    using Q_cdegF = units::Quantity<Value, cdegF>;
    namespace literals
    {
        static inline Q_cdegF<long double> operator "" _cdegF_ (long double _v) {
            return Q_cdegF<long double>(_v); }
        static inline Q_cdegF<long double> operator "" _cdegF_ (unsigned long long int _v) {
            return Q_cdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cdegF_abs"
//
    struct cdegF_abs
    {
        using factor_t = std::ratio<1, 180>; // approx. 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = cdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_cdegF_abs = units::Quantity<Value, cdegF_abs>;
    namespace literals
    {
        static inline Q_cdegF_abs<long double> operator "" _cdegF_abs_ (long double _v) {
            return Q_cdegF_abs<long double>(_v); }
        static inline Q_cdegF_abs<long double> operator "" _cdegF_abs_ (unsigned long long int _v) {
            return Q_cdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mdegF"
//
    struct mdegF
    {
        using factor_t = std::ratio<1, 1800>; // approx. 0.000555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = mdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mdegF";
        }
    };
    template<typename Value = long double>
    using Q_mdegF = units::Quantity<Value, mdegF>;
    namespace literals
    {
        static inline Q_mdegF<long double> operator "" _mdegF_ (long double _v) {
            return Q_mdegF<long double>(_v); }
        static inline Q_mdegF<long double> operator "" _mdegF_ (unsigned long long int _v) {
            return Q_mdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mdegF_abs"
//
    struct mdegF_abs
    {
        using factor_t = std::ratio<1, 1800>; // approx. 0.000555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = mdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_mdegF_abs = units::Quantity<Value, mdegF_abs>;
    namespace literals
    {
        static inline Q_mdegF_abs<long double> operator "" _mdegF_abs_ (long double _v) {
            return Q_mdegF_abs<long double>(_v); }
        static inline Q_mdegF_abs<long double> operator "" _mdegF_abs_ (unsigned long long int _v) {
            return Q_mdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "udegF"
//
    struct udegF
    {
        using factor_t = std::ratio<1, 1800000>; // approx. 5.55556e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = udegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "udegF";
        }
    };
    template<typename Value = long double>
    using Q_udegF = units::Quantity<Value, udegF>;
    namespace literals
    {
        static inline Q_udegF<long double> operator "" _udegF_ (long double _v) {
            return Q_udegF<long double>(_v); }
        static inline Q_udegF<long double> operator "" _udegF_ (unsigned long long int _v) {
            return Q_udegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "udegF_abs"
//
    struct udegF_abs
    {
        using factor_t = std::ratio<1, 1800000>; // approx. 5.55556e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = udegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "udegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_udegF_abs = units::Quantity<Value, udegF_abs>;
    namespace literals
    {
        static inline Q_udegF_abs<long double> operator "" _udegF_abs_ (long double _v) {
            return Q_udegF_abs<long double>(_v); }
        static inline Q_udegF_abs<long double> operator "" _udegF_abs_ (unsigned long long int _v) {
            return Q_udegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ndegF"
//
    struct ndegF
    {
        using factor_t = std::ratio<1, 1800000000>; // approx. 5.55556e-10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = ndegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ndegF";
        }
    };
    template<typename Value = long double>
    using Q_ndegF = units::Quantity<Value, ndegF>;
    namespace literals
    {
        static inline Q_ndegF<long double> operator "" _ndegF_ (long double _v) {
            return Q_ndegF<long double>(_v); }
        static inline Q_ndegF<long double> operator "" _ndegF_ (unsigned long long int _v) {
            return Q_ndegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ndegF_abs"
//
    struct ndegF_abs
    {
        using factor_t = std::ratio<1, 1800000000>; // approx. 5.55556e-10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = ndegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ndegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_ndegF_abs = units::Quantity<Value, ndegF_abs>;
    namespace literals
    {
        static inline Q_ndegF_abs<long double> operator "" _ndegF_abs_ (long double _v) {
            return Q_ndegF_abs<long double>(_v); }
        static inline Q_ndegF_abs<long double> operator "" _ndegF_abs_ (unsigned long long int _v) {
            return Q_ndegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdegF"
//
    struct pdegF
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = pdegF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdegF";
        }
    };
    template<typename Value = long double>
    using Q_pdegF = units::Quantity<Value, pdegF>;
    namespace literals
    {
        static inline Q_pdegF<long double> operator "" _pdegF_ (long double _v) {
            return Q_pdegF<long double>(_v); }
        static inline Q_pdegF<long double> operator "" _pdegF_ (unsigned long long int _v) {
            return Q_pdegF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdegF_abs"
//
    struct pdegF_abs
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<32, 1>;
        using relative_t = pdegF;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdegF_abs";
        }
    };
    template<typename Value = long double>
    using Q_pdegF_abs = units::Quantity<Value, pdegF_abs>;
    namespace literals
    {
        static inline Q_pdegF_abs<long double> operator "" _pdegF_abs_ (long double _v) {
            return Q_pdegF_abs<long double>(_v); }
        static inline Q_pdegF_abs<long double> operator "" _pdegF_abs_ (unsigned long long int _v) {
            return Q_pdegF_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GdegRa"
//
    struct GdegRa
    {
        using factor_t = std::ratio<5000000000, 9>; // approx. 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = GdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GdegRa";
        }
    };
    template<typename Value = long double>
    using Q_GdegRa = units::Quantity<Value, GdegRa>;
    namespace literals
    {
        static inline Q_GdegRa<long double> operator "" _GdegRa_ (long double _v) {
            return Q_GdegRa<long double>(_v); }
        static inline Q_GdegRa<long double> operator "" _GdegRa_ (unsigned long long int _v) {
            return Q_GdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GdegRa_abs"
//
    struct GdegRa_abs
    {
        using factor_t = std::ratio<5000000000, 9>; // approx. 5.55556e+08
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = GdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_GdegRa_abs = units::Quantity<Value, GdegRa_abs>;
    namespace literals
    {
        static inline Q_GdegRa_abs<long double> operator "" _GdegRa_abs_ (long double _v) {
            return Q_GdegRa_abs<long double>(_v); }
        static inline Q_GdegRa_abs<long double> operator "" _GdegRa_abs_ (unsigned long long int _v) {
            return Q_GdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MdegRa"
//
    struct MdegRa
    {
        using factor_t = std::ratio<5000000, 9>; // approx. 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = MdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MdegRa";
        }
    };
    template<typename Value = long double>
    using Q_MdegRa = units::Quantity<Value, MdegRa>;
    namespace literals
    {
        static inline Q_MdegRa<long double> operator "" _MdegRa_ (long double _v) {
            return Q_MdegRa<long double>(_v); }
        static inline Q_MdegRa<long double> operator "" _MdegRa_ (unsigned long long int _v) {
            return Q_MdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MdegRa_abs"
//
    struct MdegRa_abs
    {
        using factor_t = std::ratio<5000000, 9>; // approx. 555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = MdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_MdegRa_abs = units::Quantity<Value, MdegRa_abs>;
    namespace literals
    {
        static inline Q_MdegRa_abs<long double> operator "" _MdegRa_abs_ (long double _v) {
            return Q_MdegRa_abs<long double>(_v); }
        static inline Q_MdegRa_abs<long double> operator "" _MdegRa_abs_ (unsigned long long int _v) {
            return Q_MdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kdegRa"
//
    struct kdegRa
    {
        using factor_t = std::ratio<5000, 9>; // approx. 555.556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = kdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kdegRa";
        }
    };
    template<typename Value = long double>
    using Q_kdegRa = units::Quantity<Value, kdegRa>;
    namespace literals
    {
        static inline Q_kdegRa<long double> operator "" _kdegRa_ (long double _v) {
            return Q_kdegRa<long double>(_v); }
        static inline Q_kdegRa<long double> operator "" _kdegRa_ (unsigned long long int _v) {
            return Q_kdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kdegRa_abs"
//
    struct kdegRa_abs
    {
        using factor_t = std::ratio<5000, 9>; // approx. 555.556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = kdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_kdegRa_abs = units::Quantity<Value, kdegRa_abs>;
    namespace literals
    {
        static inline Q_kdegRa_abs<long double> operator "" _kdegRa_abs_ (long double _v) {
            return Q_kdegRa_abs<long double>(_v); }
        static inline Q_kdegRa_abs<long double> operator "" _kdegRa_abs_ (unsigned long long int _v) {
            return Q_kdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hdegRa"
//
    struct hdegRa
    {
        using factor_t = std::ratio<500, 9>; // approx. 55.5556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = hdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hdegRa";
        }
    };
    template<typename Value = long double>
    using Q_hdegRa = units::Quantity<Value, hdegRa>;
    namespace literals
    {
        static inline Q_hdegRa<long double> operator "" _hdegRa_ (long double _v) {
            return Q_hdegRa<long double>(_v); }
        static inline Q_hdegRa<long double> operator "" _hdegRa_ (unsigned long long int _v) {
            return Q_hdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hdegRa_abs"
//
    struct hdegRa_abs
    {
        using factor_t = std::ratio<500, 9>; // approx. 55.5556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = hdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_hdegRa_abs = units::Quantity<Value, hdegRa_abs>;
    namespace literals
    {
        static inline Q_hdegRa_abs<long double> operator "" _hdegRa_abs_ (long double _v) {
            return Q_hdegRa_abs<long double>(_v); }
        static inline Q_hdegRa_abs<long double> operator "" _hdegRa_abs_ (unsigned long long int _v) {
            return Q_hdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dadegRa"
//
    struct dadegRa
    {
        using factor_t = std::ratio<50, 9>; // approx. 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = dadegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dadegRa";
        }
    };
    template<typename Value = long double>
    using Q_dadegRa = units::Quantity<Value, dadegRa>;
    namespace literals
    {
        static inline Q_dadegRa<long double> operator "" _dadegRa_ (long double _v) {
            return Q_dadegRa<long double>(_v); }
        static inline Q_dadegRa<long double> operator "" _dadegRa_ (unsigned long long int _v) {
            return Q_dadegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dadegRa_abs"
//
    struct dadegRa_abs
    {
        using factor_t = std::ratio<50, 9>; // approx. 5.55556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = dadegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dadegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_dadegRa_abs = units::Quantity<Value, dadegRa_abs>;
    namespace literals
    {
        static inline Q_dadegRa_abs<long double> operator "" _dadegRa_abs_ (long double _v) {
            return Q_dadegRa_abs<long double>(_v); }
        static inline Q_dadegRa_abs<long double> operator "" _dadegRa_abs_ (unsigned long long int _v) {
            return Q_dadegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "degRa"
//
    struct degRa
    {
        using factor_t = std::ratio<5, 9>; // approx. 0.555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = degRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "degRa";
        }
    };
    template<typename Value = long double>
    using Q_degRa = units::Quantity<Value, degRa>;
    namespace literals
    {
        static inline Q_degRa<long double> operator "" _degRa_ (long double _v) {
            return Q_degRa<long double>(_v); }
        static inline Q_degRa<long double> operator "" _degRa_ (unsigned long long int _v) {
            return Q_degRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "degRa_abs"
//
    struct degRa_abs
    {
        using factor_t = std::ratio<5, 9>; // approx. 0.555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = degRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "degRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_degRa_abs = units::Quantity<Value, degRa_abs>;
    namespace literals
    {
        static inline Q_degRa_abs<long double> operator "" _degRa_abs_ (long double _v) {
            return Q_degRa_abs<long double>(_v); }
        static inline Q_degRa_abs<long double> operator "" _degRa_abs_ (unsigned long long int _v) {
            return Q_degRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ddegRa"
//
    struct ddegRa
    {
        using factor_t = std::ratio<1, 18>; // approx. 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = ddegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ddegRa";
        }
    };
    template<typename Value = long double>
    using Q_ddegRa = units::Quantity<Value, ddegRa>;
    namespace literals
    {
        static inline Q_ddegRa<long double> operator "" _ddegRa_ (long double _v) {
            return Q_ddegRa<long double>(_v); }
        static inline Q_ddegRa<long double> operator "" _ddegRa_ (unsigned long long int _v) {
            return Q_ddegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ddegRa_abs"
//
    struct ddegRa_abs
    {
        using factor_t = std::ratio<1, 18>; // approx. 0.0555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = ddegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ddegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_ddegRa_abs = units::Quantity<Value, ddegRa_abs>;
    namespace literals
    {
        static inline Q_ddegRa_abs<long double> operator "" _ddegRa_abs_ (long double _v) {
            return Q_ddegRa_abs<long double>(_v); }
        static inline Q_ddegRa_abs<long double> operator "" _ddegRa_abs_ (unsigned long long int _v) {
            return Q_ddegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cdegRa"
//
    struct cdegRa
    {
        using factor_t = std::ratio<1, 180>; // approx. 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = cdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cdegRa";
        }
    };
    template<typename Value = long double>
    using Q_cdegRa = units::Quantity<Value, cdegRa>;
    namespace literals
    {
        static inline Q_cdegRa<long double> operator "" _cdegRa_ (long double _v) {
            return Q_cdegRa<long double>(_v); }
        static inline Q_cdegRa<long double> operator "" _cdegRa_ (unsigned long long int _v) {
            return Q_cdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cdegRa_abs"
//
    struct cdegRa_abs
    {
        using factor_t = std::ratio<1, 180>; // approx. 0.00555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = cdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_cdegRa_abs = units::Quantity<Value, cdegRa_abs>;
    namespace literals
    {
        static inline Q_cdegRa_abs<long double> operator "" _cdegRa_abs_ (long double _v) {
            return Q_cdegRa_abs<long double>(_v); }
        static inline Q_cdegRa_abs<long double> operator "" _cdegRa_abs_ (unsigned long long int _v) {
            return Q_cdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mdegRa"
//
    struct mdegRa
    {
        using factor_t = std::ratio<1, 1800>; // approx. 0.000555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = mdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mdegRa";
        }
    };
    template<typename Value = long double>
    using Q_mdegRa = units::Quantity<Value, mdegRa>;
    namespace literals
    {
        static inline Q_mdegRa<long double> operator "" _mdegRa_ (long double _v) {
            return Q_mdegRa<long double>(_v); }
        static inline Q_mdegRa<long double> operator "" _mdegRa_ (unsigned long long int _v) {
            return Q_mdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mdegRa_abs"
//
    struct mdegRa_abs
    {
        using factor_t = std::ratio<1, 1800>; // approx. 0.000555556
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = mdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_mdegRa_abs = units::Quantity<Value, mdegRa_abs>;
    namespace literals
    {
        static inline Q_mdegRa_abs<long double> operator "" _mdegRa_abs_ (long double _v) {
            return Q_mdegRa_abs<long double>(_v); }
        static inline Q_mdegRa_abs<long double> operator "" _mdegRa_abs_ (unsigned long long int _v) {
            return Q_mdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "udegRa"
//
    struct udegRa
    {
        using factor_t = std::ratio<1, 1800000>; // approx. 5.55556e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = udegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "udegRa";
        }
    };
    template<typename Value = long double>
    using Q_udegRa = units::Quantity<Value, udegRa>;
    namespace literals
    {
        static inline Q_udegRa<long double> operator "" _udegRa_ (long double _v) {
            return Q_udegRa<long double>(_v); }
        static inline Q_udegRa<long double> operator "" _udegRa_ (unsigned long long int _v) {
            return Q_udegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "udegRa_abs"
//
    struct udegRa_abs
    {
        using factor_t = std::ratio<1, 1800000>; // approx. 5.55556e-07
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = udegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "udegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_udegRa_abs = units::Quantity<Value, udegRa_abs>;
    namespace literals
    {
        static inline Q_udegRa_abs<long double> operator "" _udegRa_abs_ (long double _v) {
            return Q_udegRa_abs<long double>(_v); }
        static inline Q_udegRa_abs<long double> operator "" _udegRa_abs_ (unsigned long long int _v) {
            return Q_udegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ndegRa"
//
    struct ndegRa
    {
        using factor_t = std::ratio<1, 1800000000>; // approx. 5.55556e-10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = ndegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ndegRa";
        }
    };
    template<typename Value = long double>
    using Q_ndegRa = units::Quantity<Value, ndegRa>;
    namespace literals
    {
        static inline Q_ndegRa<long double> operator "" _ndegRa_ (long double _v) {
            return Q_ndegRa<long double>(_v); }
        static inline Q_ndegRa<long double> operator "" _ndegRa_ (unsigned long long int _v) {
            return Q_ndegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ndegRa_abs"
//
    struct ndegRa_abs
    {
        using factor_t = std::ratio<1, 1800000000>; // approx. 5.55556e-10
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = ndegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ndegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_ndegRa_abs = units::Quantity<Value, ndegRa_abs>;
    namespace literals
    {
        static inline Q_ndegRa_abs<long double> operator "" _ndegRa_abs_ (long double _v) {
            return Q_ndegRa_abs<long double>(_v); }
        static inline Q_ndegRa_abs<long double> operator "" _ndegRa_abs_ (unsigned long long int _v) {
            return Q_ndegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdegRa"
//
    struct pdegRa
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = pdegRa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdegRa";
        }
    };
    template<typename Value = long double>
    using Q_pdegRa = units::Quantity<Value, pdegRa>;
    namespace literals
    {
        static inline Q_pdegRa<long double> operator "" _pdegRa_ (long double _v) {
            return Q_pdegRa<long double>(_v); }
        static inline Q_pdegRa<long double> operator "" _pdegRa_ (unsigned long long int _v) {
            return Q_pdegRa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pdegRa_abs"
//
    struct pdegRa_abs
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Temperature;
        using offset_t = std::ratio<-45967, 100>;
        using relative_t = pdegRa;
        static constexpr bool absolute = true;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pdegRa_abs";
        }
    };
    template<typename Value = long double>
    using Q_pdegRa_abs = units::Quantity<Value, pdegRa_abs>;
    namespace literals
    {
        static inline Q_pdegRa_abs<long double> operator "" _pdegRa_abs_ (long double _v) {
            return Q_pdegRa_abs<long double>(_v); }
        static inline Q_pdegRa_abs<long double> operator "" _pdegRa_abs_ (unsigned long long int _v) {
            return Q_pdegRa_abs<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TT"
//
    struct TT
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TT";
        }
    };
    template<typename Value = long double>
    using Q_TT = units::Quantity<Value, TT>;
    namespace literals
    {
        static inline Q_TT<long double> operator "" _TT_ (long double _v) {
            return Q_TT<long double>(_v); }
        static inline Q_TT<long double> operator "" _TT_ (unsigned long long int _v) {
            return Q_TT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GT"
//
    struct GT
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GT";
        }
    };
    template<typename Value = long double>
    using Q_GT = units::Quantity<Value, GT>;
    namespace literals
    {
        static inline Q_GT<long double> operator "" _GT_ (long double _v) {
            return Q_GT<long double>(_v); }
        static inline Q_GT<long double> operator "" _GT_ (unsigned long long int _v) {
            return Q_GT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MT"
//
    struct MT
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MT";
        }
    };
    template<typename Value = long double>
    using Q_MT = units::Quantity<Value, MT>;
    namespace literals
    {
        static inline Q_MT<long double> operator "" _MT_ (long double _v) {
            return Q_MT<long double>(_v); }
        static inline Q_MT<long double> operator "" _MT_ (unsigned long long int _v) {
            return Q_MT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kT"
//
    struct kT
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kT";
        }
    };
    template<typename Value = long double>
    using Q_kT = units::Quantity<Value, kT>;
    namespace literals
    {
        static inline Q_kT<long double> operator "" _kT_ (long double _v) {
            return Q_kT<long double>(_v); }
        static inline Q_kT<long double> operator "" _kT_ (unsigned long long int _v) {
            return Q_kT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hT"
//
    struct hT
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hT";
        }
    };
    template<typename Value = long double>
    using Q_hT = units::Quantity<Value, hT>;
    namespace literals
    {
        static inline Q_hT<long double> operator "" _hT_ (long double _v) {
            return Q_hT<long double>(_v); }
        static inline Q_hT<long double> operator "" _hT_ (unsigned long long int _v) {
            return Q_hT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daT"
//
    struct daT
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daT";
        }
    };
    template<typename Value = long double>
    using Q_daT = units::Quantity<Value, daT>;
    namespace literals
    {
        static inline Q_daT<long double> operator "" _daT_ (long double _v) {
            return Q_daT<long double>(_v); }
        static inline Q_daT<long double> operator "" _daT_ (unsigned long long int _v) {
            return Q_daT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "T"
//
    struct T
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = T;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "T";
        }
    };
    template<typename Value = long double>
    using Q_T = units::Quantity<Value, T>;
    namespace literals
    {
        static inline Q_T<long double> operator "" _T_ (long double _v) {
            return Q_T<long double>(_v); }
        static inline Q_T<long double> operator "" _T_ (unsigned long long int _v) {
            return Q_T<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dT"
//
    struct dT
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dT";
        }
    };
    template<typename Value = long double>
    using Q_dT = units::Quantity<Value, dT>;
    namespace literals
    {
        static inline Q_dT<long double> operator "" _dT_ (long double _v) {
            return Q_dT<long double>(_v); }
        static inline Q_dT<long double> operator "" _dT_ (unsigned long long int _v) {
            return Q_dT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cT"
//
    struct cT
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cT";
        }
    };
    template<typename Value = long double>
    using Q_cT = units::Quantity<Value, cT>;
    namespace literals
    {
        static inline Q_cT<long double> operator "" _cT_ (long double _v) {
            return Q_cT<long double>(_v); }
        static inline Q_cT<long double> operator "" _cT_ (unsigned long long int _v) {
            return Q_cT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mT"
//
    struct mT
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mT";
        }
    };
    template<typename Value = long double>
    using Q_mT = units::Quantity<Value, mT>;
    namespace literals
    {
        static inline Q_mT<long double> operator "" _mT_ (long double _v) {
            return Q_mT<long double>(_v); }
        static inline Q_mT<long double> operator "" _mT_ (unsigned long long int _v) {
            return Q_mT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uT"
//
    struct uT
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uT";
        }
    };
    template<typename Value = long double>
    using Q_uT = units::Quantity<Value, uT>;
    namespace literals
    {
        static inline Q_uT<long double> operator "" _uT_ (long double _v) {
            return Q_uT<long double>(_v); }
        static inline Q_uT<long double> operator "" _uT_ (unsigned long long int _v) {
            return Q_uT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nT"
//
    struct nT
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nT";
        }
    };
    template<typename Value = long double>
    using Q_nT = units::Quantity<Value, nT>;
    namespace literals
    {
        static inline Q_nT<long double> operator "" _nT_ (long double _v) {
            return Q_nT<long double>(_v); }
        static inline Q_nT<long double> operator "" _nT_ (unsigned long long int _v) {
            return Q_nT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pT"
//
    struct pT
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pT;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pT";
        }
    };
    template<typename Value = long double>
    using Q_pT = units::Quantity<Value, pT>;
    namespace literals
    {
        static inline Q_pT<long double> operator "" _pT_ (long double _v) {
            return Q_pT<long double>(_v); }
        static inline Q_pT<long double> operator "" _pT_ (unsigned long long int _v) {
            return Q_pT<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "PG"
//
    struct PG
    {
        using factor_t = std::ratio<100000000000, 1>; // approx. 1e+11
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PG";
        }
    };
    template<typename Value = long double>
    using Q_PG = units::Quantity<Value, PG>;
    namespace literals
    {
        static inline Q_PG<long double> operator "" _PG_ (long double _v) {
            return Q_PG<long double>(_v); }
        static inline Q_PG<long double> operator "" _PG_ (unsigned long long int _v) {
            return Q_PG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TG"
//
    struct TG
    {
        using factor_t = std::ratio<100000000, 1>; // approx. 1e+08
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TG";
        }
    };
    template<typename Value = long double>
    using Q_TG = units::Quantity<Value, TG>;
    namespace literals
    {
        static inline Q_TG<long double> operator "" _TG_ (long double _v) {
            return Q_TG<long double>(_v); }
        static inline Q_TG<long double> operator "" _TG_ (unsigned long long int _v) {
            return Q_TG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GG"
//
    struct GG
    {
        using factor_t = std::ratio<100000, 1>; // approx. 100000
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GG";
        }
    };
    template<typename Value = long double>
    using Q_GG = units::Quantity<Value, GG>;
    namespace literals
    {
        static inline Q_GG<long double> operator "" _GG_ (long double _v) {
            return Q_GG<long double>(_v); }
        static inline Q_GG<long double> operator "" _GG_ (unsigned long long int _v) {
            return Q_GG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MG"
//
    struct MG
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MG";
        }
    };
    template<typename Value = long double>
    using Q_MG = units::Quantity<Value, MG>;
    namespace literals
    {
        static inline Q_MG<long double> operator "" _MG_ (long double _v) {
            return Q_MG<long double>(_v); }
        static inline Q_MG<long double> operator "" _MG_ (unsigned long long int _v) {
            return Q_MG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kG"
//
    struct kG
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kG";
        }
    };
    template<typename Value = long double>
    using Q_kG = units::Quantity<Value, kG>;
    namespace literals
    {
        static inline Q_kG<long double> operator "" _kG_ (long double _v) {
            return Q_kG<long double>(_v); }
        static inline Q_kG<long double> operator "" _kG_ (unsigned long long int _v) {
            return Q_kG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hG"
//
    struct hG
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hG";
        }
    };
    template<typename Value = long double>
    using Q_hG = units::Quantity<Value, hG>;
    namespace literals
    {
        static inline Q_hG<long double> operator "" _hG_ (long double _v) {
            return Q_hG<long double>(_v); }
        static inline Q_hG<long double> operator "" _hG_ (unsigned long long int _v) {
            return Q_hG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daG"
//
    struct daG
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daG";
        }
    };
    template<typename Value = long double>
    using Q_daG = units::Quantity<Value, daG>;
    namespace literals
    {
        static inline Q_daG<long double> operator "" _daG_ (long double _v) {
            return Q_daG<long double>(_v); }
        static inline Q_daG<long double> operator "" _daG_ (unsigned long long int _v) {
            return Q_daG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "G"
//
    struct G
    {
        using factor_t = std::ratio<1, 10000>; // approx. 0.0001
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = G;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "G";
        }
    };
    template<typename Value = long double>
    using Q_G = units::Quantity<Value, G>;
    namespace literals
    {
        static inline Q_G<long double> operator "" _G_ (long double _v) {
            return Q_G<long double>(_v); }
        static inline Q_G<long double> operator "" _G_ (unsigned long long int _v) {
            return Q_G<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dG"
//
    struct dG
    {
        using factor_t = std::ratio<1, 100000>; // approx. 1e-05
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dG";
        }
    };
    template<typename Value = long double>
    using Q_dG = units::Quantity<Value, dG>;
    namespace literals
    {
        static inline Q_dG<long double> operator "" _dG_ (long double _v) {
            return Q_dG<long double>(_v); }
        static inline Q_dG<long double> operator "" _dG_ (unsigned long long int _v) {
            return Q_dG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cG"
//
    struct cG
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cG";
        }
    };
    template<typename Value = long double>
    using Q_cG = units::Quantity<Value, cG>;
    namespace literals
    {
        static inline Q_cG<long double> operator "" _cG_ (long double _v) {
            return Q_cG<long double>(_v); }
        static inline Q_cG<long double> operator "" _cG_ (unsigned long long int _v) {
            return Q_cG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mG"
//
    struct mG
    {
        using factor_t = std::ratio<1, 10000000>; // approx. 1e-07
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mG";
        }
    };
    template<typename Value = long double>
    using Q_mG = units::Quantity<Value, mG>;
    namespace literals
    {
        static inline Q_mG<long double> operator "" _mG_ (long double _v) {
            return Q_mG<long double>(_v); }
        static inline Q_mG<long double> operator "" _mG_ (unsigned long long int _v) {
            return Q_mG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uG"
//
    struct uG
    {
        using factor_t = std::ratio<1, 10000000000>; // approx. 1e-10
        using dimensions_t = dimensions::MagneticFlux;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uG;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uG";
        }
    };
    template<typename Value = long double>
    using Q_uG = units::Quantity<Value, uG>;
    namespace literals
    {
        static inline Q_uG<long double> operator "" _uG_ (long double _v) {
            return Q_uG<long double>(_v); }
        static inline Q_uG<long double> operator "" _uG_ (unsigned long long int _v) {
            return Q_uG<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TPa"
//
    struct TPa
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TPa";
        }
    };
    template<typename Value = long double>
    using Q_TPa = units::Quantity<Value, TPa>;
    namespace literals
    {
        static inline Q_TPa<long double> operator "" _TPa_ (long double _v) {
            return Q_TPa<long double>(_v); }
        static inline Q_TPa<long double> operator "" _TPa_ (unsigned long long int _v) {
            return Q_TPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GPa"
//
    struct GPa
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GPa";
        }
    };
    template<typename Value = long double>
    using Q_GPa = units::Quantity<Value, GPa>;
    namespace literals
    {
        static inline Q_GPa<long double> operator "" _GPa_ (long double _v) {
            return Q_GPa<long double>(_v); }
        static inline Q_GPa<long double> operator "" _GPa_ (unsigned long long int _v) {
            return Q_GPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MPa"
//
    struct MPa
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MPa";
        }
    };
    template<typename Value = long double>
    using Q_MPa = units::Quantity<Value, MPa>;
    namespace literals
    {
        static inline Q_MPa<long double> operator "" _MPa_ (long double _v) {
            return Q_MPa<long double>(_v); }
        static inline Q_MPa<long double> operator "" _MPa_ (unsigned long long int _v) {
            return Q_MPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kPa"
//
    struct kPa
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kPa";
        }
    };
    template<typename Value = long double>
    using Q_kPa = units::Quantity<Value, kPa>;
    namespace literals
    {
        static inline Q_kPa<long double> operator "" _kPa_ (long double _v) {
            return Q_kPa<long double>(_v); }
        static inline Q_kPa<long double> operator "" _kPa_ (unsigned long long int _v) {
            return Q_kPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hPa"
//
    struct hPa
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hPa";
        }
    };
    template<typename Value = long double>
    using Q_hPa = units::Quantity<Value, hPa>;
    namespace literals
    {
        static inline Q_hPa<long double> operator "" _hPa_ (long double _v) {
            return Q_hPa<long double>(_v); }
        static inline Q_hPa<long double> operator "" _hPa_ (unsigned long long int _v) {
            return Q_hPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daPa"
//
    struct daPa
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daPa";
        }
    };
    template<typename Value = long double>
    using Q_daPa = units::Quantity<Value, daPa>;
    namespace literals
    {
        static inline Q_daPa<long double> operator "" _daPa_ (long double _v) {
            return Q_daPa<long double>(_v); }
        static inline Q_daPa<long double> operator "" _daPa_ (unsigned long long int _v) {
            return Q_daPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Pa"
//
    struct Pa
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pa";
        }
    };
    template<typename Value = long double>
    using Q_Pa = units::Quantity<Value, Pa>;
    namespace literals
    {
        static inline Q_Pa<long double> operator "" _Pa_ (long double _v) {
            return Q_Pa<long double>(_v); }
        static inline Q_Pa<long double> operator "" _Pa_ (unsigned long long int _v) {
            return Q_Pa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dPa"
//
    struct dPa
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dPa";
        }
    };
    template<typename Value = long double>
    using Q_dPa = units::Quantity<Value, dPa>;
    namespace literals
    {
        static inline Q_dPa<long double> operator "" _dPa_ (long double _v) {
            return Q_dPa<long double>(_v); }
        static inline Q_dPa<long double> operator "" _dPa_ (unsigned long long int _v) {
            return Q_dPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cPa"
//
    struct cPa
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cPa";
        }
    };
    template<typename Value = long double>
    using Q_cPa = units::Quantity<Value, cPa>;
    namespace literals
    {
        static inline Q_cPa<long double> operator "" _cPa_ (long double _v) {
            return Q_cPa<long double>(_v); }
        static inline Q_cPa<long double> operator "" _cPa_ (unsigned long long int _v) {
            return Q_cPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mPa"
//
    struct mPa
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mPa";
        }
    };
    template<typename Value = long double>
    using Q_mPa = units::Quantity<Value, mPa>;
    namespace literals
    {
        static inline Q_mPa<long double> operator "" _mPa_ (long double _v) {
            return Q_mPa<long double>(_v); }
        static inline Q_mPa<long double> operator "" _mPa_ (unsigned long long int _v) {
            return Q_mPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uPa"
//
    struct uPa
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uPa";
        }
    };
    template<typename Value = long double>
    using Q_uPa = units::Quantity<Value, uPa>;
    namespace literals
    {
        static inline Q_uPa<long double> operator "" _uPa_ (long double _v) {
            return Q_uPa<long double>(_v); }
        static inline Q_uPa<long double> operator "" _uPa_ (unsigned long long int _v) {
            return Q_uPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nPa"
//
    struct nPa
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nPa";
        }
    };
    template<typename Value = long double>
    using Q_nPa = units::Quantity<Value, nPa>;
    namespace literals
    {
        static inline Q_nPa<long double> operator "" _nPa_ (long double _v) {
            return Q_nPa<long double>(_v); }
        static inline Q_nPa<long double> operator "" _nPa_ (unsigned long long int _v) {
            return Q_nPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pPa"
//
    struct pPa
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pPa;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pPa";
        }
    };
    template<typename Value = long double>
    using Q_pPa = units::Quantity<Value, pPa>;
    namespace literals
    {
        static inline Q_pPa<long double> operator "" _pPa_ (long double _v) {
            return Q_pPa<long double>(_v); }
        static inline Q_pPa<long double> operator "" _pPa_ (unsigned long long int _v) {
            return Q_pPa<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mbar"
//
    struct Mbar
    {
        using factor_t = std::ratio<100000000000, 1>; // approx. 1e+11
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mbar";
        }
    };
    template<typename Value = long double>
    using Q_Mbar = units::Quantity<Value, Mbar>;
    namespace literals
    {
        static inline Q_Mbar<long double> operator "" _Mbar_ (long double _v) {
            return Q_Mbar<long double>(_v); }
        static inline Q_Mbar<long double> operator "" _Mbar_ (unsigned long long int _v) {
            return Q_Mbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kbar"
//
    struct kbar
    {
        using factor_t = std::ratio<100000000, 1>; // approx. 1e+08
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kbar";
        }
    };
    template<typename Value = long double>
    using Q_kbar = units::Quantity<Value, kbar>;
    namespace literals
    {
        static inline Q_kbar<long double> operator "" _kbar_ (long double _v) {
            return Q_kbar<long double>(_v); }
        static inline Q_kbar<long double> operator "" _kbar_ (unsigned long long int _v) {
            return Q_kbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hbar"
//
    struct hbar
    {
        using factor_t = std::ratio<10000000, 1>; // approx. 1e+07
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hbar";
        }
    };
    template<typename Value = long double>
    using Q_hbar = units::Quantity<Value, hbar>;
    namespace literals
    {
        static inline Q_hbar<long double> operator "" _hbar_ (long double _v) {
            return Q_hbar<long double>(_v); }
        static inline Q_hbar<long double> operator "" _hbar_ (unsigned long long int _v) {
            return Q_hbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dabar"
//
    struct dabar
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dabar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dabar";
        }
    };
    template<typename Value = long double>
    using Q_dabar = units::Quantity<Value, dabar>;
    namespace literals
    {
        static inline Q_dabar<long double> operator "" _dabar_ (long double _v) {
            return Q_dabar<long double>(_v); }
        static inline Q_dabar<long double> operator "" _dabar_ (unsigned long long int _v) {
            return Q_dabar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "bar"
//
    struct bar
    {
        using factor_t = std::ratio<100000, 1>; // approx. 100000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = bar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "bar";
        }
    };
    template<typename Value = long double>
    using Q_bar = units::Quantity<Value, bar>;
    namespace literals
    {
        static inline Q_bar<long double> operator "" _bar_ (long double _v) {
            return Q_bar<long double>(_v); }
        static inline Q_bar<long double> operator "" _bar_ (unsigned long long int _v) {
            return Q_bar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dbar"
//
    struct dbar
    {
        using factor_t = std::ratio<10000, 1>; // approx. 10000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dbar";
        }
    };
    template<typename Value = long double>
    using Q_dbar = units::Quantity<Value, dbar>;
    namespace literals
    {
        static inline Q_dbar<long double> operator "" _dbar_ (long double _v) {
            return Q_dbar<long double>(_v); }
        static inline Q_dbar<long double> operator "" _dbar_ (unsigned long long int _v) {
            return Q_dbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cbar"
//
    struct cbar
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cbar";
        }
    };
    template<typename Value = long double>
    using Q_cbar = units::Quantity<Value, cbar>;
    namespace literals
    {
        static inline Q_cbar<long double> operator "" _cbar_ (long double _v) {
            return Q_cbar<long double>(_v); }
        static inline Q_cbar<long double> operator "" _cbar_ (unsigned long long int _v) {
            return Q_cbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mbar"
//
    struct mbar
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mbar";
        }
    };
    template<typename Value = long double>
    using Q_mbar = units::Quantity<Value, mbar>;
    namespace literals
    {
        static inline Q_mbar<long double> operator "" _mbar_ (long double _v) {
            return Q_mbar<long double>(_v); }
        static inline Q_mbar<long double> operator "" _mbar_ (unsigned long long int _v) {
            return Q_mbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ubar"
//
    struct ubar
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ubar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ubar";
        }
    };
    template<typename Value = long double>
    using Q_ubar = units::Quantity<Value, ubar>;
    namespace literals
    {
        static inline Q_ubar<long double> operator "" _ubar_ (long double _v) {
            return Q_ubar<long double>(_v); }
        static inline Q_ubar<long double> operator "" _ubar_ (unsigned long long int _v) {
            return Q_ubar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nbar"
//
    struct nbar
    {
        using factor_t = std::ratio<1, 10000>; // approx. 0.0001
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nbar";
        }
    };
    template<typename Value = long double>
    using Q_nbar = units::Quantity<Value, nbar>;
    namespace literals
    {
        static inline Q_nbar<long double> operator "" _nbar_ (long double _v) {
            return Q_nbar<long double>(_v); }
        static inline Q_nbar<long double> operator "" _nbar_ (unsigned long long int _v) {
            return Q_nbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pbar"
//
    struct pbar
    {
        using factor_t = std::ratio<1, 10000000>; // approx. 1e-07
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pbar";
        }
    };
    template<typename Value = long double>
    using Q_pbar = units::Quantity<Value, pbar>;
    namespace literals
    {
        static inline Q_pbar<long double> operator "" _pbar_ (long double _v) {
            return Q_pbar<long double>(_v); }
        static inline Q_pbar<long double> operator "" _pbar_ (unsigned long long int _v) {
            return Q_pbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "fbar"
//
    struct fbar
    {
        using factor_t = std::ratio<1, 10000000000>; // approx. 1e-10
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = fbar;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "fbar";
        }
    };
    template<typename Value = long double>
    using Q_fbar = units::Quantity<Value, fbar>;
    namespace literals
    {
        static inline Q_fbar<long double> operator "" _fbar_ (long double _v) {
            return Q_fbar<long double>(_v); }
        static inline Q_fbar<long double> operator "" _fbar_ (unsigned long long int _v) {
            return Q_fbar<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "psi"
//
    struct psi
    {
        using factor_t = std::ratio<172369, 25>; // approx. 6894.76
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = psi;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "psi";
        }
    };
    template<typename Value = long double>
    using Q_psi = units::Quantity<Value, psi>;
    namespace literals
    {
        static inline Q_psi<long double> operator "" _psi_ (long double _v) {
            return Q_psi<long double>(_v); }
        static inline Q_psi<long double> operator "" _psi_ (unsigned long long int _v) {
            return Q_psi<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "atm"
//
    struct atm
    {
        using factor_t = std::ratio<101325, 1>; // approx. 101325
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = atm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "atm";
        }
    };
    template<typename Value = long double>
    using Q_atm = units::Quantity<Value, atm>;
    namespace literals
    {
        static inline Q_atm<long double> operator "" _atm_ (long double _v) {
            return Q_atm<long double>(_v); }
        static inline Q_atm<long double> operator "" _atm_ (unsigned long long int _v) {
            return Q_atm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "torr"
//
    struct torr
    {
        using factor_t = std::ratio<66661, 500>; // approx. 133.322
        using dimensions_t = dimensions::Pressure;
        using offset_t = std::ratio<0, 1>;
        using relative_t = torr;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "torr";
        }
    };
    template<typename Value = long double>
    using Q_torr = units::Quantity<Value, torr>;
    namespace literals
    {
        static inline Q_torr<long double> operator "" _torr_ (long double _v) {
            return Q_torr<long double>(_v); }
        static inline Q_torr<long double> operator "" _torr_ (unsigned long long int _v) {
            return Q_torr<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TV"
//
    struct TV
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TV";
        }
    };
    template<typename Value = long double>
    using Q_TV = units::Quantity<Value, TV>;
    namespace literals
    {
        static inline Q_TV<long double> operator "" _TV_ (long double _v) {
            return Q_TV<long double>(_v); }
        static inline Q_TV<long double> operator "" _TV_ (unsigned long long int _v) {
            return Q_TV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GV"
//
    struct GV
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GV";
        }
    };
    template<typename Value = long double>
    using Q_GV = units::Quantity<Value, GV>;
    namespace literals
    {
        static inline Q_GV<long double> operator "" _GV_ (long double _v) {
            return Q_GV<long double>(_v); }
        static inline Q_GV<long double> operator "" _GV_ (unsigned long long int _v) {
            return Q_GV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MV"
//
    struct MV
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MV";
        }
    };
    template<typename Value = long double>
    using Q_MV = units::Quantity<Value, MV>;
    namespace literals
    {
        static inline Q_MV<long double> operator "" _MV_ (long double _v) {
            return Q_MV<long double>(_v); }
        static inline Q_MV<long double> operator "" _MV_ (unsigned long long int _v) {
            return Q_MV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kV"
//
    struct kV
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kV";
        }
    };
    template<typename Value = long double>
    using Q_kV = units::Quantity<Value, kV>;
    namespace literals
    {
        static inline Q_kV<long double> operator "" _kV_ (long double _v) {
            return Q_kV<long double>(_v); }
        static inline Q_kV<long double> operator "" _kV_ (unsigned long long int _v) {
            return Q_kV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hV"
//
    struct hV
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hV";
        }
    };
    template<typename Value = long double>
    using Q_hV = units::Quantity<Value, hV>;
    namespace literals
    {
        static inline Q_hV<long double> operator "" _hV_ (long double _v) {
            return Q_hV<long double>(_v); }
        static inline Q_hV<long double> operator "" _hV_ (unsigned long long int _v) {
            return Q_hV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daV"
//
    struct daV
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daV";
        }
    };
    template<typename Value = long double>
    using Q_daV = units::Quantity<Value, daV>;
    namespace literals
    {
        static inline Q_daV<long double> operator "" _daV_ (long double _v) {
            return Q_daV<long double>(_v); }
        static inline Q_daV<long double> operator "" _daV_ (unsigned long long int _v) {
            return Q_daV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "V"
//
    struct V
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = V;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "V";
        }
    };
    template<typename Value = long double>
    using Q_V = units::Quantity<Value, V>;
    namespace literals
    {
        static inline Q_V<long double> operator "" _V_ (long double _v) {
            return Q_V<long double>(_v); }
        static inline Q_V<long double> operator "" _V_ (unsigned long long int _v) {
            return Q_V<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dV"
//
    struct dV
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dV";
        }
    };
    template<typename Value = long double>
    using Q_dV = units::Quantity<Value, dV>;
    namespace literals
    {
        static inline Q_dV<long double> operator "" _dV_ (long double _v) {
            return Q_dV<long double>(_v); }
        static inline Q_dV<long double> operator "" _dV_ (unsigned long long int _v) {
            return Q_dV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cV"
//
    struct cV
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cV";
        }
    };
    template<typename Value = long double>
    using Q_cV = units::Quantity<Value, cV>;
    namespace literals
    {
        static inline Q_cV<long double> operator "" _cV_ (long double _v) {
            return Q_cV<long double>(_v); }
        static inline Q_cV<long double> operator "" _cV_ (unsigned long long int _v) {
            return Q_cV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mV"
//
    struct mV
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mV";
        }
    };
    template<typename Value = long double>
    using Q_mV = units::Quantity<Value, mV>;
    namespace literals
    {
        static inline Q_mV<long double> operator "" _mV_ (long double _v) {
            return Q_mV<long double>(_v); }
        static inline Q_mV<long double> operator "" _mV_ (unsigned long long int _v) {
            return Q_mV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uV"
//
    struct uV
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uV";
        }
    };
    template<typename Value = long double>
    using Q_uV = units::Quantity<Value, uV>;
    namespace literals
    {
        static inline Q_uV<long double> operator "" _uV_ (long double _v) {
            return Q_uV<long double>(_v); }
        static inline Q_uV<long double> operator "" _uV_ (unsigned long long int _v) {
            return Q_uV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nV"
//
    struct nV
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nV";
        }
    };
    template<typename Value = long double>
    using Q_nV = units::Quantity<Value, nV>;
    namespace literals
    {
        static inline Q_nV<long double> operator "" _nV_ (long double _v) {
            return Q_nV<long double>(_v); }
        static inline Q_nV<long double> operator "" _nV_ (unsigned long long int _v) {
            return Q_nV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pV"
//
    struct pV
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::ElectricPotential;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pV;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pV";
        }
    };
    template<typename Value = long double>
    using Q_pV = units::Quantity<Value, pV>;
    namespace literals
    {
        static inline Q_pV<long double> operator "" _pV_ (long double _v) {
            return Q_pV<long double>(_v); }
        static inline Q_pV<long double> operator "" _pV_ (unsigned long long int _v) {
            return Q_pV<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TA"
//
    struct TA
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TA";
        }
    };
    template<typename Value = long double>
    using Q_TA = units::Quantity<Value, TA>;
    namespace literals
    {
        static inline Q_TA<long double> operator "" _TA_ (long double _v) {
            return Q_TA<long double>(_v); }
        static inline Q_TA<long double> operator "" _TA_ (unsigned long long int _v) {
            return Q_TA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GA"
//
    struct GA
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GA";
        }
    };
    template<typename Value = long double>
    using Q_GA = units::Quantity<Value, GA>;
    namespace literals
    {
        static inline Q_GA<long double> operator "" _GA_ (long double _v) {
            return Q_GA<long double>(_v); }
        static inline Q_GA<long double> operator "" _GA_ (unsigned long long int _v) {
            return Q_GA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MA"
//
    struct MA
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MA";
        }
    };
    template<typename Value = long double>
    using Q_MA = units::Quantity<Value, MA>;
    namespace literals
    {
        static inline Q_MA<long double> operator "" _MA_ (long double _v) {
            return Q_MA<long double>(_v); }
        static inline Q_MA<long double> operator "" _MA_ (unsigned long long int _v) {
            return Q_MA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kA"
//
    struct kA
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kA";
        }
    };
    template<typename Value = long double>
    using Q_kA = units::Quantity<Value, kA>;
    namespace literals
    {
        static inline Q_kA<long double> operator "" _kA_ (long double _v) {
            return Q_kA<long double>(_v); }
        static inline Q_kA<long double> operator "" _kA_ (unsigned long long int _v) {
            return Q_kA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hA"
//
    struct hA
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hA";
        }
    };
    template<typename Value = long double>
    using Q_hA = units::Quantity<Value, hA>;
    namespace literals
    {
        static inline Q_hA<long double> operator "" _hA_ (long double _v) {
            return Q_hA<long double>(_v); }
        static inline Q_hA<long double> operator "" _hA_ (unsigned long long int _v) {
            return Q_hA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daA"
//
    struct daA
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daA";
        }
    };
    template<typename Value = long double>
    using Q_daA = units::Quantity<Value, daA>;
    namespace literals
    {
        static inline Q_daA<long double> operator "" _daA_ (long double _v) {
            return Q_daA<long double>(_v); }
        static inline Q_daA<long double> operator "" _daA_ (unsigned long long int _v) {
            return Q_daA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "A"
//
    struct A
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = A;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "A";
        }
    };
    template<typename Value = long double>
    using Q_A = units::Quantity<Value, A>;
    namespace literals
    {
        static inline Q_A<long double> operator "" _A_ (long double _v) {
            return Q_A<long double>(_v); }
        static inline Q_A<long double> operator "" _A_ (unsigned long long int _v) {
            return Q_A<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dA"
//
    struct dA
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dA";
        }
    };
    template<typename Value = long double>
    using Q_dA = units::Quantity<Value, dA>;
    namespace literals
    {
        static inline Q_dA<long double> operator "" _dA_ (long double _v) {
            return Q_dA<long double>(_v); }
        static inline Q_dA<long double> operator "" _dA_ (unsigned long long int _v) {
            return Q_dA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cA"
//
    struct cA
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cA";
        }
    };
    template<typename Value = long double>
    using Q_cA = units::Quantity<Value, cA>;
    namespace literals
    {
        static inline Q_cA<long double> operator "" _cA_ (long double _v) {
            return Q_cA<long double>(_v); }
        static inline Q_cA<long double> operator "" _cA_ (unsigned long long int _v) {
            return Q_cA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mA"
//
    struct mA
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mA";
        }
    };
    template<typename Value = long double>
    using Q_mA = units::Quantity<Value, mA>;
    namespace literals
    {
        static inline Q_mA<long double> operator "" _mA_ (long double _v) {
            return Q_mA<long double>(_v); }
        static inline Q_mA<long double> operator "" _mA_ (unsigned long long int _v) {
            return Q_mA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uA"
//
    struct uA
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uA";
        }
    };
    template<typename Value = long double>
    using Q_uA = units::Quantity<Value, uA>;
    namespace literals
    {
        static inline Q_uA<long double> operator "" _uA_ (long double _v) {
            return Q_uA<long double>(_v); }
        static inline Q_uA<long double> operator "" _uA_ (unsigned long long int _v) {
            return Q_uA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nA"
//
    struct nA
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nA";
        }
    };
    template<typename Value = long double>
    using Q_nA = units::Quantity<Value, nA>;
    namespace literals
    {
        static inline Q_nA<long double> operator "" _nA_ (long double _v) {
            return Q_nA<long double>(_v); }
        static inline Q_nA<long double> operator "" _nA_ (unsigned long long int _v) {
            return Q_nA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pA"
//
    struct pA
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::ElectricCurrent;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pA;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pA";
        }
    };
    template<typename Value = long double>
    using Q_pA = units::Quantity<Value, pA>;
    namespace literals
    {
        static inline Q_pA<long double> operator "" _pA_ (long double _v) {
            return Q_pA<long double>(_v); }
        static inline Q_pA<long double> operator "" _pA_ (unsigned long long int _v) {
            return Q_pA<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Pohm"
//
    struct Pohm
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Pohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Pohm";
        }
    };
    template<typename Value = long double>
    using Q_Pohm = units::Quantity<Value, Pohm>;
    namespace literals
    {
        static inline Q_Pohm<long double> operator "" _Pohm_ (long double _v) {
            return Q_Pohm<long double>(_v); }
        static inline Q_Pohm<long double> operator "" _Pohm_ (unsigned long long int _v) {
            return Q_Pohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Tohm"
//
    struct Tohm
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Tohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Tohm";
        }
    };
    template<typename Value = long double>
    using Q_Tohm = units::Quantity<Value, Tohm>;
    namespace literals
    {
        static inline Q_Tohm<long double> operator "" _Tohm_ (long double _v) {
            return Q_Tohm<long double>(_v); }
        static inline Q_Tohm<long double> operator "" _Tohm_ (unsigned long long int _v) {
            return Q_Tohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Gohm"
//
    struct Gohm
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Gohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Gohm";
        }
    };
    template<typename Value = long double>
    using Q_Gohm = units::Quantity<Value, Gohm>;
    namespace literals
    {
        static inline Q_Gohm<long double> operator "" _Gohm_ (long double _v) {
            return Q_Gohm<long double>(_v); }
        static inline Q_Gohm<long double> operator "" _Gohm_ (unsigned long long int _v) {
            return Q_Gohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "Mohm"
//
    struct Mohm
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = Mohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "Mohm";
        }
    };
    template<typename Value = long double>
    using Q_Mohm = units::Quantity<Value, Mohm>;
    namespace literals
    {
        static inline Q_Mohm<long double> operator "" _Mohm_ (long double _v) {
            return Q_Mohm<long double>(_v); }
        static inline Q_Mohm<long double> operator "" _Mohm_ (unsigned long long int _v) {
            return Q_Mohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kohm"
//
    struct kohm
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kohm";
        }
    };
    template<typename Value = long double>
    using Q_kohm = units::Quantity<Value, kohm>;
    namespace literals
    {
        static inline Q_kohm<long double> operator "" _kohm_ (long double _v) {
            return Q_kohm<long double>(_v); }
        static inline Q_kohm<long double> operator "" _kohm_ (unsigned long long int _v) {
            return Q_kohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hohm"
//
    struct hohm
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hohm";
        }
    };
    template<typename Value = long double>
    using Q_hohm = units::Quantity<Value, hohm>;
    namespace literals
    {
        static inline Q_hohm<long double> operator "" _hohm_ (long double _v) {
            return Q_hohm<long double>(_v); }
        static inline Q_hohm<long double> operator "" _hohm_ (unsigned long long int _v) {
            return Q_hohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daohm"
//
    struct daohm
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daohm";
        }
    };
    template<typename Value = long double>
    using Q_daohm = units::Quantity<Value, daohm>;
    namespace literals
    {
        static inline Q_daohm<long double> operator "" _daohm_ (long double _v) {
            return Q_daohm<long double>(_v); }
        static inline Q_daohm<long double> operator "" _daohm_ (unsigned long long int _v) {
            return Q_daohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "ohm"
//
    struct ohm
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = ohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "ohm";
        }
    };
    template<typename Value = long double>
    using Q_ohm = units::Quantity<Value, ohm>;
    namespace literals
    {
        static inline Q_ohm<long double> operator "" _ohm_ (long double _v) {
            return Q_ohm<long double>(_v); }
        static inline Q_ohm<long double> operator "" _ohm_ (unsigned long long int _v) {
            return Q_ohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dohm"
//
    struct dohm
    {
        using factor_t = std::ratio<1, 10000>; // approx. 0.0001
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dohm";
        }
    };
    template<typename Value = long double>
    using Q_dohm = units::Quantity<Value, dohm>;
    namespace literals
    {
        static inline Q_dohm<long double> operator "" _dohm_ (long double _v) {
            return Q_dohm<long double>(_v); }
        static inline Q_dohm<long double> operator "" _dohm_ (unsigned long long int _v) {
            return Q_dohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cohm"
//
    struct cohm
    {
        using factor_t = std::ratio<1, 100000>; // approx. 1e-05
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cohm";
        }
    };
    template<typename Value = long double>
    using Q_cohm = units::Quantity<Value, cohm>;
    namespace literals
    {
        static inline Q_cohm<long double> operator "" _cohm_ (long double _v) {
            return Q_cohm<long double>(_v); }
        static inline Q_cohm<long double> operator "" _cohm_ (unsigned long long int _v) {
            return Q_cohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mohm"
//
    struct mohm
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mohm";
        }
    };
    template<typename Value = long double>
    using Q_mohm = units::Quantity<Value, mohm>;
    namespace literals
    {
        static inline Q_mohm<long double> operator "" _mohm_ (long double _v) {
            return Q_mohm<long double>(_v); }
        static inline Q_mohm<long double> operator "" _mohm_ (unsigned long long int _v) {
            return Q_mohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uohm"
//
    struct uohm
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uohm";
        }
    };
    template<typename Value = long double>
    using Q_uohm = units::Quantity<Value, uohm>;
    namespace literals
    {
        static inline Q_uohm<long double> operator "" _uohm_ (long double _v) {
            return Q_uohm<long double>(_v); }
        static inline Q_uohm<long double> operator "" _uohm_ (unsigned long long int _v) {
            return Q_uohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nohm"
//
    struct nohm
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::ElectricalResistance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nohm;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nohm";
        }
    };
    template<typename Value = long double>
    using Q_nohm = units::Quantity<Value, nohm>;
    namespace literals
    {
        static inline Q_nohm<long double> operator "" _nohm_ (long double _v) {
            return Q_nohm<long double>(_v); }
        static inline Q_nohm<long double> operator "" _nohm_ (unsigned long long int _v) {
            return Q_nohm<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GS"
//
    struct GS
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GS";
        }
    };
    template<typename Value = long double>
    using Q_GS = units::Quantity<Value, GS>;
    namespace literals
    {
        static inline Q_GS<long double> operator "" _GS_ (long double _v) {
            return Q_GS<long double>(_v); }
        static inline Q_GS<long double> operator "" _GS_ (unsigned long long int _v) {
            return Q_GS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MS"
//
    struct MS
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MS";
        }
    };
    template<typename Value = long double>
    using Q_MS = units::Quantity<Value, MS>;
    namespace literals
    {
        static inline Q_MS<long double> operator "" _MS_ (long double _v) {
            return Q_MS<long double>(_v); }
        static inline Q_MS<long double> operator "" _MS_ (unsigned long long int _v) {
            return Q_MS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kS"
//
    struct kS
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kS";
        }
    };
    template<typename Value = long double>
    using Q_kS = units::Quantity<Value, kS>;
    namespace literals
    {
        static inline Q_kS<long double> operator "" _kS_ (long double _v) {
            return Q_kS<long double>(_v); }
        static inline Q_kS<long double> operator "" _kS_ (unsigned long long int _v) {
            return Q_kS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hS"
//
    struct hS
    {
        using factor_t = std::ratio<100000, 1>; // approx. 100000
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hS";
        }
    };
    template<typename Value = long double>
    using Q_hS = units::Quantity<Value, hS>;
    namespace literals
    {
        static inline Q_hS<long double> operator "" _hS_ (long double _v) {
            return Q_hS<long double>(_v); }
        static inline Q_hS<long double> operator "" _hS_ (unsigned long long int _v) {
            return Q_hS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daS"
//
    struct daS
    {
        using factor_t = std::ratio<10000, 1>; // approx. 10000
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daS";
        }
    };
    template<typename Value = long double>
    using Q_daS = units::Quantity<Value, daS>;
    namespace literals
    {
        static inline Q_daS<long double> operator "" _daS_ (long double _v) {
            return Q_daS<long double>(_v); }
        static inline Q_daS<long double> operator "" _daS_ (unsigned long long int _v) {
            return Q_daS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "S"
//
    struct S
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = S;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "S";
        }
    };
    template<typename Value = long double>
    using Q_S = units::Quantity<Value, S>;
    namespace literals
    {
        static inline Q_S<long double> operator "" _S_ (long double _v) {
            return Q_S<long double>(_v); }
        static inline Q_S<long double> operator "" _S_ (unsigned long long int _v) {
            return Q_S<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dS"
//
    struct dS
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dS";
        }
    };
    template<typename Value = long double>
    using Q_dS = units::Quantity<Value, dS>;
    namespace literals
    {
        static inline Q_dS<long double> operator "" _dS_ (long double _v) {
            return Q_dS<long double>(_v); }
        static inline Q_dS<long double> operator "" _dS_ (unsigned long long int _v) {
            return Q_dS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cS"
//
    struct cS
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cS";
        }
    };
    template<typename Value = long double>
    using Q_cS = units::Quantity<Value, cS>;
    namespace literals
    {
        static inline Q_cS<long double> operator "" _cS_ (long double _v) {
            return Q_cS<long double>(_v); }
        static inline Q_cS<long double> operator "" _cS_ (unsigned long long int _v) {
            return Q_cS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mS"
//
    struct mS
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mS";
        }
    };
    template<typename Value = long double>
    using Q_mS = units::Quantity<Value, mS>;
    namespace literals
    {
        static inline Q_mS<long double> operator "" _mS_ (long double _v) {
            return Q_mS<long double>(_v); }
        static inline Q_mS<long double> operator "" _mS_ (unsigned long long int _v) {
            return Q_mS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uS"
//
    struct uS
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uS";
        }
    };
    template<typename Value = long double>
    using Q_uS = units::Quantity<Value, uS>;
    namespace literals
    {
        static inline Q_uS<long double> operator "" _uS_ (long double _v) {
            return Q_uS<long double>(_v); }
        static inline Q_uS<long double> operator "" _uS_ (unsigned long long int _v) {
            return Q_uS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nS"
//
    struct nS
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nS";
        }
    };
    template<typename Value = long double>
    using Q_nS = units::Quantity<Value, nS>;
    namespace literals
    {
        static inline Q_nS<long double> operator "" _nS_ (long double _v) {
            return Q_nS<long double>(_v); }
        static inline Q_nS<long double> operator "" _nS_ (unsigned long long int _v) {
            return Q_nS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pS"
//
    struct pS
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pS";
        }
    };
    template<typename Value = long double>
    using Q_pS = units::Quantity<Value, pS>;
    namespace literals
    {
        static inline Q_pS<long double> operator "" _pS_ (long double _v) {
            return Q_pS<long double>(_v); }
        static inline Q_pS<long double> operator "" _pS_ (unsigned long long int _v) {
            return Q_pS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "fS"
//
    struct fS
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::ElectricalConductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = fS;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "fS";
        }
    };
    template<typename Value = long double>
    using Q_fS = units::Quantity<Value, fS>;
    namespace literals
    {
        static inline Q_fS<long double> operator "" _fS_ (long double _v) {
            return Q_fS<long double>(_v); }
        static inline Q_fS<long double> operator "" _fS_ (unsigned long long int _v) {
            return Q_fS<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GF"
//
    struct GF
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GF";
        }
    };
    template<typename Value = long double>
    using Q_GF = units::Quantity<Value, GF>;
    namespace literals
    {
        static inline Q_GF<long double> operator "" _GF_ (long double _v) {
            return Q_GF<long double>(_v); }
        static inline Q_GF<long double> operator "" _GF_ (unsigned long long int _v) {
            return Q_GF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MF"
//
    struct MF
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MF";
        }
    };
    template<typename Value = long double>
    using Q_MF = units::Quantity<Value, MF>;
    namespace literals
    {
        static inline Q_MF<long double> operator "" _MF_ (long double _v) {
            return Q_MF<long double>(_v); }
        static inline Q_MF<long double> operator "" _MF_ (unsigned long long int _v) {
            return Q_MF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kF"
//
    struct kF
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kF";
        }
    };
    template<typename Value = long double>
    using Q_kF = units::Quantity<Value, kF>;
    namespace literals
    {
        static inline Q_kF<long double> operator "" _kF_ (long double _v) {
            return Q_kF<long double>(_v); }
        static inline Q_kF<long double> operator "" _kF_ (unsigned long long int _v) {
            return Q_kF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hF"
//
    struct hF
    {
        using factor_t = std::ratio<100000, 1>; // approx. 100000
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hF";
        }
    };
    template<typename Value = long double>
    using Q_hF = units::Quantity<Value, hF>;
    namespace literals
    {
        static inline Q_hF<long double> operator "" _hF_ (long double _v) {
            return Q_hF<long double>(_v); }
        static inline Q_hF<long double> operator "" _hF_ (unsigned long long int _v) {
            return Q_hF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daF"
//
    struct daF
    {
        using factor_t = std::ratio<10000, 1>; // approx. 10000
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daF";
        }
    };
    template<typename Value = long double>
    using Q_daF = units::Quantity<Value, daF>;
    namespace literals
    {
        static inline Q_daF<long double> operator "" _daF_ (long double _v) {
            return Q_daF<long double>(_v); }
        static inline Q_daF<long double> operator "" _daF_ (unsigned long long int _v) {
            return Q_daF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "F"
//
    struct F
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = F;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "F";
        }
    };
    template<typename Value = long double>
    using Q_F = units::Quantity<Value, F>;
    namespace literals
    {
        static inline Q_F<long double> operator "" _F_ (long double _v) {
            return Q_F<long double>(_v); }
        static inline Q_F<long double> operator "" _F_ (unsigned long long int _v) {
            return Q_F<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dF"
//
    struct dF
    {
        using factor_t = std::ratio<100, 1>; // approx. 100
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dF";
        }
    };
    template<typename Value = long double>
    using Q_dF = units::Quantity<Value, dF>;
    namespace literals
    {
        static inline Q_dF<long double> operator "" _dF_ (long double _v) {
            return Q_dF<long double>(_v); }
        static inline Q_dF<long double> operator "" _dF_ (unsigned long long int _v) {
            return Q_dF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cF"
//
    struct cF
    {
        using factor_t = std::ratio<10, 1>; // approx. 10
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cF";
        }
    };
    template<typename Value = long double>
    using Q_cF = units::Quantity<Value, cF>;
    namespace literals
    {
        static inline Q_cF<long double> operator "" _cF_ (long double _v) {
            return Q_cF<long double>(_v); }
        static inline Q_cF<long double> operator "" _cF_ (unsigned long long int _v) {
            return Q_cF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mF"
//
    struct mF
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mF";
        }
    };
    template<typename Value = long double>
    using Q_mF = units::Quantity<Value, mF>;
    namespace literals
    {
        static inline Q_mF<long double> operator "" _mF_ (long double _v) {
            return Q_mF<long double>(_v); }
        static inline Q_mF<long double> operator "" _mF_ (unsigned long long int _v) {
            return Q_mF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uF"
//
    struct uF
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uF";
        }
    };
    template<typename Value = long double>
    using Q_uF = units::Quantity<Value, uF>;
    namespace literals
    {
        static inline Q_uF<long double> operator "" _uF_ (long double _v) {
            return Q_uF<long double>(_v); }
        static inline Q_uF<long double> operator "" _uF_ (unsigned long long int _v) {
            return Q_uF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nF"
//
    struct nF
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nF";
        }
    };
    template<typename Value = long double>
    using Q_nF = units::Quantity<Value, nF>;
    namespace literals
    {
        static inline Q_nF<long double> operator "" _nF_ (long double _v) {
            return Q_nF<long double>(_v); }
        static inline Q_nF<long double> operator "" _nF_ (unsigned long long int _v) {
            return Q_nF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "pF"
//
    struct pF
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = pF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "pF";
        }
    };
    template<typename Value = long double>
    using Q_pF = units::Quantity<Value, pF>;
    namespace literals
    {
        static inline Q_pF<long double> operator "" _pF_ (long double _v) {
            return Q_pF<long double>(_v); }
        static inline Q_pF<long double> operator "" _pF_ (unsigned long long int _v) {
            return Q_pF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "fF"
//
    struct fF
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Capacitance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = fF;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "fF";
        }
    };
    template<typename Value = long double>
    using Q_fF = units::Quantity<Value, fF>;
    namespace literals
    {
        static inline Q_fF<long double> operator "" _fF_ (long double _v) {
            return Q_fF<long double>(_v); }
        static inline Q_fF<long double> operator "" _fF_ (unsigned long long int _v) {
            return Q_fF<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "PH"
//
    struct PH
    {
        using factor_t = std::ratio<1000000000000, 1>; // approx. 1e+12
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = PH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "PH";
        }
    };
    template<typename Value = long double>
    using Q_PH = units::Quantity<Value, PH>;
    namespace literals
    {
        static inline Q_PH<long double> operator "" _PH_ (long double _v) {
            return Q_PH<long double>(_v); }
        static inline Q_PH<long double> operator "" _PH_ (unsigned long long int _v) {
            return Q_PH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "TH"
//
    struct TH
    {
        using factor_t = std::ratio<1000000000, 1>; // approx. 1e+09
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = TH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "TH";
        }
    };
    template<typename Value = long double>
    using Q_TH = units::Quantity<Value, TH>;
    namespace literals
    {
        static inline Q_TH<long double> operator "" _TH_ (long double _v) {
            return Q_TH<long double>(_v); }
        static inline Q_TH<long double> operator "" _TH_ (unsigned long long int _v) {
            return Q_TH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "GH"
//
    struct GH
    {
        using factor_t = std::ratio<1000000, 1>; // approx. 1e+06
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = GH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "GH";
        }
    };
    template<typename Value = long double>
    using Q_GH = units::Quantity<Value, GH>;
    namespace literals
    {
        static inline Q_GH<long double> operator "" _GH_ (long double _v) {
            return Q_GH<long double>(_v); }
        static inline Q_GH<long double> operator "" _GH_ (unsigned long long int _v) {
            return Q_GH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "MH"
//
    struct MH
    {
        using factor_t = std::ratio<1000, 1>; // approx. 1000
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = MH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "MH";
        }
    };
    template<typename Value = long double>
    using Q_MH = units::Quantity<Value, MH>;
    namespace literals
    {
        static inline Q_MH<long double> operator "" _MH_ (long double _v) {
            return Q_MH<long double>(_v); }
        static inline Q_MH<long double> operator "" _MH_ (unsigned long long int _v) {
            return Q_MH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "kH"
//
    struct kH
    {
        using factor_t = std::ratio<1, 1>; // approx. 1
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = kH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "kH";
        }
    };
    template<typename Value = long double>
    using Q_kH = units::Quantity<Value, kH>;
    namespace literals
    {
        static inline Q_kH<long double> operator "" _kH_ (long double _v) {
            return Q_kH<long double>(_v); }
        static inline Q_kH<long double> operator "" _kH_ (unsigned long long int _v) {
            return Q_kH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "hH"
//
    struct hH
    {
        using factor_t = std::ratio<1, 10>; // approx. 0.1
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = hH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "hH";
        }
    };
    template<typename Value = long double>
    using Q_hH = units::Quantity<Value, hH>;
    namespace literals
    {
        static inline Q_hH<long double> operator "" _hH_ (long double _v) {
            return Q_hH<long double>(_v); }
        static inline Q_hH<long double> operator "" _hH_ (unsigned long long int _v) {
            return Q_hH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "daH"
//
    struct daH
    {
        using factor_t = std::ratio<1, 100>; // approx. 0.01
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = daH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "daH";
        }
    };
    template<typename Value = long double>
    using Q_daH = units::Quantity<Value, daH>;
    namespace literals
    {
        static inline Q_daH<long double> operator "" _daH_ (long double _v) {
            return Q_daH<long double>(_v); }
        static inline Q_daH<long double> operator "" _daH_ (unsigned long long int _v) {
            return Q_daH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "H"
//
    struct H
    {
        using factor_t = std::ratio<1, 1000>; // approx. 0.001
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = H;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "H";
        }
    };
    template<typename Value = long double>
    using Q_H = units::Quantity<Value, H>;
    namespace literals
    {
        static inline Q_H<long double> operator "" _H_ (long double _v) {
            return Q_H<long double>(_v); }
        static inline Q_H<long double> operator "" _H_ (unsigned long long int _v) {
            return Q_H<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "dH"
//
    struct dH
    {
        using factor_t = std::ratio<1, 10000>; // approx. 0.0001
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = dH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "dH";
        }
    };
    template<typename Value = long double>
    using Q_dH = units::Quantity<Value, dH>;
    namespace literals
    {
        static inline Q_dH<long double> operator "" _dH_ (long double _v) {
            return Q_dH<long double>(_v); }
        static inline Q_dH<long double> operator "" _dH_ (unsigned long long int _v) {
            return Q_dH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "cH"
//
    struct cH
    {
        using factor_t = std::ratio<1, 100000>; // approx. 1e-05
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = cH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "cH";
        }
    };
    template<typename Value = long double>
    using Q_cH = units::Quantity<Value, cH>;
    namespace literals
    {
        static inline Q_cH<long double> operator "" _cH_ (long double _v) {
            return Q_cH<long double>(_v); }
        static inline Q_cH<long double> operator "" _cH_ (unsigned long long int _v) {
            return Q_cH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "mH"
//
    struct mH
    {
        using factor_t = std::ratio<1, 1000000>; // approx. 1e-06
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = mH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "mH";
        }
    };
    template<typename Value = long double>
    using Q_mH = units::Quantity<Value, mH>;
    namespace literals
    {
        static inline Q_mH<long double> operator "" _mH_ (long double _v) {
            return Q_mH<long double>(_v); }
        static inline Q_mH<long double> operator "" _mH_ (unsigned long long int _v) {
            return Q_mH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "uH"
//
    struct uH
    {
        using factor_t = std::ratio<1, 1000000000>; // approx. 1e-09
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = uH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "uH";
        }
    };
    template<typename Value = long double>
    using Q_uH = units::Quantity<Value, uH>;
    namespace literals
    {
        static inline Q_uH<long double> operator "" _uH_ (long double _v) {
            return Q_uH<long double>(_v); }
        static inline Q_uH<long double> operator "" _uH_ (unsigned long long int _v) {
            return Q_uH<long double>(static_cast<long double>(_v)); }
    }



//
// Unit "nH"
//
    struct nH
    {
        using factor_t = std::ratio<1, 1000000000000>; // approx. 1e-12
        using dimensions_t = dimensions::Inductance;
        using offset_t = std::ratio<0, 1>;
        using relative_t = nH;
        static constexpr bool absolute = false;
        template<typename Stream>
        static void streamname(Stream& _stream) {
            _stream << "nH";
        }
    };
    template<typename Value = long double>
    using Q_nH = units::Quantity<Value, nH>;
    namespace literals
    {
        static inline Q_nH<long double> operator "" _nH_ (long double _v) {
            return Q_nH<long double>(_v); }
        static inline Q_nH<long double> operator "" _nH_ (unsigned long long int _v) {
            return Q_nH<long double>(static_cast<long double>(_v)); }
    }

} /*namespace mks*/
} /*namespace units*/
} /*namespace chandra*/
#endif /*CHANDRA_MKS_UNITS_H*/
