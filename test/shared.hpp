#pragma once

#include <expression_parser.hpp>
#include <expression_evaluator.hpp>


auto execute_expression = [](const std::string &expression) {
	auto tree = ExpressionParser::generateTree(expression);
	return ExpressionEvaluator::fromTree(&tree);
};
