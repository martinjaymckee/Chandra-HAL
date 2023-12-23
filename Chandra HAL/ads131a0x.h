
#ifndef CHANDRA_ADS131A0X_H
#define CHANDRA_ADS131A0X_H

//
// Standard Includes
//
#include <chrono>
using namespace std::literals::chrono_literals;
#include <cstddef>
#include <ratio>
#include <utility>

//
// Chandra Includes
//
#include "bitcount.h"
#include "chip_utils.h"
#include "chrono.h"
#include "debounce.h"
#include "parity.h"
#include "spi.h"
#include "units.h"

namespace chandra
{
using namespace std::literals::chrono_literals;

namespace driver
{
struct ADS131Config
{
	static constexpr uint8_t SynchronusMaster = 0b000000;
	static constexpr uint8_t AsynchronusSlave = 0b000001;
	static constexpr uint8_t SynchronusSlave = 0b000010;
	static constexpr uint8_t Frame24Bit = 0b000000;
	static constexpr uint8_t Frame32Bit = 0b000100;
	static constexpr uint8_t Frame16Bit = 0b001000;
	static constexpr uint8_t HammingOff = 0b000000;
	static constexpr uint8_t HammingOn = 0b010000;
};

template<class Value, size_t Channels,
	uint8_t M0 = ADS131Config::AsynchronusSlave,
	uint8_t M1 = ADS131Config::Frame32Bit,
	uint8_t M2 = ADS131Config::HammingOn
>
class ADS131A0X
{
	public:
		using value_t = Value;
		using pin_t = chandra::io::IO;

		enum class ReferenceSource : uint8_t {
			Internal,
			External
		};

		static constexpr uint8_t config_pins = M2 | M1 | M0;

	protected:
		class ADS131A0XHammingCode
		{
			// TODO: THIS IS GOING TO ASSUME 32-BIT VALUE MODE.  LATER IT COULD BE MODIFIED TO ALSO
			//	HANDLE 24-BIT MODE.

			protected:
				static constexpr uint32_t mask_b0 = 0x00DAB555;
				static constexpr uint32_t mask_b1 = 0x00B66CCC;
				static constexpr uint32_t mask_b2 = 0x0071E3C3;
				static constexpr uint32_t mask_b3 = 0x000FE03F;
				static constexpr uint32_t mask_b4 = 0x00001FFF;
				static constexpr uint32_t checksum_mask = 0xFFFFFF00;

				struct DecodeData
				{
					uint32_t data;
					uint8_t code;
					uint8_t chk;
				};

				struct ValidateResult
				{
					uint32_t data;
					bool valid;
				};

			public:
				constexpr uint8_t hammingcode(uint32_t _data) const {
					uint8_t code = 0;
					const bool b0 = chandra::even_parity(_data & mask_b0);
					code |= b0 ? 0x01 : 0;
					const bool b1 = chandra::even_parity(_data & mask_b1);
					code |= b1 ? 0x02 : 0;
					const bool b2 = chandra::even_parity(_data & mask_b2);
					code |= b2 ? 0x04 : 0;
					const bool b3 = chandra::even_parity(_data & mask_b3);
					code |= b3 ? 0x08 : 0;
					const bool b4 = chandra::even_parity(_data & mask_b4);
					code |= b4 ? 0x10 : 0;
					return code;
				}

				constexpr uint8_t checksum(uint32_t _data) const {
					return static_cast<uint8_t>(chandra::pop_ones(_data & checksum_mask) & 0x03);
				}

				constexpr uint32_t encode(uint32_t _data) const { // Note: Data is in LSB format
					const uint8_t code = hammingcode(_data);
					const uint32_t data_with_hamming = (_data << 8) | (code << 3);
					const uint8_t chk = checksum(data_with_hamming);
					return  data_with_hamming | (chk << 1);
				}

				constexpr DecodeData decode(uint32_t _data, const bool& _fix = true) const {
					DecodeData result;
					result.chk = (_data >> 1) & 0x03;
					result.code = (_data >> 3) & 0x1F;
					result.data = (_data >> 8) & 0x00FFFFFF;
					// TODO: ATTEMPT TO FIX THE DATA IF THAT IS ALLOWED AND POSSIBLE.
					return result;
				}
				// NEED A FUNCTION TO FIX A VALUE
				constexpr ValidateResult validate(uint32_t _data, const bool& _fix = true) const {
					// EXTRACT THE DATA, CODE AND CHECKSUM
					// RECALCULATE THE CODE AND CHECKSUM
					// DO COMPARISONS OF THE CODE AND CHECKSUM
					// IF THERE IS A FIXABLE ERROR, APPLY THE FIX AND RETURN SUCCESS
					// IF A NON-FIXABLE ERROR IS DETECTED, RETURN FAILURE
					// ELSE, RETURN THE ORIGINAL DATA AND SUCCESS
					return false;
				}

