#include "expression_evaluator.hpp"


int ExpressionEvaluator::fromTree(SyntaxTree &&tree) {
  auto tree_data = tree.get_data();

  if (tree_data.hold_operator()) {
    return tree_data.get_arithmetic_operator()
      .execute(tree.get_left_child() -> get_data().get_element(), tree.get_right_child() -> get_data().get_element());
  } else if (tree_data.empty()) {
    throw std::runtime_error(std::string("[ExpressionEvaluator] Can not evaluate empty tree"));
  }
  else {
    return tree_data.get_element();
  }
}
