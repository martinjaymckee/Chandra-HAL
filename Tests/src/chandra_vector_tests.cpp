//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <matrix_vectors.h>
#include <matrix_vector_ops.h>

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
		//CAPTURE(a.w, a.x, a.y, a.z);
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
		REQUIRE( ((a.w == 1) && (a.x == 2) && (a.y == 3) && (a.z == 4)) );
	};

	SECTION("Scalar Addition Test - 1") {
		const vector_t a = vector_t::Count();
		const auto c = vector_t{ a + 1 };
		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};

	SECTION("Scalar Addition Test - 2") {
		const vector_t a = vector_t::Count();
		const auto c = vector_t{ 1 + a };
		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};

	SECTION("Matrix Addition Test - 1") {
		const vector_t a = vector_t::Count();
		const matrix_t one = matrix_t::Filled(1);
		const auto c = vector_t{ a + one };
		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};

	// TODO: THE NEXT TWO DO NOT WORK BECAUSE THEY ARE NOT FINDING THE CORRECT OVERLOADS....  THEY ARE TRYING TO USE THE
	//	SCALAR OVERLOAD BECAUSE IT'S NOT SEEING A VECTOR AS A REFERENCE TO A (TEMPLATED) MATRIX.  IDEALLY, IT COULD USE
	//	THE SAME FORM AS MATRIX + MATRIX AND JUST USE SOME TEMPLATE MAGIC TO MAKE IT WORK.
	SECTION("Matrix Addition Test - 2") {
		const vector_t a = vector_t::Count();
		const matrix_t one = matrix_t::Filled(1);
//		const auto c = vector_t{ one + a };
//		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
//		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};

	SECTION("Matrix Addition Test - 3") {
		const vector_t a = vector_t::Count();
		const vector_t one = vector_t::Filled(1);
//		const auto c = vector_t{ one + a };
//		REQUIRE(std::is_same_v<const vector_t, decltype(c)>);
//		REQUIRE(((c.w == 1) && (c.x == 2) && (c.y == 3) && (c.z == 4)));
	};
}