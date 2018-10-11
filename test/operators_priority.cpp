#include <catch2/catch.hpp>
#include "shared.hpp"


TEST_CASE("Priority_of_operators") {
	SECTION( "Simple examples" ) {
		REQUIRE(execute_expression("3 * 2 + 3") == (3 * 2 + 3));
		REQUIRE(execute_expression("3 + 2 * 3") == (3 + 2 * 3));
	}
}
