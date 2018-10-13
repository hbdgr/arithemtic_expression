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
  explicit SyntaxTree(int element);
  // new tree with operator and optional parent
  SyntaxTree(const ArithmeticOperator &op, SyntaxTree *parent = nullptr);
  // copy whole tree
  SyntaxTree(SyntaxTree *child);
  // move whole tree
  SyntaxTree(SyntaxTree &&rhs) noexcept;

  void add_element(int element);
  void add_operator(const ArithmeticOperator &new_op);

  SimpleCustomVariant get_data() const;

  void update_data(int element);

  SyntaxTree* get_parent() const;
  SyntaxTree* get_left_child() const;
  SyntaxTree* get_right_child() const;

private:
  bool have_space_for_child() const;

  bool add_element_to_child(std::unique_ptr<SyntaxTree> &child, int num);
  // add new operator to the tree respecting operators priority
  void add_priority_operator(const ArithmeticOperator &actual_operator, const ArithmeticOperator &new_operator);

  bool m_is_empty = false;

  // std::variant from c++17 or at least variant from boost would be great here
  // std::variant<ArithmeticOperator, int> m_data;
  SimpleCustomVariant m_data;

  SyntaxTree* m_parent = nullptr;
  std::unique_ptr<SyntaxTree> m_left_child = nullptr;
  std::unique_ptr<SyntaxTree> m_right_child = nullptr;
};
