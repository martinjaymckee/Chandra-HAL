
#ifndef CHANDRA_AD56X3R_H
#define CHANDRA_AD56X3R_H

#include <chrono>
#include <cstddef>
#include <ratio>
#include <utility>

#include "chip_utils.h"
#include "chrono.h"
#include "spi.h"
#include "units.h"

namespace chandra
{
using namespace std::literals::chrono_literals;

namespace driver
{
template<class Value, uint8_t Bits, bool full_scale_5v>
class AD56X3R
{
	public:
		using value_t = Value;
		using pin_t = chandra::io::IO;

		enum class ReferenceSource : uint8_t {
			Internal,
			External
		};

		enum class Address : uint8_t {
			DACA = 0x00,
			DACB = 0x01,
			ALL_DACS = 0x07
		};

	protected:
		static constexpr uint16_t dac_max = uint16_t{uint32_t{1<<Bits}-1};
		static constexpr size_t offset_bits = 16 - Bits;

		enum class Command : uint8_t {
			Write = 0x00,
			Update = 0x01,
			WriteAndUpdateAll = 0x02,
			WriteAndUpdate = 0x03,
			PowerDownUp = 0x04,
			Reset = 0x05,
			LDACSetup = 0x06,
			ReferenceSetup = 0x07
		};

		class ChannelProxy
		{
			public:
				ChannelProxy(AD56X3R& _ref, const Address& _addr)
					: ref_{_ref}, addr_{_addr} {
					enable(true);
				}

				bool enable(const bool& _en) {
					ref_.set_channel_enabled(_en, addr_);
					return _en;
				}

				constexpr bool enabled() const {
					return ref_.get_channel_enabled(addr_);
				}

				bool clear() {
					ref_.set_clr(true);
					chandra::chrono::delay(10us);
					ref_.set_clr(false);
					return true;
				}

				ChannelProxy& operator = (value_t _val) {
					ref_.set_channel(addr_, _val);
					return *this;
				}

			private:
				AD56X3R& ref_;
				Address addr_;
		};

	public:
		AD56X3R(chandra::io::SPIMaster& _spi, chandra::io::SPI::cs_t _cs, pin_t _ldac, pin_t _clr)
    	: spi_{_spi}, cs_{_cs}, ldac_{_ldac}, clr_{_clr} {}

		AD56X3R(chandra::io::SPIMaster& _spi, chandra::io::SPI::cs_t _cs, const pin_t& _ldac)
    	: AD56X3R{_spi, _cs, _ldac, io::IO()} {}

		AD56X3R(chandra::io::SPIMaster& _spi, chandra::io::SPI::cs_t _cs)
    	: AD56X3R{_spi, _cs, io::IO(), io::IO()} {}

		bool init() {
    		reference(ReferenceSource::External, 2.5);
    		set_clr(true);
    		chandra::chrono::delay(10ms);
    		set_clr(false);
			return true;
		}

		ChannelProxy operator[] (const Address& _addr) {
			return ChannelProxy(*this, _addr);
		}

		ChannelProxy operator[] (const size_t _idx) {
			switch(_idx) {
				case 0:
					return ChannelProxy(*this, Address::DACA);

				case 1:
					return ChannelProxy(*this, Address::DACB);

				default:
					break;
			}

			return ChannelProxy(*this, Address::ALL_DACS); // TODO: DECIDE IF THIS IS THE BEST FALL-BACK METHOD
		}

		ReferenceSource reference(const ReferenceSource& _src, const value_t _v_ref = value_t(0.0)) {
			reference_src_ = _src;
			switch(reference_src_) {
				case ReferenceSource::Internal:
					send_cmd(Command::ReferenceSetup, Address::ALL_DACS, 0x01);
					v_ref_ = vref_int();
					break;

				case ReferenceSource::External:
					send_cmd(Command::ReferenceSetup, Address::ALL_DACS, 0x00);
					v_ref_ = _v_ref;
					break;

				default:
					break;
			}

			return reference_src_;
		}

