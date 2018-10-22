#ifndef CHANDRA_THERMAL_H
#define CHANDRA_THERMAL_H

#include "quantity.h"
#include "units.h"

namespace chandra
{
namespace drivers
{

template<typename Derived, typename Value>
class Thermal
{
    public:
        using value_t = Value;

    protected:
        template<typename Impl, typename BaseUnits>
        class Proxy
        {
            public:
                Proxy(value_t& _v) : v_(_v) {}

                // Current reading of the axes
                constexpr auto quantity() const {
                    return units::Quantity<value_t, BaseUnits>{v_};
                }

                constexpr auto operator () () const { return quantity(); }

            protected:
                value_t& v_;
        };
};

template<typename Derived, typename Value, typename TempUnits = units::mks::degC>
class Thermometer : public Thermal<Thermometer<Derived, Value, TempUnits>, Value>
{
    protected:
        friend class Thermal<Thermometer<Derived, Value, TempUnits>, Value>;
        using base_t = Thermal<Thermometer<Derived, Value, TempUnits>, Value>;
        using thermometer_proxy_t = typename base_t::template Proxy<Derived, TempUnits>;
        typename base_t::value_t temp_raw_;

    public:
        Thermometer() : temperature(temp_raw_) {}
        thermometer_proxy_t temperature;
};

}/*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_THERMAL_H*/
