#include <algorithm>
#include <stdexcept>
#include "expression_parser.hpp"
#include "arithmetic_operator.hpp"


SyntaxTree ExpressionParser::generateTree(const std::string &expression) {
  auto formatted_expression = remove_whitespaces(expression);
  if (formatted_expression.empty()) {
    throw std::invalid_argument("[ExpressionParser] Empty expression");
  }
  return consume_expression(std::move(formatted_expression));
}

SyntaxTree ExpressionParser::consume_expression(const std::string &formatted_expression) {
  SyntaxTree local_tree = SyntaxTree();

  for (const auto &ch : formatted_expression) {
    if (is_element(ch)) {
      // throw if stack is not empty, it means that numeric value > 9 was found in expression
      push_to_stack_if_empty(ch);
    }
    else if(Operators.count(ch)) {
        local_tree.add_operator(ArithmeticOperator(ch, m_increased_priority));
        // will throw error if stack is empty, it means that duplicated operator or negative element was found
        insert_element_from_stack(local_tree);
    } else if (SpecialOperators.count(ch)) {
      m_increased_priority += SpecialOperators.at(ch); // '(' or ')'
      if (m_increased_priority < 0) {
        // right parenthesis without its left pair
        throw std::invalid_argument(std::string("[ExpressionParser] Negative increased priority not allowed: ") + ch);
      }
    } else {
      throw std::invalid_argument(std::string("[ExpressionParser] Bad input char: ") + ch);
    }
  }

  // check post-conditions, require elements_stack empty and increased_priority equal 0
  // add last element - throw exception if operator at the end of expression was found.
  insert_element_from_stack(local_tree);

  if (m_increased_priority != 0) {
    throw std::invalid_argument("[ExpressionParser] Missing parentheses!");
  }

  return local_tree;
}

void ExpressionParser::push_to_stack_if_empty(char ch) {
  if (!m_elements_stack.empty()) {
    auto error_msg = std::string("[ExpressionParser] Bad numeric input: ") + std::to_string(m_elements_stack.top()) + ch;
    throw std::invalid_argument(error_msg);
  }
  m_elements_stack.emplace(static_cast<int>(ch) - static_cast<int>('0')); // ASCII char to int
}

void ExpressionParser::insert_element_from_stack(SyntaxTree &tree) {
  if (!m_elements_stack.empty()) {
    auto element = m_elements_stack.top();
    m_elements_stack.pop();
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
