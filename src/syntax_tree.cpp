#include <stdexcept>
#include "syntax_tree.hpp"


SyntaxTree::SyntaxTree() :
  m_is_empty(true) {}

SyntaxTree::SyntaxTree(int element) :
  m_data(element) {}

SyntaxTree::SyntaxTree(const ArithmeticOperator &op, SyntaxTree *parent) :
  m_data(op),
  m_parent(parent)
  {}

SyntaxTree::SyntaxTree(SyntaxTree *parent) :
  m_is_empty(parent -> m_is_empty),
  m_data(parent -> m_data),
  m_parent(parent),
  m_left_child(std::move(parent -> m_left_child)),
  m_right_child(std::move(parent -> m_right_child))
  {}


SyntaxTree::SyntaxTree(SyntaxTree &&rhs) noexcept :
  m_is_empty(rhs.m_is_empty),
  m_data(rhs.m_data),
  m_parent(rhs.m_parent),
  m_left_child(std::move(rhs.m_left_child)),
  m_right_child(std::move(rhs.m_right_child))
  {}


void SyntaxTree::add_element(int num) {
  if (m_is_empty) {
    // Adding element to myself
    m_is_empty = false;
    m_data = num;
    return;
  }

  if (add_element_to_child(m_left_child, num)) {
    return;
  }

  if (add_element_to_child(m_right_child, num)) {
    return;
  }

  if (m_parent != nullptr) {
    // Move add_elemnet decision back to parent
    m_parent -> add_element(num);
  } else {
    throw std::runtime_error("[SyntaxTree] Unexpected add_element, bad tree format!");
  }
}

bool SyntaxTree::add_element_to_child(std::unique_ptr<SyntaxTree> &child, int num) {
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
  if (m_is_empty) {
    // Adding operator to myself
    m_is_empty = false;
    m_data = SimpleCustomVariant(new_op);
    return;
  }

  if (m_data.hold_operator()) {
    add_priority_operator(m_data.get_arithmetic_operator(), new_op);
    return;
  }

  if (m_left_child == nullptr) {
    // Add operator to left_child
    m_left_child = std::make_unique<SyntaxTree>(new_op);
    return;
  }

  if (m_right_child == nullptr) {
    // Add operator to right_child
    m_right_child = std::make_unique<SyntaxTree>(new_op);
    return;
  }

  throw std::runtime_error("[SyntaxTree] Unexpected add_operator, bed tree format!");
}

void SyntaxTree::add_priority_operator(const ArithmeticOperator &actual_op, const ArithmeticOperator &new_op) {

  if (new_op.get_priority() > actual_op.get_priority()) {
    // Bigger priority
    if (m_right_child == nullptr) {
      // Add operator to right_child
      m_right_child = std::make_unique<SyntaxTree>(new_op, this);
      return;
    }

    if (m_right_child -> get_data().hold_operator()) {
      // Move add_operator decision to right child
      m_right_child -> add_operator(new_op);
      return;
    }

    throw std::runtime_error("[SyntaxTree] add_operator right child occupied with element!");
  } else {
    // Normal (Lower or equal) priority as parent, set this to left child
    m_left_child = std::make_unique<SyntaxTree>(this);
    m_data = SimpleCustomVariant(new_op);
  }
}

SimpleCustomVariant SyntaxTree::get_data() const {
  return m_data;
}

void SyntaxTree::update_data(int element) {
  if (m_data.hold_operator()) {
    m_data = element;
  } else {
    throw std::runtime_error("[SyntaxTree] Update data is allowed only for node holing operator");
  }
}

bool SyntaxTree::have_space_for_child() const {
  if (m_left_child == nullptr || m_right_child == nullptr) {
    return true;
  } else {
    if (m_left_child -> get_data().hold_operator() && m_left_child -> have_space_for_child()) {
      return true;
    }
    if (m_right_child -> get_data().hold_operator() && m_right_child -> have_space_for_child()) {
      return true;
    }
  }
  return false;
}

SyntaxTree* SyntaxTree::get_parent() const {
  return m_parent;
}

SyntaxTree* SyntaxTree::get_left_child() const {
  return m_left_child.get();
}

SyntaxTree* SyntaxTree::get_right_child() const {
  return m_right_child.get();
}
