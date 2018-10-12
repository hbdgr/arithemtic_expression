#include <stdexcept>
#include "syntax_tree.hpp"


SyntaxTree::SyntaxTree() :
  _is_empty(true) {}

SyntaxTree::SyntaxTree(short element) :
  _data(element) {}

SyntaxTree::SyntaxTree(const ArithmeticOperator &op, SyntaxTree *parent) :
  _data(op),
  _parent(parent)
  {}

SyntaxTree::SyntaxTree(SyntaxTree *parent) :
  _is_empty(parent -> _is_empty),
  _data(parent -> _data),
  _parent(parent),
  _left_child(std::move(parent -> _left_child)),
  _right_child(std::move(parent -> _right_child))
  {}


SyntaxTree::SyntaxTree(SyntaxTree &&rhs) noexcept :
  _is_empty(rhs._is_empty),
  _data(rhs._data),
  _parent(rhs._parent),
  _left_child(std::move(rhs._left_child)),
  _right_child(std::move(rhs._right_child))
  {}


void SyntaxTree::add_element(short num) {
  if (_is_empty) {
    // Adding element to myself
    _is_empty = false;
    _data = num;
    return;
  }

  if (add_element_to_child(_left_child, num)) {
    return;
  }

  if (add_element_to_child(_right_child, num)) {
    return;
  }

  if (_parent != nullptr) {
    // Move add_elemnet decision back to parent
    _parent -> add_element(num);
  } else {
    throw std::runtime_error(std::string("[SyntaxTree] Unexpected add_element, bad tree format!"));
  }
}

bool SyntaxTree::add_element_to_child(std::unique_ptr<SyntaxTree> &child, short num) {
  if (child == nullptr) {
    // Adding element to left child
    child = std::make_unique<SyntaxTree>(num);
    return true;
  }
  if (child -> get_data().hold_operator() && child -> have_space_for_child()) {
    // Move add_element decision to left child
    child -> add_element(num);
    return true;
  }
  return false;
}


void SyntaxTree::add_operator(const ArithmeticOperator &new_op) {
  if (_is_empty) {
    // Adding operator to myself
    _is_empty = false;
    _data = new_op;
    return;
  }

  if (_data.hold_operator()) {
    add_priority_operator(_data.get_arithmetic_operator(), new_op);
    return;
  }

  if (_left_child == nullptr) {
    // Add operator to left_child
    _left_child = std::make_unique<SyntaxTree>(new_op);
    return;
  }

  if (_right_child == nullptr) {
    // Add operator to right_child
    _right_child = std::make_unique<SyntaxTree>(new_op);
    return;
  }

  throw std::runtime_error(std::string("[SyntaxTree] Unexpected add_operator, bed tree format!"));
}

void SyntaxTree::add_priority_operator(const ArithmeticOperator &actual_op, const ArithmeticOperator &new_op) {

  if (new_op.get_priority() > actual_op.get_priority()) {
    // Bigger priority
    if (_right_child == nullptr) {
      // Add operator to right_child
      _right_child = std::make_unique<SyntaxTree>(new_op, this);
      return;
    }

    if (_right_child -> get_data().hold_operator()) {
      // Move add_operator decision to right child
      _right_child -> add_operator(new_op);
      return;
    }

    throw std::runtime_error(std::string("[SyntaxTree] add_operator right child occupied with element!"));
  } else {
    // Normal (Lower or equal) priority as parent, set this to left child
    _left_child = std::make_unique<SyntaxTree>(SyntaxTree(this));
    _data = new_op;
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