			protected:

		};

		enum class Register : uint8_t {
			// Identification Registers
			ID_MSB = 0x00,
			ID_LSB = 0x01,

			// Status Registers
			Status1 = 0x02,
			StatusP = 0x03,
			StatusN = 0x04,
			StatusS = 0x05,
			ErrorCnt = 0x06,
			StatusM = 0x07,

			// ADC Registers
			AnalogSystemCfg = 0x0B,
			DigitalSystemCfg = 0x0C,
			CLK1 = 0x0D,
			CLK2 = 0x0E,
			ADC_ENA = 0x0F,

			ADC_base = 0x11
		};

		static constexpr int32_t adc_max = static_cast<int32_t>(static_cast<uint32_t>(1<<23)-1);

		enum class SystemCommand : uint32_t {
			// System Commands
			Null = 0x0000,
			Reset = 0x0011,
			Standby = 0x0022,
			Wakeup = 0x0033,
			Lock = 0x0555,
			Unlock = 0x0655,
		};

		constexpr auto RRegsCmd(const Register& _reg, const uint8_t _num) const {
			return (static_cast<uint16_t>(0b01100000 | static_cast<uint8_t>(_reg)) << 8) | _num;
		}

		constexpr auto RRegCmd(const Register& _reg) const {
			return (static_cast<uint16_t>(0b00100000 | static_cast<uint8_t>(_reg)) << 8);
		}

		constexpr uint8_t RRegExtract(const uint32_t& _status) const {
			return (_status >> 16) & 0xFF;
		}

		constexpr auto WRegCmd(const Register& _reg, const uint8_t _data) const {
			return (static_cast<uint32_t>(0b01000000 | static_cast<uint8_t>(_reg)) << 8) | _data;
		}

		constexpr auto WRegsCmd(const Register& _reg, const uint8_t _num) const {
			return (static_cast<uint32_t>(0b01100000 | static_cast<uint8_t>(_reg)) << 8) | _num;
		}

		struct CmdStatus
		{
			uint16_t status = 0;
			bool valid = false;
		};

		struct RXData
		{
			int32_t channels[Channels];
			bool ok[Channels];
			uint16_t crc = 0;
			CmdStatus status;
			uint8_t num = 0;
			bool valid = false;
		};

		class ChannelProxy
		{
			public:
				ChannelProxy(ADS131A0X& _ref, const uint8_t& _ch)
					: ref_{_ref}, ch_{_ch} {
					gain(1);
				}

				template<class V>
				operator V () const {
					return static_cast<V>(ref_.channels_[ch_]);
				}

				template<class V>
				value_t gain(const V& _av) {
					const uint8_t av = static_cast<uint8_t>(_av);
					uint8_t mask = 0x00;
					if(av <= 1) {
						ref_.gains_[ch_] = 1;
					} else if(av <= 2) {
						mask = 0x01;
						ref_.gains_[ch_] = 2;
					} else if(av <= 4) {
						mask = 0x02;
						ref_.gains_[ch_] = 4;
					} else if(av <= 8) {
						mask = 0x03;
						ref_.gains_[ch_] = 8;
					} else {
						mask = 0x04;
						ref_.gains_[ch_] = 16;
					}

					const bool relock = ref_.regs_locked_;
					if(relock) ref_.unlock();
					const Register reg_addr = static_cast<Register>(static_cast<uint8_t>(Register::ADC_base) + ch_);
					ref_.write_register(reg_addr, mask);
					if(relock) ref_.lock();

					return ref_.gains_[ch_];
				}

				value_t gain() const {
					return ref_.gains_[ch_];
				}

				int32_t raw() const {
					return ref_.channels_raw_[ch_];
				}

			private:
				ADS131A0X& ref_;
				uint8_t ch_;
		};

	public:
		ADS131A0X(chandra::io::SPIMaster& _spi, chandra::io::SPI::cs_t _cs, pin_t _drdy)
    	: spi_{_spi}, cs_{_cs}, drdy_{_drdy} {
    		for(uint8_t idx = 0; idx < Channels; ++idx) {
    			gains_[idx] = 1;
    		}
    	}

    	ADS131A0X(chandra::io::SPIMaster& _spi, chandra::io::SPI::cs_t _cs)
    	: ADS131A0X{_spi, _cs, io::IO()} {}

    	// TODO:
    	//	REFERENCE

