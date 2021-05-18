//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <matrix_vectors.h>
//#include <matrix_ops.h>
#include <matrix_vector_ops.h>

template<class T> struct TD;

//
// Vector Construction
//
TEST_CASE( "2D vectors are constructed", "[vector]" ) {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 2, 1>;
	using vector_t = chandra::math::Vector<value_t, 2>;

	SECTION("Construction from matrix") {
		const matrix_t m_a = matrix_t::Filled(0);
		const vector_t a{m_a};
		REQUIRE( a.x == 0 );
	};

	SECTION("Copy Construction from matrix") {
		const matrix_t m_a = matrix_t::Count();
		const matrix_t m_b = matrix_t::Count();
		const vector_t a{m_a};
		const vector_t b{m_b};
		const vector_t c{b};

		REQUIRE( a == c );
	};

	SECTION("Static Construction objects of vectors") {
		const vector_t a = vector_t::Count();
		CAPTURE(a.x, a.y);
		REQUIRE(((a.x == 0) && (a.y == 1)));
	};
}

TEST_CASE( "3D vectors are constructed", "[vector]" ) {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 3, 1>;
	using vector_t = chandra::math::Vector<value_t, 3>;

	SECTION("Construction from matrix") {
		const matrix_t m_a = matrix_t::Filled(0);
		const vector_t a{m_a};
		REQUIRE( a.x == 0 );
	};

	SECTION("Copy Construction from vector") {
		const matrix_t m_a = matrix_t::Count();
		const matrix_t m_b = matrix_t::Count();
		const vector_t a{m_a};
		const vector_t b{m_b};
		const vector_t c{b};

		REQUIRE( a == c );
	};

	SECTION("Static Construction objects of vectors") {
		const vector_t a = vector_t::Count();
		CAPTURE(a.x, a.y, a.z);
		REQUIRE(((a.x == 0) && (a.y == 1) && (a.z == 2)));
	};
}

TEST_CASE("4D vectors are constructed", "[vector]") {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 4, 1>;
	using vector_t = chandra::math::Vector<value_t, 4>;

	SECTION("Construction from matrix") {
		const matrix_t m_a = matrix_t::Filled(0);
		const vector_t a{ m_a };
		REQUIRE(a.x == 0);
	};

	SECTION("Copy Construction from vector") {
		const matrix_t m_a = matrix_t::Count();
		const matrix_t m_b = matrix_t::Count();
		const vector_t a{ m_a };
		const vector_t b{ m_b };
		const vector_t c{ b };

		REQUIRE(a == c);
	};

	SECTION("Static Construction objects of vectors") {
		const vector_t a = vector_t::Count();
		CAPTURE(a.w, a.x, a.y, a.z);
		REQUIRE(((a.w == 0) && (a.x == 1) && (a.y == 2) && (a.z == 3)));
	};
}

//
// Vector Operations
//
TEST_CASE("4D Vectors Math Operations", "[vector]") {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 4, 1>;
	using vector_t = chandra::math::Vector<value_t, 4>;

	SECTION("Assign-Add Test") {
		vector_t a = vector_t::Count();
		a += 1;
		CAPTURE(a.w, a.x, a.y, a.z);
		REQUIRE( ((a.w == 1) && (a.x == 2) && (a.y == 3) && (a.z == 4)) );
	};

	SECTION("Scalar Addition Test - Value check") {
		const vector_t a = vector_t::Count();
		const auto c = a + value_t(1);
		CAPTURE(a, c, c.w, c.x, c.y, c.z);
		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};

	SECTION("Scalar Addition Test - Type check") {
		const vector_t a = vector_t::Count();
		const auto c = a + value_t(1);
		CAPTURE(a, c);
		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
	};

	SECTION("Matrix Addition Test - Value check") {
		const vector_t a = vector_t::Count();
		const matrix_t one = matrix_t::Filled(1);
		const vector_t b{ a };
		const auto c = a + one;
		CAPTURE(a, one, c, &c, &c.w, &a, &a.w, c.w, c.x, c.y, c.z);
		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};

	SECTION("Matrix Addition Test - Type check") {
		const vector_t a = vector_t::Count();
		const matrix_t one = matrix_t::Filled(1);
		const auto c = a + one;
		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
	};
}