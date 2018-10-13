#pragma once

#include <stack>
#include "syntax_tree.hpp"


class ExpressionParser {
public:
  ExpressionParser() = default;
  SyntaxTree generateTree(const std::string &expression);

private:
  // contain parsing logic, require std::string without whitespaces
  SyntaxTree consume_expression(const std::string &formatted_expression);

  // helper functions
  void push_to_stack_if_empty(char ch);
  void insert_element_from_stack(SyntaxTree &tree);

  // create copy of original string with removed whitespaces
  std::string remove_whitespaces(const std::string &str);
  bool is_element(char ch);

  // private members
  std::stack<int> m_elements_stack;
  int m_increased_priority = 0;
};
