#include "parser.h"

#include <stdexcept>
#include <map>
#include <vector>
#include <iostream>

static Statement* getNodeInstanceByKeyword(std::vector<Token>& tokenization, int index);

void Node::generateSubTree(std::vector<Token>& tokenization, int& index) {}

void IntDeclaration::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(++index).type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier after int");

	variable = new Variable();
	variable->generateSubTree(tokenization, index);

	if (tokenization.at(index++).s != ";")
		throw std::runtime_error("Expected a semicolon after name");
	next = getNodeInstanceByKeyword(tokenization, index);
	next->generateSubTree(tokenization, index);
}

void Variable::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	name = tokenization.at(index++).s;
}

void Number::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	value = std::stoi(tokenization.at(index++).s);
}

void Boolean::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(index++).s == "true")
		value = true;
	else if (tokenization.at(index).s == "false")
		value = false;
	else
		throw std::runtime_error("Invalid token for boolean value");
}

void Assignment::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(index).type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier");

	variable = new Variable();
	variable->generateSubTree(tokenization, index);

	index++; //Skip over equal sign

	expression = new Expression();
	expression->generateSubTree(tokenization, index);

	if (tokenization.at(index++).s != ";")
		throw std::runtime_error("Expected a semicolon after assignment");

	next = getNodeInstanceByKeyword(tokenization, index);
	next->generateSubTree(tokenization, index);
}

void Statement::generateSubTree(std::vector<Token>& tokenization, int& index) {}

void Expression::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	next = new Expression2();
	next->generateSubTree(tokenization, index);

	if (tokenization.at(index).s == "+")
	{
		optional = new Expression();
		optional->generateSubTree(tokenization, ++index);
		isSubtraction = false;
	}
	else if (tokenization.at(index).s == "-")
	{
		optional = new Expression();
		optional->generateSubTree(tokenization, ++index);
		isSubtraction = true;
	}
}

void Expression2::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	next = new Expression3();
	next->generateSubTree(tokenization, index);

	if (tokenization.at(index).s == "*")
	{
		isMultiplication = true;
		optional = new Expression2();
		optional->generateSubTree(tokenization, ++index);
	}
	else if (tokenization.at(index).s == "/")
	{
		optional = new Expression2();
		optional->generateSubTree(tokenization, ++index);
	}
}

void Expression3::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	negation = tokenization.at(index).s == "-";
	if (negation)
		index++;

	if (negation)
		next = new Expression3();
	else
		next = new Expression4();

	next->generateSubTree(tokenization, index);
}

void Expression4::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(index).s == "(")
	{
		index++;
		next = new Expression();
		next->generateSubTree(tokenization, index);
		index++;
	}
	else if (tokenization.at(index).type == TokenType::Constant) {
		next = new Number();
		next->generateSubTree(tokenization, index);
	}
	else if (tokenization.at(index).s == "read")
	{
		next = new Read();
		next->generateSubTree(tokenization, index);
	}
	else
	{
		next = new Variable();
		next->generateSubTree(tokenization, index);
	}
}

void BoolExpression::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	next = new BoolExpression2();
	next->generateSubTree(tokenization, index);

	if (tokenization.at(index).s == "||")
	{
		optional = new BoolExpression();
		optional->generateSubTree(tokenization, ++index);
	}
}

void BoolExpression2::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	next = new BoolExpression3();
	next->generateSubTree(tokenization, index);

	if (tokenization.at(index).s == "&&")
	{
		optional = new BoolExpression2();
		optional->generateSubTree(tokenization, ++index);
	}
}

void BoolExpression3::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	negation = tokenization.at(index).s == "!";
	if (negation)
		index++;

	if (negation)
		next = new BoolExpression3();
	else
		next = new BoolExpression4();

	next->generateSubTree(tokenization, index);
}

