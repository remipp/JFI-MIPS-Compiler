#include <iostream>
#include <fstream>
#include <streambuf>

#include "lexer.h"
#include "parser.h"
#include "codeGenerator.h"
#include "ast.h"

#include "debug.h"

int main(int argc, char** argv) {
	if (argc < 3) 
	{
		std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << '\n';
		exit(-1);
	}

	//Create file handle and get contents as std::string
	std::ifstream inFile(argv[1]);
	std::string str((std::istreambuf_iterator<char>(inFile)),
			std::istreambuf_iterator<char>());
	inFile.close();

	//Tokenize the C code
	std::cout << "Lexer: " << std::endl;
	Lexer l(str);
	for (auto a : l.tokens)
		std::cout << a << std::endl;
	std::cout << std::endl;

	//Parse tokenization into AST
	std::cout << "Parser: " << std::endl;
	Node* ast = generateAST(l.tokens);
	std::cout << *ast << std::endl;

	//Generate code
	std::string code = generateCode(ast);
	std::cout << "Code:" << std::endl;
	std::cout << code << std::endl;

	//Write code to output file
	std::ofstream outFile(argv[2]);
	outFile << code;
	outFile.close();

	std::cout << "Compilation finished" << std::endl;

	return 0;
}
