#pragma once
#include <string>
enum class TokenType {
	Keyword,
	Identifier,
	Constant,
	SpecialSymbol
};

class Token
{
public:
	std::string s;
	TokenType type;
};
