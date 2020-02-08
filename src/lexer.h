#pragma once

#include <string>
#include <map>
#include <vector>

#include "token.h"

class Lexer{
private:
	std::map<std::string, TokenType> typeMap {
		{"int", TokenType::Keyword},
		{"while", TokenType::Keyword},
		{"if", TokenType::Keyword}
	};

public:
	Lexer(std::string fileContent);
	std::vector<Token> tokens;
};
