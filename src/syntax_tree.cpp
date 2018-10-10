#include <stdexcept>
#include "syntax_tree.hpp"


SyntaxTree::SyntaxTree() :
  _is_empty(true) {}

SyntaxTree::SyntaxTree(short element) :
  _data(element) {}

SyntaxTree::SyntaxTree(char ch) :
  _data(ArithmeticOperator(ch)) {}

SyntaxTree::SyntaxTree(SyntaxTree *parent, SimpleCustomVariant data) :
  _data(data),
  _parent(parent),
  _left_child(std::move(parent -> _left_child)),
  _right_child(std::move(parent -> _right_child))
  {}

SyntaxTree::SyntaxTree(SyntaxTree &&rhs) :
  _is_empty(rhs._is_empty),
  _data(std::move(rhs._data)),
  _parent(std::move(rhs._parent)),
  _left_child(std::move(rhs._left_child)),
  _right_child(std::move(rhs._right_child)) {}


void SyntaxTree::add_element(short num) {
  if (_is_empty) {
    _is_empty = false;
    _data = num;
  } else if (_left_child == nullptr) {
    // Adding element to left child
    _left_child = std::make_unique<SyntaxTree>(num);
  } else if (_left_child -> get_data().hold_operator() && _left_child -> have_space_for_child()) {
    // Move add_element decision to left child
    _left_child -> add_element(num);
  } else if (_right_child == nullptr) {
    // Adding element to right child
    _right_child = std::make_unique<SyntaxTree>(num);
  } else if (_parent != nullptr) {
    // Move add_elemnet back to parent"
    _parent -> add_element(num);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] add_element not fully implemented!"));
  }
}

void SyntaxTree::add_operator(char ch) {
  if (_is_empty) {
    _is_empty = false;
    _data = ArithmeticOperator(ch);
  } else if (_data.hold_operator()) {
    _left_child = std::make_unique<SyntaxTree>(SyntaxTree(this, _data));
    _data = ArithmeticOperator(ch);
  } else if (_left_child == nullptr) {
    _left_child = std::make_unique<SyntaxTree>(ch);
  } else if (_right_child == nullptr) {
    _right_child = std::make_unique<SyntaxTree>(ch);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] add_operator not fully implemented!"));
  }
}

SimpleCustomVariant SyntaxTree::get_data() const {
  return _data;
}

void SyntaxTree::update_data(short element) {
  if (_data.hold_operator()) {
    _data = element;
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] Update data is allowed only for node holing operator"));
  }
}

bool SyntaxTree::have_space_for_child() const {
  if (_left_child == nullptr || _right_child == nullptr) {
    return true;
  } else {
    if (_left_child -> get_data().hold_operator() && _left_child -> have_space_for_child()) {
      return true;
    }
    if (_right_child -> get_data().hold_operator() && _right_child -> have_space_for_child()) {
      return true;
    }
  }
  return false;
}

SyntaxTree* SyntaxTree::get_parent() const {
  return _parent;
}

SyntaxTree* SyntaxTree::get_left_child() const {
  return _left_child.get();
}

SyntaxTree* SyntaxTree::get_right_child() const {
  return _right_child.get();
}
