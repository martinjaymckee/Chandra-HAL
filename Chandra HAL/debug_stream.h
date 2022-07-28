#ifndef CHANDRA_DEBUG_STREAM_H
#define CHANDRA_DEBUG_STREAM_H

#include <cstdio>
#include "stream.h"

namespace chandra
{
class DebugStream : public Stream<DebugStream>
{
  public:
    bool put(char _ch, bool /*_raw*/ = false ) {
      putchar(_ch);
      fflush(stdout);
      return true;
    }
};

} /*namespace chandra*/

#endif /*CHANDRA_DEBUG_STREAM_H*/
