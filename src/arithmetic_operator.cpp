#include <stdexcept>
#include <ostream>
#include "arithmetic_operator.hpp"


ArithmeticOperator::ArithmeticOperator(Operator op, int increased_priority) :
  _op(op),
  _priority(Op_priorities.at(op) + increased_priority)
  {}

ArithmeticOperator::ArithmeticOperator(char ch, int increased_priority) {
  switch (ch) {
    case '+':
      _op = Operator::addition;
      break;
    case '-':
      _op = Operator::subtraction;
      break;
    case '*':
      _op = Operator::multiplication;
      break;
    case '/':
      _op = Operator::division;
      break;
    default:
      throw std::runtime_error(std::string("[ArithmeticOperator] Unknown operator: ") + ch);
  }
  // add _priority from operator priorities map, optional increased_priority
  _priority = Op_priorities.at(_op) + increased_priority;
}

Operator ArithmeticOperator::get_operator() const {
  return _op;
}

int ArithmeticOperator::get_priority() const {
  return _priority;
}

int ArithmeticOperator::execute(short x, short y) const {
  switch (_op) {
    case Operator::addition:
      return x + y;
    case Operator::subtraction:
      return x - y;
    case Operator::multiplication:
      return x * y;
    case Operator::division: {
      if (y == 0) {
        throw std::overflow_error("Divide by zero!");
      }
      return x / y;
    }
  }
}

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs) {
  switch (rhs.get_operator()) {
    case Operator::addition:
      os << "addition";
      break;
    case Operator::subtraction:
      os << "subtraction";
      break;
    case Operator::multiplication:
      os << "multiplication";
      break;
    case Operator::division:
      os << "division";
      break;
    }

    return os;
}
