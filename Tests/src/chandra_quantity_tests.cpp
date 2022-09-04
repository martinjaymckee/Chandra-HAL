//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <quantity.h>
#include <units.h>
using namespace chandra::units::mks::literals;

//
// Quantity Construction
//
TEST_CASE( "Quantities are constructed", "[quantity]" ) {
	using value_t = double;
	using meters_t = chandra::units::mks::Q_m<value_t>;

	SECTION("Default Construction") {
		const meters_t a;
		REQUIRE( (a.value() == 0) );
	};

	SECTION("Explicit Construction") {
		const meters_t a{2};
		REQUIRE( (a.value() == 2) );
	};
}

//
// Quantity Conversion
//
TEST_CASE( "Quantities are converted", "[quantity]" ) {
	using value_t = double;
	using meters_t = chandra::units::mks::Q_m<value_t>;
	using seconds_t = chandra::units::mks::Q_s<value_t>;
	using m_per_s_t = chandra::units::mks::Q_m_per_s<value_t>;

	SECTION("Convert ft -> m") {
		const meters_t a = 2_ft_;
		REQUIRE( (a.value() == (0.3048*2)) );
	};

	SECTION("Calculate m/s from m and s") {
		const meters_t l{3};
		const seconds_t t{4};
		const m_per_s_t v{ 0.75 };
		REQUIRE( (v == (l/t)) );
	};

	SECTION("Calculate m/s from explicit ft and s") {
		const seconds_t t{1};
		const m_per_s_t v{ 0.3048 };
		REQUIRE( (v == (1_ft_/t)) );
	};
}

//
// Scalar Quantity Handling
//
TEST_CASE("Scalar quantity handling", "[quantity]") {
	using value_t = double;
	using meters_t = chandra::units::mks::Q_m<value_t>;
	using ft_t = chandra::units::mks::Q_ft<value_t>;
	using meters_per_second_t = chandra::units::mks::Q_m_per_s<value_t>;
	using seconds_t = chandra::units::mks::Q_s<value_t>;

	SECTION("Create Scalar from meters and meters") {
		const meters_t a{ 1 };
		const meters_t b{ 2 };
		const value_t c = a / b;
		REQUIRE((c == Approx(0.5)));
	};

	SECTION("Create Scalar from meters and feet") {
		const meters_t a{ 1 };
		const ft_t b{ 1 };
		const value_t c = a / b;
		REQUIRE((c == Approx(3.28083989501)));
	};

	SECTION("Use Reduced scalar in an expression") {
		const meters_t a{ 1 };
		const meters_t b{ 2 };
		const value_t c = 1 - (a / b);
		REQUIRE((c == Approx(0.5)));
	}

	SECTION("Use Reduced scalar in a complex expression") {
		const meters_t a{ 1 };
		const meters_per_second_t b{ 2 };
		const seconds_t c{ 10 };
		const value_t d = b / (a / c);
		REQUIRE((d == Approx(20)));
	}
}
