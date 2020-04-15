#ifndef CHANDRA_REGISTER_DEVICE_H
#define CHANDRA_REGISTER_DEVICE_H

#include <algorithm>

#include "i2c.h"
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
};

template<class Derived>
struct RegisterDeviceMixin
{
  //
  // Register Update Commands
  //

  //  Single Byte
  void update(const uint8_t reg, const auto mask, const uint8_t data) {
      const uint8_t init = static_cast<Derived*>(this)->byte(reg);
      const uint8_t new_data = (init&~mask)|(data&mask);
      return static_cast<Derived*>(this)->write(reg, new_data);
  }

  // 16-Bit Half Word
  void update(const uint8_t reg, const auto mask, const uint16_t& data) {
      const uint16_t init = static_cast<Derived*>(this)->hword(reg);
      const uint16_t new_data = (init&~mask)|(data&mask);
      return static_cast<Derived*>(this)->write(reg, new_data);
  }

  // TODO: IMPLEMET REGISTER FIELD UPDATE COMMANDS
  //  FOR INSTANCE FIELD(REG, OFFSET, WIDTH, VALUE)
  //  HOW TO HANDLE BYTE REGISTERS VS. HWORD REGISTERS
};

// SPI Register Machine Implementation
template<>
struct RegisterDevice<chandra::io::SPIMaster>
 : public RegisterDeviceMixin<RegisterDevice<chandra::io::SPIMaster>>
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

        void write(const uint8_t reg, const uint8_t& data) {
            const uint8_t cmd[2] = {reg, data};
            comm.tx(cmd, 2, cs);
            return;
        }

        void write(const uint8_t reg, const uint16_t& data) {
            const uint8_t cmd[3] = {reg, static_cast<uint8_t>(data>>8), static_cast<uint8_t>(data&0xFF)};
            comm.tx(cmd, 3, cs);
            return;
        }

        comm_t comm;
        util_t::cs_t cs;
};

// I2C Register Machine Implementation
//  THERE ARE A NUMBER OF CONST CORRECTNESS PROBLEMS WITH THIS THAT ARE A RESULT OF
//    THE I2C OBJECT NOT BEING AS CONST CORRECT AS WOULD BE NICE.  WORK ON THAT
template<>
struct RegisterDevice<chandra::io::I2CMaster>
 : public RegisterDeviceMixin<RegisterDevice<chandra::io::I2CMaster>>
{
        using comm_t = chandra::io::I2CMaster;
        using ref_t = RegisterDevice<comm_t>;

        RegisterDevice(comm_t& _comm, uint8_t _addr)
            : comm(_comm), addr(_addr) {}

        RegisterDevice(const ref_t& _other) : comm(_other.comm), addr(_other.addr) {}

        uint8_t byte(const uint8_t reg) { // CONST
            uint8_t val;
            comm.readReg(addr, reg, &val);
            return val;
        }

        template<size_t N>
        uint8_t bytes(const uint8_t reg, const size_t _num, uint8_t (&_buffer)[N]) { // CONST
            const size_t num = std::min(N, _num);
            comm.readReg(addr, reg, _buffer, num);
            return num;
        }

        int16_t hword(const uint8_t reg) { // CONST
            uint8_t val[2];
            comm.readReg(addr, reg, val);
            return static_cast<int16_t>((uint16_t(val[1])<<8)|val[0]);
        }

        void write(const uint8_t reg, const uint8_t& data) {
            comm.writeReg(addr, reg, &data);
            return;
        }

        void write(const uint8_t reg, const uint16_t& _data) {
            const uint8_t data[2] = {static_cast<uint8_t>(_data>>8), static_cast<uint8_t>(_data&0xFF)};
            comm.writeReg(addr, reg, data, 2);
            return;
        }

        comm_t comm;
        uint8_t addr;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_REGISTER_DEVICE_H*/
