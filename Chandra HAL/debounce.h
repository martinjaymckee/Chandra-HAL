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
// TODO: IT WOULD BE GOOD TO RETURN A TIMESTAMP ALONG WITH THE LOGIC STATE
template<typename Source, typename Clock = chandra::chrono::timestamp_clock>
class DebounceWrapper
{
    public:
        using clock_t = Clock;
        using time_point_t = typename Clock::time_point;

        DebounceWrapper(Source& _src, const time_point_t& _timestamp = clock_t::now())
            : src_(_src),
              buffer_{bool(_src) ? uint8_t(0xFF) : uint8_t(0x00)},
              last_{bool(_src)},
              timestamp_(_timestamp) {}

        Logic operator() () {
            static const auto delay = std::chrono::duration<uint32_t, std::micro>(2500);
            const auto current = clock_t::now();
            if(chandra::chrono::after(delay, timestamp_, current)) {
                buffer_ <<= 1;
                buffer_ |= bool(src_) ? 0x1 : 0x0;
                timestamp_ += delay;
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

    protected:
        Source& src_;
        uint8_t buffer_;
        bool last_;
        time_point_t timestamp_;
};

} /*namespace internal*/

template<typename Source>
internal::DebounceWrapper<Source> debounce(Source& _src) {
    return {_src};
}

} /*namespace io*/
} /*namespace chandra*/


#endif /*CHANDRA_DEBOUNCE_H*/

