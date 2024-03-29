//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <matrix.h>

//
// Matrix Traits
// 
TEST_CASE("Check Matrix Traits") {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 2, 2>;
	value_t a(0);
	matrix_t M(0);
	
	SECTION("is_matrix") {
		REQUIRE((chandra::math::is_matrix(a) == false));
		REQUIRE((chandra::math::is_matrix(M) == true));
	}

	SECTION("is_derived_matrix") {
		REQUIRE((chandra::math::is_derived_matrix(M) == true));
	}

	SECTION("is_matrix_assignable") {
		REQUIRE((chandra::math::is_matrix_assignable<decltype(M), decltype(a)>() == false));
		REQUIRE((chandra::math::is_matrix_assignable<decltype(M), decltype(M)>() == true));
	}
}

//
// Matrix Construction
//
TEST_CASE( "Matricies are constructed", "[matrix]" ) {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 2, 2>;

	SECTION("Default Construction") {
		const matrix_t a;
		(void) a;
	};

	SECTION("Initializer List Construction - Row-Major") {
		const matrix_t a{ {1, 1, 2, 2} };
		const matrix_t b = { 1, 1, 2, 2 };
		REQUIRE( ((a(0, 0) == 1) && (a(0, 1) == 1) && (a(1, 0) == 2) && (a(1, 1) == 2)) );
		REQUIRE(a == b);
	}

	SECTION("Initializer List Construction - Column-Major") {
		const matrix_t a{ {1, 1, 2, 2}, false };
		REQUIRE( ((a(0, 0) == 1) && (a(0, 1) == 2) && (a(1, 0) == 1) && (a(1, 1) == 2)) );
	}

	SECTION("Copy-Constructor") {
		const matrix_t a = { 1, 1, 2, 2 };
		const matrix_t b{ a };
		REQUIRE(((b(0, 0) == 1) && (b(0, 1) == 1) && (b(1, 0) == 2) && (b(1, 1) == 2)));

	}

	SECTION("Conversion Constructor") {
		const chandra::math::Matrix<int, 2, 2> a = { 1, 1, 2, 2 };
		const matrix_t b{ a };
		REQUIRE(((b(0, 0) == 1) && (b(0, 1) == 1) && (b(1, 0) == 2) && (b(1, 1) == 2)));

	}

	SECTION("Single-Value Constructor") {
		const matrix_t filled = matrix_t(1);
		REQUIRE(((filled(0, 0) == 1) && (filled(0, 1) == 1) && (filled(1, 0) == 1) && (filled(1, 1) == 1)));
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

	auto ax = a(0);
};

//
// Matrix Operations
//
TEST_CASE("Basic operations between Matricies are attempted", "[matrix]") {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 2, 2>;
	const value_t a = 1.5;
	const matrix_t Ma = matrix_t::Count();
	const matrix_t Mb = matrix_t::Eye();

	SECTION("Addition") {
		const auto Mc = Ma + Mb;
		const auto Md = Ma + a;
		//REQUIRE((a == c));
	};
	
	SECTION("Subtraction") {
		const auto Mc = Ma - Mb;
		const auto Md = Ma - a;
		//REQUIRE((a == c));
	};

};
