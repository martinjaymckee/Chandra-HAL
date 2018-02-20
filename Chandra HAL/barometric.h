#ifndef CHANDRA_BAROMETRIC_H
#define CHANDRA_BAROMETRIC_H

// TODO: IMPORT A SERIAL REGISTER ACCESS HEADER TO ALLOW FOR REGISTER ACCESSES USING BOTH
//  I2C AND SPI


// TODO: EVERYTHING HERE SHOULD RETURN A QUANTITY THAT CAN BE CONVERTED TO OTHER UNITS

namespace chandra
{
namespace drivers
{

// TODO: THIS ALSO NEEDS TO IMPORT SOME TYPE OF CONVERSION TO BE USED FOR RETURNING THE CORRECT VALUES
template<typename Value, typename Interface, typename Conversion>
class Barometric
{
    public:
        using value_t = Value;

        struct BarometricStatus
        {
            value_t pressure;
            value_t temperature;
        };

        Barometric() {}

        value_t pressure() { update(); return pressure_; }
        value_t temperature() { update(); return temperature_; }
        BarometricStatus status() { update(); return {pressure_, temperature_}; }

        bool update() { return false; } // THIS IS WHERE THE READING GOES....

    protected:
        value_t pressure_;
        value_t temperature_;
};

// TODO: IMPLEMENT ALTITUDE CALCULATOR FUNCTIONS
// TODO: THESE NEED TO BE TESTED....
template<typename Value, typename Interface, typename Conversion>
Value isaAltitude(const Barometric<Value, Interface, Conversion>& _baro, const auto& p0 = 1015.0) {
    const auto e = Value(1.0) / Value(5.255);
    const auto C = Value(44330.0);
    const auto r = _baro.status();
    return C * ( Value(1.0) - pow(r.pressure / p0, e));
}

template<typename Value, typename Interface, typename Conversion>
Value hypsometricAltitude(const Barometric<Value, Interface, Conversion>& _baro,
                          const auto& p0 = 1015.0, const auto& L = 0.0065) {
    const auto e = Value(1.0) / Value(5.255);
    const auto r = _baro.status();
    return (r.temperature / L)* (pow(p0 / r.pressure, e));
}

// TODO: THERE SHOULD ALSO BE SOME COMPENSATED PRESSURE/TEMPERATURE CALCULATION
//  FUNCTIONS TO ALLOW FOR BARO CALIBRATION AS THINGS MOVE FORWARD

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_BAROMETRIC_H*/

