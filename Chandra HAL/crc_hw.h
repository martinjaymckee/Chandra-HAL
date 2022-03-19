#ifndef CHANDRA_CRC_HW_H
#define CHANDRA_CRC_HW_H

#include "chip_utils.h"
#include "crc_utils.h"

namespace chandra
{

enum class CRCPolyHW
{
  CRC16_CCITT = 0x00,
  CRC16 = 0x01,
  CRC32 = 0x10
};

namespace internal
{
//
// Hardware CRC Type
//
template<CRCPolyHW Poly>
struct CRCTypeImpl
{
  using type = uint32_t;
};

template<>
struct CRCTypeImpl<CRCPolyHW::CRC16_CCITT>
{
  using type = uint16_t;
};

template<>
struct CRCTypeImpl<CRCPolyHW::CRC16>
{
  using type = uint16_t;
};

template<CRCPolyHW Poly>
using CRCType = typename CRCTypeImpl<Poly>::type;
} /* namespace internal */

template<CRCPolyHW Poly, internal::CRCType<Poly> Init=0, bool doRefIn=false, bool doRefOut=false, internal::CRCType<Poly> XOROut=0xFFFF>
class HardwareCRC : public CRCBase<HardwareCRC<Poly, Init, doRefIn, doRefOut, XOROut>, internal::CRCType<Poly>>
{
  public:
    using crc_value_t = internal::CRCType<Poly>;

    bool init() {
      SystemClock::enable(0, 13);
      PeripheralActivity::reset(0, 13);
      LPC_CRC->MODE = (doRefOut ? (1<<4) : 0) | (doRefIn ? (1<<2) : 0) | static_cast<uint32_t>(Poly);
      return reset();
    }

    bool reset(const crc_value_t _init = Init) {
      LPC_CRC->SEED = _init;
      return true;
    }

    crc_value_t crc() const {
      return internal::XOROut<crc_value_t, XOROut>(LPC_CRC->SUM);
    }

    crc_value_t current() const {
      return LPC_CRC->SUM;
    }
    
    void update8(const uint8_t& _byte) {
      // printf("Hardware Update with 0x%02X\n", _byte);
      reinterpret_cast<volatile uint8_t&>(LPC_CRC->WR_DATA) = _byte;
      return;
    }

    void update16(const uint16_t& _word) {
      // printf("Hardware Update with 0x%04X\n", _word);
      reinterpret_cast<volatile uint16_t&>(LPC_CRC->WR_DATA) = _word;
      return;
    }

    void update32(const uint32_t& _dword) {
      // printf("Hardware Update with 0x%08X\n", _dword);
      LPC_CRC->WR_DATA = _dword;
      return;
    }
};

using HardwareCRC16_CCITT_False = HardwareCRC<CRCPolyHW::CRC16_CCITT, 0xFFFF, false, false, 0x0000>;
using HardwareCRC16_CCITT_True = HardwareCRC<CRCPolyHW::CRC16_CCITT, 0xFFFF, true, true, 0x0000>;
using HardwareCRC16_Kermit = HardwareCRC<CRCPolyHW::CRC16_CCITT, 0x0000, true, true, 0x0000>;
using HardwareCRC16_X25 = HardwareCRC<CRCPolyHW::CRC16_CCITT, 0xFFFF, true, true, 0xFFFF>;
using HardwareCRC16_XMODEM = HardwareCRC<CRCPolyHW::CRC16_CCITT, 0x0000, false, false, 0x0000>;

using HardwareCRC16_USB = HardwareCRC<CRCPolyHW::CRC16, 0xFFFF, true, true, 0xFFFF>;
using HardwareCRC16_MODBUS = HardwareCRC<CRCPolyHW::CRC16, 0xFFFF, true, true, 0x0000>;
} /*namespace chandra*/

#endif /*CHANDRA_CRC_HW_H*/
