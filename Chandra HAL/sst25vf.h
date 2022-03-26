#ifndef CHANDRA_SST25VF_H
#define CHANDRA_SST25VF_H

#include <flash_utils.h>
#include <spi.h>
#include <spi_flash_25_series.h>

namespace chandra
{
namespace drivers
{

using SST25VF080BConfiguration = FlashConfiguration<256, 8192, 4096, 512, 1>; // THIS IS NOT CORRECT
using SST25VF080BJEDECID = JEDECFlashID<0xBF, 0x25, 0xBE>;

using SST25VF016BConfiguration = FlashConfiguration<256, 8192, 4096, 512, 1>; // THIS IS NOT CORRECT
using SST25VF016BJEDECID = JEDECFlashID<0xBF, 0x25, 0x41>;

template<class FlashConfiguration, class JEDECID, bool RangeChecked=true>
class SST25VF0xx : public SPIFlash25Series<SST25VF0xx<FlashConfiguration, JEDECID, RangeChecked>, FlashConfiguration, JEDECID, RangeChecked>
{
    public:
        using base_t = SPIFlash25Series<SST25VF0xx<FlashConfiguration, JEDECID, RangeChecked>, FlashConfiguration, JEDECID, RangeChecked>;
        using base_t::SPIFlash25Series;
};

using SST25VF080B = SST25VF0xx<SST25VF080BConfiguration, SST25VF080BJEDECID>;
using SST25VF016B = SST25VF0xx<SST25VF016BConfiguration, SST25VF016BJEDECID>;

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_SST25VF_H*/
