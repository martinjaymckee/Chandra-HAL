#ifndef CHANDRA_TRACKER_PROTOCOL_H
#define CHANDRA_TRACKER_PROTOCOL_H

#include <iostream>

#include "binary_serialize.h"
#include "chrono.h"
#include "circular_buffer.h"
#include "coordinates.h"
#include "units.h"
using namespace chandra::units::mks::literals;

namespace chandra
{
namespace aero
{
namespace protocol
{

enum class TrackerFlightMode {
	Initializing = 0x00,
	Preflight = 0x01,
	Ascent = 0x02,
	Descent = 0x03,
	Postflight = 0x04,
	Invalid = 0x07
};

enum class TrackerLocalizationStatus {
	NoFix,
	Raw,
	Augmented,
	Failed
};

enum class TrackerGNSSAugmentation {
	None,
	SBAS,
	WAAS,
	RTK
};

enum class TrackerIMUAugmentation {
	None
};

class TrackerHeader
{
	public:
		uint8_t format;
		uint8_t vehicle_id = 0xFF;
		uint8_t tracker_id = 0xFF;
		TrackerFlightMode mode = TrackerFlightMode::Invalid;
		TrackerLocalizationStatus status = TrackerLocalizationStatus::NoFix;
};

constexpr bool operator == (const TrackerHeader& _a, const TrackerHeader& _b) {
	if (_a.format != _b.format) return false;
	if (_a.vehicle_id != _b.vehicle_id) return false;
	if (_a.tracker_id != _b.tracker_id) return false;
	if (_a.mode != _b.mode) return false;
	if (_a.status != _b.status) return false;
	return true;
}

constexpr bool operator != (const TrackerHeader& _a, const TrackerHeader& _b) {
	return !operator == (_a, _b);
}

template<class Value>
class TrackerState
{
	public:
		using value_t = Value;
		using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
		using meters_per_second2_t = chandra::units::mks::Q_m_per_s2<value_t>;
		using time_t = chandra::units::mks::Q_s<value_t>;
		using pos_t = chandra::aero::ECEF<value_t>;
		using vel_t = chandra::math::Vector3D<meters_per_second_t>;

		TrackerHeader header;
		pos_t pos;
		vel_t vel;
};

template<class V1, class V2>
constexpr bool operator == (const TrackerState<V1>& _a, const TrackerState<V2>& _b) {
	if (_a.header != _b.header) return false;
	if (_a.pos != _b.pos) return false;
	if (_a.vel != _b.vel) return false;
	return true;
}

template<class V1, class V2>
constexpr bool operator != (const TrackerState<V1>& _a, const TrackerState<V2>& _b) {
	return !operator == (_a, _b);
}

template<class Value, class CovType = chandra::units::mks::m2>
using TrackerPositionCovariance = chandra::math::Matrix<chandra::units::Quantity<Value, CovType>, 3, 3>;

template<class Value, class CovType = chandra::units::mks::m_per_s> // TODO: FIX THIS UNITS TYPE
using TrackerVelocityCovariance = chandra::math::Matrix<chandra::units::Quantity<Value, CovType>, 3, 3>;

class TrackerGNSSDatetime
{
	public:
		uint16_t year; // Year -- 12-bit
		uint8_t month; // Month -- 4-bit
		uint8_t day; // Day -- 5-bit
		uint8_t hour; // Hour -- 5-bit
		uint8_t minute; // Minute -- 6-bit
		uint8_t second; // Second -- 6-bit
		uint8_t centiseconds; // Centiseconds -- 7-bit
};

class TrackerGNSSFix
{
	public:
		using duration_t = chandra::chrono::timestamp_clock::time_point::duration;

