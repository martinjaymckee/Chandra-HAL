#ifndef CHANDRA_TRACKER_PROTOCOL_H
#define CHANDRA_TRACKER_PROTOCOL_H

// #include <iostream>

#include "binary_serialize.h"
#include "chrono.h"
#include "circular_buffer.h"
#include "coordinates.h"
#include "units.h"
//using namespace chandra::units::mks::literals;

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
	protected:
		static constexpr uint16_t year_mod = 4096;
		static constexpr uint8_t month_mod = 12;
		static constexpr uint8_t day_mod = 32;
		static constexpr uint8_t hour_mod = 24;
		static constexpr uint8_t minute_mod = 60;
		static constexpr uint8_t second_mod = 60;
		static constexpr uint16_t millisecond_mod = 1000;

	public:
		uint16_t y = 0; // Year -- 12-bit
		uint8_t m = 0; // Month -- 4-bit
		uint8_t d = 0; // Day -- 5-bit
		uint8_t hh = 0; // Hour -- 5-bit
		uint8_t mm = 0; // Minute -- 6-bit
		uint8_t ss = 0; // Second -- 6-bit
		uint16_t ms = 0; // Milliseconds -- 10-bit

		constexpr bool valid() const {
			return (m < month_mod) && (d < day_mod) &&
				(hh < hour_mod) && (mm < minute_mod) && (ss < second_mod) && (ms < millisecond_mod);
		}

		constexpr bool operator == (const TrackerGNSSDatetime& _other) const {
			return ((y % year_mod) == (_other.y % year_mod)) &&
			 	((m % month_mod) == (_other.m % month_mod)) &&
				((d % day_mod) == (_other.d % day_mod)) &&
				((hh % hour_mod) == (_other.hh % hour_mod)) &&
				((mm % minute_mod) == (_other.mm % minute_mod)) &&
				((ss % second_mod) == (_other.ss % second_mod)) &&
				((ms % millisecond_mod) == (_other.ms % millisecond_mod));
		}
};

template<class Stream>
Stream& operator << (Stream& _stream, const TrackerGNSSDatetime& _date_time) {
	_stream << uint32_t(_date_time.y) << "-" << uint32_t(_date_time.m) << "-" << uint32_t(_date_time.d) << " ";
	_stream << uint32_t(_date_time.hh) << ":" << uint32_t(_date_time.mm) << ":" << uint32_t(_date_time.ss) << "." << uint32_t(_date_time.ms);

	return _stream;
}

class TrackerGNSSFix
{
	public:
		using duration_t = std::chrono::duration<uint32_t, std::milli>;

		TrackerHeader header;

		uint8_t satellites = 0;
		duration_t t_since_last_fix;
		TrackerGNSSAugmentation gnss_augmentation = TrackerGNSSAugmentation::None;
		TrackerIMUAugmentation imu_augmentation = TrackerIMUAugmentation::None;
		TrackerGNSSDatetime date_time;

		constexpr bool operator == (const TrackerGNSSFix& _other) const {
			return (satellites == _other.satellites) && (t_since_last_fix == _other.t_since_last_fix) &&
				(gnss_augmentation == _other.gnss_augmentation) && (imu_augmentation == _other.imu_augmentation) &&
				(date_time == _other.date_time);
		}
};

