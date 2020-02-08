#pragma once

#include <map>

#include "ast.h"

std::string generateCode(Node* astRoot)
{
	std::map<std::string, int> variables;
	int stackCounter = 0;
	std::string code = astRoot->generateCode(variables, stackCounter);
	return code;
}