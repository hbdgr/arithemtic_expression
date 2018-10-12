#pragma once

#include <stack>
#include "syntax_tree.hpp"


class ExpressionParser {
public:
  static SyntaxTree generateTree(const std::string &expression);

private:
  // contain parsing logic, require std::string without whitespaces
  static SyntaxTree consume_expression(std::string &&formatted_expression);

  // helper functions

  static void push_to_stack_if_empty(std::stack<short> &stack, char ch);
  static void insert_element_from_stack(std::stack<short> &elements_stack, SyntaxTree &tree);

  // create copy of original string with removed whitespaces
  static std::string remove_whitespaces(const std::string &str);
  static bool is_element(char ch);
  static bool is_operator(char ch);

  static bool is_lparanthes(char ch);
  static bool is_rparanthes(char ch);
};