		ReferenceSource reference(const value_t& _v_ref) {
			return reference(ReferenceSource::External, _v_ref);
		}

	protected:
		constexpr value_t vref_int() const {
			return full_scale_5v ? value_t{2.5} : value_t{1.25};
		}

		bool send_cmd(Command _cmd, Address _addr, uint16_t _data) {
			uint8_t cmd[3] = {
				static_cast<uint8_t>((static_cast<uint8_t>(_cmd) << 3) | (static_cast<uint8_t>(_addr))),
				static_cast<uint8_t>(((_data >> 8) & 0xFF)),
				static_cast<uint8_t>((_data & 0xFF))
			};

			spi_.tx(cmd, 3, cs_);

			return true;
		}

		constexpr bool set_channel_raw(const Address& _addr, const uint16_t _dac, const bool& _update = true) {
			const uint16_t dac = (_dac << offset_bits);
			const bool do_ldac = _update && ldac_.valid();
			const auto cmd = (_update && !ldac_.valid()) ? Command::WriteAndUpdateAll : Command::Write;
			const bool success = send_cmd(cmd, _addr, dac);
			if(do_ldac) {
				set_ldac(true);
				chandra::chrono::delay(10us);
				set_ldac(false);
			}
			return success;
		}

		constexpr bool set_channel_raw(uint8_t _ch, const uint16_t _dac, const bool& _update = true) {
			return set_channel_raw((_ch == 1) ? Address::DACB : Address::DACA, _dac, _update);
		}

		constexpr bool set_channel(const Address& _addr, const value_t _val, const bool& _update = true) {
			const uint16_t dac = (_val >= v_ref_) ? dac_max : static_cast<uint16_t>((dac_max * _val) / v_ref_) ;
			return set_channel_raw(_addr, dac, _update);
		}

		constexpr bool set_channel(uint8_t _ch, const value_t _val, const bool& _update = true) {
			const uint16_t dac = (_val >= v_ref_) ? dac_max : static_cast<uint16_t>((dac_max * _val) / v_ref_) ;
			return set_channel_raw(_ch, dac, _update);
		}

		bool set_channel_enabled(bool _enable, const Address& _addr) {
			if(_enable) { // Enable the specified channels
				power_status_ |= static_cast<uint16_t>(_addr);
			} else { // Disable the specified channels
				power_status_ = (power_status_ & 0xFFFC) | (power_status_ & 0x03 & static_cast<uint16_t>(_addr));
			}
			send_cmd(Command::PowerDownUp, Address::ALL_DACS, power_status_);
			chandra::chrono::delay(4us);
			return true;
		}

		bool get_channel_enabled(const Address& _addr) {
			return (power_status_ & static_cast<uint16_t>(_addr) & 0x03) != 0x00;
		}

		bool set_clr(bool _state) {
			if(clr_.valid()) {
				clr_ = _state;
			}

			return _state;
		}

		bool set_ldac(bool _state) {
			if(clr_.valid()) {
				clr_ = _state;
			}

			return _state;
		}

	private:
		chandra::io::SPIMaster& spi_;
		chandra::io::SPI::cs_t cs_;
		chandra::io::IO ldac_;
		chandra::io::IO clr_;
		ReferenceSource reference_src_ = ReferenceSource::Internal;
		uint16_t power_status_ = 0x0000;
		value_t v_ref_;
};

template<class Value = float>
using AD5663R_3 = AD56X3R<Value, 16, false>;

template<class Value = float>
using AD5663R_5 = AD56X3R<Value, 16, true>;

template<class Value = float>
using AD5643R_3 = AD56X3R<Value, 14, false>;

template<class Value = float>
using AD5643R_5 = AD56X3R<Value, 14, true>;

template<class Value = float>
using AD5623R_3 = AD56X3R<Value, 12, false>;

template<class Value = float>
using AD5623R_5 = AD56X3R<Value, 12, true>;

} /*namespace driver*/
} /*namespace chandra*/

#endif /*CHANDRA_AD56X3R_H*/
