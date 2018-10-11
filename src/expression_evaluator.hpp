#pragma once

#include "syntax_tree.hpp"


class ExpressionEvaluator {
public:
  static int fromTree(SyntaxTree *tree);

private:
  // gets data from currect tree node, throws if it is empty or not initialized
  static SimpleCustomVariant get_tree_data(SyntaxTree *tree);

  // replace operators in tree with actual results
  static void update_tree(SyntaxTree *tree);
};
