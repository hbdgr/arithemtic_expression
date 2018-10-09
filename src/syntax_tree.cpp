#include <iostream>
#include <stdexcept>
#include "syntax_tree.hpp"
#include "utils.hpp"

ArithmeticOperator::ArithmeticOperator(char ch) {
  switch (ch) {
    case '+':
      _op = Operator::addition;
      break;
    case '-':
      _op = Operator::subtraction;
      break;
    case '*':
      _op = Operator::multiplication;
      break;
    case '/':
      _op = Operator::division;
      break;
    default:
      throw std::runtime_error(std::string("[ArithmeticOperator] Unknown operator: ") + ch);
  }
}

int ArithmeticOperator::execute(short x, short y) const {
  switch (_op) {
    case Operator::addition:
      return x + y;
    case Operator::subtraction:
      return x - y;
    case Operator::multiplication:
      return x * y;
    case Operator::division:
      return x / y;
    case Operator::none:
    default:
      throw std::runtime_error(std::string("[ArithmeticOperator] Should not happen bad op:"));
  }
}


void SyntaxTree::add_element(short num) {
  if (_is_empty) {
    _is_empty = false;
    _data = num;
  } else if (_left_child == nullptr) {
    _left_child = std::make_unique<SyntaxTree>(num);
  } else if (_right_child == nullptr) {
    _right_child = std::make_unique<SyntaxTree>(num);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] add_element not fully implemented!"));
  }
}

void SyntaxTree::add_operator(char ch) {
  if (_is_empty) {
    _is_empty = false;
    _data = ArithmeticOperator(ch);
  } else if (_left_child == nullptr) {
    _left_child = std::make_unique<SyntaxTree>(ch);
  } else if (_right_child == nullptr) {
    _right_child = std::make_unique<SyntaxTree>(ch);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] add_operator not fully implemented!"));
  }
}
