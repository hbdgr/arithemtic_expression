#include <iostream>
#include <stack>
#include <algorithm>
#include <stdexcept>

#include "expression_parser.hpp"


SyntaxTree ExpressionParser::generateTree(const std::string &expression) {
  std::stack<short> elements_stack;

  SyntaxTree local_tree = SyntaxTree();

  auto formatted_expression = remove_whitespaces(expression);
  if (formatted_expression.length() == 0) {
    throw std::invalid_argument(std::string("[ExpressionParser] Empty expression"));
  }
  for (auto ch : remove_whitespaces(expression)) {
    if (is_element(ch)) {
      if (elements_stack.size() > 0) {
        auto error_msg = std::string("[ExpressionParser] Bad numeric input: ") + std::to_string(elements_stack.top()) + ch;
        throw std::invalid_argument(error_msg);
      }
      elements_stack.emplace(static_cast<short>(ch) - static_cast<short>('0')); // ASCII char to int
    } else if(is_operator(ch)) {
      if (elements_stack.size() == 0) {
        auto error_msg = std::string("[ExpressionParser] Duplicated operator or negative element are not allowed: ") + ch;
        throw std::invalid_argument(error_msg);
      }
      local_tree.add_operator(ch);
      auto element = elements_stack.top();
      elements_stack.pop();
      local_tree.add_element(element);
    } else {
      throw std::invalid_argument(std::string("[ExpressionParser] bad input: ") + ch);
    }
  }
  // add last element
  if (elements_stack.size() > 0) {
    auto element = elements_stack.top();
    elements_stack.pop();
    local_tree.add_element(element);
  } else {
    throw std::invalid_argument("[ExpressionParser] Operator at the end of expression");
  }

  return local_tree;
}

std::string ExpressionParser::remove_whitespaces(const std::string &str) {
  std::string new_str = str;
  new_str.erase(
    std::remove_if(new_str.begin(), new_str.end(),
      [](char c){
        return (c =='\r' || c =='\t' || c == ' ' || c == '\n');
      }), new_str.end());
  return new_str;
}

bool ExpressionParser::is_element(char ch) {
  if (ch < '0' || ch > '9')
    return false;

  return true;
}

bool ExpressionParser::is_operator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    return true;
  return false;
}
