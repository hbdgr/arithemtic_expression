#pragma once
#include <iostream>

#include <string>
#include <memory>


// deifine operators enum with thier priority
enum class Operator : unsigned char {
  division = 0x01,
  multiplication = 0x02,
  addition = 0x03,
  subtraction = 0x04,
  none = 0x05,
};

class ArithmeticOperator {
public:
  ArithmeticOperator() = delete;
  ArithmeticOperator(char ch);
  ArithmeticOperator(Operator op) : _op(op) {}

  int execute(short x, short y) const;
private:

  Operator _op;
};


struct SimpleCustomVariant {
  SimpleCustomVariant() :
    is_empty(true),
    hold_operator(false),
    arithmetic_operator(Operator::none)
      {};

  SimpleCustomVariant(short ele) :
    hold_operator(false),
    arithmetic_operator(Operator::none),
    element(ele)
      {};

  SimpleCustomVariant(ArithmeticOperator op) :
    hold_operator(true),
    arithmetic_operator(op)
      {};

  bool is_empty = false;
  bool hold_operator = false;
  ArithmeticOperator arithmetic_operator;
  short element;
};


class SyntaxTree {
public:
  SyntaxTree() : _is_empty(true) {}
  SyntaxTree(short element) : _data(element) {}
  SyntaxTree(char ch) : _data(ArithmeticOperator(ch)) {}

  void add_element(short element);
  void add_operator(char ch);

  SimpleCustomVariant get_data() const {
    return _data;
  }

  int evaluate() {
    if (_data.hold_operator) {
      return _data.arithmetic_operator
        .execute(_left_child -> get_data().element, _right_child -> get_data().element);
    } else if (_data.is_empty) {
      throw std::runtime_error(std::string("[SyntaxTree] Can not evaluate empty tree"));
    }
    else {
      return _data.element;
    }
  }
private:
  bool _is_empty = false;
  // std::variant from c++17 or at least from boost would be great here
  // std::variant<ArithmeticOperator, short> _data;
  SimpleCustomVariant _data;

  std::unique_ptr<SyntaxTree> _parent = nullptr;
  std::unique_ptr<SyntaxTree> _left_child = nullptr;
  std::unique_ptr<SyntaxTree> _right_child = nullptr;
};
