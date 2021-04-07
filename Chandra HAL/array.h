#ifndef CHANDRA_ARRAY_H
#define CHANDRA_ARRAY_H

#include <stdint.h>

//
// NOTE: THIS IS CURRENTLY JUST A ( VERY ) THIN WRAPPER AROUND BUILTIN ARRAYS
//
namespace chandra
{
template<class Value, size_t N>
class Array
{
    public:
        using value_t = Value;
        Array() {} // TODO: ADD UNIFORM INITIALIZATION OF THE ARRAY

        value_t& operator[] ( const size_t& _idx ) { return array_[_idx];}
        value_t operator[] ( const size_t& _idx ) const { return array_[_idx];}

        constexpr size_t size() const { return N; }
        constexpr size_t capacity() const { return N; }

    private:
        value_t array_[N];
};

} /*namespace chandra*/
#endif /*CHANDRA_ARRAY_H*/
