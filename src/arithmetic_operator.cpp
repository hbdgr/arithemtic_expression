#include <stdexcept>
#include <ostream>
#include "arithmetic_operator.hpp"


ArithmeticOperator::ArithmeticOperator(char ch, int increased_priority) {
  if (Operators.count(ch)) {
    // save operator
    _op = ch;
  } else {
    throw std::runtime_error(std::string("[ArithmeticOperator] Unsupported operator for arithmetic operations: ") + ch);
  }

  // add _priority from operator priorities map, optional increased_priority
  _priority = Operators.at(ch).first + increased_priority;
}

char ArithmeticOperator::get_operator() const {
  return _op;
}

int ArithmeticOperator::get_priority() const {
  return _priority;
}

int ArithmeticOperator::execute(short x, short y) const {
  if (_op == '/' && y == 0) {
    throw std::overflow_error("Divide by zero!");
  }
  return Operators.at(_op).second(x, y);
}

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs) {
  os << rhs.get_operator();
  return os;
}
