#include <stdexcept>
#include "syntax_tree.hpp"


SyntaxTree::SyntaxTree() :
  _is_empty(true) {}

SyntaxTree::SyntaxTree(short element) :
  _data(element) {}

SyntaxTree::SyntaxTree(const ArithmeticOperator &op, SyntaxTree *parent) :
  _parent(parent),
  _data(op)
  {}

SyntaxTree::SyntaxTree(SyntaxTree *parent, const SimpleCustomVariant &data) :
  _data(data),
  _parent(parent),
  _left_child(std::move(parent -> _left_child)),
  _right_child(std::move(parent -> _right_child))
  {}

// move whole tree
SyntaxTree::SyntaxTree(SyntaxTree &&rhs) :
  _is_empty(rhs._is_empty),
  _data(std::move(rhs._data)),
  _parent(std::move(rhs._parent)),
  _left_child(std::move(rhs._left_child)),
  _right_child(std::move(rhs._right_child)) {}


void SyntaxTree::add_element(short num) {
  if (_is_empty) {
    // Adding element to myself
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
  } else if (_right_child -> get_data().hold_operator() && _right_child -> have_space_for_child()) {
    // Move add_element decision to right child"
    _right_child -> add_element(num);
  } else if (_parent != nullptr) {
    // Move add_elemnet decision back to parent
    _parent -> add_element(num);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] Unexpected add_element, bad tree format!"));
  }
}

void SyntaxTree::add_operator(char ch) {
  if (_is_empty) {
    // Adding operator to myself
    _is_empty = false;
    _data = ArithmeticOperator(ch);
  } else if (_data.hold_operator()) {
    auto actual_operator = _data.get_arithmetic_operator();
    auto new_operator = ArithmeticOperator(ch);

    if (new_operator.get_priority() > actual_operator.get_priority()) {
      // Bigger priority add_operator
      if (_right_child == nullptr) {
        // Add operator to right_child
        _right_child = std::make_unique<SyntaxTree>(new_operator, this);
      } else if (_right_child -> get_data().hold_operator()) {
        // Move add_operator decision to right child
        _right_child -> add_operator(ch);
      } else {
        throw std::runtime_error(std::string("[SyntaxTree] add_operator right child occupied with element!"));
      }
    } else {
      // Normal priority add operator as parent, this to left child
      _left_child = std::make_unique<SyntaxTree>(SyntaxTree(this, _data));
      _data = new_operator;
    }
  } else if (_left_child == nullptr) {
    // Add operator to left_child
    _left_child = std::make_unique<SyntaxTree>(ch);
  } else if (_right_child == nullptr) {
    // Add operator to right_child
    _right_child = std::make_unique<SyntaxTree>(ch);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] Unexpected add_operator, bed tree format!"));
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
