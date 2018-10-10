#include "expression_evaluator.hpp"


int ExpressionEvaluator::fromTree(SyntaxTree &&tree) {
  auto tree_data = tree.get_data();

  if (tree_data.empty()) {
    throw std::runtime_error(std::string("[ExpressionEvaluator] Can not evaluate empty tree"));
  } else if (tree_data.hold_operator()) {
    auto left_child = tree.get_left_child();
    auto right_child = tree.get_right_child();

    // should not happen
    if (left_child == nullptr)
      throw std::runtime_error(std::string("[ExpressionEvaluator] Left child is null.."));

    auto left_child_data = left_child -> get_data();

    if (left_child_data.hold_operator()) {
      return fromTree(std::move(*tree.get_left_child()));
    }

    // should not happen
    if (right_child == nullptr)
      throw std::runtime_error(std::string("[ExpressionEvaluator] Right child is null.."));

    auto right_child_data = right_child -> get_data();

    if (right_child_data.hold_operator()) {
      return fromTree(std::move(*tree.get_right_child()));
    }

    auto result = tree_data.get_arithmetic_operator()
      .execute(left_child_data.get_element(), right_child_data.get_element());

    if (tree.get_parent() == nullptr) {
      return result;
    }

    tree.update_data(result);
    return fromTree(std::move(*tree.get_parent()));
  } else {
    // one element expression
    return tree_data.get_element();
  }
}
