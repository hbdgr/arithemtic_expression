#include <stdexcept>
#include "simple_custom_variant.hpp"
#include "utils.hpp"


SimpleCustomVariant::SimpleCustomVariant() :
  m_empty(true),
  m_hold_operator(false)
  {}

SimpleCustomVariant::SimpleCustomVariant(int ele) :
  m_hold_operator(false),
  m_element(ele)
  {}

SimpleCustomVariant::SimpleCustomVariant(ArithmeticOperator op) :
  m_hold_operator(true),
  m_arithmetic_operator(std::make_unique<ArithmeticOperator>(op))
  {}

SimpleCustomVariant::SimpleCustomVariant(const SimpleCustomVariant &rhs) :
  m_empty(rhs.m_empty),
  m_hold_operator(rhs.m_hold_operator)
  {
    if (m_hold_operator) {
      m_arithmetic_operator = std::make_unique<ArithmeticOperator>(*rhs.m_arithmetic_operator);
    } else if (!m_empty) {
      m_element = rhs.m_element;
    }
  }

SimpleCustomVariant& SimpleCustomVariant::operator=(const SimpleCustomVariant &rhs) {
  m_empty = rhs.m_empty;
  m_hold_operator = rhs.m_hold_operator;

  if (m_hold_operator) {
    m_arithmetic_operator = std::make_unique<ArithmeticOperator>(*rhs.m_arithmetic_operator);
  } else if (!m_empty) {
    m_element = rhs.m_element;
  }
  return *this;
}

SimpleCustomVariant& SimpleCustomVariant::operator=(int rhs) {
  m_empty = false;
  m_hold_operator = false;
  m_arithmetic_operator = nullptr;
  m_element = rhs;

  return *this;
}

bool SimpleCustomVariant::empty() const {
  return m_empty;
}

bool SimpleCustomVariant::hold_operator() const {
  return m_hold_operator;
}

int SimpleCustomVariant::get_element() const {
  if (!m_empty && !m_hold_operator) {
    return m_element;
  }
  throw std::runtime_error("[SimpleCustomVariant] does not hold element!");
}

ArithmeticOperator SimpleCustomVariant::get_arithmetic_operator() const {
  if (m_hold_operator) {
    return *m_arithmetic_operator;
  }
  throw std::runtime_error("[SimpleCustomVariant] does not hold ArithmeticOperator!");
}
