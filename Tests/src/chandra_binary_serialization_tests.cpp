//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <binary_serialize.h>

//
// Helper Functions
//
template<size_t N>
bool buffers_match(const uint8_t(&_a)[N], const uint8_t(&_b)[N]) {
	for (size_t idx = 0; idx < N; ++idx) {
		if (_a[idx] != _b[idx]) return false;
	}
	return true;
}

struct SerializeTest
{
	static constexpr size_t buffer_size = 5; // Bytes

	uint8_t a = 0x05; // 0b101
	static constexpr size_t a_bits = 3;

	uint8_t b = 0x02; // 0b10
	static constexpr size_t b_bits = 2;
	
	uint32_t c = 0x14756609; // 0b1 0100 0111 0101 0110 0110 0000 1001
	static constexpr size_t c_bits = 29;

	uint32_t d = 0x37; // 0b11 0111
	static constexpr size_t d_bits = 6;
};

static const uint8_t serialize_test_buffer[SerializeTest::buffer_size] = {
	0b10110101,
	0b00011101,
	0b01011001,
	0b10000010,
	0b01110111
};

//
// Binary Serializer/Deserializer Construction
//
TEST_CASE("Construct serialize and deserializer", "[serialize]") {
	static constexpr size_t N = 5;
	uint8_t buffer[N] = { 0 };

	SECTION("Buffer begins empty") {
		const uint8_t zero[N] = { 0, 0, 0, 0, 0 };
		REQUIRE(buffers_match(buffer, zero));
	}

	SECTION("Serializer Construction") {
		auto serializer = chandra::serialize::make_binary_serializer(buffer);

		REQUIRE((serializer.buffer_size() == N));
		REQUIRE((serializer.write_pos() == 0));
	};

	SECTION("Deserializer Construction") {
		auto deserializer = chandra::serialize::make_binary_deserializer(buffer);

		REQUIRE((deserializer.buffer_size() == N));
		REQUIRE((deserializer.read_pos() == 0));
	};
}

//
// Binary Serialization
//
TEST_CASE("Run Serialization", "[serialize]") {
	const SerializeTest data;
	uint8_t buffer[data.buffer_size] = { 0 };
	auto serializer = chandra::serialize::make_binary_serializer(buffer);

	size_t offset = 0;

	serializer.write<data.a_bits>(data.a);
	offset += data.a_bits;
	REQUIRE((serializer.write_pos() == offset));

	serializer.write<data.b_bits>(data.b);
	offset += data.b_bits;
	REQUIRE((serializer.write_pos() == offset));

	serializer.write<data.c_bits>(data.c);
	offset += data.c_bits;
	CAPTURE(buffer, serialize_test_buffer);
	REQUIRE((serializer.write_pos() == offset));

	serializer.write<data.d_bits>(data.d);
	offset += data.d_bits;
	REQUIRE((serializer.write_pos() == offset));

	CAPTURE(buffer, serialize_test_buffer);
	REQUIRE(buffers_match(buffer, serialize_test_buffer));
}

//
// Binary Serialization
//
TEST_CASE("Run Deserialization", "[serialize]") {
	const SerializeTest data;
	auto deserializer = chandra::serialize::make_binary_deserializer(serialize_test_buffer);

	size_t offset = 0;

	decltype(data.a) a;
	auto idx = deserializer.read_pos();
	deserializer.read<data.a_bits>(a);
	offset += data.a_bits;
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((a == data.a));
	uint32_t a32;
	deserializer.read_at<data.a_bits>(idx, a32);
	REQUIRE((deserializer.read_pos() == offset));
	CAPTURE(a32, data.a);
	REQUIRE((a32 == data.a));

	decltype(data.b) b;
	idx = deserializer.read_pos();
	deserializer.read<data.b_bits>(b);
	offset += data.b_bits;
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((b == data.b));
	uint32_t b32;
	deserializer.read_at<data.b_bits>(idx, b32);
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((b32 == data.b));

	decltype(data.c) c;
	idx = deserializer.read_pos();
	deserializer.read<data.c_bits>(c);
	offset += data.c_bits;
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((c == data.c));
	uint32_t c32;
	deserializer.read_at<data.c_bits>(idx, c32);
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((c32 == data.c));

	decltype(data.d) d;
	idx = deserializer.read_pos();
	deserializer.read<data.d_bits>(d);
	offset += data.d_bits;
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((d == data.d));
	uint32_t d32;
	deserializer.read_at<data.d_bits>(idx, d32);
	REQUIRE((deserializer.read_pos() == offset));
	REQUIRE((d32 == data.d));

}