		bool init() {
//			wait_for_ready();
			const bool success = valid();

			unlock();
			write_register(Register::DigitalSystemCfg, (1<<1)); // Enable Fixed Frame
			write_register(Register::AnalogSystemCfg, (0x7<<5)); // Enable Negative Charge Pump and High-Resolution Mode, Ext. Ref.
			write_register(Register::CLK1, (1<<1)); // f_iclk = f_clkin / 2
			write_register(Register::CLK2, (1<<5)); // f_mod = f_iclk / 2, osr = 4096
			write_register(Register::ADC_ENA, 0x0F); // Enable all ADC Channels
			wakeup();
			lock();

			return success;
		}

		constexpr uint8_t revision() const {
			return read_register(Register::ID_LSB);
		}

		constexpr uint8_t channels() const {
			return read_register(Register::ID_MSB);
		}

		constexpr bool valid() {
			const bool lock_last = regs_locked_;
			const auto status = txrx_cmd(SystemCommand::Lock);
			const auto config = read_register(Register::StatusM);
			if(!lock_last) unlock();
			return (channels() == Channels) && (status.status == 0x0555) && (config_pins == config);
		}

		ChannelProxy operator[] (const size_t& _ch) {
			return ChannelProxy(*this, _ch);
		}

		ReferenceSource reference(const ReferenceSource& _src, const value_t _v_ref = value_t(0.0)) {
			reference_src_ = _src;
			v_ref_ = _v_ref;

			return reference_src_;
		}

		ReferenceSource reference(const value_t& _v_ref) {
			return reference(ReferenceSource::External, _v_ref);
		}

		bool update() {
//			static auto drdy_edges = chandra::io::logic(drdy_);

			bool updated = false;
			if(!drdy_) {
				const auto results = read_channels();
				if(results.valid) {
					updated = true;
					for(size_t idx = 0; idx < Channels; ++idx) {
						channels_raw_[idx] = results.channels[idx];
						channels_[idx] = calc_channel_value(results.channels[idx], gains_[idx]);
					}
				}
				chandra::chrono::delay(100us);
			}

			return updated;
		}

	protected:
		constexpr value_t vref_int() const {
			return 2.5;
//			return full_scale_5v ? value_t{2.5} : value_t{1.25};
		}

		RXData read_channels() {
			RXData result;
			result.num = Channels;
			const size_t txrx_bytes = (Channels + 2) * word_bytes_;

			uint8_t tx_buffer[txrx_bytes] = {0};
			uint8_t rx_buffer[txrx_bytes];
			spi_.txrx(tx_buffer, rx_buffer, txrx_bytes, cs_);

			// Extract the status
			result.status.status = ((static_cast<uint16_t>(rx_buffer[0]) << 8) | rx_buffer[1]);
//			const uint32_t test = ((static_cast<uint32_t>(rx_buffer[0]) << 24) | (static_cast<uint32_t>(rx_buffer[1]) << 16) | (static_cast<uint32_t>(rx_buffer[2]) << 8) | rx_buffer[3] );
//			const auto status_chk = hamming_.hammingcode((test>>8));//(static_cast<uint32_t>(result.status.status) << 8) | rx_buffer[2]);
			const auto status_chk = hamming_.hammingcode((static_cast<uint32_t>(result.status.status) << 8) | rx_buffer[2]);
			const auto cmp_chk = rx_buffer[3] >> 3;
			result.status.valid = (cmp_chk == status_chk);

			// Extract the channel data
			for(size_t idx = 0; idx < Channels; ++idx) {
				const size_t base = 4 + (4 * idx);
				const uint32_t hsb = static_cast<uint32_t>(rx_buffer[base]) << 16;
				const uint32_t msb = static_cast<uint32_t>(rx_buffer[base + 1]) << 8;
				const uint32_t lsb = static_cast<uint32_t>(rx_buffer[base + 2]);
				const uint32_t val = ((((hsb & 0x800000) == 0) ? 0 : 0xFF000000) | hsb | msb | lsb); // TODO: CHECK THAT THIS IS CALCULATING PROPERLY
				result.channels[idx] = static_cast<int32_t>(val);
				const auto chk = hamming_.hammingcode(val);
				result.ok[idx] = ((rx_buffer[base + 3] >> 4) == chk); // TODO: THE BUFFER VALUE SHOULD BE SHIFTED....
				(void) chk;
			}
//
//			volatile const uint8_t stat_s = read_register(Register::StatusS);
//			volatile const uint8_t stat_n = read_register(Register::StatusN);
//			volatile const uint8_t stat_p = read_register(Register::StatusP);
//			volatile const uint8_t stat_m = read_register(Register::StatusM);
//			(void) stat_s;
//			(void) stat_n;
//			(void) stat_p;
//			(void) stat_m;

			// Extract the CRC
			result.crc = (static_cast<uint16_t>(rx_buffer[txrx_bytes-4]) << 8) | static_cast<uint16_t>(rx_buffer[txrx_bytes-4]);

			// TODO: ACTUALLY CALCULATE THE CRC OF THE RECEIVED DATA AND VALIDATE THE DATA....
			result.valid = true; // TODO: DO SOMETHING BETTER HERE
			return result;
		}

