//
// Include Catch2 Testing Framework
//
#include <catch.hpp>

//
// Include Chandra Features to Test
//
#include <gravity.h>
#include <units.h>
using namespace chandra::units::mks::literals;


TEST_CASE( "Scalar Standard Gravity", "[gravity]" ) {
	using value_t = double;
	using gravity_t = chandra::aero::StandardGravity<value_t>;
	const gravity_t gravity;

	SECTION("Check Base Gravity") {
		REQUIRE(gravity.g0().value() == Approx(9.80665));
	};

	SECTION("Check Standard Gravity at 5000m asl") {
		REQUIRE(gravity.gh_asl(5000_m_).value() == Approx(9.80665)); 
	};
}

TEST_CASE( "Scalar WGS84 Gravity", "[gravity]" ) {
	using value_t = double;
	using gravity_t = chandra::aero::WGS84Gravity<value_t>;
	const auto lat = 38.83_deg_;
	const auto lon = -104.75_deg_;
	const gravity_t gravity{ lat, lon };

	SECTION("Check Base Gravity") {
		REQUIRE(gravity.g0().value() == Approx(9.800659));
	};

	SECTION("Check WGS84 Gravity at 5000m asl") {
		REQUIRE(gravity.gh_asl(5000_m_).value() == Approx(9.78527));
	};
}
