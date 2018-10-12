#pragma once

#include <map>
#include <utility>

using arithmetic_func = int (*)(short, short);

// define arithmetic operators with its priorities and functions
const std::map<char, std::pair<int, arithmetic_func>> Operators {
  { '/', { 2, [](short x, short y){ return x / y; }}},  // division
  { '*', { 2, [](short x, short y){ return x * y; }}},  // multiplication
  { '+', { 1, [](short x, short y){ return x + y; }}},  // addition
  { '-', { 1, [](short x, short y){ return x - y; }}}   // subtraction
};

// define special operators with its priorities
const std::map<char, int> SpecialOperators {
  { '(', 3 },  // left_parenthesis
  { ')', -3 }, // right_parenthesis
};

class ArithmeticOperator {
public:
  ArithmeticOperator() = delete;
  ArithmeticOperator(char ch, int increased_priority = 0);

  char get_operator() const;
  int get_priority() const;

  int execute(short x, short y) const;
private:
  char _op;
  int _priority;
};

std::ostream& operator<<(std::ostream &os, const ArithmeticOperator &rhs);
