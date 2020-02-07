#include "lexer.h"
#include "parser.h"
#include "ast.h"

#include "debug.h"

#include <iostream>
#include <fstream>
#include <streambuf>

int main(int argc, char** argv) {
	if (argc < 2) {
		exit(-1);
	}

	std::ifstream f(argv[1]);
	std::string str((std::istreambuf_iterator<char>(f)),
			std::istreambuf_iterator<char>());

	std::cout << "Lexer: " << std::endl;
	Lexer l(str);
	for (auto a : l.tokens) {
		std::cout << a.s << " " << (int)a.type << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Parser: " << std::endl;
	Node* ast = generateAST(l.tokens);
	std::cout << *ast << std::endl;
}
