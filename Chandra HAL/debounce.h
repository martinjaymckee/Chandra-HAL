#ifndef CHANDRA_DEBOUNCE_H
#define CHANDRA_DEBOUNCE_H
#include "chrono.h"

namespace chandra
{
namespace io
{

// TODO: THIS SHOULD GO SOMEWHERE ELSE....
enum class Logic
{
    Low,
    High,
    Rising,
    Falling,
    Undefined
};

namespace internal
{
template<class Derived>
class LogicWrapperBase
{
  public:
    bool low() { return static_cast<Derived*>(this)->operator()() == Logic::Low; }
    bool high() { return static_cast<Derived*>(this)->operator()() == Logic::High; }
    bool falling() { return static_cast<Derived*>(this)->operator()() == Logic::Falling; }
    bool rising() { return static_cast<Derived*>(this)->operator()() == Logic::Rising; }
};

template<typename Source>
class LogicWrapper : public LogicWrapperBase<LogicWrapper<Source>>
{
    public:
        LogicWrapper(Source& _src)
            : src_(_src), last_{bool(_src)} {}

        constexpr bool reset() const { return true; }
        
        constexpr operator bool() const {
          return last_;
        }

        Logic operator() () {
            if(last_) { // Currently reading as High
                if(bool(src_) == false) {
                    last_ = false;
                    return Logic::Falling;
                }
                return Logic::High;
            } else { // Currently reading as Low
                if(bool(src_) == true) {
                    last_ = true;
                    return Logic::Rising;
                }
                return Logic::Low;
            }

            return Logic::Undefined;
        }

        constexpr bool valid() const { return true; }

    protected:
        Source& src_;
        bool last_;
};

// TODO: IT WOULD BE GOOD TO RETURN A TIMESTAMP ALONG WITH THE LOGIC STATE
template<typename Source, typename Clock = chandra::chrono::timestamp_clock>
class DebounceWrapper : public LogicWrapperBase<DebounceWrapper<Source, Clock>>
{
    public:
        using clock_t = Clock;
        using time_point_t = typename Clock::time_point;

        DebounceWrapper(Source& _src, const time_point_t& _timestamp = clock_t::now())
            : src_(_src),
              buffer_{bool(_src) ? uint8_t(0xFF) : uint8_t(0x00)},
              last_{bool(_src)},
              timestamp_(_timestamp) {}

        bool reset(const time_point_t& _t) {
          last_ = bool(src_);
          buffer_ = 0;
          timestamp_ = clock_t::now();
          return true;

        }

        bool reset() {
          return reset(clock_t::now());
        }

        constexpr operator bool() const {
          return last_;
        }

        Logic operator() () {
            static const auto delay = std::chrono::duration<uint32_t, std::micro>(2500);
            const auto current = clock_t::now();
            if(chandra::chrono::after(delay, timestamp_, current)) {
                buffer_ <<= 1;
                buffer_ |= bool(src_) ? 0x1 : 0x0;
                timestamp_ += delay;
                if(samples_ < 8) ++samples_;
            }

            if(last_) { // Currently reading as High
                if(buffer_ == 0x00) {
                    last_ = false;
                    return Logic::Falling;
                }
                return Logic::High;
            } else { // Currently reading as Low
                if(buffer_ == 0xFF) {
                    last_ = true;
                    return Logic::Rising;
                }
                return Logic::Low;
            }

            return Logic::Undefined;
        }

        constexpr bool valid() const { return samples_ >= 8; }

    protected:
        Source& src_;
        uint8_t buffer_;
        uint8_t samples_;
        bool last_;
        time_point_t timestamp_;
};

} /*namespace internal*/

template<typename Source>
internal::DebounceWrapper<Source> debounce(Source& _src) {
    return {_src};
}

template<typename Source>
internal::LogicWrapper<Source> logic(Source& _src) {
    return {_src};
}
} /*namespace io*/
} /*namespace chandra*/


#endif /*CHANDRA_DEBOUNCE_H*/
