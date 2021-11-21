#ifndef CHANDRA_RATIO_UTILS_H
#define CHANDRA_RATIO_UTILS_H

#include <ratio>

namespace chandra
{

template<class R>
using ratio_square = std::ratio_multiply<R, R>;



} /* namespace chandra */

#endif /* CHANDRA_RATIO_UTILS_H */
