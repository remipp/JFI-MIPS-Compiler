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

	std::string command = "li $v0 0\n";
	command += "sw $v0 ($sp)\n";
	command += "addi $sp $sp 4\n";

	command += this->next->generateCode(variables, s);

	return command;
}

std::string Assignment::generateCode(std::map<std::string, int> variables, int s)
{
	if(variables.find(this->variable->name) == variables.end())
	{
		throw std::runtime_error("Syntax error: " + this->variable->name + " not declared.");
	}

	int relLocation = variables[this->variable->name];
	int offset = 4*s - relLocation;


	std::string command = "addi $sp $sp -" + std::to_string(offset) + "\n";
	command += "li $v0 " + std::to_string(5) + "\n";
	command += "sw $v0 ($sp)\n";
	command += "addi $sp $sp " + std::to_string(offset) + "\n";

	command += this->next->generateCode(variables, s);

	return command;
}

std::string Epsilon::generateCode(std::map<std::string, int> variables, int s){
	return "";
}

std::string Node::generateCode(std::map<std::string, int> variables, int s){
	return "";
}

std::string Statement::generateCode(std::map<std::string, int> variables, int s){
	return "";
}
