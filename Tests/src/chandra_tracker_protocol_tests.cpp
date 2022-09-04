//
// Include C++ Library
// 
#include <iostream>

//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <gnss_tracker_protocol.h>
#include <units.h>
using namespace chandra::units::mks::literals;

//
// Value Encoding and Decoding
// 

template<size_t Bits, class Value>
constexpr bool encoded_value_in_range(const Value& _val) {
	static constexpr size_t value_bits = 8 * sizeof(Value);
	static constexpr size_t upper_bits = value_bits - Bits;
	static constexpr Value val_min = static_cast<Value>((((1ull << (upper_bits+1))-1ull) << (value_bits - upper_bits - 1ul)) + 1ull);
	static constexpr Value val_max = static_cast<Value>((1ul << (Bits - 1)) - 1ul);
	const auto value_mask = (1ul << (Bits)) - 1ul;

	if (_val >= 0) {
		return _val <= val_max;
	}

	return _val >= val_min;
}

TEST_CASE("Value Encode/Decode Tests", "[protocol]") {
	using value_t = double;
	using encoding_error_t = chandra::aero::protocol::internal::EncodingErrors;
	const uint32_t value_mask = static_cast<uint32_t>((1ul << (chandra::aero::protocol::internal::TrackingStateEncoding::distance_bits)) - 1ul);
	const size_t encoding_bits = chandra::aero::protocol::internal::TrackingStateEncoding::distance_bits;
	const auto x_max = chandra::aero::protocol::internal::TrackingStateRange<value_t>::distance_max;
	const auto x_min = -chandra::aero::protocol::internal::TrackingStateRange<value_t>::distance_max;
	const int32_t y_min = static_cast<int32_t>(0xF0000001); // Note: This is for a 29-bit encoding
	const int32_t y_zero{ 0 };
	const int32_t y_max = static_cast<int32_t>((1ul << (encoding_bits - 1ul)) - 1ul);

	SECTION("Test Encoded Value Range Checker") {
		REQUIRE((encoded_value_in_range<encoding_bits>(y_zero) == true));
		REQUIRE((encoded_value_in_range<encoding_bits>(y_min) == true));
		REQUIRE((encoded_value_in_range<encoding_bits>(y_max) == true));
		REQUIRE((encoded_value_in_range<encoding_bits>(y_min - 1) == false));
		REQUIRE((encoded_value_in_range<encoding_bits>(y_max + 1) == false));
	}

	SECTION("Test Encode Overflow Detection") {

		encoding_error_t errors;
		chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(x_max, x_min, x_max, errors);
		REQUIRE((errors == encoding_error_t::None));
		chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(x_max+1, x_min, x_max, errors);
		REQUIRE((errors == encoding_error_t::Overflow));
		chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(x_min - 1, x_min, x_max, errors);
		REQUIRE((errors == encoding_error_t::Overflow));
	}

	SECTION("Test Encode Underflow Detection") {
		const auto res = chandra::aero::protocol::internal::encode_resolution<encoding_bits>(x_min, x_max);

		encoding_error_t errors;
		chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(0, x_min, x_max, errors);
		REQUIRE((errors == encoding_error_t::None));
		chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(res, x_min, x_max, errors);
		REQUIRE((errors == encoding_error_t::Underflow));
		chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(res / 2, x_min, x_max, errors);
		REQUIRE((errors == encoding_error_t::Underflow));
	}

	SECTION("Test Basic Roundtrip For Max Value") {
		const auto x = x_max;
		const auto y = chandra::aero::protocol::internal::encode_range<int32_t, encoding_bits>(x, x_min, x_max);
		const auto x_est = chandra::aero::protocol::internal::decode_range<value_t, encoding_bits>(y, x_min, x_max);
		CAPTURE(y, y_max, x, x_max);

		REQUIRE((encoded_value_in_range<encoding_bits>(y) == true));
		REQUIRE((y == y_max));
		REQUIRE((x == Approx(x_max)));
	}

	SECTION("Test Basic Roundtrip For Min Value") {
		const auto x = x_min;
		const auto y = chandra::aero::protocol::internal::encode_range<int32_t, chandra::aero::protocol::internal::TrackingStateEncoding::distance_bits>(x, x_min, x_max);
		const auto x_est = chandra::aero::protocol::internal::decode_range<value_t, chandra::aero::protocol::internal::TrackingStateEncoding::distance_bits>(y, x_min, x_max);
		CAPTURE(y, y_min, x, x_min);

		REQUIRE((encoded_value_in_range<encoding_bits>(y) == true));
		REQUIRE((y == y_min));
		REQUIRE((x == Approx(x_min)));
	}

	SECTION("Test Basic Roundtrip For Zero Value") {
		const value_t zero{ 0 };
		const auto x = zero;
		const auto y = chandra::aero::protocol::internal::encode_range<int32_t, chandra::aero::protocol::internal::TrackingStateEncoding::distance_bits>(x, x_min, x_max);
		const auto x_est = chandra::aero::protocol::internal::decode_range<value_t, chandra::aero::protocol::internal::TrackingStateEncoding::distance_bits>(y, x_min, x_max);
		CAPTURE(y, y_zero, x, zero);

		REQUIRE((encoded_value_in_range<encoding_bits>(y) == true));
		REQUIRE((y == y_zero));
		REQUIRE((x == Approx(zero)));
	}
}

//
// Tracker Protocol Construction
//
TEST_CASE("Construction of Tracker Protocol Objects", "[protocol]") {
	using value_t = double;

	SECTION("Default Construction of TrackerState") {
		chandra::aero::protocol::TrackerState<value_t> tracker_state;
		REQUIRE((tracker_state.header.vehicle_id == 0xFF));
		REQUIRE((tracker_state.header.tracker_id == 0xFF));
	};

	SECTION("Default Construction of BasestationTrackingState") {
		chandra::aero::protocol::BasestationTrackingState<value_t> basestation_state;

	};

}

TEST_CASE("TrackerState Roundtrip Serialize/Deserialize Test", "[protocol]") {
	using value_t = double;
	chandra::aero::protocol::TrackerState<value_t> tgt_tracker_state;
	uint8_t buffer[21];

	// Initialize Tracker State
	tgt_tracker_state.header.format = 0x00;
	tgt_tracker_state.header.vehicle_id = 0x00;
	tgt_tracker_state.header.tracker_id = 0x01;
	tgt_tracker_state.header.mode = chandra::aero::protocol::TrackerFlightMode::Preflight;
	tgt_tracker_state.header.status = chandra::aero::protocol::TrackerLocalizationStatus::Raw;
	tgt_tracker_state.pos.x = 1_m_; // TODO: FIX THE ASSIGNMENT OPERATOR IMPLEMENTATION HERE....
	tgt_tracker_state.pos.y = 2_m_;
	tgt_tracker_state.pos.z = 3_m_;
	tgt_tracker_state.vel.x = 5_m_per_s_;
	tgt_tracker_state.vel.y = 7_m_per_s_;
	tgt_tracker_state.vel.z = 9_m_per_s_;


	// Serialize Tracker State
	const bool serialize_success = chandra::aero::protocol::serialize_tracking_state(tgt_tracker_state, buffer);
	REQUIRE((serialize_success == true));

	// Deserialize Tracker State
	chandra::aero::protocol::TrackerState<value_t> result_tracker_state;
	const bool deserialize_success = chandra::aero::protocol::deserialize_tracking_state(buffer, result_tracker_state);
	REQUIRE((deserialize_success == true));

	REQUIRE((result_tracker_state == tgt_tracker_state));
}

