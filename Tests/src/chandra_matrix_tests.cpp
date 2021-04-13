//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <matrix.h>

//
// Matrix Construction
//
TEST_CASE( "Matricies are constructed", "[matrix]" ) {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 2, 2>;

	SECTION("Default Construction") {
		const matrix_t a;
	};

	SECTION("Fill Constructor") {
		const matrix_t filled = matrix_t::Filled(1);
		REQUIRE( ((filled(0, 0) == 1) && (filled(0, 1) == 1) && (filled(1, 0) == 1) && (filled(1, 1) == 1)) );
	};

	SECTION("Identity Constructor") {
		const matrix_t ident = matrix_t::Eye();
		REQUIRE(((ident(0, 0) == 1) && (ident(0, 1) == 0) && (ident(1, 0) == 0) && (ident(1, 1) == 1)));
	};

	SECTION("Diagonal Constructor") {
		const matrix_t diag = matrix_t::Diagonal({ 1, 2 });
		REQUIRE(((diag(0, 0) == 1) && (diag(0, 1) == 0) && (diag(1, 0) == 0) && (diag(1, 1) == 2)));
	};

	SECTION("Count Constructor") {
		const matrix_t count = matrix_t::Count();
		REQUIRE(((count(0, 0) == 0) && (count(0, 1) == 1) && (count(1, 0) == 2) && (count(1, 1) == 3)));
		const matrix_t count2 = matrix_t::Count(1);
		REQUIRE(((count2(0, 0) == 1) && (count2(0, 1) == 2) && (count2(1, 0) == 3) && (count2(1, 1) == 4)));
	};

	SECTION("List Constructor") {
		const matrix_t list{1, 2, 3, 4};
		const matrix_t count = matrix_t::Count(1);
		REQUIRE((list == count));
	};
}

//
// Matrix Access
//
TEST_CASE("Matricies are accessed", "[matrix]") {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 2, 2>;
	const matrix_t a = matrix_t::Count();
	const matrix_t b = matrix_t::Eye();

	SECTION("Assignment Operator") {
		const matrix_t c = a;
		REQUIRE((a == c));
	};
};
