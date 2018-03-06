/*
 * usart.h
 *
 *  Created on: Apr 9, 2016
 *      Author: martin
 */

#ifndef CHANDRA_VIRTUAL_SERIAL_H_
#define CHANDRA_SERIAL_H_

#include <cstdio>
#include <cmath>
#include <stdint.h>
#include <string.h>

#include "../format.h"
//#include "../usart_utils.h"

namespace chandra
{
namespace io
{

// TODO: MODIFY TO USE STREAM....
template<uint32_t _rxtx_buffer_length = 128>
class LoopbackVirtualSerial
        : public Stream< LoopbackVirtualSerial<_rxtx_buffer_length, _rxtx_buffer_length> >
{
	protected:
        using calc_t = long;
        using LoopbackVirtualSerial<_rxtx_buffer_length>;

	public:
        LoopbackVirtualSerial() {}

        USARTClockStatus<calc_t> uclk( unsigned long = 0 ) {
			USARTClockStatus<calc_t> status;
			status.clk = -1;
			status.ppm = -1;

			return status;
		}

		calc_t actual_uclk() {
			return -1;
		}

		bool enable(bool _enable) {
			return true;
		}

		bool enable() const { return true; }

        USARTClockStatus<calc_t> baud( unsigned int, unsigned int = 0 ){
			USARTClockStatus<calc_t> status;
			status.clk = -1;
			status.ppm = -1;
			return status;
		}

		bool available() const {
			return buffer_.available();
		}

        bool put( char _ch ) {
			buffer_ << _ch;
            return true;
		}

		operator char() { return read(); }

		char read() { return char(buffer_); }

        virtual_serial_t& operator >> ( char& _ch ) {
			_ch = read();
			return *this;
		}

	private:
		FixedCircularBuffer<char, _rxtx_buffer_length> buffer_;
};

template<uint32_t _tx_buffer_length = 256, uint32_t _rx_buffer_length = 256>
class FlowthroughVirtualSerial
        : public Stream< FlowthroughVirtualSerial<_tx_buffer_length, _rx_buffer_length> >
{
        protected:
                using calc_t = long;
                using virtual_serial_t = FlowthroughVirtualSerial<_tx_buffer_length, _rx_buffer_length>;

                struct RXBufferProxy : public Stream<RXBufferProxy>
                {
                    public:
                        RXBufferProxy(virtual_serial_t& _serial) : serial_(_serial) {}

                        bool put( char _ch ) {
                            serial_.rx_buffer_ << _ch;
                            return true;
                        }

                    private:
                        virtual_serial_t& serial_;
                };

        public:
                FlowthroughVirtualSerial() : rx(*this) {}

                USARTClockStatus<calc_t> uclk( unsigned long = 0 ) {
                        USARTClockStatus<calc_t> status;
                        status.clk = -1;
                        status.ppm = -1;

                        return status;
                }

                calc_t actual_uclk() {
                        return -1;
                }

                bool enable(bool _enable) {
                        return true;
                }

                bool enable() const { return true; }

                USARTClockStatus<calc_t> baud( unsigned int, unsigned int = 0 ){
                        USARTClockStatus<calc_t> status;
                        status.clk = -1;
                        status.ppm = -1;
                        return status;
                }

                bool available() const {
                        return rx_buffer_.available();
                }

                bool put( char _ch ) {
                        tx_buffer_ << _ch;
                        return true;
                }

                operator char() { return read(); }

                char read() { return char(rx_buffer_); }

                virtual_serial_t& operator >> ( char& _ch ) {
                        _ch = read();
                        return *this;
                }

                RXBufferProxy rx;

        private:
                FixedCircularBuffer<char, _tx_buffer_length> tx_buffer_;
                FixedCircularBuffer<char, _rx_buffer_length> rx_buffer_;
};

} /*namespace io*/
} /*namespace chandra*/

#endif /*CHANDRA_virtualUAL_SERIAL_H*/
