#pragma once

#include <string>
#include <vector>


class SyntaxTree {
public:
  void add_element(int num);
  int pop_element();

private:
  std::vector<int> m_data;
};
