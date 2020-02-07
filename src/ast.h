#pragma once

#include <vector>
#include <string>
#include <map>

#include "token.h"

class Node
{
public:
	virtual void generateSubTree(std::vector<Token>& tokenization, int& index);
	virtual std::string generateCode(std::map<std::string, int> variables, int s);
};

class Variable : public Node
{
public:
	std::string name;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Number : public Node
{
public:
	int value;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Expression : public Node
{
public:
	Expression2* next;
	Expression* optional;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Expression2 : public Node
{
public:
	Expression3* next;
	Expression2* optional;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Expression3 : public Node
{
public:
	Node* next;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Expression4 : public Node
{
public:
	Node* value;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Statement : public Node
{
public:
	void generateSubTree(std::vector<Token>& tokenization, int& index);
	std::string generateCode(std::map<std::string, int> variables, int s);
};

class IntDeclaration : public Statement
{
public:
	Variable* variable;
	Statement* next;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
	std::string generateCode(std::map<std::string, int> variables, int s);
};

class Assigment : public Statement
{
public:
	Variable* variable;
	Expression* expression;
	Statement* next;

	void generateSubTree(std::vector<Token>& tokenization, int& index);
};

class Epsilon : public Statement
{
public:
	void generateSubTree(std::vector<Token>& tokenization, int& index);
};
