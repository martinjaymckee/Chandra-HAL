#ifndef CHANDRA_FLASH_UTILS_H
#define CHANDRA_FLASH_UTILS_H

#include<algorithm>

namespace chandra
{
namespace drivers
{

struct AddressRange
{
        size_t start;
        size_t end;

        operator bool() const { return end > start; }
};

struct SectorRange
{
        size_t start;
        size_t end;

        operator bool() const { return end > start; }
};

template<uint8_t Manufacturer, uint8_t Type, uint8_t Capacity>
struct JEDECFlashID
{
    uint8_t manufacturer;
    uint8_t type;
    uint8_t capacity;

    operator bool() const {
      return (manufacturer == Manufacturer) and
          (type == Type) and (capacity == Capacity);
    }
};

// TODO: NEED TO REMOVE PAGES FROM THE CONFIGURATION AND CALCULATE NUMBER OF PAGES FROM THE CAPACITY AND PAGE SIZE, CAPACITY FROM THE SECTOR SIZE AND NUMBER OF SECTORS
template<size_t PageSize=256, size_t Pages=8192, size_t SectorSize=4096,
  size_t Sectors=512, size_t AccessBytes=1>
struct FlashConfiguration
{
  //
  // Configuration Values
  //
  static constexpr size_t pageSize() { return PageSize; }
  static constexpr size_t pages() { return Pages; }
  static constexpr size_t sectorSize() { return SectorSize; }
  static constexpr size_t sectors() { return Sectors; }
  static constexpr size_t accessBytes() { return AccessBytes; }
  static constexpr size_t capacity() { return sectors() * sectorSize(); }

  static constexpr AddressRange sectorExtents(const size_t& _sector) {
      const size_t start = _sector * sectorSize();
      return {start, start+sectorSize()-1};
  }

  static constexpr AddressRange memoryExtents() {
    return {0, capacity()-1};
  }
};

} /*namespace drivers*/
} /*namespace chandra*/
#endif /*CHANDRA_FLASH_UTILS_H*/
