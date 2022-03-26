#ifndef CHANDRA_FT25H_H
#define CHANDRA_FT25H_H

#include<spi_flash_25_series.h>

namespace chandra
{
namespace drivers
{

using FT25H16Configuration = FlashConfiguration<256, 8192, 4096, 512, 1>;
using FT25H16JEDECID = JEDECFlashID<0x0E, 0x40, 0x15>;

template<class FlashConfiguration, class JEDECID, bool RangeChecked=true>
class FT25Hxx : public  SPIFlash25Series<FT25Hxx<FlashConfiguration, JEDECID, RangeChecked>, FlashConfiguration, JEDECID, RangeChecked>
{
    public:
        using base_t = SPIFlash25Series<FT25Hxx<FlashConfiguration, JEDECID, RangeChecked>, FlashConfiguration, JEDECID, RangeChecked>;
        using base_t::SPIFlash25Series;
};

using FT25H16 = FT25Hxx<FT25H16Configuration, FT25H16JEDECID>;

} /*namespace drivers*/
} /*namespace chandra*/
#endif /* CHANDRA_FT25H_H */
