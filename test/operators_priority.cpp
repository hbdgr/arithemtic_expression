#include <catch2/catch.hpp>
#include <utils.hpp>


TEST_CASE("Priority_of_operators") {
	SECTION( "Two operators" ) {
		REQUIRE(execute_expression("3 * 2 + 3") == (3 * 2 + 3));
		REQUIRE(execute_expression("3 + 2 * 3") == (3 + 2 * 3));
		REQUIRE(execute_expression("3 - 5 * 7") == (3 - 5 * 7));
		REQUIRE(execute_expression("8 / 2 - 2") == (8 / 2 - 2));
		REQUIRE(execute_expression("7 + 4 / 2") == (7 + 4 / 2));
		REQUIRE(execute_expression("3 - 4 / 2") == (3 - 4 / 2));
	}

	SECTION("Three operators") {
		REQUIRE(execute_expression("3 * 2 + 3 * 4") == (3 * 2 + 3 * 4));
		REQUIRE(execute_expression("2 - 5 * 5 + 1") == (2 - 5 * 5 + 1));
		REQUIRE(execute_expression("6 / 2 / 2 + 1") == (6 / 2 / 2 + 1));
		REQUIRE(execute_expression("4 + 3 + 3 * 5") == (4 + 3 + 3 * 5));
		REQUIRE(execute_expression("7 / 5 * 5 + 1") == (7 / 5 * 5 + 1));
	}

	SECTION("Description example 2") {
		REQUIRE(execute_expression("4+5+7/2") == (12));
	}

	SECTION("More complex expressions") {
		REQUIRE(execute_expression("2 - 5 * 5 * 6 + 1 - 8 / 2") == (2 - 5 * 5 * 6 + 1 - 8 / 2));
		REQUIRE(execute_expression("2 * 5 * 5 + 6 + 1 * 8 / 2 + 2 * 2 / 3") == (2 * 5 * 5 + 6 + 1 * 8 / 2 + 2 * 2 / 3));
		REQUIRE(execute_expression("0 * 9 + 3 / 2 * 7 * 4 / 2 + 1 + 2 - 9") == (0 * 9 + 3 / 2 * 7 * 4 / 2 + 1 + 2 - 9));
	}
}
