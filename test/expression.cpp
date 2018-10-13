#include <catch2/catch.hpp>
#include <utils.hpp>


TEST_CASE("Basic_Correct_Expressions") {
	SECTION( "Simple one element" ) {
		REQUIRE(execute_expression("0") == 0);
	}

	SECTION( "Simple one element (2)" ) {
		REQUIRE(execute_expression("5") == 5);
	}

	SECTION( "Basic addition") {
		REQUIRE(execute_expression("2 + 3") == 5);
	}

	SECTION( "Basic subtraction") {
		REQUIRE(execute_expression("9 - 3") == 6);
	}

	SECTION( "Basic subtraction (negative result)") {
		REQUIRE(execute_expression("2 - 7") == -5);
	}

	SECTION( "Basic multiplication") {
		REQUIRE(execute_expression("7 * 5") == 35);
	}

	SECTION( "Basic division") {
		REQUIRE(execute_expression("6 / 3") == 2);
	}

	SECTION( "Basic division (cutting off the remainder)") {
		REQUIRE(execute_expression("7 / 5") == 1);
	}

	SECTION( "Basic expression without spaces") {
		REQUIRE(execute_expression("5-5") == 0);
	}

	SECTION( "Basic expression with tabs") {
		REQUIRE(execute_expression("2\t+\t6") == 8);
	}

	SECTION( "Basic expression with new lines") {
		REQUIRE(execute_expression("6\n*\n5") == 30);
	}

	SECTION( "Basic expression with mixed whitespaces") {
		REQUIRE(execute_expression("2\t  \n*\r\n0") == 0);
	}
}

TEST_CASE("Invalid_Expressions") {
	SECTION( "Division by zero") {
		REQUIRE_THROWS_AS(execute_expression("2/0"), std::overflow_error);
	}
}
