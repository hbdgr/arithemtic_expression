#pragma once


// deifine operators
enum class Operator : unsigned char {
  division,
  multiplication,
  addition,
  subtraction,
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
