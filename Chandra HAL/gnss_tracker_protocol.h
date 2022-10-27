#ifndef CHANDRA_TRACKER_PROTOCOL_H
#define CHANDRA_TRACKER_PROTOCOL_H

#include "binary_serialize.h"
#include "chrono.h"
#include "circular_buffer.h"
#include "coordinates.h"
#include "geometry.h"
#include "kalman.h"
#include "matrix_vectors.h"
#include "matrix_vector_ops.h"
#include "units.h"
//using namespace chandra::units::mks::literals;

namespace chandra
{
namespace aero
{
namespace protocol
{

enum class TrackerFrameFormats {
		Localization = 0x00,
		PositionCovariance = 0x01,
		VelocityCovariance = 0x02,
		EventError = 0x03,
		GNSSFix = 0x04,
		SystemStatus = 0x05,
		Command = 0x07,
		Invalid = 0xFF
};

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
		static constexpr TrackerHeader Format(TrackerFrameFormats _format) {
			return TrackerHeader(_format);
		}

		explicit constexpr TrackerHeader(const TrackerFrameFormats& _format = TrackerFrameFormats::Invalid) : format(_format) {}

		constexpr TrackerHeader(const TrackerHeader& _other)
			:	format{_other.format}, vehicle_id{_other.vehicle_id}, tracker_id{_other.tracker_id},
			mode{ _other.mode }, status{ _other.status } {}

		TrackerFrameFormats format;
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

		TrackerHeader header = TrackerHeader::Format(TrackerFrameFormats::Localization);
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

		TrackerHeader header = TrackerHeader::Format(TrackerFrameFormats::GNSSFix);

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
	static constexpr auto distance_max() { return Value(6428140); } // m
	static constexpr auto distance_variance() { return Value(250); } // m^2
	static constexpr auto velocity_max() { return Value(1029); } // m/s
	static constexpr auto velocity_variance() { return Value(100); } // m^2/s^2
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
	_serializer.template write<encoding_t::format_bits>(uint8_t(_header.format));
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
constexpr bool deserialize_tracker_header(chandra::serialize::BinaryDeserializer<N>& _deserializer, TrackerHeader& _header, const TrackerFrameFormats& _tgt_format) {
	using encoding_t = TrackerHeaderEncoding;
	uint8_t enum_intermediate;
	_deserializer.template read<encoding_t::format_bits>(enum_intermediate);
	const auto parsed_format( static_cast<TrackerFrameFormats>(enum_intermediate ));
	if (parsed_format != _tgt_format) return false;
	_header.format = parsed_format;
	_deserializer.advance(encoding_t::reserved_bits);
	_deserializer.template read<encoding_t::vehicle_id_bits>(_header.vehicle_id);
	_deserializer.template read<encoding_t::tracker_id_bits>(_header.tracker_id);
	_deserializer.template read<encoding_t::mode_bits>(enum_intermediate);
	_header.mode = static_cast<chandra::aero::protocol::TrackerFlightMode>(enum_intermediate);
	_deserializer.template read<encoding_t::localization_status_bits>(enum_intermediate);
	_header.status = static_cast<chandra::aero::protocol::TrackerLocalizationStatus>(enum_intermediate);

	// TODO: NEED TO DECIDE WHAT TO DO ABOUT THE PARITY BIT...
	//	IF IT IS GOING TO BE USED, THE PARSED HEADER NEEDS TO BE BUFFERED UNTIL THIS POINT
	//	SO THAT THERE WILL BE NO CHANGES TO THE PASSED IN HEADER OBJECT UNLESS THE DESERIALIZATION
	//	SUCCEEDED.
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
		const int32_t enc_val = internal::encode_range<int32_t, encoding_t::distance_bits>(_state.pos(idx).value(), -range_t::distance_max(), range_t::distance_max());
		serializer.template write<encoding_t::distance_bits>(enc_val);
	}

