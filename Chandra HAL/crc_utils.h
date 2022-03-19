#ifndef CHANDRA_CRC_UTILS_H
#define CHANDRA_CRC_UTILS_H

namespace chandra
{
namespace internal
{
//
// Reflection Implementation
//
template<class Value, bool doIt>
struct ReflectImpl
{
  static constexpr Value exec(const Value& _val) {
    // printf("No Reflection\n");
    return _val;
  }
};

template<class Value>
struct ReflectImpl<Value, true>
{
  static constexpr Value exec(Value _val) {
    constexpr uint8_t Bits{8*sizeof(Value)};
    // printf("Do Reflection\n");
    Value reflection = 0;

    for (uint8_t bit = 0; bit < Bits; ++bit) {
        if(_val & 0x01) {
            reflection |= (1 << ((Bits - 1) - bit));
        }

        _val >>= 1;
    }

    return reflection;
  }
};

template<bool doIt, class Value>
auto Reflect(const Value& _val) {
  return ReflectImpl<Value, doIt>::exec(_val);
}

//
// XOR Implementation
//
template<class Value, bool doIt, Value XOROut>
struct XOROutImpl
{
  static constexpr Value exec(const Value& _val) {
    // printf("No XOR\n");
    return _val;
  }
};

template<class Value, Value XOROut>
struct XOROutImpl<Value, false, XOROut>
{
  static constexpr Value exec(const Value& _val) {
    // printf("Doing XOR with 0x%04X\n", XOROut);
    return static_cast<Value>(XOROut) ^ _val;
  }
};

template<class Value, Value XOROutVal>
auto XOROut(const Value& _val) {
  return XOROutImpl<Value, (XOROutVal == 0), XOROutVal>::exec(_val);
}

} /* namespace internal */
} /* namespace chandra */

#endif /*CHANDRA_CRC_UTILS_H*/
