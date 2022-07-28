#ifndef CHANDRA_RFM9X_H
#define CHANDRA_RFM9X_H

//
// Chandra-HAL Includes
//
#include "register_device.h"
#include "spi.h"
#include "units.h"
// using namespace chandra::units::mks::literals;

namespace chandra
{
namespace drivers
{
struct LoRa
{
	enum bw_t {
		BW_7k8 = 0x00,
		BW_10k4 = 0x01,
		BW_15k6 = 0x02,
		BW_20k8 = 0x03,
		BW_31k2 = 0x04,
		BW_41k7 = 0x05,
		BW_62k5 = 0x06,
		BW_125k = 0x07,
		BW_250k = 0x08,
		BW_500k = 0x09,
	};

	enum sf_t {
		SF_6 = 6,
		SF_7 = 7,
		SF_8 = 8,
		SF_9 = 9,
		SF_10 = 10,
		SF_11 = 11,
		SF_12 = 12
	};

	enum cr_t {
		CR_4_5 = 0x01,
		CR_4_6 = 0x02,
		CR_4_7 = 0x03,
		CR_4_8 = 0x04
	};
};

class RFM9xLoRa
{
	protected:
		using register_device_t = chandra::drivers::RegisterDevice<chandra::io::SPIMaster>;

	public:
		enum registers_t {
			RegFIFO = 0x00,
			RegOpMode = 0x01,
			RegFreqH = 0x06,
			RegFreqM = 0x07,
			RegFreqL = 0x08,
			RegPaConfig = 0x09,
			RegPaRamp = 0x0A,
			RegOcp = 0x0B,
			RegLna = 0x0C,
			RegFIFOAddrPtr = 0x0D,
			RegFIFOTxBaseAddr = 0x0E,
			RegFIFORxBaseAddr = 0x0F,
			RegFIFORxCurrentAddr = 0x10,
			RegIrqFlagMask = 0x11,
			RegIrqFlag = 0x12,
			RegRxPayloadBytes = 0x13,
			RegRxHeaderCountH = 0x14,
			RegRxHeaderCountL = 0x15,
			RegRxPacketCountH = 0x16,
			RegRxPacketCountL = 0x17,
			RegModemStatus = 0x18,
			RegLastSNR = 0x19,
			RegLastRSSI = 0x1A,
			RegCurrentRSSI = 0x1B,
			RegHopChannel = 0x1C,
			RegModemConfig1 = 0x1D,
			RegModemConfig2 = 0x1E,
			RegSymbolTimeoutL = 0x1F,
			RegPreambleH = 0x20,
			RegPreambleL = 0x21,
			RegPayloadLength = 0x22,
			RegMaxPayloadLength = 0x23,
			RegHopPeriod = 0x24,
			RegFIFORxPeriod = 0x25,
			RegModemConfig3 = 0x26,
			RegFrequencyErrorH = 0x28,
			RegFrequencyErrorM = 0x29,
			RegFrequencyErrorL = 0x2A,
			RegWidebandRSSI = 0x2C,

			RegDIOMapping1 = 0x40,
			RegDIOMapping2 = 0x41,
			RegVersion = 0x42
		};

		enum modes_t {
			Sleep = 0x00,
			Standby = 0x01,
			FSTX = 0x02,
			Transmit = 0x03,
			FSRX = 0x04,
			ReceiveContinuous = 0x05,
			Receive = 0x06,
			ChannelActivityDetect = 0x07
		};

