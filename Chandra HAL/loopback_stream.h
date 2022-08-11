#ifndef CHANDRA_LOOPBACK_STREAM_H
#define CHANDRA_LOOPBACK_STREAM_H

#include "circular_buffer.h"
#include "stream.h"
#include "usart_utils.h"

namespace chandra
{
namespace internal
{

template<class Value, class Echo, class Buffer>
class ProcessorEchoWrapper
{
  public:
    ProcessorEchoWrapper(Echo& _echo, Buffer& _buffer) : echo_(_echo), buffer_(_buffer) {}

    ProcessorEchoWrapper& operator << (const Value& _val) {
      buffer_ << _val;
      echo_.put( static_cast<char>(_val)); // TODO: MAYBE MAKE THIS ABLE TO HANDLE RAW???
      return *this;
    }

  private:
    Echo& echo_;
    Buffer& buffer_;
};

struct NullLoopbackProcessor
{
  template<class Buffer>
  bool operator() (char, Buffer&, bool = false) {
    return true;
  }
};



} /* namespace internal */

template<class Echo, class Processor, bool _timestamped=false, size_t loopback_buffer_length = 128>
class LoopbackStream : public chandra::Stream< LoopbackStream<Echo, Processor> >
{
  protected:
    using clock_t = chandra::chrono::timestamp_clock;
    using encoder_t = chandra::io::internal::RX<char, typename clock_t::time_point, _timestamped>;

  public:
    using loopback_value_t = decltype(encoder_t::encode('0'));
    using buffer_t = chandra::FixedCircularBuffer<loopback_value_t, loopback_buffer_length>;
    using processor_buffer_t = internal::ProcessorEchoWrapper<loopback_value_t, Echo, buffer_t>;

    LoopbackStream(Echo& _echo, Processor& _processor)
      : echo_(_echo), processor_(_processor),
        processor_buffer_(echo_, loopback_buffer_)
    {
      // INIT Processor?
    }

    bool put(char _ch, bool _raw=false) {
      processor_(_ch, loopback_buffer_, _raw);
      echo_.put(_ch, _raw);
      return true;
    }

    size_t available() const { return loopback_buffer_.size(); }

    loopback_value_t read() { return loopback_buffer_; }

    operator loopback_value_t() { return read(); }

		LoopbackStream& operator >> ( char& _ch ) {
			_ch = read();
			return *this;
		}

    auto& buffer() { return loopback_buffer_; }

  private:
    Processor& processor_;
    Echo& echo_;
    buffer_t loopback_buffer_;
    processor_buffer_t processor_buffer_;
};

template<class Echo, class Processor>
auto make_loopback_stream(Echo& _echo, Processor& _processor) {
  return chandra::LoopbackStream<Echo, Processor>{_echo, _processor};
}

} /*namespace chandra*/

#endif /*CHANDRA_LOOPBACK_STREAM_H*/
