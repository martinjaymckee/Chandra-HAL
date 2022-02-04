#ifndef CHANDRA_SPI_FLASH_25_SERIES_H
#define CHANDRA_SPI_FLASH_25_SERIES_H

#include <chrono>
using namespace std::literals::chrono_literals;

#include <chrono.h>
#include <flash_utils.h>
#include <memory_utils.h>
#include <spi.h>

namespace chandra
{
namespace drivers
{

// NOTE: AT THIS POINT, THIS IS ONLY IMPLEMENTING A BLOCKING VERSION OF THE INTERFACE.
//  IT WOULD BE BEST TO BE ABLE TO ALSO CONFIGURE THIS TO WORK WITH DMA... THAT ISN'T
//  SUPPORTED BY CHANDRA YET THOUGH.  THERE SHOULD BE SOME "SIMPLE" DMA API BEFORE
//  WORRYING ABOUT HOW TO GET THIS WORKING.

// NOTE: CONSIDER IF WRITE PROTECT (WP) AND HOLD SHOULD BE INCLUDED IN THIS DRIVER

// NOTE: CONSIDER IF THIS SHOULD HANDLE QSPI INTERFACE (THIS ISN'T SUPPORTED BY THE HARDWARE)

template<class Derived, class FlashConfiguration, class JEDECID, bool RangeChecked = true>
class SPIFlash25Series
{
    public:
        using derived_t = Derived;
        using flash_configuration_t = FlashConfiguration;
        using jedec_id_t = JEDECID;

        static constexpr bool range_checked = RangeChecked;

        //
        // Memory Constructor
        //
        SPIFlash25Series(chandra::io::SPIMaster& _spi, const chandra::io::SPI::cs_t& _cs = chandra::io::SPI::CS0) : spi_(_spi), cs_(_cs) {}

        bool init() {
            if(!spi_.enabled()) {
              spi_.enable(true, 0);
            }

            return true;
        }

        bool valid() {
          return bool(id());
        }

        //
        // Status Accessors
        //
        jedec_id_t id() const {
            const uint8_t cmd = 0x9F; // Request Device ID First
            uint8_t bytes[3];
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::START);
            spi_.rx(bytes, 3, cs_, chandra::io::SPI::STOP);
            return {bytes[0], bytes[1], bytes[2]};
        }

        bool busy() const {
            return static_cast<const derived_t *>(this)->status(0) & 0x01;
        }

        uint8_t status(uint8_t idx=0) const {
            (void) idx;
            const uint8_t cmd = 0x05;
            uint8_t status;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::START);
            spi_.rx(&status, 1, cs_, chandra::io::SPI::STOP);
            return status;
        }

        //
        // Control Methods
        //
        // Write Protect
        bool protect(const SectorRange& range = {}) const {
            uint8_t cmd[2] = {
                0x01,
                0x0F<<2
            };
            // Clear BPL bit to make block protect bits R/W
            static_cast<const derived_t *>(this)->ewsr();
            spi_.tx(cmd, 2, cs_, chandra::io::SPI::WRAP);
            (void) range; // HACK: THE CURRENT IMPLEMENTATION WILL ALWAYS PREVENT WRITING TO THE WHOLE CHIP
            return true;
        }

        // Write Allow
        bool allow(const SectorRange& range = {}) const {
            uint8_t cmd[2] = {
                0x01,
                0x00
            };
            // Clear BPL bit to make block protect bits R/W
            static_cast<const derived_t *>(this)->wren();
            spi_.tx(cmd, 2, cs_, chandra::io::SPI::WRAP);
            (void) range; // HACK: THE CURRENT IMPLEMENTATION WILL ALWAYS ALLOW WRITING TO THE WHOLE CHIP
            return true;
        }