namespace internal
{
struct TrackerHeaderEncoding
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
struct TrackerStateRange
{
	// TODO: CALCULATE THE DISTANCE AND VELOCITY MAXIMUM AND VARIANCE VALUES
	static constexpr Value distance_max{6428140}; // m
	static constexpr Value distance_variance{250}; // m^2
	static constexpr Value velocity_max{1029}; // m/s
	static constexpr Value velocity_variance{100}; // m^2/s^2
};

struct TrackerStateEncoding
{
	static constexpr uint8_t distance_bits = 29;
	static constexpr uint8_t velocity_bits = 20;
	static constexpr uint8_t variance_bits = 25;
	static constexpr uint8_t covariance_bits = 24;
};

struct TrackerGNSSDatetimeEncoding
{
	static constexpr uint8_t year_bits = 12;
	static constexpr uint8_t month_bits = 4;
	static constexpr uint8_t day_bits = 5;
	static constexpr uint8_t hour_bits = 5;
	static constexpr uint8_t minute_bits = 6;
	static constexpr uint8_t second_bits = 6;
	static constexpr uint8_t millisecond_bits = 10;
};

struct TrackerGNSSFixEncoding
{
	static constexpr uint8_t satellites_bits = 7;
	static constexpr uint8_t t_since_last_fix_bits = 32;
	static constexpr uint8_t gnss_augmentation_bits = 2;
	static constexpr uint8_t imu_augmentation_bits = 2;
};

enum class EncodingErrors {
	None,
	Underflow,
	Overflow
};

template<size_t Bits, class V1, class V2>
constexpr auto encode_resolution(const V1& _min, const V2& _max) {
	using calc_t = typename std::common_type<V1, V2>::type;
	constexpr calc_t value_max{ static_cast<calc_t>((1ul << Bits) - 2ul) };
	const calc_t value_range{ static_cast<calc_t>(_max) - static_cast<calc_t>(_min) };
	return value_range / value_max;
}

template<class Dest, size_t Bits, class Src, class V1, class V2>
constexpr Dest encode_range(const Src& _val, const V1& _min, const V2& _max, EncodingErrors& _error) {
	using calc_t = typename std::common_type<Src, Dest>::type;
	using range_t = chandra::serialize::internal::BitmaskRange<Dest, Bits>;
	constexpr calc_t value_max{ static_cast<calc_t>((1ul << Bits) - 2ul) };
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
	constexpr calc_t value_max{ static_cast<calc_t>((1ul << Bits) - 2ul) };
	const calc_t value_range{ static_cast<calc_t>(_max) - static_cast<calc_t>(_min) };
	const calc_t m{ value_range / value_max };
	const calc_t b{ (_max + _min) / 2 };
	return static_cast<Dest>((m * _val) + b);
}

template<size_t N>
constexpr bool serialize_tracker_header(const TrackerHeader& _header, chandra::serialize::BinarySerializer<N>& _serializer) {
	using encoding_t = TrackerHeaderEncoding;
	_serializer.template write<encoding_t::format_bits>(_header.format);
	_serializer.template write<encoding_t::reserved_bits>(0x00);
	_serializer.template write<encoding_t::vehicle_id_bits>(_header.vehicle_id);
	_serializer.template write<encoding_t::tracker_id_bits>(_header.tracker_id);
	_serializer.template write<encoding_t::mode_bits>(uint8_t(_header.mode));
	_serializer.template write<encoding_t::localization_status_bits>(uint8_t(_header.status));

	// Calculate header parity and insert bit...
	_serializer.template write<encoding_t::header_parity_bits>(0); // TODO: DECIDE WHAT TO DO ABOUT THE PARITY BIT...
	return true;
}

template<size_t N>
constexpr bool deserialize_tracker_header(chandra::serialize::BinaryDeserializer<N>& _deserializer, TrackerHeader& _header) {
	using encoding_t = TrackerHeaderEncoding;
	_deserializer.template read<encoding_t::format_bits>(_header.format);
	_deserializer.advance(encoding_t::reserved_bits);
	_deserializer.template read<encoding_t::vehicle_id_bits>(_header.vehicle_id);
	_deserializer.template read<encoding_t::tracker_id_bits>(_header.tracker_id);
	uint8_t enum_intermediate;
	_deserializer.template read<encoding_t::mode_bits>(enum_intermediate);
	_header.mode = static_cast<chandra::aero::protocol::TrackerFlightMode>(enum_intermediate);
	_deserializer.template read<encoding_t::localization_status_bits>(enum_intermediate);
	_header.status = static_cast<chandra::aero::protocol::TrackerLocalizationStatus>(enum_intermediate);

	// TODO: NEED TO DECIDE WHAT TO DO ABOUT THE PARITY BIT...
	_deserializer.template read<encoding_t::header_parity_bits>(enum_intermediate);
	return true;
}

template<size_t N>
constexpr bool serialize_gnss_datetime(const TrackerGNSSDatetime& _datetime, chandra::serialize::BinarySerializer<N>& _serializer) {
	using encoding_t = TrackerGNSSDatetimeEncoding;

	// Serialize Date
	_serializer.template write<encoding_t::year_bits>(_datetime.y);
	_serializer.template write<encoding_t::month_bits>(_datetime.m);
	_serializer.template write<encoding_t::day_bits>(_datetime.d);

	// Serialize Time
	_serializer.template write<encoding_t::hour_bits>(_datetime.hh);
	_serializer.template write<encoding_t::minute_bits>(_datetime.mm);
	_serializer.template write<encoding_t::second_bits>(_datetime.ss);
	_serializer.template write<encoding_t::millisecond_bits>(_datetime.ms);

	return true;
}

template<size_t N>
constexpr bool deserialize_gnss_datetime(chandra::serialize::BinaryDeserializer<N>& _deserializer, TrackerGNSSDatetime& _datetime) {
	using encoding_t = TrackerGNSSDatetimeEncoding;

	// Deserialize Date
	_deserializer.template read<encoding_t::year_bits>(_datetime.y);
	_deserializer.template read<encoding_t::month_bits>(_datetime.m);
	_deserializer.template read<encoding_t::day_bits>(_datetime.d);

	// Deserialize Time
	_deserializer.template read<encoding_t::hour_bits>(_datetime.hh);
	_deserializer.template read<encoding_t::minute_bits>(_datetime.mm);
	_deserializer.template read<encoding_t::second_bits>(_datetime.ss);
	_deserializer.template read<encoding_t::millisecond_bits>(_datetime.ms);

	return true;
}
} /*namespace internal*/

