#pragma once

#include <string>
#include <memory>
#include "arithmetic_operator.hpp"
#include "simple_custom_variant.hpp"
#include "utils.hpp"


class SyntaxTree {
public:
  SyntaxTree();
  SyntaxTree(short element);
  SyntaxTree(char ch);
  SyntaxTree(SyntaxTree *child, SimpleCustomVariant data);
  SyntaxTree(SyntaxTree &&rhs);

  void add_element(short element);

  // returns pointer to actual root node.
  void add_operator(char ch);

  SimpleCustomVariant get_data() const;

  void update_data(short element);
  bool have_space_for_child() const;

  SyntaxTree* get_parent() const;
  SyntaxTree* get_left_child() const;
  SyntaxTree* get_right_child() const;

private:
  bool _is_empty = false;
  // std::variant from c++17 or at least variant from boost would be great here
  // std::variant<ArithmeticOperator, short> _data;
  SimpleCustomVariant _data;

  SyntaxTree* _parent = nullptr;
  std::unique_ptr<SyntaxTree> _left_child = nullptr;
  std::unique_ptr<SyntaxTree> _right_child = nullptr;
};
