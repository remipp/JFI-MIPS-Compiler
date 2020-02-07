#include "parser.h"

#include <stdexcept>
#include <map>
#include <vector>

static Statement* getNodeInstanceByKeyword(std::vector<Token>& tokenization, int index);

void Node::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	throw std::runtime_error("Cannot call generateSubTree for base class Node");
}

void IntDeclaration::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization[++index].type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier after int");

	variable = new Variable();
	variable->generateSubTree(tokenization, index);

	if (tokenization[index++].s != ";")
		throw std::runtime_error("Expected a semicolon after name");
	next = getNodeInstanceByKeyword(tokenization, index);
	next->generateSubTree(tokenization, index);
}

void Variable::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	name = tokenization[index++].s;
}

void Number::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	value = std::stoi(tokenization[index++].s);
}

void Assignment::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization[index].type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier");

	variable = new Variable();
	variable->generateSubTree(tokenization, index);

	index++; //Skip over equal sign

	expression = new Expression();
	expression->generateSubTree(tokenization, index);

	if (tokenization[index++].s != ";")
		throw std::runtime_error("Expected a semicolon after assignment");

	next = getNodeInstanceByKeyword(tokenization, index);
	next->generateSubTree(tokenization, index);
}

void Statement::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	throw std::runtime_error("Cannot call generateSubTree for base class Statement");
}

void Expression::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	next = new Expression2();
	next->generateSubTree(tokenization, index);

	if (tokenization[index].s == "+")
	{
		optional = new Expression();
		optional->generateSubTree(tokenization, ++index);
	}
}

void Expression2::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	next = new Expression3();
	next->generateSubTree(tokenization, index);

	if (tokenization[index].s == "*")
	{
		optional = new Expression2();
		optional->generateSubTree(tokenization, ++index);
	}
}

void Expression3::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	negation = tokenization[index].s == "-";
	if (negation)
		index++;
	next = new Expression4();
	next->generateSubTree(tokenization, index);
}

void Expression4::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization[index].s == "(")
	{
		index++;
		next = new Expression();
		next->generateSubTree(tokenization, index);
		index++;
	}
	else if (tokenization[index].type == TokenType::Constant) {
		next = new Number();
		next->generateSubTree(tokenization, index);
	}
	else
	{
		next = new Variable();
		next->generateSubTree(tokenization, index);
	}
}

Node* generateAST(std::vector<Token>& tokenization)
{
	Node* root = getNodeInstanceByKeyword(tokenization, 0);
	int index = 0;
	root->generateSubTree(tokenization, index);
	return root;
}

static Statement* getNodeInstanceByKeyword(std::vector<Token>& tokenization, int index)
{
	if (index >= tokenization.size())
		return new Epsilon();

	if (tokenization[index].s == "int")
		return new IntDeclaration();
	else if (tokenization[index+1].s == "=")
	{
		if (tokenization[index+2].type == TokenType::Keyword)
		{
			// TODO syscall?
		}
		else
		{
			return new Assignment();
		}
	}
	else
		return nullptr;
}

void Epsilon::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	return;
}