		RFM9xLoRa(
				chandra::io::SPIMaster& _spi,
				const chandra::io::SPI::cs_t& _cs = chandra::io::SPI::CS0
		) : regs(_spi, _cs, (1<<7), (0<<7)) {}

//		bool init(const LoRa::bw_t& _bw=LoRa::BW_250k, const LoRa::sf_t& _sf = LoRa::SF_7, const LoRa::cr_t& _cr = LoRa::CR_4_6, const float& _db = 0) {
		bool init(const LoRa::bw_t& _bw=LoRa::BW_7k8, const LoRa::sf_t& _sf = LoRa::SF_12, const LoRa::cr_t& _cr = LoRa::CR_4_8, const float& _db = 0) {

			uint8_t data = 0;

			// Enter Sleep Mode
			regs.write(RegOpMode, static_cast<uint8_t>(0));

			// Set Long Range Mode
			regs.write(RegOpMode, static_cast<uint8_t>(1<<7));

			// Configure Bandwidth, Coding Rate and Explicit Header
			data = (_bw << 4) | (_cr << 1);
			regs.write(RegModemConfig1, data);

			// Configure Spreading Factor, and RxPayloadCRC
			data = (_sf << 4) | (1<<2);
			regs.write(RegModemConfig2, data);

			// Clear all interrupts
			regs.write(RegIrqFlag, static_cast<uint8_t>(0xFF));

			// Clear Payload Bytes
			regs.write(RegRxPayloadBytes, static_cast<uint8_t>(0));

			// Configure Output Power
			power(_db);

			// Configure Rx Timeout

			// Enter Standby Mode
			standby();

			return valid();
		}

		uint8_t cfg() { return regs.byte(RegOpMode); }

		uint8_t id() const {
			return regs.byte(RegVersion);
		}

		bool valid() const {
			return id() == 0x12;
		}

		bool power(float _db) {
			static const bool allow_rfo = false;
			bool success = false;
			if(_db < 2 and allow_rfo) { // Transmit through RFO pin
				const double dP = _db + 4.2;
				const uint8_t OutputPower = uint8_t(std::min(15.0, dP));
				const uint8_t MaxPower = uint8_t((dP - OutputPower + 0.3) / 0.6);
				regs.write(RegPaConfig, static_cast<uint8_t>((MaxPower << 4) | OutputPower));  // Transmit through the RFO
			} else {
				uint8_t output_power = 0;
				if(_db > 2) {
					if(_db > 17) _db = 17;
					output_power = static_cast<uint8_t>(_db - 2);
				}
				regs.write(RegPaConfig, static_cast<uint8_t>((1<<7) | output_power));  // Transmit through the PA_BOOST pin
			}
			return success;
		}

		template<class Rep>
		bool center_frequency(const chandra::units::mks::Q_Hz<Rep> _f_rf) {
			const Rep f_osc{32e6};
			const uint32_t frf{
				static_cast<uint32_t>(
					static_cast<uint64_t>((1 << 19) * _f_rf.value()) / static_cast<uint64_t>(f_osc)
				)
			};
			const auto last_mode = get_mode();
			if((last_mode != Sleep) and (last_mode != Standby)) {
				standby();
			}
			const uint8_t data[3] = {
				static_cast<uint8_t>((frf >> 16) & 0xFF),
				static_cast<uint8_t>((frf >> 8) & 0xFF),
				static_cast<uint8_t>(frf & 0xFF)
			};
			regs.writebytes(RegFreqH, 3, data);
			set_mode(last_mode);

			return true;
		}

		template<uint8_t N>
		bool tx(const uint8_t (&_msg)[N]) { // TODO: CONST
			standby();

			// Set FIFO Base Address
			const uint8_t addr = regs.byte(RegFIFOTxBaseAddr);
			regs.write(RegFIFOAddrPtr, addr);

			// Load FIFO
			regs.writebytes(RegFIFO, N, _msg);

			// Set FIFO Base Address
			regs.write(RegFIFOAddrPtr, addr);

			// Load FIFO
			uint8_t buffer[N];
			regs.bytes(RegFIFO, N, buffer);
			(void) buffer;

			// Set payload length
			regs.write(RegPayloadLength, N);

			// Trigger transmission
			transmit();
			return true;
		}

		auto available() const {
			return regs.byte(RegRxPayloadBytes);
		}

