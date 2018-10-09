#pragma once

#include "syntax_tree.hpp"


class ExpressionEvaluator {
public:
  static int fromTree(SyntaxTree &&tree);
};
