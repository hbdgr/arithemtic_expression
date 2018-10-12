#pragma once

#include <map>


// define operators
enum class Operator : char {
  division = '/',
  multiplication = '*',
  addition = '+',
  subtraction = '-',
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
  ArithmeticOperator(char ch, int increased_priority = 0);
  ArithmeticOperator(Operator op, int increased_priority = 0);

  Operator get_operator() const;
  int get_priority() const;

  int execute(short x, short y) const;
private:
  Operator _op;
  int _priority;
};

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs);
