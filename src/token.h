#pragma once

#include <string>

enum class TokenType
{
	Keyword,
	Identifier,
	Constant,
	SpecialSymbol,
	BooleanOperator
};

class Token
{
public:
	std::string s;
	TokenType type;
};
