#ifndef CHANDRA_CRC_CORE_H
#define CHANDRA_CRC_CORE_H

#include <utility>


#include "stream.h"

namespace chandra
{

namespace internal
{

template <typename T>
struct has_optimized_16
{
  template<class U>
  static constexpr auto exec(int)
    -> decltype(std::declval<U>().update16(uint16_t()), bool())
  {
    return true;
  }

  template <typename U>
  static constexpr bool exec(...) {
    return false;
  }

  static constexpr bool value = exec<T>(int());
};

template <typename T>
struct has_optimized_32
{
  template<class U>
  static constexpr auto exec(int)
    -> decltype(std::declval<U>().update32(uint32_t()), bool())
  {
    return true;
  }

  template <typename U>
  static constexpr bool exec(...) {
    return false;
  }

  static constexpr bool value = exec<T>(int());
};

template<class Derived, class Value>
void default_bytewise_update(Derived& _obj, const Value& _val) {
  const uint8_t* p = reinterpret_cast<const uint8_t*>(&_val);
  for(size_t idx = 0; idx < sizeof(Value); ++idx) {
    // printf("Update with 0x%02X\n", p[idx]);
    _obj.update8(p[idx]);
  }
}

template<class Derived, class Value, bool opt = has_optimized_16<Derived>::value>
struct Update16Impl
{
  static void exec(Derived& _obj, const Value& _val) {
    // printf("Default bytewise 16-bit\n");
    default_bytewise_update(_obj, _val);
  }
};

template<class Derived, class Value>
struct Update16Impl<Derived, Value, true>
{
  static void exec(Derived& _obj, const Value& _val) {
    // printf("Optimized 16-bit\n");
    _obj.update16(_val);
  }
};

template<class Derived, class Value, bool hasOptimized = has_optimized_32<Derived>::value>
struct Update32Impl
{
  static void exec(Derived& _obj, const Value& _val) {
    // printf("Default bytewise 32-bit\n");
    default_bytewise_update(_obj, _val);
  }
};

template<class Derived, class Value>
struct Update32Impl<Derived, Value, true>
{
  static void exec(Derived& _obj, const Value& _val) {
    // printf("Optimized 32-bit\n");
    _obj.update32(_val);
  }
};

} /* namespace internal */

template<class Derived, class CRCValue>
class CRCBase
{
  public:
    using crc_value_t = CRCValue;

    //
    // Derived classes must provide:
    //  bool init()
    //  bool reset()
    //  crc_value_t crc() const
    //  crc_value_t update8(const uint8_t& _byte)

    // Derived classes *may* provide:
    //  crc_value_t update16(const uint16_t& _byte)
    //  crc_value_t update32(const uint32_t& _byte)
    //  Note: these should only be included if they are optimized beyond multiple byte updates

    // void update(const uint8_t& _byte) {
    //   // reinterpret_cast<volatile uint8_t&>(LPC_CRC->WR_DATA) = _byte;
    //   return;
    // }
    //
    // void update(const uint16_t& _word) {
    //   // reinterpret_cast<volatile uint16_t&>(LPC_CRC->WR_DATA) = _word;
    //   return;
    // }
    //
    // void update(const uint32_t& _dword) {
    //   // LPC_CRC->WR_DATA = _dword;
    //   return;
    // }

    void update(const uint8_t& _val) {
      // printf("Explicit uint8_t update\n");
      return static_cast<Derived&>(*this).update8(_val);
    }

    void update(const uint16_t& _val) {
      // printf("Explicit uint16_t update\n");
      internal::Update16Impl<Derived, uint16_t>::exec(static_cast<Derived&>(*this), _val);
    }

    void update(const uint32_t& _val) {
      // printf("Explicit uint32_t update\n");
      internal::Update32Impl<Derived, uint32_t>::exec(static_cast<Derived&>(*this), _val);
    }

    crc_value_t operator() (const uint8_t& _byte) {
      static_cast<Derived&>(*this).update(_byte);
      return static_cast<Derived&>(*this).crc();
    }

    template<size_t N>
    void update(const char (&_bytes)[N]) {
      for(const auto& b: _bytes) {
        // printf("Update with 0x%02X\n", b);
        static_cast<Derived&>(*this).update8(static_cast<uint8_t>(b)); // Bytewise update
      }
      return;
    }

    template<size_t N>
    crc_value_t operator() (const char (&_bytes)[N]) {
      this->update<N>(_bytes);
      return static_cast<Derived&>(*this).crc();
    }

    template<class Value>
    void update(const Value& _val) {
      internal::default_bytewise_update(static_cast<Derived&>(*this), _val);
    }

    template<class Value>
    crc_value_t operator()(const Value& _val) {
      this->update<Value>(_val);
      return static_cast<Derived&>(*this).crc();
    }
};

} /*namespace chandra*/

#endif /*CHANDRA_CRC_CORE_H*/
