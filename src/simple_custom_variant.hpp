#pragma once

#include <memory>
#include "arithmetic_operator.hpp"


class SimpleCustomVariant {
public:
  SimpleCustomVariant();
  explicit SimpleCustomVariant(int ele);
  explicit SimpleCustomVariant(ArithmeticOperator op);
  SimpleCustomVariant(const SimpleCustomVariant &rhs);

  SimpleCustomVariant& operator=(const SimpleCustomVariant &rhs);
  SimpleCustomVariant& operator=(int rhs);

  bool empty() const;
  bool hold_operator() const;
  int get_element() const;
  ArithmeticOperator get_arithmetic_operator() const;

private:
  bool m_empty = false;
  bool m_hold_operator = false;
  int m_element;
  std::unique_ptr<ArithmeticOperator> m_arithmetic_operator = nullptr;
};
