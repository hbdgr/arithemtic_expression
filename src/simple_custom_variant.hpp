#pragma once

#include <memory>
#include "arithmetic_operator.hpp"


class SimpleCustomVariant {
public:
  SimpleCustomVariant();
  SimpleCustomVariant(short ele);
  SimpleCustomVariant(ArithmeticOperator op);
  SimpleCustomVariant(const SimpleCustomVariant &rhs);

  SimpleCustomVariant& operator=(const SimpleCustomVariant &rhs);
  SimpleCustomVariant& operator=(short rhs);

  bool empty() const;
  bool hold_operator() const;
  short get_element() const;
  ArithmeticOperator get_arithmetic_operator() const;

private:
  bool _empty = false;
  bool _hold_operator = false;
  short _element;
  std::unique_ptr<ArithmeticOperator> _arithmetic_operator = nullptr;
};