void BoolExpression4::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(index).s == "(")
	{
		index++;
		next = new BoolExpression();
		next->generateSubTree(tokenization, index);
		index++;
	}
	else if (tokenization.at(index).type == TokenType::Keyword)
	{
		next = new Boolean();
		next->generateSubTree(tokenization, index);
	}
	else
	{
		next = new Comparison();
		next->generateSubTree(tokenization, index);
	}
}

void Comparison::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	a = new Expression();
	a->generateSubTree(tokenization, index);

	if (tokenization.at(index).type != TokenType::BooleanOperator)
		throw std::runtime_error("Expected a boolean operator");
	comparator = tokenization.at(index).s;

	b = new Expression();
	b->generateSubTree(tokenization, ++index);
}

void While::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(++index).s != "(")
		throw std::runtime_error("Expected opening bracket ( after while");

	expression = new BoolExpression();
	expression->generateSubTree(tokenization, ++index);

	if (tokenization.at(index++).s != ")")
		throw std::runtime_error("Expected closing bracket ) after while");

	if (tokenization.at(index).s != "{")
		throw std::runtime_error("Expected opening bracket { after while");
	
	body = getNodeInstanceByKeyword(tokenization, ++index);
	body->generateSubTree(tokenization, index);

	if (tokenization.at(index++).s != "}")
		throw std::runtime_error("Expected closing bracket } after while block");

	next = getNodeInstanceByKeyword(tokenization, index);
	next->generateSubTree(tokenization, index);
}

void If::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(++index).s != "(")
		throw std::runtime_error("Expected opening bracket ( after if");

	expression = new BoolExpression();
	expression->generateSubTree(tokenization, ++index);

	if (tokenization.at(index++).s != ")")
		throw std::runtime_error("Expected closing bracket ) after if");

	if (tokenization.at(index).s != "{")
		throw std::runtime_error("Expected opening bracket { after if");
	
	body = getNodeInstanceByKeyword(tokenization, ++index);
	body->generateSubTree(tokenization, index);

	if (tokenization.at(index).s != "}")
		throw std::runtime_error("Expected closing bracket } after if block");

	next = getNodeInstanceByKeyword(tokenization, ++index);
	next->generateSubTree(tokenization, index);
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

	if (tokenization.at(index).s == "int")
		return new IntDeclaration();
	else if (tokenization.at(index).s == "while")
		return new While();
	else if (tokenization.at(index).s == "if")
		return new If();
	else if (tokenization.at(index).s == "print")
		return new Print();
	else if (tokenization.at(index).s == "exit")
		return new Exit();
	else if (index < tokenization.size() - 1 && tokenization.at(index + 1).s == "=")
	{
		return new Assignment();
	}
	else
		return new Statement();
}

void Epsilon::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	return;
}

void Print::generateSubTree(std::vector<Token>& tokenization, int& index)
{ 
	if (tokenization.at(++index).s != "(")
		throw std::runtime_error("Expected opening bracket ( after print");

	expression = new Expression();
	expression->generateSubTree(tokenization, ++index);

	if (tokenization.at(index++).s != ")")
		throw std::runtime_error("Expected closing bracket ) after print");
	if (tokenization.at(index++).s != ";")
		throw std::runtime_error("Expected semicolon");
	next = getNodeInstanceByKeyword(tokenization, index);
	next->generateSubTree(tokenization, index);
}

void Exit::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(++index).s != "(" || tokenization.at(++index).s != ")")
		throw std::runtime_error("Expected opening and closing bracket after exit");
	if (tokenization.at(++index).s != ";")
		throw std::runtime_error("Expected semicolon");
	next = getNodeInstanceByKeyword(tokenization, ++index);
	next->generateSubTree(tokenization, index);
}

void Read::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization.at(++index).s != "(" || tokenization.at(++index).s != ")")
		throw std::runtime_error("Expected opening and closing bracket after print");
	next = getNodeInstanceByKeyword(tokenization, ++index);
	next->generateSubTree(tokenization, index);
}
