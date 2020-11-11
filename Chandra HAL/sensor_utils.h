#ifndef CHANDRA_SENSOR_UTILS_H
#define CHANDRA_SENSOR_UTILS_H

#include "chrono.h"

namespace chandra
{
namespace drivers
{

//
// Update Status Return Type
//
template<class StateType=uint8_t>
struct SensorUpdateStatus
{
        using clock_t = chandra::chrono::timestamp_clock;
        using timestamp_t = clock_t::time_point;
        using ref_t = SensorUpdateStatus;

        typedef enum {
            Ok = 0x00,
            CommunicationsError = 0x01,
            TimeoutError = 0x02,
            ArithmeticError = 0x04,
            ModeError = 0x08
        } error_t;

        struct ErrorProxy
        {
                ErrorProxy(const uint8_t& _errors) : byte(_errors) {}
                ErrorProxy(const ErrorProxy& _other) : byte(_other.byte) {}

                ErrorProxy& operator = (error_t _err) {
                    if(_err == Ok) {
                        byte = 0;
                    } else {
                        byte |= _err;
                    }
                    return *this;
                }

                bool communication() const { return byte & CommunicationsError; }
                bool timeout() const { return byte & TimeoutError; }
                bool arithmetic() const { return byte & ArithmeticError; }
                bool mode() const { return byte & ModeError; }

                uint8_t byte;
        };

        SensorUpdateStatus(
                const bool& _restart = false,
                const bool& _processed = false,
                const bool& _calculated = false,
                const bool& _calibrating = false,
                const uint8_t& _errors = Ok,
                const timestamp_t& _timestamp = clock_t::now()
        ) : restart(_restart), processed(_processed), calculated(_calculated),
            calibrating(_calibrating), errors(_errors), timestamp(_timestamp) {}

        SensorUpdateStatus(const ref_t& _other)
            : restart(_other.restart), processed(_other.processed), calculated(_other.calculated),
              calibrating(_other.calibrating), errors(_other.errors), timestamp(_other.timestamp) {}

        operator bool() const { return processed; }

        bool ok() const { return errors.byte == 0; }

        bool restart = false;
        bool processed = false;
        bool calculated = false;
        bool calibrating = false;
        ErrorProxy errors;
        timestamp_t timestamp;
        StateType state;
};

// TODO: FIGURE OUT HOW TO MAKE THIS WORK WITH THE STREAM FUNCTIONALITY...
//  THIS IS PROBABLY GOING TO REQUIRE USING SFINAE OR SOMETHING IN THE CORE OF
//  OF THE STREAM LIBRARY

// template<typename Stream>
// Stream& operator << (Stream& _stream, const SensorUpdateStatus& _status) {
//     _stream << "SensorUpdateStatus( ";
//     if(_status.updated){
//         _stream << "updated";
//     } else {
//         _stream << "held";
//     }
//     _stream << ", " << _status.timestamp.time_since_epoch().count();
//     if(!_status.ok()) {
//         bool first = true;
//         _stream << ", ";
//         if(_status.errors.communication()) {
//             _stream << "CommunicationsError";
//             first = false;
//         }
//         if(_status.errors.timeout()) {
//             if(!first) _stream << "|";
//             _stream << "TimeoutError";
//             first = false;
//         }
//         if(_status.errors.arithmetic()) {
//             if(!first) _stream << "|";
//             _stream << "ArithmeticError";
//             first = false;
//         }
//         if(_status.errors.mode()) {
//             if(!first) _stream << "|";
//             _stream << "ModeError";
//         }
//     }
//     _stream << " )";
//     return _stream;
// }

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_SENSOR_UTILS_H*/
