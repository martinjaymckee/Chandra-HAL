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
// Matrix Traits
// 

template<class T>
class TD;

TEST_CASE("Check Matrix Traits for Vectors") {
	using value_t = double;
	using matrix_t = chandra::math::Matrix<value_t, 3, 1>;
	using vector_t = chandra::math::Vector3D<value_t>;

	value_t a(0);
	matrix_t M(0);
	vector_t V;

	SECTION("is_matrix") {
		REQUIRE((chandra::math::is_matrix(a) == false));
		REQUIRE((chandra::math::is_matrix(M) == true));
	}

	SECTION("is_derived_matrix") {
		REQUIRE((chandra::math::is_derived_matrix(a) == false));
		REQUIRE((chandra::math::is_derived_matrix(V) == true));
	}

	SECTION("is_matrix_assignable") {
		REQUIRE((chandra::math::is_matrix_assignable<decltype(M), decltype(a)>() == false));
		REQUIRE((chandra::math::is_matrix_assignable<decltype(M), decltype(M)>() == true));
		REQUIRE((chandra::math::is_matrix_assignable<decltype(M), decltype(V)>() == true));
		REQUIRE((chandra::math::is_matrix_assignable<decltype(V), decltype(V)>() == true));
	}
}

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
	using row_vector_t = chandra::math::Vector<value_t, 4, false>;

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

	SECTION("Vector Transpose") {
		const vector_t a = vector_t::Count();
		const row_vector_t b = row_vector_t::Count();

		const auto c = a.T();
		const auto d = b.T();

//		TD<decltype(c)> a;
		REQUIRE(std::is_same_v<const row_vector_t, decltype(c)>);
		REQUIRE(std::is_same_v<const vector_t, decltype(d)>);
		REQUIRE(c == b);
		REQUIRE(d == a);
	}
}