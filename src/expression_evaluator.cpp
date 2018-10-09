#include <iostream>
#include "expression_evaluator.hpp"


int ExpressionEvaluator::fromTree(SyntaxTree &&tree) {
    return tree.evaluate();
}
