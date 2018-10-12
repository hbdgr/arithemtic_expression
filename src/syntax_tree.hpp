#pragma once

#include <string>
#include <memory>
#include "arithmetic_operator.hpp"
#include "simple_custom_variant.hpp"
#include "utils.hpp"


class SyntaxTree {
public:
  // new empty tree
  SyntaxTree();
  // new tree with element
  SyntaxTree(short element);
  // new tree with operator and optional parent
  SyntaxTree(const ArithmeticOperator &op, SyntaxTree *parent = nullptr);
  // copy whole tree
  SyntaxTree(SyntaxTree *child);
  // move whole tree
  SyntaxTree(SyntaxTree &&rhs) noexcept;

  void add_element(short element);
  void add_operator(const ArithmeticOperator &new_op);

  SimpleCustomVariant get_data() const;

  void update_data(short element);

  SyntaxTree* get_parent() const;
  SyntaxTree* get_left_child() const;
  SyntaxTree* get_right_child() const;

private:
  bool have_space_for_child() const;

  bool add_element_to_child(std::unique_ptr<SyntaxTree> &child, short num);
  // add new operator to the tree respecting operators priority
  void add_priority_operator(const ArithmeticOperator &actual_operator, const ArithmeticOperator &new_operator);

  bool _is_empty = false;

  // std::variant from c++17 or at least variant from boost would be great here
  // std::variant<ArithmeticOperator, short> _data;
  SimpleCustomVariant _data;

  SyntaxTree* _parent = nullptr;
  std::unique_ptr<SyntaxTree> _left_child = nullptr;
  std::unique_ptr<SyntaxTree> _right_child = nullptr;
};
