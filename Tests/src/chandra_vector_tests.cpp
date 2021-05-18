//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <matrix_vectors.h>

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
}