template<class Value, size_t N>
constexpr bool serialize_tracking_state(const TrackerState<Value>& _state, uint8_t (&_buffer)[N]) {
	using range_t = internal::TrackerStateRange<Value>;
	using encoding_t = internal::TrackerStateEncoding;
	auto serializer = chandra::serialize::make_binary_serializer(_buffer);

	// Serialize the header
	internal::serialize_tracker_header(_state.header, serializer);

	serializer.advance(1); // This bit is currently undefined

	// Serialize the position
	for (int idx = 0; idx < 3; ++idx) {
		const int32_t enc_val = internal::encode_range<int32_t, encoding_t::distance_bits>(_state.pos(idx).value(), -range_t::distance_max, range_t::distance_max);
		serializer.template write<encoding_t::distance_bits>(enc_val);
	}

	// Serialize the velocity
	for (int idx = 0; idx < 3; ++idx) {
		const int32_t enc_val = internal::encode_range<int32_t, encoding_t::velocity_bits>(_state.vel(idx).value(), -range_t::velocity_max, range_t::velocity_max);
		serializer.template write<encoding_t::velocity_bits>(enc_val);
	}

	return true;
}

template<class Value, size_t N>
constexpr bool deserialize_tracking_state(const uint8_t (&_buffer)[N], TrackerState<Value>& _state) {
	using range_t = internal::TrackerStateRange<Value>;
	using encoding_t = internal::TrackerStateEncoding;
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
		deserializer.template read<encoding_t::distance_bits>(encoded_value);
		decode_result = internal::decode_range<Value, encoding_t::distance_bits>(encoded_value, -range_t::distance_max, range_t::distance_max);
		_state.pos(idx) = pos_t(decode_result);
	}

	// Deserialize the velocity
	for (int idx = 0; idx < 3; ++idx) {
		using vel_t = decltype(_state.vel(0));
		deserializer.template read<encoding_t::velocity_bits>(encoded_value);
		decode_result = internal::decode_range<Value, encoding_t::velocity_bits>(encoded_value, -range_t::velocity_max, range_t::velocity_max);
		_state.vel(idx) = vel_t(decode_result);
	}

	return true;
}


