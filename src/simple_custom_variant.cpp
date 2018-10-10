#include <stdexcept>
#include "simple_custom_variant.hpp"
#include "utils.hpp"


SimpleCustomVariant::SimpleCustomVariant() :
  _empty(true),
  _hold_operator(false)
  {}

SimpleCustomVariant::SimpleCustomVariant(short ele) :
  _hold_operator(false),
  _element(ele)
  {}

SimpleCustomVariant::SimpleCustomVariant(ArithmeticOperator op) :
  _hold_operator(true),
  _arithmetic_operator(std::make_unique<ArithmeticOperator>(op))
  {}

SimpleCustomVariant::SimpleCustomVariant(const SimpleCustomVariant &rhs) :
  _empty(rhs._empty),
  _hold_operator(rhs._hold_operator)
  {
    if (_hold_operator) {
      _arithmetic_operator = std::make_unique<ArithmeticOperator>(*rhs._arithmetic_operator);
    } else if (!_empty) {
      _element = rhs._element;
    }
  }

SimpleCustomVariant& SimpleCustomVariant::operator=(const SimpleCustomVariant &rhs) {
  _empty = rhs._empty;
  _hold_operator = rhs._hold_operator;

  if (_hold_operator) {
    _arithmetic_operator = std::make_unique<ArithmeticOperator>(*rhs._arithmetic_operator);
  } else if (!_empty) {
    _element = rhs._element;
  }
  return *this;
}

SimpleCustomVariant& SimpleCustomVariant::operator=(short rhs) {
  _empty = false;
  _hold_operator = false;
  _arithmetic_operator = nullptr;
  _element = rhs;

  return *this;
}

bool SimpleCustomVariant::empty() const {
  return _empty;
}

bool SimpleCustomVariant::hold_operator() const {
  return _hold_operator;
}

short SimpleCustomVariant::get_element() const {
  if (!_empty && !_hold_operator) {
    return _element;
  }
  throw std::runtime_error("[SimpleCustomVariant] does not hold element!");
}

ArithmeticOperator SimpleCustomVariant::get_arithmetic_operator() const {
  if (_hold_operator) {
    return *_arithmetic_operator;
  }
  throw std::runtime_error("[SimpleCustomVariant] does not hold ArithmeticOperator!");
}
