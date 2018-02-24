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

template<uint32_t _rxtx_buffer_length = 128>
class LoopbackVirtualSerial
{
	protected:
		typedef long calc_t;
        typedef LoopbackVirtualSerial<_rxtx_buffer_length> virtual_serial_t;

	public:
        LoopbackVirtualSerial() {}


		USARTClockStatus<calc_t> uclk( unsigned long _clk = ( 4 * 115200 * 16 ) ) {
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

		USARTClockStatus<calc_t> baud( unsigned int _baud, unsigned int _osr = 16 ){
			USARTClockStatus<calc_t> status;
			status.clk = -1;
			status.ppm = -1;
			return status;
		}

		bool available() const {
			return buffer_.available();
		}

        virtual_serial_t& operator << ( char _ch ) {
			buffer_ << _ch;
			return *this;
		}

        virtual_serial_t& operator << ( const char* _str ) {
			while( *_str ) {
				buffer_ << *_str;
				++_str;
			}
			return *this;
		}

        virtual_serial_t& operator << ( unsigned int _val ) {
			char temp[20];
			Unsigned<unsigned int>::toA(_val, temp);
			return this->operator << ( temp );
		}

        virtual_serial_t& operator << ( int _val ) {
			char temp[20];
			Signed<int>::toA(_val, temp);
			return this->operator << ( temp );
		}

        virtual_serial_t& operator << ( double _val ) {
			char temp[20];
			Float<double>::toD(_val, temp);
			return this->operator << ( temp );
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
{
        protected:
                typedef long calc_t;
                typedef FlowthroughVirtualSerial<_tx_buffer_length, _rx_buffer_length> virtual_serial_t;

                struct RXBufferProxy
                {
                    public:
                        RXBufferProxy(virtual_serial_t& _serial) : serial_(_serial) {}
                        void operator << ( char _ch ) {
                            serial_.rx_buffer_ << _ch;
                        }

                        void operator << ( const char* _str ) {
                            while( *_str ) {
                                serial_.rx_buffer_ << *_str;
                                ++_str;
                            }
                        }

                        void operator << ( unsigned int _val ) {
                            char temp[20];
                            Unsigned<unsigned int>::toA(_val, temp);
                        }

                        void operator << ( int _val ) {
                            char temp[20];
                            Signed<int>::toA(_val, temp);
                        }

                        void operator << ( double _val ) {
                            char temp[20];
                            Float<double>::toD(_val, temp);
                        }

                    private:
                        virtual_serial_t& serial_;
                };

        public:
                FlowthroughVirtualSerial() : rx(*this) {}

                USARTClockStatus<calc_t> uclk( unsigned long _clk = ( 4 * 115200 * 16 ) ) {
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

                USARTClockStatus<calc_t> baud( unsigned int _baud, unsigned int _osr = 16 ){
                        USARTClockStatus<calc_t> status;
                        status.clk = -1;
                        status.ppm = -1;
                        return status;
                }

                bool available() const {
                        return rx_buffer_.available();
                }

                virtual_serial_t& operator << ( char _ch ) {
                        tx_buffer_ << _ch;
                        return *this;
                }

                virtual_serial_t& operator << ( const char* _str ) {
                        while( *_str ) {
                                tx_buffer_ << *_str;
                                ++_str;
                        }
                        return *this;
                }

                virtual_serial_t& operator << ( unsigned int _val ) {
                        char temp[20];
                        Unsigned<unsigned int>::toA(_val, temp);
                        return this->operator << ( temp );
                }

                virtual_serial_t& operator << ( int _val ) {
                        char temp[20];
                        Signed<int>::toA(_val, temp);
                        return this->operator << ( temp );
                }

                virtual_serial_t& operator << ( double _val ) {
                        char temp[20];
                        Float<double>::toD(_val, temp);
                        return this->operator << ( temp );
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
