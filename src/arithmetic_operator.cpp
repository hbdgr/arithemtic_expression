#include <stdexcept>
#include "arithmetic_operator.hpp"


ArithmeticOperator::ArithmeticOperator(Operator op) : _op(op) {}

ArithmeticOperator::ArithmeticOperator(char ch) {
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
}

int ArithmeticOperator::execute(short x, short y) const {
  switch (_op) {
    case Operator::addition:
      return x + y;
    case Operator::subtraction:
      return x - y;
    case Operator::multiplication:
      return x * y;
    case Operator::division:
      return x / y;
    }
  //  default:
    //  throw std::runtime_error(std::string("[ArithmeticOperator] Should not happen bad op"));
}