		CmdStatus txrx_cmd(uint16_t _cmd, const std::chrono::microseconds& _us = std::chrono::microseconds{0}) const {
			const size_t txrx_bytes = (Channels + 2) * word_bytes_;
			const uint32_t encoded_cmd = hamming_.encode(uint32_t(_cmd)<<8);
			uint8_t cmd[txrx_bytes] = {0};
			cmd[0] = static_cast<uint8_t>((encoded_cmd >> 24) & 0xFF);
			cmd[1] = static_cast<uint8_t>((encoded_cmd >> 16) & 0xFF);
			cmd[2] = static_cast<uint8_t>((encoded_cmd >> 8) & 0xFF);
			cmd[3] = static_cast<uint8_t>(encoded_cmd & 0xFF);

			spi_.tx(cmd, txrx_bytes, cs_); // Transmit command in first transfer

			chandra::chrono::delay(_us);

			uint8_t rx_buffer[txrx_bytes] = {0};
			spi_.rx(rx_buffer, txrx_bytes, cs_, chandra::io::SPI::WRAP, 0x00);
			return {static_cast<uint16_t>((static_cast<uint16_t>(rx_buffer[0]) << 8) | rx_buffer[1]), true};
		}

		CmdStatus txrx_cmd(SystemCommand _cmd, const std::chrono::microseconds& _us = std::chrono::microseconds{0}) const {
			auto status = txrx_cmd(static_cast<uint16_t>(_cmd), _us);
			if( (_cmd == SystemCommand::Null) || (_cmd == SystemCommand::Reset)) return status;
			status.valid = (_cmd == static_cast<SystemCommand>(status.status)); // Check for ACK
			return status;
		}

		bool null_cmd() {
			const auto status = txrx_cmd(SystemCommand::Null);
			return status.valid;
		}

		bool soft_reset() {
			const auto status = txrx_cmd(SystemCommand::Reset, 5ms); // Note: The defined reset delay is 4.5ms max....
			return status.valid;
		}

		bool standby() {
			const auto status = txrx_cmd(SystemCommand::Standby);
			return status.valid;
		}

		bool wakeup() {
			const auto status = txrx_cmd(SystemCommand::Wakeup);
			return status.valid;
		}

		bool lock() {
			const auto status = txrx_cmd(SystemCommand::Lock);
			if(status.valid) {
				regs_locked_ = true;
				return true;
			}

			return false;
		}

		bool unlock() {
			const auto status = txrx_cmd(SystemCommand::Unlock);
			if(status.valid) {
				regs_locked_ = false;
				return true;
			}

			return false;
		}

		void wait_for_ready() {
			while(true) {
				const auto status = txrx_cmd(SystemCommand::Null);
				if(status.status == (0xFF00 | Channels)) return;
			}
		}

		bool write_register(const Register& _reg, uint8_t _data) {
			auto result = txrx_cmd(WRegCmd(_reg, _data));
			return (_data == RRegExtract(result.status));
		}

		uint8_t read_register(const Register& _reg) const {
			const auto result = txrx_cmd(RRegCmd(_reg));
			return result.status & 0xFF; //RRegExtract(result.status);
		}

	protected:
		constexpr value_t calc_channel_value(const int32_t _val, const value_t& _av ) const {
			return (v_ref_ * _val) / (_av * adc_max);
		}

	private:
		ADS131A0XHammingCode hamming_;
		chandra::io::SPIMaster& spi_;
		chandra::io::SPI::cs_t cs_;
		pin_t drdy_;
		ReferenceSource reference_src_ = ReferenceSource::Internal;
		value_t v_ref_;
		int32_t channels_raw_[Channels];
		value_t channels_[Channels];
		value_t gains_[Channels];
		size_t word_bytes_ = 4; // TODO: NEED TO FIGURE THIS OUT FROM THE CONFIGURATION
		bool regs_locked_ = true;
};

template<class Value = float,
	uint8_t M0 = ADS131Config::AsynchronusSlave,
	uint8_t M1 = ADS131Config::Frame32Bit,
	uint8_t M2 = ADS131Config::HammingOn
>
using ADS131A02 = ADS131A0X<Value, 2, M0, M1, M2>;

template<class Value = float,
	uint8_t M0 = ADS131Config::AsynchronusSlave,
	uint8_t M1 = ADS131Config::Frame32Bit,
	uint8_t M2 = ADS131Config::HammingOn
>
using ADS131A04 = ADS131A0X<Value, 4, M0, M1, M2>;

} /*namespace driver*/
} /*namespace chandra*/

#endif /*CHANDRA_ADS131A0X_H*/