		uint8_t satellites = 0;
		duration_t t_since_last_fix;
		TrackerGNSSAugmentation gnss_augmentation = TrackerGNSSAugmentation::None;
		TrackerIMUAugmentation imu_augmentation = TrackerIMUAugmentation::None;
		TrackerGNSSDatetime date_time;
};

namespace internal
{
struct TrackingHeaderEncoding
{
	static constexpr uint8_t format_bits = 3;
	static constexpr uint8_t reserved_bits = 3;
	static constexpr uint8_t vehicle_id_bits = 3;
	static constexpr uint8_t tracker_id_bits = 3;
	static constexpr uint8_t mode_bits = 3;
	static constexpr uint8_t localization_status_bits = 2;
	static constexpr uint8_t header_parity_bits = 1;
};

template<class Value>
struct TrackingStateRange
{
	static constexpr Value distance_max{6428140}; // m
	static constexpr Value distance_variance{250}; // m^2
	static constexpr Value velocity_max{1029}; // m/s
	static constexpr Value velocity_variance{100}; // m^2/s^2
};

struct TrackingStateEncoding
{
	static constexpr uint8_t distance_bits = 29;
	static constexpr uint8_t velocity_bits = 20;
	static constexpr uint8_t variance_bits = 25;
	static constexpr uint8_t covariance_bits = 24;
};

struct TrackingGNSSDatetimeEncoding
{
	static constexpr uint8_t year_bits = 12;
	static constexpr uint8_t month_bits = 4;
	static constexpr uint8_t day_bits = 5;
	static constexpr uint8_t hour_bits = 5;
	static constexpr uint8_t minute_bits = 6;
	static constexpr uint8_t second_bits = 6;
	static constexpr uint8_t centiseconds_bits = 7;
};

struct TrackingGNSSFix
{
	static constexpr uint8_t year_bits = 12;
	static constexpr uint8_t month_bits = 4;
	static constexpr uint8_t day_bits = 5;
	static constexpr uint8_t hour_bits = 5;
	static constexpr uint8_t minute_bits = 6;
	static constexpr uint8_t second_bits = 6;
	static constexpr uint8_t centiseconds_bits = 7;
};

enum class EncodingErrors {
	None,
	Underflow,
	Overflow
};

template<size_t Bits, class V1, class V2>
constexpr auto encode_resolution(const V1& _min, const V2& _max) {
	using calc_t = typename std::common_type<V1, V2>::type;
	static constexpr const calc_t value_max{ static_cast<calc_t>((1ul << Bits) - 2ul) };
	const calc_t value_range{ static_cast<calc_t>(_max) - static_cast<calc_t>(_min) };
	return value_range / value_max;
}

template<class Dest, size_t Bits, class Src, class V1, class V2>
constexpr Dest encode_range(const Src& _val, const V1& _min, const V2& _max, EncodingErrors& _error) {
	using calc_t = typename std::common_type<Src, Dest>::type;
	using range_t = chandra::serialize::internal::BitmaskRange<Dest, Bits>;
	static constexpr const calc_t value_max{ static_cast<calc_t>((1ul << Bits) - 2ul) };
	const calc_t value_range{ static_cast<calc_t>(_max) - static_cast<calc_t>(_min) };
	const calc_t inv_m{ value_max / value_range };
	const calc_t b{ (static_cast<calc_t>(_max) + static_cast<calc_t>(_min)) / 2 };
	calc_t val{ static_cast<calc_t>(_val) };

	_error = EncodingErrors::None;
	if(val > _max) {
		val = static_cast<calc_t>(_max);
		_error = EncodingErrors::Overflow;
	}

	if(val < _min) {
		val = static_cast<calc_t>(_min);
		_error = EncodingErrors::Overflow;
	}

	if((val != 0) && (abs(val) <= encode_resolution<Bits>(_min, _max)) ) {
		_error = EncodingErrors::Underflow;
	}

	const Dest y = static_cast<Dest>(inv_m * (val - b) + static_cast<calc_t>(0.5));
	if (y < range_t::min) return range_t::min;
	else if (y > range_t::max) return range_t::max;
	return y;
}

template<class Dest, size_t Bits, class Src, class V1, class V2>
constexpr Dest encode_range(const Src& _val, const V1& _min, const V2& _max) {
	EncodingErrors errors = EncodingErrors::None;
	return encode_range<Dest, Bits>(_val, _min, _max, errors);
}

template<class Dest, size_t Bits>
constexpr Dest encode_value_error() {
	return static_cast<Dest>(1ul << (Bits - 1));
}

template<class Dest, size_t Bits, class Src, class V1, class V2>
constexpr Dest decode_range(const Src& _val, const V1& _min, const V2& _max) {
	using calc_t = typename std::common_type<Dest, Src>::type;
	static constexpr calc_t value_max{ static_cast<calc_t>((1ul << Bits) - 2ul) };
	const calc_t value_range{ static_cast<calc_t>(_max) - static_cast<calc_t>(_min) };
	const calc_t m{ value_range / value_max };
	const calc_t b{ (_max + _min) / 2 };
	return static_cast<Dest>((m * _val) + b);
}


template<size_t N>
bool serialize_tracker_header(const TrackerHeader& _header, chandra::serialize::BinarySerializer<N>& _serializer) {
	_serializer.write<TrackingHeaderEncoding::format_bits>(_header.format);
	_serializer.write<TrackingHeaderEncoding::reserved_bits>(0x00);
	_serializer.write<TrackingHeaderEncoding::vehicle_id_bits>(_header.vehicle_id);
	_serializer.write<TrackingHeaderEncoding::tracker_id_bits>(_header.tracker_id);
	_serializer.write<TrackingHeaderEncoding::mode_bits>(uint8_t(_header.mode));
	_serializer.write<TrackingHeaderEncoding::localization_status_bits>(uint8_t(_header.status));

	// Calculate header parity and insert bit...
	_serializer.write<TrackingHeaderEncoding::header_parity_bits>(0); // TODO: DECIDE WHAT TO DO ABOUT THE PARITY BIT...
	return true;
}

template<size_t N>
bool deserialize_tracker_header(chandra::serialize::BinaryDeserializer<N>& _deserializer, TrackerHeader& _header) {
	_deserializer.read<TrackingHeaderEncoding::format_bits>(_header.format);
	_deserializer.advance(TrackingHeaderEncoding::reserved_bits);
	_deserializer.read<TrackingHeaderEncoding::vehicle_id_bits>(_header.vehicle_id);
	_deserializer.read<TrackingHeaderEncoding::tracker_id_bits>(_header.tracker_id);
	uint8_t enum_intermediate;
	_deserializer.read<TrackingHeaderEncoding::mode_bits>(enum_intermediate);
	_header.mode = static_cast<chandra::aero::protocol::TrackerFlightMode>(enum_intermediate);
	_deserializer.read<TrackingHeaderEncoding::localization_status_bits>(enum_intermediate);
	_header.status = static_cast<chandra::aero::protocol::TrackerLocalizationStatus>(enum_intermediate);

	// TODO: NEED TO DECIDE WHAT TO DO ABOUT THE PARITY BIT...
	_deserializer.read<TrackingHeaderEncoding::header_parity_bits>(enum_intermediate);
	return true;
}
} /*namespace internal*/

template<class Value, size_t N>
bool serialize_tracking_state(const TrackerState<Value>& _state, uint8_t (&_buffer)[N]) {
	using range_t = internal::TrackingStateRange<Value>;
	using encoding_t = internal::TrackingStateEncoding;
	auto serializer = chandra::serialize::make_binary_serializer(_buffer);
	
	// Serialize the header
	internal::serialize_tracker_header(_state.header, serializer);

	serializer.advance(1); // This bit is currently undefined

	// Serialize the position
	for (int idx = 0; idx < 3; ++idx) {
		const int32_t enc_val = internal::encode_range<int32_t, encoding_t::distance_bits>(_state.pos(idx).value(), -range_t::distance_max, range_t::distance_max);
		std::cout << "Encode " << _state.pos(idx) << " -> 0x" << std::hex << enc_val << std::dec << "\n";
		serializer.write<encoding_t::distance_bits>(enc_val);
	}

	// Serialize the velocity
	for (int idx = 0; idx < 3; ++idx) {
		const int32_t enc_val = internal::encode_range<int32_t, encoding_t::velocity_bits>(_state.vel(idx).value(), -range_t::velocity_max, range_t::velocity_max);
		serializer.write<encoding_t::velocity_bits>(enc_val);
	}

	return true;
}

template<class Value, size_t N>
bool deserialize_tracking_state(const uint8_t (&_buffer)[N], TrackerState<Value>& _state) {
	using range_t = internal::TrackingStateRange<Value>;
	using encoding_t = internal::TrackingStateEncoding;
	auto deserializer = chandra::serialize::make_binary_deserializer(_buffer);

	// Deserialize the header
	const bool header_success = internal::deserialize_tracker_header(deserializer, _state.header);
	if (!header_success) return false;

	deserializer.advance(1); // This bit is currently undefined

	// Deserialize the position
	Value decode_result = 0;
	int32_t encoded_value = 0;

	for (int idx = 0; idx < 3; ++idx) {
		using pos_t = decltype(_state.pos(0));
		deserializer.read<encoding_t::distance_bits>(encoded_value);
		decode_result = internal::decode_range<Value, encoding_t::distance_bits>(encoded_value, -range_t::distance_max, range_t::distance_max);
		std::cout << "Decode 0x" << std::hex << encoded_value << " -> " << std::dec << decode_result << "\n";
		_state.pos(idx) = pos_t(decode_result);
	}

	// Deserialize the velocity
	for (int idx = 0; idx < 3; ++idx) {
		using vel_t = decltype(_state.vel(0));
		deserializer.read<encoding_t::velocity_bits>(encoded_value);
		decode_result = internal::decode_range<Value, encoding_t::velocity_bits>(encoded_value, -range_t::velocity_max, range_t::velocity_max);
		_state.vel(idx) = vel_t(decode_result);
	}

	return true;
}

template<size_t N>
bool serialize_gnss_fix(const TrackerGNSSFix& _fix, uint8_t (&_buffer)[N]) {
	using range_t = TrackerGNSSFix;
	return false;
}

template<size_t N>
bool deserialize_gnss_fix(const uint8_t (&_buffer)[N], TrackerGNSSFix& _fix) {
	using range_t = TrackerGNSSFix;
	return false;
}

template<class Value>
class BasestationTrackingState
{
	public:
		using value_t = Value;
		using meters_t = chandra::units::mks::Q_m<value_t>;
		using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
		using pos_t = chandra::aero::ECEF<value_t>;
		using vel_t = chandra::math::Vector3D<meters_per_second_t>;
		using offset_t = chandra::math::Vector3D<meters_t>;