        //
        // Access Methods
        //
        //  Read
        //      --> Buffer With Explicit Length
        template<typename Value, size_t N>
        AddressRange read(const size_t& _addr, Value (&buffer)[N], const size_t& _values) const {
            if(!(valid_addr_range(_addr, sizeof(Value), _values) and (N >= _values))) return {};
            static_cast<const derived_t *>(this)->block();
            return readUnprotected(_addr, &buffer[0], _values);
        }

        //      --> Direct Buffer
        template<typename Value, size_t N>
        AddressRange read(const size_t& _addr, Value (&buffer)[N]) const {
            return read(_addr, &buffer[0], N);
        }

        //      --> Single Value
        template<typename Value>
        AddressRange read(const size_t& _addr, Value& _val) const {
            if(!valid_addr_range(_addr, sizeof(Value), 1)) return {};
            static_cast<const derived_t *>(this)->block();
            return readUnprotected(_addr, &_val, 1);
        }

        //  Write
        //      --> Buffer With Explicit Length
        template<typename Value, size_t N>
        AddressRange write(const size_t& _addr, const Value (&buffer)[N], const size_t& _values) const {
            if(!(valid_addr_range(_addr, sizeof(Value), _values) and (N >= _values))) return {};
            static_cast<const derived_t *>(this)->block();
            static_cast<const derived_t *>(this)->wren();
            while(!static_cast<const derived_t *>(this)->wel()){}
            return writeUnprotected(_addr, &buffer[0], _values);
        }

        //      --> Direct Buffer
        template<typename Value, size_t N>
        AddressRange write(const size_t& _addr, const Value (&buffer)[N]) const {
            return write(_addr, buffer, N);
        }

        //      --> Single Value
        template<typename Value>
        AddressRange write(const size_t& _addr, const Value& _val) {
            if(!valid_addr_range(_addr, sizeof(Value), 1)) return {};
            static_cast<const derived_t *>(this)->block();
            static_cast<const derived_t *>(this)->wren();
            while(!static_cast<const derived_t *>(this)->wel()){}
            return writeUnprotected(_addr, &_val, 1);
        }

        //  Erase
        //      --> Whole Chip
        AddressRange erase(bool blocking=false) const {
            static_cast<const derived_t *>(this)->block();
            static_cast<const derived_t *>(this)->wren();
            while(!static_cast<const derived_t *>(this)->wel()){}
            const uint8_t cmd = 0x60;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            static_cast<const derived_t *>(this)->block(blocking);
            return flash_configuration_t::memoryExtents();
        }

        //      --> Sector Range
        AddressRange erase(const SectorRange& _sectors, bool blocking=false) const {
            static_cast<const derived_t *>(this)->block();
            static_cast<const derived_t *>(this)->wren();
            while(!static_cast<const derived_t *>(this)->wel()){}
            // TODO: BASE THIS ON AN INTERFACE COMMAND SO THAT THIS CAN BE OVERLOADED
            static_cast<const derived_t *>(this)->block(blocking);
            return {}; // TODO: THIS NEEDS TO RETURN EITHER THE ACTUAL ERASED SECTORS OR AN INVALID ADDRESS RANGE
        }

        void block(bool blocking=true) const {
            if(blocking) {
                while(static_cast<const derived_t *>(this)->busy()) {}
            }
            return;
        }

    protected:
        bool ewsr() const {
            const uint8_t cmd = 0x50;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            return true;
        }

        bool wren() const {
            const uint8_t cmd = 0x06;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            return true;
        }

        bool wrdi() const {
            const uint8_t cmd = 0x04;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            return true;
        }

        bool wel() const {
            return static_cast<const derived_t *>(this)->status(0) & 0x02;
        }

        bool init_read(const size_t& _addr) const {
            const uint8_t cmd[4] = {
                0x03,
                static_cast<uint8_t>((_addr&0xFF0000)>>16),
                static_cast<uint8_t>((_addr&0x00FF00)>>8),
                static_cast<uint8_t>(_addr&0x0000FF)
            };

            spi_.tx(cmd, 4, cs_, chandra::io::SPI::START);
            return true;
        }

