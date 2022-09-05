#ifndef CHANDRA_BINARY_SERIALIZE_H
#define CHANDRA_BINARY_SERIALIZE_H

#include <type_traits>

namespace chandra
{
namespace serialize
{
namespace internal
{
class BinarySerializeIndex
{
    public:
        constexpr BinarySerializeIndex() {}

        constexpr BinarySerializeIndex(const size_t& _bit_index) {
            advance(_bit_index);
        }

        constexpr bool reset() {
            byte_ = 0;
            filled_ = 0;
            return true;
        }

        constexpr size_t bit_index() const {
            return (8 * byte_) + filled_;
        }

        constexpr bool advance(size_t _bits) { // TODO: SEE IF THERE IS A WAY TO OPTIMIZE THIS....
            filled_ += _bits;
            while (filled_ >= 8) {
                byte_ += 1;
                filled_ -= 8;
            }
            return true;
        }

        constexpr size_t byte() const {
            return byte_;
        }

        constexpr size_t remaining() const {
            return 8 - filled_;
        }

    private:
        size_t byte_ = 0;
        size_t filled_ = 0;
};

struct ExtractRecord
{
    uint8_t data;
    uint8_t mask;
};

template<class V>
constexpr auto extract_bits(const V& _value, size_t _begin, size_t _num) {
    const uint8_t end = static_cast<uint8_t>(_begin - (_num-1));
    const uint8_t mask = static_cast<uint8_t>((1ul << _num) - 1ul);
    ExtractRecord result{ static_cast<uint8_t>(_value >> end & mask), mask };
    return result;
}


template<size_t Bits, class V, size_t N>
constexpr bool binary_buffer_write(const V& _val, BinarySerializeIndex& _idx, uint8_t(&_buffer)[N]) {
    size_t remaining_to_write = Bits;
    while (remaining_to_write > 0) {
        const size_t byte_idx = _idx.byte();
        const size_t bits_to_write = std::min(_idx.remaining(), remaining_to_write);
        const auto extract_result = extract_bits(_val, remaining_to_write - 1, bits_to_write);
        const size_t write_offset = _idx.remaining() - bits_to_write;
        const uint8_t keep_mask = ~(extract_result.mask << write_offset);
        _buffer[byte_idx] = (_buffer[byte_idx] & keep_mask) | (extract_result.data << write_offset);
        _idx.advance(bits_to_write);
        remaining_to_write -= bits_to_write;
    }
    return true;
}


template<bool do_sign_extend, size_t Bits>
struct sign_extend_read
{
    template<class V>
    static constexpr bool exec(V&) {
        return true;
    }
};

template<size_t Bits>
struct sign_extend_read<true, Bits>
{
    template<class V>
    static constexpr bool exec(V& _val) {
        if((_val & (1ul << (Bits-1))) != 0) {
          constexpr size_t bits_total = 8 * sizeof(_val);
          constexpr size_t bits_extended = bits_total - Bits;
          constexpr V sign_bits = static_cast<V>(((1ul << bits_extended) - 1ul) << Bits);
          _val |= sign_bits;
        }
        return true;
    }
};

template<size_t Bits, class V, size_t N>
constexpr bool binary_buffer_read(const uint8_t (&_buffer)[N], BinarySerializeIndex& _idx, V& _val) {
    size_t remaining_to_read = Bits;
    _val = 0;
    while (remaining_to_read > 0) {
        const size_t byte_idx = _idx.byte();
        const size_t bits_to_read = std::min(_idx.remaining(), remaining_to_read);
        const auto extract_result = extract_bits(_buffer[byte_idx], _idx.remaining()-1, bits_to_read);
        _val = (_val << bits_to_read) | extract_result.data;
        _idx.advance(bits_to_read);
        remaining_to_read -= bits_to_read;
    }
    sign_extend_read<std::is_signed<V>::value, Bits>::exec(_val);
    return true;
}

} /*namespace internal*/

template<size_t N>
class BinarySerializer
{
  public:
    constexpr BinarySerializer(uint8_t (&_buffer)[N]) : buffer_(_buffer) {}

    constexpr bool reset() {
        idx_.reset();
    }

    constexpr size_t write_pos() const {
      return idx_.bit_index();
    }

    constexpr size_t buffer_size() const {
      return N;
    }

    constexpr bool advance(size_t _bits) {
        return idx_.advance(_bits);
    }

    template<size_t Bits, class V>
    constexpr bool write(const V& _val) {
      return internal::binary_buffer_write<Bits>(_val, idx_, buffer_);
    }

    template<size_t Bits, class V>
    constexpr bool write_at(const size_t _idx, V& _val) {
        internal::BinarySerializeIndex local_idx(_idx);
        return internal::binary_buffer_write<Bits>(_val, local_idx, buffer_);
    }

  private:
    uint8_t (&buffer_)[N];
    internal::BinarySerializeIndex idx_;
};

template<size_t N>
constexpr BinarySerializer<N> make_binary_serializer(uint8_t (&_buffer)[N]) {
  return BinarySerializer<N>(_buffer);
}


template<size_t N>
class BinaryDeserializer
{
  public:
    constexpr BinaryDeserializer(const uint8_t (&_buffer)[N]) : buffer_(_buffer) {}

    constexpr bool reset() {
        idx_.reset();
    }

    constexpr size_t read_pos() const {
      return idx_.bit_index();
    }

    constexpr size_t buffer_size() const {
      return N;
    }

    constexpr bool advance(size_t _bits) {
        return idx_.advance(_bits);
    }

    template<size_t Bits, class V>
    constexpr bool read(V& _val) {
        return internal::binary_buffer_read<Bits>(buffer_, idx_, _val);
    }

    template<size_t Bits, class V>
    constexpr bool read_at(const size_t _idx, V& _val) {
        internal::BinarySerializeIndex local_idx(_idx);
        return internal::binary_buffer_read<Bits>(buffer_, local_idx, _val);
    }

  private:
    const uint8_t (&buffer_)[N];
    internal::BinarySerializeIndex idx_;
};

template<size_t N>
constexpr BinaryDeserializer<N> make_binary_deserializer(const uint8_t (&_buffer)[N]) {
  return BinaryDeserializer<N>(_buffer);
}


} /*namespace serialize*/
} /*namespace chandra*/

#endif /*CHANDRA_BINARY_SERIALIZE_H*/
