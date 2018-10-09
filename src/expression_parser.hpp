#pragma once

#include "syntax_tree.hpp"


class ExpressionParser {
public:
  static SyntaxTree generateTree(const std::string &expression) {
    SyntaxTree local_tree = SyntaxTree();
    for (auto ch : expression) {
        local_tree.add_element(static_cast<int>(ch) - static_cast<int>('0'));
    }

    return local_tree;
  }
};