	// Serialize the velocity
	for (int idx = 0; idx < 3; ++idx) {
		const int32_t enc_val = internal::encode_range<int32_t, encoding_t::velocity_bits>(_state.vel(idx).value(), -range_t::velocity_max(), range_t::velocity_max());
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
	const bool header_success = internal::deserialize_tracker_header(deserializer, _state.header, TrackerFrameFormats::Localization);
	if (!header_success) return false;

	deserializer.advance(1); // This bit is currently undefined

	// Deserialize the position
	Value decode_result = 0;
	int32_t encoded_value = 0;

	for (int idx = 0; idx < 3; ++idx) {
		using pos_t = decltype(_state.pos(0));
		deserializer.template read<encoding_t::distance_bits>(encoded_value);
		decode_result = internal::decode_range<Value, encoding_t::distance_bits>(encoded_value, -range_t::distance_max(), range_t::distance_max());
		_state.pos(idx) = pos_t(decode_result);
	}

	// Deserialize the velocity
	for (int idx = 0; idx < 3; ++idx) {
		using vel_t = decltype(_state.vel(0));
		deserializer.template read<encoding_t::velocity_bits>(encoded_value);
		decode_result = internal::decode_range<Value, encoding_t::velocity_bits>(encoded_value, -range_t::velocity_max(), range_t::velocity_max());
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
	const bool header_success = internal::deserialize_tracker_header(deserializer, _fix.header, TrackerFrameFormats::GNSSFix);
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

template<class T>
struct TD;

template<class Value>
class BasestationTrackingState
{
	public:
		using value_t = Value;
		using meters_t = chandra::units::mks::Q_m<value_t>;
		using seconds_t = chandra::units::mks::Q_s<value_t>;
		using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
		using pos_t = chandra::aero::ECEF<value_t>;
		using vel_t = chandra::math::Vector3D<meters_per_second_t>;
		using offset_t = chandra::math::Vector3D<meters_t>;


		constexpr bool init() {
			projected_tracker_pos_ = pos_t{ 0_m_, 0_m_, 0_m_ };
			base_pos_ = pos_t{ 0_m_, 0_m_, 0_m_ };
			home_pos_ = pos_t{ 0_m_, 0_m_, 0_m_ };

//			offset_t tracker_base_offset_;
//			offset_t tracker_home_offset_;
//			offset_t base_home_offset_;
			return true;
		}

		//
		// Access Functions
		//
		constexpr bool current_tracker_valid() const {
			return tracker_valid_;
		}

		constexpr pos_t current_tracker_pos() const {
			return tracker_pos_history_[0];
		}

		constexpr bool projected_tracker_valid() const {
			return tracker_valid_ && base_valid_; // TODO: CHECK IF THIS ACTUALLY WORKS....
		}

		constexpr pos_t projected_tracker_pos() const {
			return projected_tracker_pos_;
		}

		constexpr bool base_valid() const {
			return base_valid_;
		}

		constexpr pos_t base_pos() const {
			return base_pos_;
		}

		constexpr bool home_valid() const {
			return home_valid_;
		}

		constexpr pos_t home_pos() const {
			return home_pos_;
		}

		constexpr bool updated() {
			if (updated_) {
				updated_ = false;
				return true;
			}

			return false;
		}

		//
		// Update functions
		//
		constexpr bool tracker_update(const pos_t& _tracker_pos, const vel_t& _tracker_vel) {
			tracker_pos_history_.enqueue(_tracker_pos);
			tracker_vel_history_.enqueue(_tracker_vel);
			// TODO: UPDATE ESTIMATED FINAL LANDING POSITION (USING POSITION/VELOCITY HISTORY)
			if(tracker_valid_) {
				const auto v_mag = chandra::math::magnitude(_tracker_vel);
				if (v_mag > 0.5_m_per_s_) {
					const seconds_t dt(1); // TODO: THIS NEEDS TO BE CALCULATED USING THE TIME FROM LAST UPDATE AND THE CURRENT TIME
					const auto dpos = dt * _tracker_vel;
					const auto descent_line = chandra::geometry::Line3D<meters_t>::FromPointVector(_tracker_pos, dpos);
					const auto llh_ref = chandra::aero::ECEFToLLH(base_pos_); // TODO: THIS SHOULD PROBABLY BE THE LAT/LON FROM THE PROJECTED TRACKER POSITION AND THE ALTITUDE OF THE BASE POSITION
//					const auto llh_ref = chandra::aero::ECEFToLLH(projected_tracker_pos_); // TODO: THIS SHOULD PROBABLY BE THE LAT/LON FROM THE PROJECTED TRACKER POSITION AND THE ALTITUDE OF THE BASE POSITION
					const auto ground_plane = calc_ground_plane(llh_ref);
					const auto result = chandra::geometry::intersect(descent_line, ground_plane);
					if (bool(result)) {
						projected_tracker_pos_ = pos_t(result.intersection());

						// TODO: CALCULATE THE LANDING TIME FROM THE DISTANCE TO INTERSECTION AND THE VELOCITY MAGNITUDE
						const auto t_projected = chandra::geometry::distance(_tracker_pos, projected_tracker_pos_) / chandra::math::magnitude(_tracker_vel);
						// TODO: NEED TO ADD THE PROJECTED LANDING TIME TO THE PACKET BEING SENT TO THE GUI PROCESSOR
					}
					else {
						// std::cout << "Splashdown Projection Error!\n";
						// std::cout << "\tbase = " << llh_ref << "\n";
						// std::cout << "\tpos = " << _tracker_pos << "\n\tvel = " << _tracker_vel << "\n";
						// std::cout << "\tline = " << descent_line << "\n\tplane = " << ground_plane << "\n";
						// std::cout << "\tpredicted pos = " << result.intersection() << "\n";
					}
				}
				else {
					projected_tracker_pos_ = _tracker_pos;
				}
			} else {
				projected_tracker_pos_ = _tracker_pos; // Initialize projection to current position
			}

			if (base_valid_) {
				tracker_base_offset_ = offset_between(projected_tracker_pos_, base_pos());
			}

			if (home_valid_) {
				tracker_home_offset_ = offset_between(projected_tracker_pos_, home_pos());
			}

			check_updated();
			tracker_valid_ = true;
			return false;
		}

		constexpr bool tracker_update(const pos_t& _tracker_pos) {
			return tracker_update(_tracker_pos, vel_t{ 0_m_per_s_, 0_m_per_s_, 0_m_per_s_ });
		}

		constexpr bool base_update(const pos_t& _base_pos) {
			base_pos_ = _base_pos;
			base_valid_ = true; // TODO: MAKE THIS USE A TIMEOUT...
			if(base_valid_ and !home_valid_) {
				home_pos_ = _base_pos;
				home_valid_ = true;
			}

			if (tracker_valid_) {
				tracker_base_offset_ = offset_between(projected_tracker_pos(), _base_pos);
			}

			if (home_valid_) {
				base_home_offset_ = offset_between(_base_pos, home_pos());
			}

			check_updated();
			return false;
		}

		constexpr bool home_update(const pos_t& _home_pos) {
			home_pos_ = _home_pos;
			home_valid_ = true;

			if (tracker_valid_) {
				tracker_home_offset_ = offset_between(projected_tracker_pos(), _home_pos);
			}

			if (base_valid_) {
				base_home_offset_ = offset_between(base_pos(), _home_pos);
			}

			check_updated();
			return false;
		}

	protected:
		template<class V, class AngleUnits, class LengthUnits>
		constexpr auto calc_ground_plane(const chandra::aero::LLH<V, AngleUnits, LengthUnits>& _llh) {
			using length_t = chandra::units::mks::Q_m<V>;
			using result_t = chandra::geometry::Plane3D<length_t>;
			using normal_t = chandra::aero::ENU<Value, LengthUnits>;

			const auto p0 = chandra::aero::LLHToECEF(_llh); // TODO: FIGURE OUT IF THERE'S A WAY TO OPTIMIZE THIS... IF SO, IT CAN BE ADDED TO THE LIBRARY
			const auto N = chandra::aero::RotateENUToECEF(normal_t{0_m_, 0_m_, 1_m_}, _llh);

			return result_t::FromOriginAndNormal(p0, N);
		}

		template<class V, class AngleUnits, class LengthUnits>
		constexpr auto calc_ground_plane_2(const chandra::aero::LLH<V, AngleUnits, LengthUnits>& _llh) {
			using meters_t = chandra::units::mks::Q_m<Value>;
			using radians_t = chandra::units::mks::Q_rad<Value>;
			using llh_t = chandra::aero::LLH<Value, AngleUnits, LengthUnits>;
			using length_t = typename llh_t::length_t;
			using result_t = chandra::geometry::Plane3D<length_t>;
//			using point_t = chandra::geometry::Point3D<length_t>;

			const auto distance = meters_t(100);
			const auto m_to_rad_lat = radians_t(2*3.1415926535) / meters_t(40.075e6);
			const auto m_to_rad_lon = m_to_rad_lat / cos(_llh.latitude);

			const auto dlat = distance * m_to_rad_lat;
			const auto dlon = distance * m_to_rad_lon;
			const auto p0 = chandra::aero::LLHToECEF(_llh);
			const llh_t llh_a{_llh.latitude, _llh.longitude + dlon, _llh.altitude};
			const llh_t llh_b{_llh.latitude + dlat, _llh.longitude, _llh.altitude};
			const auto p1 = chandra::aero::LLHToECEF(llh_a);
			const auto p2 = chandra::aero::LLHToECEF(llh_b);

			return result_t::FromPoints(p0, p1, p2);
		}

		constexpr void check_updated() {
			updated_ = base_valid_ && home_valid_ && tracker_valid_;
			return;
		}

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
		bool updated_ = false;
		chandra::NonblockingFixedCircularBuffer<pos_t, 8> tracker_pos_history_;
		pos_t projected_tracker_pos_;
		pos_t base_pos_;
		pos_t home_pos_;

		chandra::NonblockingFixedCircularBuffer<vel_t, 8> tracker_vel_history_;

		offset_t tracker_base_offset_;
		offset_t tracker_home_offset_;
		offset_t base_home_offset_;
};

template<class Value>
class TrackerGNSSSample
{
	public:
		using value_t = Value;

		using time_t = chandra::units::mks::Q_s<value_t>;
		using pos_t = chandra::aero::ECEF<value_t>;

		pos_t pos;
		uint8_t satellites = 0;
		time_t t_since_last;
		bool valid = false;
};


template<class Value>
class TrackerStateEstimator
{
	public:
		using value_t = Value;
		using meters_t = chandra::units::mks::Q_m<value_t>;
		using meters2_t = decltype(meters_t{} *meters_t{});
		using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
		using meters_per_second2_t = chandra::units::mks::Q_m_per_s2<value_t>;
		using time_t = chandra::units::mks::Q_s<value_t>;
		using pos_t = chandra::aero::ECEF<value_t>;
		using enu_t = chandra::aero::ENU<value_t>;
		using vel_t = chandra::math::Vector3D<meters_per_second_t>;
		using accel_t = chandra::math::Vector3D<meters_per_second2_t>;
		using gnss_t = TrackerGNSSSample<value_t>;
		using state_t = TrackerState<value_t>;
		using kf_t = chandra::control::KalmanFilter<value_t, 3, 1>;

		//
		// Constructor
		//
		TrackerStateEstimator(uint8_t _vehicle_id, uint8_t _tracker_id)
			: header_(TrackerFrameFormats::Localization), dt_ref_{0.2_s_}, en_sd_{1.5_m_}, u_sd_{3_m_}
		{
				header_.vehicle_id = _vehicle_id;
				header_.tracker_id = _tracker_id;
		}

		constexpr bool init() {
			pos_ = pos_t{ 0_m_, 0_m_, 0_m_ };
			vel_ = vel_t{ 0_m_per_s_, 0_m_per_s_, 0_m_per_s_ };

			return true;
		}

		//
		// Accessors
		//
		constexpr bool updated() const {
			return updated_;
		}

		constexpr bool valid() const {
			return initialized_;
		}

		constexpr state_t state() {
			updated_ = false;
			state_t result;
			result.pos = pos();
			result.vel = vel();
			return result;
		}

		constexpr pos_t pos() const {
			return pos_;
		}

		constexpr vel_t vel() const {
			return vel_;
		}

		constexpr bool update_gnss(const gnss_t& _gnss) { // TODO: THIS SHOULD EITHER ONLY HANDLE A SINGLE GPS, OR IT NEEDS TO DO SOMETHING TO MAKE SURE THE SAMPLES ARE CORRECTED....
			if(initialized_) {
				using measurement = typename kf_t::measurement_t;
				x_kf_.update(measurement{ chandra::units::scalar_cast(_gnss.pos.x) });
				y_kf_.update(measurement{ chandra::units::scalar_cast(_gnss.pos.y) });
				z_kf_.update(measurement{ chandra::units::scalar_cast(_gnss.pos.z) });

				pos_ = pos_t{meters_t{x_kf_.X_post(0)}, meters_t{y_kf_.X_post(0)}, meters_t{z_kf_.X_post(0)} };
				vel_ = vel_t{meters_per_second_t{x_kf_.X_post(1)}, meters_per_second_t{y_kf_.X_post(1)}, meters_per_second_t{z_kf_.X_post(1)} };
			} else {
				using x_t = typename kf_t::state_t;
				using p_t = typename kf_t::state_covariance_t;

				initialized_ = true;
				const auto sd_vec = chandra::aero::RotateENUToECEF(enu_t{en_sd_, en_sd_, u_sd_}, _gnss.pos);
				const auto P0 = p_t{u_sd_.value() * u_sd_.value(), 0, 0, 0, 0, 0, 0, 0, 0 };
				initialize_filter(x_kf_, (sd_vec.x * sd_vec.x), dt_ref_);
				const auto X0 = x_t{chandra::units::scalar_cast(meters_t{_gnss.pos.x}), 0, 0};
				x_kf_.init(X0, P0);
				initialize_filter(y_kf_, (sd_vec.y * sd_vec.y), dt_ref_);
				const auto Y0 = x_t{chandra::units::scalar_cast(meters_t{_gnss.pos.y}), 0, 0};
				y_kf_.init(Y0, P0);
				initialize_filter(z_kf_, (sd_vec.z * sd_vec.z), dt_ref_);
				const auto Z0 = x_t{chandra::units::scalar_cast(meters_t{_gnss.pos.z}), 0, 0};
				z_kf_.init(Z0, P0);
			}

			updated_ = true;
			return true;
		}

		constexpr bool update_accel(accel_t /*_accel*/) {
			if(initialized_) {
				// TODO: RUN A PREDICTION STEP IN THE KALMAN FILTER

				updated_ = true;
			}
			return true;
		}

	protected:
		void initialize_filter(kf_t& _kf, const meters2_t _pos_var, const time_t _dt) {
			using state_transition_t = typename kf_t::state_transition_t;
			using observation_model_t = typename kf_t::observation_model_t;
//			using state_covariance_t = typename kf_t::state_covariance_t;
			using measurement_covariance_t = typename kf_t::measurement_covariance_t;
			using namespace chandra::units;

			const auto dt = scalar_cast(_dt);
			const auto pos_var = std::abs(scalar_cast(_pos_var)); // NOTE: THIS SHOULD NEVER BE NEGATIVE... PERHAPS SOME ERROR CHECKING WOULD BE BETTER HERE

			_kf.F = state_transition_t{ 1, dt, (dt * dt) / 2, 0, 1, dt, 0, 0, 1};
			_kf.Q = 1 * pos_var * _kf.F * _kf.F.T(); // TODO: THIS IS NOT A GOOD PROCESS COVARIANCE ESTIMATE....
			_kf.H = observation_model_t{1, 0, 0};
			_kf.R = measurement_covariance_t{pos_var};

			return;
		}

	private:
		bool initialized_ = false;
		bool updated_ = false;
		TrackerHeader header_;
		time_t dt_ref_;
		meters_t en_sd_;
		meters_t u_sd_;
		kf_t x_kf_;
		kf_t y_kf_;
		kf_t z_kf_;
		pos_t pos_;
		vel_t vel_;
};

template<class Value>
class TrackerStateEstimator2
{
public:
	using value_t = Value;
	//		using meters_t = chandra::units::mks::Q_m<value_t>;
	using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
	using meters_per_second2_t = chandra::units::mks::Q_m_per_s2<value_t>;
	using time_t = chandra::units::mks::Q_s<value_t>;
	using pos_t = chandra::aero::ECEF<value_t>;
	using dir_t = chandra::math::Vector3D<value_t>; // TODO: DIR_T, VEL_T AND ACCEL_T SHOULD BE IN THE ECEF FRAME, BUT SOMETHING IS FAILING IF I DO THAT....
	using vel_t = chandra::math::Vector3D<meters_per_second_t>;
	using accel_t = chandra::math::Vector3D<meters_per_second2_t>;
	using gnss_t = TrackerGNSSSample<value_t>;
	using state_t = TrackerState<value_t>;

	//
	// Constructor
	//
	TrackerStateEstimator2(uint8_t _vehicle_id, uint8_t _tracker_id)
		: header_(TrackerFrameFormats::Localization)
	{
		header_.vehicle_id = _vehicle_id;
		header_.tracker_id = _tracker_id;
	}

	constexpr bool init() {
		pos_ = pos_t{ 0_m_, 0_m_, 0_m_ };
		vel_ = vel_t{ 0_m_per_s_, 0_m_per_s_, 0_m_per_s_ };
		initialized_ = false;
		return true;
	}

	//
	// Accessors
	//
	constexpr bool updated() const {
		return updated_;
	}

	constexpr bool valid() const {
		return initialized_;
	}

	constexpr state_t state() {
		updated_ = false;
		state_t result;
		result.pos = pos();
		result.vel = vel();
		return result;
	}

	constexpr pos_t pos() const {
		return pos_;
	}

	constexpr vel_t vel() const {
		return vel_;
	}

	constexpr bool update_gnss(const gnss_t& _gnss) { // TODO: THIS SHOULD EITHER ONLY HANDLE A SINGLE GPS, OR IT NEEDS TO DO SOMETHING TO MAKE SURE THE SAMPLES ARE CORRECTED....
		if (initialized_) {
			const auto offset = last_pos_ - _gnss.pos;
			const auto new_vel = offset / _gnss.t_since_last;
			vel_ = (e_vel_ * vel_) + vel_t((1 - e_vel_) * new_vel);
			pos_ = (e_pos_ * pos_) + pos_t((1 - e_pos_) * _gnss.pos);
		}
		else {
			initialized_ = true;
			pos_ = _gnss.pos;
		}
		last_pos_ = _gnss.pos;
		updated_ = true;
		return true;
	}

	constexpr bool update_accel(accel_t _accel) { // NOTE: THIS NEEDS TO TAKE THE UPDATE TIME SOMEHOW....
		if (dir_initialized_ && (chandra::math::magnitude(vel_) > 0.1_m_per_s_)) {
			const accel_t a_proj(dir_ * -_accel.z);
//			pos_ = pos_ + pos_t(pos_t(10_ms_ * vel_) + pos_t((10_ms_ * 10_ms_) * a_proj / 2)); // TODO: THE CASTING IS GETTING ANNOYING AND SEEMS TO BE A RESULT OF THE OPERATOR + OVERLOAD BEINING AMBIGUOUS....
//			vel_ = vel_ + vel_t(10_ms_ * a_proj / 2);
//			dir_ = chandra::math::direction(vel_);
			updated_ = true;
		}
		else {
			dir_ = chandra::math::direction(_accel);
			dir_initialized_ = true;
		}
		return true;
	}

protected:

private:
	value_t e_pos_ = 0.6;
	value_t e_vel_ = 0.85;
	bool initialized_ = false;
	bool dir_initialized_ = false;
	bool updated_ = false;
	TrackerHeader header_;
	dir_t dir_;
	pos_t pos_;
	pos_t last_pos_;
	vel_t vel_;
};

struct GNSSStatus // TODO: FIGURE OUT WHERE THIS SHOULD ACTUALLY GO AND BUILD A NEW FILE FOR IT....
{
	using timestamp_t = chandra::chrono::timestamp_clock::time_point;
	bool loc_valid = false;
	bool loc_updated = false;
	bool fix_valid = false;
	bool fix_updated = false;
	timestamp_t timestamp = chandra::chrono::timestamp_clock::now();
};

template<class Value, class TrackerEstimatorType, class Clock = chandra::chrono::timestamp_clock>
class TrackerFrameScheduler
{
	public:
		using value_t = Value;
		using tracker_estimator_t = TrackerEstimatorType;
		using pos_t = chandra::aero::ECEF<value_t>;
		using distance_t = typename pos_t::value_t;
		using clock_t = Clock;
		using timestamp_t = typename clock_t::time_point;
		using duration_t = typename timestamp_t::duration;

		TrackerFrameScheduler() {}

		bool init() {
			const auto t = clock_t::now();
			t_last_fix_ = t;
			t_last_frame_ = t;
			t_last_loc_ = t;
			pos_initialized_ = false;

			return true;
		}


		chandra::aero::protocol::TrackerFrameFormats operator () (GNSSStatus& _status, tracker_estimator_t& _state_estimator) {
			const auto t = clock_t::now();
			const auto estimator_updated = _state_estimator.valid() && _state_estimator.updated();

			if(chandra::chrono::after(t_frame_min_, t_last_frame_, t)) {
				if (!pos_initialized_ && _state_estimator.valid()) {
					last_pos_ = _state_estimator.pos();
					pos_initialized_ = true;
				}

				if(estimator_updated && (
						chandra::chrono::after(t_localize_max_, t_last_loc_, t) ||
						( distance(last_pos_, _state_estimator.pos()) >= d_update_ )
					)
				) {
					const auto state = _state_estimator.state();
					last_pos_ = state.pos;
					t_last_loc_ = t;
					t_last_frame_ = t;
					_status.loc_updated = false;
					return chandra::aero::protocol::TrackerFrameFormats::Localization;
				}

				if(_status.fix_updated && (
						chandra::chrono::after(t_fix_max_, t_last_fix_, t)
					)
				) {
					t_last_fix_ = t;
					t_last_frame_ = t;
					_status.fix_updated = false;
					return chandra::aero::protocol::TrackerFrameFormats::GNSSFix;
				}
			}

			return chandra::aero::protocol::TrackerFrameFormats::Invalid;
		}

	protected:
		constexpr auto distance(const pos_t& _pos_a, const pos_t& _pos_b) const{
			return chandra::math::magnitude(_pos_a - _pos_b);
		}

	private:
		distance_t d_update_{10_m_};
		duration_t t_frame_min_{250ms};
		duration_t t_localize_max_{5s};
		duration_t t_fix_min_{1s};
		duration_t t_fix_max_{5s};

		timestamp_t t_last_loc_;
		timestamp_t t_last_fix_;
		timestamp_t t_last_frame_;

		bool pos_initialized_ = false;
		pos_t last_pos_;
};

} /*namespace protocol*/
} /*namespace aero*/
} /*namespace chandra*/

#endif /* CHANDRA_TRACKER_PROTOCOL_H */
