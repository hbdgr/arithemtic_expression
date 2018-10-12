#include <algorithm>
#include <stdexcept>
#include "expression_parser.hpp"
#include "arithmetic_operator.hpp"


SyntaxTree ExpressionParser::generateTree(const std::string &expression) {
  auto formatted_expression = remove_whitespaces(expression);
  if (formatted_expression.length() == 0) {
    throw std::invalid_argument(std::string("[ExpressionParser] Empty expression"));
  }
  return consume_expression(std::move(formatted_expression));
}

SyntaxTree ExpressionParser::consume_expression(std::string &&formatted_expression) {
  std::stack<short> elements_stack;
  SyntaxTree local_tree = SyntaxTree();

  int increased_priority= 0;

  for (auto ch : formatted_expression) {
    if (is_element(ch)) {
      // throw if stack is not empty, it means that numeric value > 9 was found in expression
      push_to_stack_if_empty(elements_stack, ch);
    } else if(is_operator(ch)) {
      local_tree.add_operator(ArithmeticOperator(ch, increased_priority));
      // will throw error if stack is empty, it means that duplicated operator or negative element was found
      insert_element_from_stack(elements_stack, local_tree);
    } else if (is_lparanthes(ch)){
      increased_priority += 3;
    } else if (is_rparanthes(ch)){
      increased_priority -= 3;
    } else {
      throw std::invalid_argument(std::string("[ExpressionParser] Bad input char: ") + ch);
    }
  }
  // add last element - throw exception if operator at the end of expression was found.
  insert_element_from_stack(elements_stack, local_tree);

  if (increased_priority != 0) {
    throw std::invalid_argument(std::string("[ExpressionParser] Missing parentheses!"));
  }

  return local_tree;
}

void ExpressionParser::push_to_stack_if_empty(std::stack<short> &stack, char ch) {
  if (stack.size() > 0) {
    auto error_msg = std::string("[ExpressionParser] Bad numeric input: ") + std::to_string(stack.top()) + ch;
    throw std::invalid_argument(error_msg);
  }
  stack.emplace(static_cast<short>(ch) - static_cast<short>('0')); // ASCII char to int
}

void ExpressionParser::insert_element_from_stack(std::stack<short> &stack, SyntaxTree &tree) {
  if (stack.size() > 0) {
    auto element = stack.top();
    stack.pop();
    tree.add_element(element);
  } else {
    throw std::invalid_argument("[ExpressionParser] Can not insert from empty stack");
  }
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

bool ExpressionParser::is_lparanthes(char ch) {
  if (ch == '(' )
    return true;
  return false;
}

bool ExpressionParser::is_rparanthes(char ch) {
  if (ch == ')' )
    return true;
  return false;
}
