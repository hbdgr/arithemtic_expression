#include <array>
#include <iostream>

#include "expression_parser.hpp"
#include "expression_evaluator.hpp"


auto execute_expression = [](const std::string &expression) {
	auto tree = ExpressionParser::generateTree(expression);
	return ExpressionEvaluator::fromTree(&tree);
};

int main() {
	auto expressions = {
		"6 * 4 * 3 / 2 / 5 * 9 / 3 * 2 / 2",
		"2 + 3 + 7 + 2 + 1 - 9 - 9 - 9 - 3 + 2 - 6 + 2"
	};

	for (auto expr : expressions) {
		std::cout << expr << " = " << execute_expression(expr) << std::endl;
	}

	return 0;
}
