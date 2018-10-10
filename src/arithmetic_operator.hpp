#pragma once


// deifine operators enum with thier priority
enum class Operator : unsigned char {
  division = 0x01,
  multiplication = 0x02,
  addition = 0x03,
  subtraction = 0x04,
};

class ArithmeticOperator {
public:
  ArithmeticOperator() = delete;
  ArithmeticOperator(char ch);
  ArithmeticOperator(Operator op);

  Operator get_operator() const;

  int execute(short x, short y) const;
private:
  Operator _op;
};

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs);
