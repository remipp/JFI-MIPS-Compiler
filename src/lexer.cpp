#include "lexer.h"
#include "token.h"
#include <regex>
#include <iostream>
#include <set>

Lexer::Lexer(std::string fileContent)
{
	std::regex rgx("([A-z0-9]+)|!=|[=<>]=?|[\\(\\)\\{\\}+*-;=]");
	std::regex intConst("^\\d+$");
	std::regex identifier("^[A-z][A-z0-9_]*$");
	std::regex booleanOperator("^!=|[=<>]=?$");
	std::regex special("^[=;,\\(\\)\\{\\}\\+*-]");
	std::smatch m;
	std::sregex_iterator it(fileContent.begin(), fileContent.end(), rgx), it_end;
	for(; it != it_end; ++it)
	{
		Token buf;
		buf.s = (*it)[0];
		if (typeMap.find(buf.s) != typeMap.end())
		{
			buf.type = typeMap[buf.s];
		}
		else
		{
			if (std::regex_match(buf.s, intConst))
			{
				buf.type = TokenType::Constant;
			}
			else if (std::regex_match(buf.s, identifier))
			{
				buf.type = TokenType::Identifier;
			}
			else if (std::regex_match(buf.s, booleanOperator))
			{
				buf.type = TokenType::BooleanOperator;
			}
			else if (std::regex_match(buf.s, special))
			{
				buf.type = TokenType::SpecialSymbol;
			}
			else
			{
				buf.type = (TokenType)-1;
			}
		}
		tokens.push_back(buf);
	}
}