template<size_t N>
constexpr bool serialize_gnss_fix(const TrackerGNSSFix& _fix, uint8_t (&_buffer)[N]) {
	using encoding_t = internal::TrackerGNSSFixEncoding;
	auto serializer = chandra::serialize::make_binary_serializer(_buffer);

	// Serialize the header
	internal::serialize_tracker_header(_fix.header, serializer);

	// Serialize data
	serializer.template write<encoding_t::satellites_bits>(_fix.satellites);
	serializer.template write<encoding_t::t_since_last_fix_bits>(_fix.t_since_last_fix.count());
	serializer.template write<encoding_t::gnss_augmentation_bits>(uint8_t(_fix.gnss_augmentation));
	serializer.template write<encoding_t::imu_augmentation_bits>(uint8_t(_fix.imu_augmentation));

	// Serialize the date/time
	internal::serialize_gnss_datetime(_fix.date_time, serializer);

	return true;
}

template<size_t N>
constexpr bool deserialize_gnss_fix(const uint8_t (&_buffer)[N], TrackerGNSSFix& _fix) {
	using encoding_t = internal::TrackerGNSSFixEncoding;
	auto deserializer = chandra::serialize::make_binary_deserializer(_buffer);

	// Deserialize the header
	const bool header_success = internal::deserialize_tracker_header(deserializer, _fix.header);
	if (!header_success) return false;

	// Deserialize data
	deserializer.template read<encoding_t::satellites_bits>(_fix.satellites);
	uint32_t t_since_last_fix_ms;
	deserializer.template read<encoding_t::t_since_last_fix_bits>(t_since_last_fix_ms);
	_fix.t_since_last_fix = decltype(_fix.t_since_last_fix)(t_since_last_fix_ms);

	uint8_t enum_intermediate;
	deserializer.template read<encoding_t::gnss_augmentation_bits>(enum_intermediate);
	_fix.gnss_augmentation = static_cast<chandra::aero::protocol::TrackerGNSSAugmentation>(enum_intermediate);
	deserializer.template read<encoding_t::imu_augmentation_bits>(enum_intermediate);
	_fix.imu_augmentation = static_cast<chandra::aero::protocol::TrackerIMUAugmentation>(enum_intermediate);

	// Deserialize the header
	const bool date_time_success = internal::deserialize_gnss_datetime(deserializer, _fix.date_time);
	if (!date_time_success) return false;

	return true;
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
		constexpr bool tracker_update(const pos_t& _tracker_pos, const vel_t& _tracker_vel) {
			tracker_valid_ = true;
			tracker_pos_history_.enqueue(_tracker_pos);
			tracker_vel_history_.enqueue(_tracker_vel);
			// TODO: UPDATE ESTIMATED FINAL LANDING POSITION (USING POSITION/VELOCITY HISTORY)
			projected_tracker_pos_ = _tracker_pos; // HACK: NOT ESTIMATING POSITION!
			tracker_base_offset_ = offset_between(projected_tracker_pos_, base_pos());
			tracker_home_offset_ = offset_between(projected_tracker_pos_, home_pos());
			return false;
		}

		constexpr bool base_update(const pos_t& _base_pos) {
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

		constexpr bool home_update(const pos_t& _home_pos) {
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

		constexpr bool update_pos(time_t _dt, pos_t _pos) {
			// TODO: RUN A MEASUREMENT STEP IN THE KALMAN FILTER
			return true;
		}

		constexpr bool update_accel(time_t _dt, accel_t _accel) {
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
