#include <catch2/catch.hpp>
#include <stdexcept>
#include "shared.hpp"


TEST_CASE("Parentheses") {
	SECTION( "Simple case, two operators one pair of parentheses" ) {
		REQUIRE(execute_expression("2 * (5 + 3)") == (2 * (5 + 3)));
		REQUIRE(execute_expression("8 / (4 - 3)") == (8 / (4 - 3)));
		REQUIRE(execute_expression("(2 - 9) * 2") == ((2 - 9) * 2));
	}

	SECTION( "Nested parentheses" ) {
		REQUIRE(execute_expression("((2 + 2 - 4 * 7 ) +  2 * (5 + 3)) * 8") == ((2 + 2 - 4 * 7 ) + 2 * (5 + 3)) * 8);
		REQUIRE(execute_expression("(8 / (4 - 3) * 2) - 6 / (7 - 1 )") == ((8 / (4 - 3) * 2) - 6 / (7 - 1 )));
		REQUIRE(execute_expression("(2 * 2 * 3 + 5) * (9 - 2 - 6 + 8) + (7 - (9 - 2 * 6) / 5) + 2") == ((2 * 2 * 3 + 5) * (9 - 2 - 6 + 8) + (7 - (9 - 2 * 6) / 5) + 2));
		REQUIRE(execute_expression("(((((((1 + 0) + 5) * (9 - 2) - 6) + 8) + 7) - (9 - 2)) / 5) + 2") == ((((((((1 + 0) + 5) * (9 - 2) - 6) + 8) + 7) - (9 - 2)) / 5) + 2));
	}

	SECTION( "Description example 1" ) {
		REQUIRE(execute_expression("(4 + 5 * (7 - 3)) - 2") == 22);
	}
}

TEST_CASE("Missing parentheses") {
	SECTION( "Missing right" ) {
		REQUIRE_THROWS_AS(execute_expression("2 * (4 + 1"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("(2) * (5 + (1 * 5 + 9)"), std::invalid_argument);
	}

	SECTION( "Missing left" ) {
		REQUIRE_THROWS_AS(execute_expression("2 * 4) + 1"), std::invalid_argument);
		REQUIRE_THROWS_AS(execute_expression("6 * (4 + (8 * 2 + 3)))"), std::invalid_argument);
	}
}
