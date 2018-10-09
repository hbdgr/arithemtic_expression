#include <iostream>
#include "syntax_tree.hpp"


void SyntaxTree::add_element(int num) {
  m_data.push_back(num);
}

int SyntaxTree::pop_element() {
  int ele = m_data.back();
  m_data.pop_back();
  return ele;
}
