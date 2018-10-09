#include <stdexcept>
#include "syntax_tree.hpp"


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