		//
		// Access Functions
		//
		constexpr pos_t current_tracker_pos() const {
			return tracker_pos_history_[0];
		}

		constexpr pos_t projected_tracker_pos() const {
			return projected_tracker_pos_;
		}

		constexpr pos_t base_pos() const {
			return base_pos_;
		}

		constexpr pos_t home_pos() const {
			return home_pos_;
		}

		//
		// Update functions
		//
		// bool tracker_update(TrackerState _tracker) {}
		bool tracker_update(const pos_t& _tracker_pos, const vel_t& _tracker_vel) {
			tracker_valid_ = true;
			tracker_pos_history_.enqueue(_tracker_pos);
			tracker_vel_history_.enqueue(_tracker_vel);
			// TODO: UPDATE ESTIMATED FINAL LANDING POSITION (USING POSITION/VELOCITY HISTORY)
			projected_tracker_pos_ = _tracker_pos; // HACK: NOT ESTIMATING POSITION!
			tracker_base_offset_ = offset_between(projected_tracker_pos_, base_pos());
			tracker_home_offset_ = offset_between(projected_tracker_pos_, home_pos());
			return false;
		}

		bool base_update(const pos_t& _base_pos) {
			base_pos_ = _base_pos;
			base_valid_ = true; // TODO: MAKE THIS USE A TIMEOUT...
			if(base_valid_ and !home_valid_) {
				home_pos_ = _base_pos;
				home_valid_ = true;
			}
			tracker_base_offset_ = offset_between(projected_tracker_pos(), _base_pos);
			base_home_offset_ = offset_between(_base_pos, home_pos());
			return false;
		}

