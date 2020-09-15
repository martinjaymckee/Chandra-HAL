#ifndef CHANDRA_MEMORY_UTILS_H
#define CHANDRA_MEMORY_UTILS_H

namespace chandra
{
namespace utils
{

using ByteIterator = uint8_t *;
using ConstByteIterator = const uint8_t*;

template<class T>
class ByteReadWriteWrapper
{
    public:
        ByteReadWriteWrapper(T& _ref) : ref_(static_cast<void*>(&_ref)) {}

        constexpr ByteIterator begin() const { return static_cast<ByteIterator>(ref_); }
        constexpr ByteIterator end() const { return begin() + size() + 1; }
        constexpr size_t size() const { return sizeof(T); }

        template<class IterType>
        constexpr bool isLast(IterType _itr) const {
          return (begin() + size()) == static_cast<ByteIterator>(_itr);
        }

    private:
        void* ref_;
};

template<class T>
class ByteReadWrapper
{
    public:
        ByteReadWrapper(const T& _ref) : ref_(static_cast<const void*>(&_ref)) {}

        constexpr ConstByteIterator begin() const { return static_cast<ConstByteIterator>(ref_); }
        constexpr ConstByteIterator end() const { return begin() + size() + 1; }
        constexpr size_t size() const { return sizeof(T); }

        template<class IterType>
        constexpr bool isLast(const IterType _itr) const {
          return (begin() + size()) == static_cast<ConstByteIterator>(_itr);
        }

    private:
        const void* ref_;
};
} /*namespace utils*/
} /*namespace chandra*/

#endif /*CHANDRA_MEMORY_UTILS_H*/
