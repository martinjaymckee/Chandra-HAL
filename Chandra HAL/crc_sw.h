#ifndef CHANDRA_CRC_SW_H
#define CHANDRA_CRC_SW_H

#include "crc_utils.h"

namespace chandra
{

namespace internal
{

template<class Value>
constexpr Value getTopBitMask() {
  constexpr Value width{8*sizeof(Value)};
  constexpr Value mask{1 << (width-1)};
  return mask;
}

} /* namespace internal */

template<class Value, Value Poly, Value Init=0, bool doRefIn=false, bool doRefOut=false, Value XOROut=0xFFFF>
class SoftwareCRC : public CRCBase<SoftwareCRC<Value, Poly, Init, doRefIn, doRefOut, XOROut>, Value>
{
  public:
    using crc_value_t = Value;
    static constexpr crc_value_t topBitMask = internal::getTopBitMask<crc_value_t>();

    bool init() {
      return reset();
    }

    bool reset(const crc_value_t& _init = Init) {
      crc_ = _init;
      return true;
    }

    crc_value_t crc() const {
      const auto crc_reflected = internal::Reflect<doRefOut>(crc_);
      return internal::XOROut<crc_value_t, XOROut>(crc_reflected);
    }

    crc_value_t current() const {
      return crc_;
    }

    void update8(const uint8_t& _byte) {
      // printf("Software Update with 0x%02X\n", _byte);
      const uint8_t data = internal::Reflect<doRefIn>(_byte);
      crc_ ^= (static_cast<crc_value_t>(data) << 8); // TODO: FIGURE OUT HOW TO MAKE THIS MORE GENERAL AND USE FOR 8-/16-/32-BIT IMPLEMENTATIONS
      for(uint8_t bit = 8; bit > 0; --bit) {
        if(crc_ & topBitMask) {
          crc_ = (crc_ << 1) ^ Poly;
        } else {
          crc_ <<= 1;
        }
      }
      return;
    }

  private:
    crc_value_t crc_ = Init;
};

using SoftwareCRC16_CCITT_False = SoftwareCRC<uint16_t, 0x1021, 0xFFFF, false, false, 0x0000>;
using SoftwareCRC16_CCITT_True = SoftwareCRC<uint16_t, 0x1021, 0xFFFF, true, true, 0x0000>;  // TODO: CHECK THAT THIS IS CORRECT
using SoftwareCRC16_Kermit = SoftwareCRC<uint16_t, 0x1021, 0x0000, true, true, 0x0000>;
using SoftwareCRC16_X25 = SoftwareCRC<uint16_t, 0x1021, 0xFFFF, true, true, 0xFFFF>;
using SoftwareCRC16_XMODEM = SoftwareCRC<uint16_t, 0x1021, 0x0000, false, false, 0x0000>;

using SoftwareCRC16_USB = SoftwareCRC<uint16_t, 0x8005, 0xFFFF, true, true, 0xFFFF>;
using SoftwareCRC16_MODBUS = SoftwareCRC<uint16_t, 0x8005, 0xFFFF, true, true, 0x0000>;

} /*namespace chandra*/

#endif /*CHANDRA_CRC_SW_H*/
