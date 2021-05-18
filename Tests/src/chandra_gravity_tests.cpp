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
		REQUIRE(gravity.g0().value() == 9.80665);
	};

	SECTION("Check Standard Gravity at 5000m asl") {
		REQUIRE(gravity.gh_asl(5000_m_).value() < 9.80665);  // TODO: THIS SHOULD CHECK EQUALITY 
	};
}

TEST_CASE( "Scalar WGS84 Gravity", "[gravity]" ) {
	using value_t = double;
	using gravity_t = chandra::aero::WGS84Gravity<value_t>;
	const gravity_t gravity;

}
