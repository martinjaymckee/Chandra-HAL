#ifndef CHANDRA_REGISTER_DEVICE_H
#define CHANDRA_REGISTER_DEVICE_H

#include <algorithm>

//#include "i2c.h" // TODO: NEED TO PORT THE I2C HEADER AND CREATE A REGISTER DEVICE
#include "spi.h"

namespace chandra
{
namespace drivers
{

// Default (Null) Implementation of a register device
template<typename Comm>
struct RegisterDevice
{
        using comm_t = Comm;
        using ref_t = RegisterDevice<comm_t>;

        template<typename... Args>
        RegisterDevice(comm_t&, Args...) {}

        RegisterDevice(const ref_t&) {}

        //
        // Read Register Commands
        //
        //  Single Byte
        uint8_t byte(const uint8_t /*reg*/) const { return 0; }

        //  Multiple Bytes
        template<size_t N>
        uint8_t bytes(const uint8_t /*reg*/, const size_t /*_num*/, uint8_t (&/*_buffer*/)[N]) const {
            return 0;
        }

        //  16-Bit Half Word
        int16_t hword(const uint8_t /*reg*/) const { return 0; }

        //
        // Write Register Commands
        //
        //  Single Byte
        void write(const uint8_t /*reg*/, const uint8_t /*data*/) {}

        // 16-Bit Half Word
        void write(const uint8_t /*reg*/, const uint16_t /*data*/) {}

        //
        // Register Update Commands
        //
        //  Single Byte
        void update(const uint8_t /*reg*/, const uint8_t /*mask*/, const uint8_t /*data*/) {}

        //  16-Bit Half Word
        void update(const uint8_t /*reg*/, const uint16_t /*mask*/, const uint16_t /*data*/) {}
};

// SPI Register Machine Implementation
template<>
struct RegisterDevice<chandra::io::SPIMaster>
{
        using comm_t = chandra::io::SPIMaster;
        using util_t = chandra::io::SPI;
        using ref_t = RegisterDevice<comm_t>;

        RegisterDevice(comm_t& _comm, const util_t::cs_t& _cs = util_t::CS0)
            : comm(_comm), cs(_cs) {}

        RegisterDevice(const ref_t& _other) : comm(_other.comm), cs(_other.cs) {}

        uint8_t byte(const uint8_t reg) const {
            const uint8_t cmd = (1<<7) | reg;
            uint8_t val = 0x12;
            comm.tx(&cmd, 1, cs, util_t::START);
            comm.rx(&val, 1, cs, util_t::STOP);
            return val;
        }

        template<size_t N>
        uint8_t bytes(const uint8_t reg, const size_t _num, uint8_t (&_buffer)[N]) const {
            const size_t num = std::min(N, _num);
            const uint8_t cmd = (1<<7) | reg;
            comm.tx(&cmd, 1, cs, util_t::START);
            comm.rx(_buffer, num, cs, util_t::STOP);
            return num;
        }

        int16_t hword(const uint8_t reg) const {
            const uint8_t cmd = (1<<7) | reg;
            uint8_t val[2];
            comm.tx(&cmd, 1, cs, util_t::START);
            comm.rx(val, 2, cs, util_t::STOP);
            return static_cast<int16_t>((uint16_t(val[1])<<8)|val[0]);
        }

        void write(const uint8_t reg, const uint8_t data) {
            const uint8_t cmd[2] = {reg, data};
            comm.tx(cmd, 2, cs);
            return;
        }

        void write(const uint8_t reg, const uint16_t data) {
            const uint8_t cmd[3] = {reg, static_cast<uint8_t>(data>>8), static_cast<uint8_t>(data&0xFF)};
            comm.tx(cmd, 3, cs);
            return;
        }

        void update(const uint8_t reg, const auto mask, const uint8_t data) {
            const uint8_t init = byte(reg);
            const uint8_t new_data = (init&~mask)|(data&mask);
            return write(reg, new_data);
        }

        void update(const uint8_t reg, const auto mask, const uint16_t data) {
            const uint16_t init = hword(reg);
            const uint16_t new_data = (init&~mask)|(data&mask);
            return write(reg, new_data);
        }

        comm_t comm;
        util_t::cs_t cs;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_REGISTER_DEVICE_H*/

