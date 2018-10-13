#include "expression_evaluator.hpp"


int ExpressionEvaluator::fromTree(SyntaxTree *tree) {
  update_tree(tree);

  // return calculated result
  return get_tree_data(tree).get_element();
}

SimpleCustomVariant ExpressionEvaluator::get_tree_data(SyntaxTree *tree) {
  // should not happen
  if (tree == nullptr)
    throw std::runtime_error("[ExpressionEvaluator] Tree is null..");

  auto tree_data = tree -> get_data();

  if (tree_data.empty())
    throw std::runtime_error("[ExpressionEvaluator] Can not evaluate empty tree");

    return tree_data;
}

void ExpressionEvaluator::update_tree(SyntaxTree *tree) {
  auto tree_data = get_tree_data(tree);
  if (tree_data.hold_operator()) {
    auto left_child_data = get_tree_data(tree -> get_left_child());
    if (left_child_data.hold_operator())
      return update_tree(tree -> get_left_child());

    auto right_child_data = get_tree_data(tree -> get_right_child());
    if (right_child_data.hold_operator())
      return update_tree(tree -> get_right_child());

    auto result = tree_data.get_arithmetic_operator()
      .execute(left_child_data.get_element(), right_child_data.get_element());

    // replace branch oprator node with actual children result
    tree -> update_data(result);

    // end if root node of tree
    if (tree -> get_parent() != nullptr) {
      return update_tree(tree -> get_parent());
    }
  }
}
