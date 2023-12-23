#ifndef CHANDRA_S25FL_H
#define CHANDRA_S25FL_H

#include <flash_utils.h>
#include <spi.h>
#include <spi_flash_25_series.h>

namespace chandra
{
namespace drivers
{

using S25FL064LConfiguration = FlashConfiguration<256, 8192, 4096, 512, 1>; // THIS IS NOT CORRECT
using S25FL064LJEDECID = JEDECFlashID<0xBF, 0x25, 0xBE>;

template<class FlashConfiguration, class JEDECID, bool RangeChecked=true>
class S25FL0xx : public SPIFlash25Series<S25FL0xx<FlashConfiguration, JEDECID, RangeChecked>, FlashConfiguration, JEDECID, RangeChecked>
{
    public:
        using base_t = SPIFlash25Series<S25FL0xx<FlashConfiguration, JEDECID, RangeChecked>, FlashConfiguration, JEDECID, RangeChecked>;
        using base_t::SPIFlash25Series;
};

using S25FL064L = S25FL0xx<S25FL064LConfiguration, S25FL064LJEDECID>;

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_S25FL_H*/
