#include "ast.h"
#include <map>
#include <iostream>

static int finallyCounter = 0;
static int resetCounter = 0;

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

	std::string command = this->expression->generateCode(variables, s);

	int relLocation = variables[this->variable->name];
	int offset = 4*(s - relLocation);

	command += "lw $v0 4($sp)\n";
	command += "sw $v0 " + std::to_string(offset) + "($sp)\n";

	command += this->next->generateCode(variables, s);

	return command;
}

std::string If::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command;

	command += expression->generateCode(variables, s);
	command += "lw $v0 4($sp)\n";
	command += "beq $v0 $zero finally" + std::to_string(finallyCounter) + "\n";
	command += body->generateCode(variables, s);
	command += "finally" + std::to_string(finallyCounter) + ":\n";
	command += next->generateCode(variables, s);

	finallyCounter++;
	return command;
}

std::string While::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command;

	command += "reset" + std::to_string(resetCounter) + ":\n";
	command += expression->generateCode(variables, s);
	command += "lw $v0 4($sp)\n";
	command += "beq $v0 $zero finally" + std::to_string(finallyCounter) + "\n";
	command += body->generateCode(variables, s);
	command += "j reset" + std::to_string(resetCounter) + "\n";
	command += "finally" + std::to_string(finallyCounter) + ":\n";
	command += next->generateCode(variables, s);

	finallyCounter++;
	resetCounter++;
	return command;
}

std::string Expression::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	if(this->optional){
		command += this->optional->generateCode(variables, s);
		command += "lw $v0 8($sp)\n";
		command += "lw $v1 4($sp)\n";

		if (isSubtraction)
			command += "sub $v0 $v0 $v1\n";
		else
			command += "add $v0 $v0 $v1\n";

		command += "sw $v0 8($sp)\n";
		command += "addi $sp $sp 4\n";

		s--;
	}

	return command;
}

std::string Expression2::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	if(this->optional){
		if (this->isMultiplication)
		{
			command += this->optional->generateCode(variables, s);
			command += "lw $v0 4($sp)\n";
			command += "lw $v1 8($sp)\n";
			command += "mul $v0 $v0 $v1\n";
			command += "sw $v0 8($sp)\n";
			command += "addi $sp $sp 4\n";

			s--;
		}
		else
		{
			command += this->optional->generateCode(variables, s);
			command += "lw $v1 4($sp)\n";
			command += "lw $v0 8($sp)\n";
			command += "div $v0 $v0 $v1\n";
			command += "sw $v0 8($sp)\n";
			command += "addi $sp $sp 4\n";

			s--;
		}
	}

	return command;
}

std::string Expression3::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = this->next->generateCode(variables, s);

	if(negation)
	{
		command += "lw $v0 4($sp)\n";
		command += "sub $v0 $zero $v0\n";
		command += "sw $v0 4($sp)\n";
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
	command += "addi $sp $sp -4\n";

	s++;

	return command;
}

std::string Variable::generateCode(std::map<std::string, int>& variables, int& s)
{
	int relLocation = variables[this->name];
	int offset = 4*(s - relLocation);

	std::string command;
	command += "lw $v0 " + std::to_string(offset) + "($sp)\n";
	command += "sw $v0 ($sp)\n";
	command += "addi $sp $sp -4\n";

	s++;

	return command;
}

std::string BoolExpression::generateCode(std::map<std::string, int>& variables, int& s){
	std::string command = this->next->generateCode(variables, s);

 if(this->optional){
	 command += this->optional->generateCode(variables, s);
	 command += "lw $v0 4($sp)\n";
	 command += "lw $v1 8($sp)\n";
	 command += "or $v0 $v0 $v1\n";
	 command += "sw $v0 8($sp)\n";
	 command += "addi $sp $sp 4\n";

	 s--;
 }

 return command;
}

std::string BoolExpression2::generateCode(std::map<std::string, int>& variables, int& s){
	std::string command = this->next->generateCode(variables, s);

 if(this->optional){
	 command += this->optional->generateCode(variables, s);
	 command += "lw $v0 4($sp)\n";
	 command += "lw $v1 8($sp)\n";
	 command += "and $v0 $v0 $v1\n";
	 command += "sw $v0 8($sp)\n";
	 command += "addi $sp $sp 4\n";

	 s--;
 }

 return command;
}

std::string BoolExpression3::generateCode(std::map<std::string, int>& variables, int& s){
	std::string command = this->next->generateCode(variables, s);

 if(this->negation){
	 command += "lw $v0 4($sp)\n";
	 command += "neg $v0 $v0\n";
	 command += "sw $v0 8($sp)\n";
 }

 return command;
}

std::string BoolExpression4::generateCode(std::map<std::string, int>& variables, int& s){
	std::string command = this->next->generateCode(variables, s);

 return command;
}

std::string Comparison::generateCode(std::map<std::string, int>& variables, int& s){
	std::string command = this->a->generateCode(variables, s);
	command += this->b->generateCode(variables, s);

	command += "lw $t0 4($sp)\n";
	command += "lw $t1 8($sp)\n";

	if(this->comparator == "<"){
		command += "sgt $v0 $t0 $t1\n";
	}else if(this->comparator == ">"){
		command += "sgt $v0 $t1 $t0\n";
	}else if(this->comparator == "=="){
		command += "seq $v0 $t1 $t0\n";
	}else if(this->comparator == "!="){
		command += "sne $v0 $t1 $t0\n";
	}else if(this->comparator == "<="){
		command += "sle $v0 $t1 $t0\n";
	}else if(this->comparator == ">="){
		command += "sge $v0 $t1 $t0\n";
	}else{
		command += "li $v0 0\n";
	}

	command += "sw $v0 8($sp)\n";
	command += "addi $sp $sp 4\n";

	s--;

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

std::string Print::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = expression->generateCode(variables, s);
	command += "li $v0, 1\n";
	command += "lw $a0, 4($sp)\n";
	command += "syscall\n";
	command += next->generateCode(variables, s);
	return command;
}

std::string Exit::generateCode(std::map<std::string, int>& variables, int& s)
{
	std::string command = "li $v0, 10\n";
	command += "syscall\n";
	command += next->generateCode(variables, s);
	return command;
}

std::string Read::generateCode(std::map<std::string, int>& variables, int& s) {
	std::string command =  "li $v0, 5\n";
	command +=  "syscall\n";
	command +=  "sw $v0, ($sp)\n";
	command += next->generateCode(variables, s);
	return command;
}
