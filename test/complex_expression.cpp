#include <catch2/catch.hpp>
#include "shared.hpp"


TEST_CASE("Complex_Correct_Expressions") {
	SECTION( "Two additions" ) {
		REQUIRE(execute_expression("1 + 2 + 3") == (1 + 2 + 3));
	}

	SECTION( "Two substitutions" ) {
		REQUIRE(execute_expression("5 - 2 - 3") == (5 - 2 - 3));
	}

	SECTION( "Two addition / substitution" ) {
		REQUIRE(execute_expression("7 + 4 - 3") == (7 + 4 - 3));
	}

	SECTION( "Two subtraction / addition" ) {
		REQUIRE(execute_expression("8 - 2 + 6") == (8 - 2 + 6));
	}

	SECTION( "Long addition" ) {
		REQUIRE(execute_expression("8 + 2 + 6 + 7 + 9 + 2") == (8 + 2 + 6 + 7 + 9 + 2));
	}

	SECTION( "Long substitution" ) {
		REQUIRE(execute_expression("6 - 1 - 3 - 7 - 3 - 2") == (6 - 1 - 3 - 7 - 3 - 2));
	}

	SECTION( "Long addition / substitution" ) {
		REQUIRE(execute_expression("6 + 1 - 3 + 7 - 3 + 2 - 8 - 2 + 2") == (6 + 1 - 3 + 7 - 3 + 2 - 8 - 2 + 2));
	}

	SECTION( "Two multiplications" ) {
		REQUIRE(execute_expression("5 * 2 * 9") == (5 * 2 * 9));
	}

	SECTION( "Two divisions" ) {
		REQUIRE(execute_expression("8 / 4 / 2") == (8 / 4 / 2));
	}

	SECTION( "Two multiplication / division" ) {
		REQUIRE(execute_expression("6 * 4 / 2") == (6 * 4 / 2));
	}

	SECTION( "Two division / multiplication" ) {
		REQUIRE(execute_expression("4 / 2 * 2") == (4 / 2 * 2));
	}

	SECTION( "Long multiplications" ) {
		REQUIRE(execute_expression("5 * 2 * 9 * 7 * 2 * 1 * 1") == (5 * 2 * 9 * 7 * 2 * 1 * 1));
	}

	SECTION( "Long divisions" ) {
		REQUIRE(execute_expression("8 / 2 / 2 / 1 / 2 / 2 / 5") == (8 / 2 / 2 / 1 / 2 / 2 / 5));
	}

	SECTION( "Long multiplication / division" ) {
		REQUIRE(execute_expression("6 * 4 * 3 / 2 / 5 * 9 / 3 * 2 / 2") == (6 * 4 * 3 / 2 / 5 * 9 / 3 * 2 / 2));
	}
}
