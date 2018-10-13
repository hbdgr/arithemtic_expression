#include <stdexcept>
#include <ostream>
#include "arithmetic_operator.hpp"


ArithmeticOperator::ArithmeticOperator(char ch, int increased_priority) {
  if (Operators.count(ch)) {
    // save operator
    m_op = ch;
  } else {
    throw std::runtime_error(std::string("[ArithmeticOperator] Unsupported operator for arithmetic operations: ") + ch);
  }

  // add m_priority from operator priorities map, optional increased_priority
  m_priority = Operators.at(ch).first + increased_priority;
}

char ArithmeticOperator::get_operator() const {
  return m_op;
}

int ArithmeticOperator::get_priority() const {
  return m_priority;
}

int ArithmeticOperator::execute(int x, int y) const {
  if (m_op == '/' && y == 0) {
    throw std::overflow_error("Divide by zero!");
  }
  return Operators.at(m_op).second(x, y);
}

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs) {
  os << rhs.get_operator();
  return os;
}
