#include "ast.h"
#include <map>

std::string IntDeclaration::generateCode(std::map<std::string, int>& variables, int& s)
{
	if(variables.find(this->variable->name) != variables.end())
	{
		throw std::runtime_error("Syntax error: " + this->variable->name + " is already taken.");
	}

	variables.insert(make_pair(this->variable->name, s));
	s++;

	std::string command = "li $v0 0\n";
	command += "sw $v0 ($sp)\n";
	command += "addi $sp $sp -4\n";

	command += this->next->generateCode(variables, s);

	return command;
}

std::string Assignment::generateCode(std::map<std::string, int>& variables, int& s)
{
	if(variables.find(this->variable->name) == variables.end())
	{
		throw std::runtime_error("Syntax error: " + this->variable->name + " not declared.");
	}

	int relLocation = variables[this->variable->name];
	int offset = 4*s - relLocation;

	std::string command = this->expression->generateCode(variables, s);;

	command += "lw $v0 4($sp)\n";
	command += "sw $v0 " + std::to_string(offset) + "($sp)\n";

	s--;

	command += this->next->generateCode(variables, s);

	return command;
}

std::string Expression::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	if(this->optional){
		command += this->optional->generateCode(variables, s);
		command += "li $v0 4($sp)\n";
		command += "li $v1 8($sp)\n";
		command += "addi $v0 $v0 $v1\n";
		command += "sw $v0 8($)\n";
		command += "addi $sp 4\n";

		s--;
	}

	return command;
}

std::string Expression2::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	if(this->optional){
		command += this->optional->generateCode(variables, s);
		command += "li $v0 4($sp)\n";
		command += "li $v1 8($sp)\n";
		command += "mul $v0 $v0 $v1\n";
		command += "sw $v0 8($)\n";
		command += "addi $sp 4\n";

		s--;
	}

	return command;
}

std::string Expression3::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	if(negation)
	{
		command += "li $v0 4($sp)\n";
		command += "neg $v0 $v0\n";
		command += "sw $v0 4($sp)\n";
		command += "addi $sp 4\n";
	}

	return command;
}

std::string Expression4::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	return command;
}

std::string Number::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = "li $v0 " + std::to_string(this->value) + "\n";
	command += "sw $v0 ($sp)\n";
	command += "addi $sp $sp -4";

	s++;

	return command;
}

std::string Epsilon::generateCode(std::map<std::string, int>& variables, int& s){
	return "";
}

std::string Node::generateCode(std::map<std::string, int>& variables, int& s){
	return "";
}

std::string Statement::generateCode(std::map<std::string, int>& variables, int& s){
	return "";
}
