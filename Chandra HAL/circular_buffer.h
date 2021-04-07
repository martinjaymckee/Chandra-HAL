#ifndef CHANDRA_CIRCULAR_BUFFER_H
#define CHANDRA_CIRCULAR_BUFFER_H

#include <stdint.h>

#include "array.h"
#include "meta.h"

namespace chandra
{

template<class Value, size_t N>
class FixedCircularBuffer
{
    public:
        using value_t = Value;
        using ref_t = FixedCircularBuffer<Value, N>&;

        FixedCircularBuffer() : idx_(0), cnt_(0) {}

        ref_t enqueue(const value_t& _val ) {
            return this->operator <<(_val);
        }

        ref_t operator << ( const value_t& _val ) {
            if( full() ){
                ++idx_;
            } else {
                ++cnt_;
            }
            buffer_[w_idx()] = _val;
            return *this;
        }

        operator value_t() {
            if( empty() ){
                return value_t();
            }
            const value_t result = buffer_[r_idx()];
            --cnt_;
            ++idx_;
            return result;
        }

        ref_t operator >> ( value_t& _dest ) {
        	_dest = value_t(_dest);
            return *this;
        }

        //	Directly read (peek) values from the buffer.  Index 0 is the oldest value (the first to be read)
        //		from the queue, and subsequent indicies are progressively newer.
        constexpr value_t operator [] ( const size_t& _id ) const {
          const auto idx = id_idx(_id);
          return buffer_[idx];
        }

        ref_t drop(uint8_t _num) {
        	_num = (_num>cnt_) ? cnt_ : _num;
        	idx_ += _num;
        	cnt_ -= _num;
        	return *this;
        }

        ref_t clear() { return drop(cnt_); }

        constexpr bool available() const { return !empty(); }
        constexpr bool empty() const { return (cnt_ == 0); }
        constexpr bool full() const { return (cnt_ == N); }

        constexpr size_t size() const { return cnt_; }
        constexpr size_t capacity() const { return N; }

    protected:
        //  Index Calculation
        constexpr size_t w_idx() const {
            return select_optimized() ?
                        ((idx_+cnt_-1UL) & (N-1UL)) :
                        ((idx_+cnt_-1UL) % N);
        }

        constexpr size_t r_idx() const {
            return select_optimized() ?
                        (idx_ & (N-1UL)) :
                        (idx_ % N);
        }

        constexpr size_t id_idx( const size_t& _id ) const {
            (void) _id;
            return select_optimized() ?
                        ((idx_+_id) & (N-1UL)) :
                        ((idx_+_id) % N);
        }

        static constexpr bool select_optimized() {
            return meta::is_power_of_two<N>::value;
        }

    private:
        Array<value_t,N> buffer_;
        size_t idx_;
        volatile size_t cnt_;
};

} /*namespace chandra*/

#endif /*CHANDRA_CIRCULAR_BUFFER_H*/
