#ifndef FT25H_H
#define FT25H_H

#include<algorithm>

#include "spi.h"

namespace chandra
{
namespace drivers
{

struct AddressRange
{
        size_t start;
        size_t end;

        operator bool() const { return end > start; }
};

struct SectorRange
{
        size_t start;
        size_t end;

        operator bool() const { return end > start; }
};

class FT25H16
{
    public:
        //
        // Configuration Values
        //
        static constexpr size_t pageSize() { return 256; }
        static constexpr size_t pages() { return 8192; }
        static constexpr size_t sectorSize() { return 4096; }
        static constexpr size_t sectors() { return 512; }
        static constexpr size_t accessBytes() { return 1; }
        static constexpr size_t capacity() { return sectors() * sectorSize(); }
        static AddressRange sectorExtents(const size_t& _sector) {
            const size_t start = _sector * sectorSize();
            return {start, start+sectorSize()-1};
        }

        //
        // Memory Constructor
        //
        FT25H16(chandra::io::SPIMaster& _spi, chandra::io::SPI::cs_t _cs) : spi_(_spi), cs_(_cs) {}

        //
        // Status Accessors
        //
        uint16_t id() const { // ID should be 0x4015
            const uint8_t cmd[4] = {0x9F, 0x00, 0x00, 0x01}; // Request Device ID First
            uint8_t bytes[3];
            spi_.tx(cmd, 4, cs_, chandra::io::SPI::START);
            spi_.rx(bytes, 3, cs_, chandra::io::SPI::STOP);
            return (static_cast<uint16_t>(bytes[1])<<8) | bytes[2];
        }

        bool busy() const { return statusL() & 0x01; }

        //
        // Access Methods
        //
        //  Read
        //      --> Buffer Length
        template<typename Value, size_t N>
        AddressRange read(const size_t& _addr, Value (&buffer)[N]) const {
            return readUnprotected(_addr, buffer, N);
            return {};
        }

        //      --> Explicit Length
        template<typename Value, size_t N>
        AddressRange read(const size_t& _addr, Value (&buffer)[N], const size_t& _values) const {
            if(_values >= N) return {};
            return readUnprotected(_addr, buffer, _values);
        }

        //  Write
        //      --> Buffer Length
        template<typename Value, size_t N>
        AddressRange write(const size_t& _addr, const Value (&buffer)[N]) const {
            return writeUnprotected(_addr, buffer, N);
            return {};
        }

        //      --> Explicit Length
        template<typename Value, size_t N>
        AddressRange write(const size_t& _addr, const Value (&buffer)[N], const size_t& _values) const {
            if(_values >= N) return {};
            return writeUnprotected(_addr, buffer, _values);
        }

        //  Erase
        //      --> Whole Chip
        AddressRange erase() const {
            wren();
            const uint8_t cmd = 0x60;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            return {0, capacity()-1};
        }

    protected:
        void wren() const {
            const uint8_t cmd = 0x06;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            while(!wel()){}
        }

        void wrdi() const {
            const uint8_t cmd = 0x04;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::WRAP);
            while(wel()){}
        }

        bool wel() const {
            return statusL() & 0x02;
        }

        uint8_t statusL() const {
            const uint8_t cmd = 0x05;
            uint8_t byte;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::START);
            spi_.rx(&byte, 1, cs_, chandra::io::SPI::STOP);
            return byte;
        }

        uint8_t statusH() const {
            const uint8_t cmd = 0x35;
            uint8_t byte;
            spi_.tx(&cmd, 1, cs_, chandra::io::SPI::START);
            spi_.rx(&byte, 1, cs_, chandra::io::SPI::STOP);
            return byte;
        }

        uint16_t status() const {
            return (static_cast<uint16_t>(statusH())<<8) | statusL();
        }

        template<typename Value, size_t N>
        AddressRange readUnprotected(const size_t& addr, Value (&buffer)[N], const size_t& remaining) const {
            const size_t length = remaining * sizeof(Value);
            const size_t start = addr;
            const size_t end = start + length;
            const uint8_t cmd[4] = {
                0x03,
                static_cast<uint8_t>((addr&0xFF0000)>>16),
                static_cast<uint8_t>((addr&0x00FF00)>>8),
                static_cast<uint8_t>(addr&0x0000FF)
            };

            spi_.tx(cmd, 4, cs_, chandra::io::SPI::START);
            spi_.rx(buffer, length, cs_, chandra::io::SPI::STOP);
            return {start, end};
        }

        template<typename Value, size_t N>
        AddressRange writeUnprotected(size_t addr, const Value (&buffer)[N], size_t remaining) const {
            const uint8_t status = statusL();
            const size_t length = remaining * sizeof(Value);
            const size_t start = addr;
            const size_t end = start + length - 1;
            size_t offset = 0;

            while(remaining > 0) {
                while(busy()) {}; // CAUTION: THIS DOES BLOCK

                const uint32_t page_bytes_available = 256 - (addr - (addr&0xFFFF00));
                const size_t write_bytes = page_bytes_available < remaining ? page_bytes_available : remaining;
                const uint8_t cmd[4] = {
                    0x02,
                    static_cast<uint8_t>((addr&0xFF0000)>>16),
                    static_cast<uint8_t>((addr&0x00FF00)>>8),
                    static_cast<uint8_t>(addr&0x0000FF)
                };

                wren();
                spi_.tx(cmd, 4, cs_, chandra::io::SPI::START);
                spi_.tx(&buffer[offset], write_bytes, cs_, chandra::io::SPI::STOP);

                remaining -= write_bytes;
                addr += write_bytes;
                offset += write_bytes;
            }

            return {start, end};
        }

        chandra::io::SPIMaster& spi_;
        chandra::io::SPI::cs_t cs_;
};

} /*namespace drivers*/
} /*namespace chandra*/
#endif // FT25H_H

