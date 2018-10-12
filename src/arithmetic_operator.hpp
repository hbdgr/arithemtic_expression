#pragma once

#include <map>


// define operators
enum class Operator : unsigned char {
  division,
  multiplication,
  addition,
  subtraction,
};

// define Operators priority
const std::map<Operator, int> Op_priorities {
  { Operator::division, 2 },
  { Operator::multiplication, 2 },
  { Operator::addition, 1 },
  { Operator::subtraction, 1 }
};


class ArithmeticOperator {
public:
  ArithmeticOperator() = delete;
  ArithmeticOperator(char ch);
  ArithmeticOperator(Operator op);

  Operator get_operator() const;
  int get_priority() const;

  int execute(short x, short y) const;
private:
  Operator _op;
  int _priority;
};

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs);
