#include <iostream>
#include "expression_parser.hpp"

int main() {
	Syntax_Tree tree = Syntax_Tree();
	std::cout << "tree: " << tree.print_hello() << std::endl;

	return 0;
}