        uint8_t read_byte(const bool _close) const {
          uint8_t byte;
          spi_.rx(&byte, 1, cs_, _close ? chandra::io::SPI::STOP : chandra::io::SPI::PASS);
          return byte;
        }

        bool init_write_byte(const size_t& _addr) const {
            return false;
        }

        bool write_byte(const uint8_t _byte) const {
          return false;
        }

        bool init_write_stream(const size_t& _addr) const {
            return false;
        }

        bool write_stream_byte(const uint8_t _byte, const bool _close) const {
          return false;
        }

        constexpr bool valid_addr_range(const size_t& _addr, const uint8_t _bytes, const size_t _N) const {
          if(!range_checked) {
            return true;
          } else {
            const auto end = flash_configuration_t::memoryExtents().end;
            if( (_addr < end) and ((end-_addr) >= (_bytes*_N))) return true;
            return false;
          }
        }

        constexpr bool valid_wrapped_addr_range(const size_t& _addr, const uint8_t _bytes, const size_t _N) const {
          if(!range_checked) {
            return true;
          } else {
            return flash_configuration_t::memoryBytes() >= _bytes*_N;
          }
        }

        //
        // TODO: MODULARIZE READ ALGORITHM AND WRITE ALGORITHM
        // TODO: GENERALIZE SO THAT IT IS POSSIBLE FOR VALUE TO BE NON-BYTE SIZED
        //
        template<typename Value>
        AddressRange readUnprotected(const size_t& addr, Value* buffer, const size_t& remaining) const {
            static_cast<const derived_t *>(this)->init_read(addr);
            for(size_t ele=0; ele < remaining; ++ele) {
                chandra::utils::ByteReadWriteWrapper<Value> io_wrapper(buffer[ele]);
                for(auto& byte : io_wrapper) {
                    byte = static_cast<const derived_t *>(this)->read_byte(io_wrapper.isLast(&byte));
                    (void) byte;
                }
            }

            return {addr, addr + (remaining * sizeof(Value))};
        }

        // HACK: THIS IS USING A BYTE-WISE WRITE METHOD THAT SHOULDN'T REALLY BE USED FOR EFFICIENCY....
        // HACK: THIS IS NOT USING AN EXTENSIBLE API, THE SPI CODE IS DIRECTLY IN THE IMPLEMENTATION
        template<typename Value>
        AddressRange writeUnprotected(size_t addr, const Value* buffer, size_t remaining) const {
          const size_t start = addr;
          //static_cast<const derived_t *>(this)->init_write_stream(addr);
          for(size_t ele=0; ele < remaining; ++ele) {
              chandra::utils::ByteReadWrapper<Value> out_wrapper(buffer[ele]);
              for(const auto& byte : out_wrapper) {
                  //const bool close = (ele == (remaining - 1)) and io_wrapper.isLast(&byte);
                  //static_cast<const derived_t *>(this)->write_stream_byte(byte, close);
                  const uint8_t data[5] = {
                      0x02,
                      static_cast<uint8_t>((addr&0xFF0000)>>16),
                      static_cast<uint8_t>((addr&0x00FF00)>>8),
                      static_cast<uint8_t>(addr&0x0000FF),
                      byte
                  };
                  static_cast<const derived_t *>(this)->wren();
                  while(!static_cast<const derived_t *>(this)->wel()){}
                  spi_.tx(data, 5, cs_, chandra::io::SPI::WRAP);
                  static_cast<const derived_t *>(this)->block();
                  ++addr;
              }
          }

          return {start, start + (remaining * sizeof(Value))};
        }

        chandra::io::SPIMaster& spi_;
        chandra::io::SPI::cs_t cs_;
};

} /*namespace drivers*/
} /*namespace chandra*/

#endif /*CHANDRA_SPI_FLASH_25_SERIES_H*/
