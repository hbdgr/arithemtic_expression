#pragma once

#include "syntax_tree.hpp"


class ExpressionParser {
public:
  static SyntaxTree generateTree(const std::string &expression);

private:
  // create copy of original string with removed whitespaces
  static std::string remove_whitespaces(const std::string &str);
  static bool is_element(char ch);
  static bool is_operator(char ch);
};