		bool home_update(const pos_t& _home_pos) {
			home_pos_ = _home_pos;
			home_valid_ = true;
			tracker_home_offset_ = offset_between(projected_tracker_pos(), _home_pos);
			base_home_offset_ = offset_between(base_pos(), _home_pos);
			return false;
		}

	protected:
		constexpr offset_t offset_between(const pos_t& _a, const pos_t& _b) {
			offset_t o;
			o.x = (_a.x - _b.x);
			o.y = (_a.y - _b.y);
			o.z = (_a.z - _b.z);
			return o;
		}

	private:
		bool tracker_valid_ = false;
		bool base_valid_ = false;
		bool home_valid_ = false;
		chandra::NonblockingFixedCircularBuffer<pos_t, 8> tracker_pos_history_;
		pos_t projected_tracker_pos_;
		pos_t base_pos_;
		pos_t home_pos_;

		chandra::NonblockingFixedCircularBuffer<vel_t, 8> tracker_vel_history_;

		offset_t tracker_base_offset_;
		offset_t tracker_home_offset_;
		offset_t base_home_offset_;
};

template<class Value, size_t N=2>
class TrackerStateEstimator
{
	public:
		using value_t = Value;
//		using meters_t = chandra::units::mks::Q_m<value_t>;
		using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
		using meters_per_second2_t = chandra::units::mks::Q_m_per_s2<value_t>;
		using time_t = chandra::units::mks::Q_s<value_t>;
		using pos_t = chandra::aero::ECEF<value_t>;
		using vel_t = chandra::math::Vector3D<meters_per_second_t>;
		using accel_t = chandra::math::Vector3D<meters_per_second2_t>;
		using state_t = TrackerState<value_t>;

		//
		// Accessors
		//
		constexpr state_t state() const {
			return {};
		}

		constexpr pos_t pos() const {
			return pos_history_[0];
		}

		constexpr vel_t vel() const {
			return vel_;
		}

		bool update_pos(time_t _dt, pos_t _pos) {
			// TODO: RUN A MEASUREMENT STEP IN THE KALMAN FILTER
			return true;
		}

		bool update_accel(time_t _dt, accel_t _accel) {
			// TODO: RUN A PREDICTION STEP IN THE KALMAN FILTER
			return true;
		}

	protected:

	private:
		chandra::NonblockingFixedCircularBuffer<pos_t, N> pos_history_;
		pos_t pos_;
		chandra::math::Vector3D<meters_per_second_t> vel_;
};

} /*namespace protocol*/
} /*namespace aero*/
} /*namespace chandra*/

#endif /* CHANDRA_TRACKER_PROTOCOL_H */
