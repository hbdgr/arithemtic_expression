#include <catch2/catch.hpp>
#include <expression_parser.hpp>
#include <expression_evaluator.hpp>


TEST_CASE("Parse_Correct_Expression") {
	auto execute_expression = [](const std::string &expression) {
		auto tree = ExpressionParser::generateTree(expression);
		return ExpressionEvaluator::fromTree(std::move(tree));
	};

	SECTION( "Simple one element: 0" ) {
		REQUIRE(execute_expression("0") == 0);
	}

	SECTION( "Simple one element: 5" ) {
		REQUIRE(execute_expression("5") == 5);
	}
}
