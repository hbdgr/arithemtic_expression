#include <catch2/catch.hpp>
#include <expression_parser.hpp>

TEST_CASE("Syntax_Tree hello") {
	Syntax_Tree tree = Syntax_Tree();
	REQUIRE(tree.print_hello() == "syntax_hello!");
}
