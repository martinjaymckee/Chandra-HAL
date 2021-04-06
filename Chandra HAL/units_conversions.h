#ifndef CHANDRA_UNITS_CONVERSIONS_H
#define CHANDRA_UNITS_CONVERSIONS_H

#include <ratio>

#include "quantity.h"

namespace chandra
{
namespace units
{
namespace conversions
{
namespace internal
{
template<class Ratio>
struct ChronoTimeUnits
{
  using factor_t = Ratio;//std::ratio<1000000000000000, 1>;
  using dimensions_t = dimensions::Time;
  using offset_t = std::ratio<0, 1>;
  // using relative_t = Eg;
  static constexpr bool absolute = false;
};

}
template<class Quantity, class ChronoDuration>
Quantity chronoToQuantity(const ChronoDuration& _t) {
  using value_t = typename Quantity::value_t;
  using dest_t = typename Quantity::units_t;
  using src_t = internal::ChronoTimeUnits<typename ChronoDuration::period>;

  return Quantity{chandra::units::convert<value_t, dest_t, src_t>(_t.count())};
}

template<class ChronoDuration, class Quantity>
ChronoDuration quantityToChrono(const Quantity& _t) {
  return ChronoDuration{_t.value()}; // TODO: THIS IS A HACK....
}

} /*namespace conversions*/
} /*namespace units*/
} /*namespace chandra*/

#endif /*CHANDRA_UNITS_CONVERSIONS_H*/
