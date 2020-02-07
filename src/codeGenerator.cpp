#include "ast.h"
#include <map>

std::string IntDeclaration::generateCode(std::map<std::string, int> variables, int s)
{
  if(variables.find(this->variable->name) != variables.end())
  {
    throw std::runtime_error("Syntax error: " + this->variable->name + " is already taken.");
  }

  variables.insert(make_pair(this->variable->name, s));
  s++;

	return "";
}
