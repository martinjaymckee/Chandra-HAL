#ifndef CHANDRA_CRC_STREAM_H
#define CHANDRA_CRC_STREAM_H

#include "stream.h"

namespace chandra
{
template<class Stream, class CRC>
class CRCStream : public chandra::Stream< CRCStream<Stream, CRC> >
{
  public:
    CRCStream(Stream& _stream, CRC& _crc) : stream_(_stream), crc_(_crc) {
      seed_ = crc_.current();
      crc_.reset();
    }

    ~CRCStream() {
      crc_.reset(seed_);
    }

    bool put(char _ch, bool _raw=false) {
      crc_.update(_ch);
      stream_.put(_ch, _raw);
      return true;
    }

    auto reset() {
      return crc_.reset();
    }

    auto crc() const {
      return crc_.crc();
    }

  private:
    Stream& stream_;
    CRC& crc_;
    typename CRC::crc_value_t seed_;
};

template<class Stream, class CRC>
auto make_crc_stream(Stream& _stream, CRC& _crc) {
  return chandra::CRCStream<Stream, CRC>{_stream, _crc};
}

} /*namespace chandra*/

#endif /*CHANDRA_CRC_STREAM_H*/
