#ifndef CHANDRA_WINDOWED_FILTERS_H
#define CHANDRA_WINDOWED_FILTERS_H

#include "meta.h"

namespace chandra
{
namespace signal
{

template<typename Value>
class ExponentialWeightedAverage
{
    public:
        using value_t = Value;
        using scalar_t = scalar_of_t<value_t>;

        ExponentialWeightedAverage(const scalar_t& _w = scalar_t(0.5)) : w_(_w), v_(0) {}

        value_t v(value_t _v) {
            v_ = _v;
            return v_;
        }

        value_t v() const { return v_; }

        value_t operator() (const value_t& _v) {
            v_ += w_* (_v - v_);
            return v_;
        }

    private:
        scalar_t w_;
        value_t v_;
};

} /*namespace signal*/
} /*namespace chandra*/

#endif /*CHANDRA_WINDOWED_FILTERS_H*/

