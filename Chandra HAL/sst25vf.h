#ifndef CHANDRA_SST25VF_H
#define CHANDRA_SST25VF_H

#include <flash_utils.h>
#include <spi.h>
#include <spi_flash_25_series.h>

namespace chandra
{
namespace drivers
{

using SST25VF080Configuration = FlashConfiguration<256, 8192, 4096, 512, 1>; // THIS IS NOT CORRECT
using SST25VF080JEDECID = JEDECFlashID<0xBF, 0x25, 0xBE>;

using SST25VF016Configuration = FlashConfiguration<256, 8192, 4096, 512, 1>; // THIS IS NOT CORRECT
using SST25VF016JEDECID = JEDECFlashID<0xBF, 0x25, 0x41>;

template<class FlashConfiguration, class JEDECID>
class SST25VF0xx : public SPIFlash25Series<SST25VF0xx<FlashConfiguration, JEDECID>, FlashConfiguration, JEDECID>
{
    public:
        using base_t = SPIFlash25Series<SST25VF0xx<FlashConfiguration, JEDECID>, FlashConfiguration, JEDECID>;
        using base_t::SPIFlash25Series;

    protected:

};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_SST25VF_H*/
