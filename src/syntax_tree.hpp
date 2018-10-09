#pragma once

#include <string>
#include <memory>
#include "arithmetic_operator.hpp"
#include "simple_custom_variant.hpp"
#include "utils.hpp"


class SyntaxTree {
public:
  SyntaxTree() : _is_empty(true) {}
  SyntaxTree(short element) : _data(element) {}
  SyntaxTree(char ch) : _data(ArithmeticOperator(ch)) {}

  void add_element(short element);
  void add_operator(char ch);

  SimpleCustomVariant get_data() const {
    return _data;
  }

  SyntaxTree* get_left_child() const {
    return _left_child.get();
  }

  SyntaxTree* get_right_child() const {
    return _right_child.get();
  }

private:
  bool _is_empty = false;
  // std::variant from c++17 or at least from boost would be great here
  // std::variant<ArithmeticOperator, short> _data;
  SimpleCustomVariant _data;

  std::unique_ptr<SyntaxTree> _parent = nullptr;
  std::unique_ptr<SyntaxTree> _left_child = nullptr;
  std::unique_ptr<SyntaxTree> _right_child = nullptr;
};
