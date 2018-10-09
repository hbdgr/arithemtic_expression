#include <catch2/catch.hpp>
#include <stdexcept>
#include "shared.hpp"


TEST_CASE("Invalid_Expression") {
	SECTION( "Invalid element: a B @" ) {
		REQUIRE_THROWS_AS(execute_expression("a"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("B"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("@"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("@"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("@"), std::invalid_argument);
	}

	SECTION( "Invalid element inside the expression" ) {
		REQUIRE_THROWS_AS(execute_expression("2a +4"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("2+5   y"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("7 /, 5"), std::invalid_argument);
	}

	SECTION( "Empty expression" ) {
		REQUIRE_THROWS_AS(execute_expression(""), std::invalid_argument);
	}

	SECTION( "Number > 9" ) {
		REQUIRE_THROWS_AS(execute_expression("13"), std::invalid_argument);
	}

	SECTION( "Number > 9 in expression" ) {
		REQUIRE_THROWS_AS(execute_expression("1 + 37"), std::invalid_argument);
	}

	SECTION( "Negtive number < 0" ) {
		REQUIRE_THROWS_AS(execute_expression("-5"), std::invalid_argument);
	}

	SECTION( "Negtive number in expression" ) {
		REQUIRE_THROWS_AS(execute_expression("6 + -9"), std::invalid_argument);
	}

	SECTION( "Doubled operators" ) {
		REQUIRE_THROWS_AS(execute_expression("6 +/ 9"), std::invalid_argument);
	}

	SECTION( "Lonely operator" ) {
		REQUIRE_THROWS_AS(execute_expression("/ "), std::invalid_argument);
	}

	SECTION( "Operator at the end" ) {
		REQUIRE_THROWS_AS(execute_expression("2+"), std::invalid_argument);
	}
}