		template<uint8_t N>
		bool rx(uint8_t (&_msg)[N]) {
			// Set FIFO Base Address
			const uint8_t addr = regs.byte(RegFIFORxCurrentAddr);
			regs.write(RegFIFOAddrPtr, addr);

			// Load From FIFO
			const auto message_size = available();
			if(message_size > N) return false;
			regs.bytes(RegFIFO, N, _msg);

			// Reposition Rx Pointer
			regs.write(RegFIFORxCurrentAddr, static_cast<uint8_t>(addr - N));

			return true;
		}

		int16_t snr() const {
			return 4*static_cast<int8_t>(regs.byte(RegLastSNR));
		}

		int16_t rssi() const {
			const int16_t rssi_offset(-157); // NOTE: THIS OFFSET IS FOR THE HF PORT (LF IS -164)
			const uint8_t raw_rssi = regs.byte(RegLastRSSI);
			const auto snr_val = snr();
			if(snr_val > 0){
				return rssi_offset + ((static_cast<int16_t>(15)*raw_rssi) / 16);
			} else {
				return rssi_offset + raw_rssi + (snr_val / 4);
			}
		}

		void set_mode(const modes_t& _mode) {
			//const uint8_t data = regs.byte(RegOpMode); // TODO: CHECK IF THIS NEEDS TO BE READ FIRST
			//regs.write(RegOpMode, static_cast<uint8_t>((0xF8&data)|uint8_t(_mode)));
			 regs.update(RegOpMode, 0x07, static_cast<uint8_t>(_mode));
			return;
		}

		modes_t get_mode() {
			return modes_t(regs.byte(RegOpMode) & 0x07);
		}

		void sleep() {
			set_mode(Sleep);
		}

		bool in_sleep() {
			const mode_t mode = get_mode();
			return (mode == Sleep);
		}

		void standby() {
			set_mode(Standby);
		}

		bool in_standby() {
			const mode_t mode = get_mode();
			return (mode == Standby);
		}

		void transmit() {
			// Configure DIO0 Pin for TxDone
			regs.update(RegDIOMapping1, (0x3<<6), static_cast<uint8_t>(0x1<<6));

			set_mode(Transmit);
		}

		bool in_transmit() {
			return get_mode() == Transmit;
		}

		void receive() {
			// Set FIFO Base Address
			const uint8_t addr = regs.byte(RegFIFORxBaseAddr);
			regs.write(RegFIFOAddrPtr, addr);

			// Configure DIO0 Pin for RxDone
			regs.update(RegDIOMapping1, (0x3<<6), static_cast<uint8_t>(0));

			set_mode(Receive);
		}

		void continuousReceive() {
			// Set FIFO Base Address
			const uint8_t addr = regs.byte(RegFIFORxBaseAddr);
			regs.write(RegFIFOAddrPtr, addr);

			// Configure DIO0 Pin for RxDone
			regs.update(RegDIOMapping1, (0x3<<6), static_cast<uint8_t>(0));

			set_mode(ReceiveContinuous);
		}

		// TODO: FIX IN_RECEIVE AND IN_TRANSMIT
		bool in_receive() {
			const mode_t mode = get_mode();
			return (mode == Receive) | (mode == ReceiveContinuous) | (mode == ChannelActivityDetect);
		}

		uint8_t get_irqs() {
			return regs.byte(RegIrqFlag);
		}

		void clear_irqs(const uint8_t& _mask) {
			regs.write(RegIrqFlag, _mask); // Clear the Interrupt
		}

		bool check_irq(const uint8_t& _mask, const bool& _auto_clear=true) {
			const uint8_t interrupts = get_irqs();
			if((_mask & interrupts) != _mask) return false;
			if(_auto_clear) clear_irqs(_mask);
			return true;
		}

		bool tx_done() {
			return check_irq(1<<3);
		}

		bool rx_done() {
			return check_irq(1<<6);
		}

	protected:
		register_device_t regs;
};

} /*namespace drivers*/
} /*namespace chandra*/


#endif /* CHANDRA_RFM9X_H */
