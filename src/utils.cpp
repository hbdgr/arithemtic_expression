#include <expression_parser.hpp>
#include <expression_evaluator.hpp>

int execute_expression(const std::string &expression) {
	auto tree = ExpressionParser().generateTree(expression);
	return ExpressionEvaluator::fromTree(&tree);
}
