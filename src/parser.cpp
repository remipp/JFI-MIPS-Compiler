#include "parser.h"

#include <stdexcept>
#include <map>
#include <vector>

static Statement* getNodeInstanceByKeyword(Token token);

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

	if (tokenization[++index].type != TokenType::SpecialSymbol)
		throw std::runtime_error("Expected a semicolon name");
	next = getNodeInstanceByKeyword(tokenization[index]);
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

void Assigment::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization[index].type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier");
	
	variable = new Variable();
	variable->generateSubTree(tokenization, index);

	index++; //Skip over equal sign

	expression = new Expression();
	expression->generateSubTree(tokenization, index);

	if (tokenization[index++].type != TokenType::SpecialSymbol)
		throw std::runtime_error("Expected a semicolon after assignment");
}

void Statement::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	throw std::runtime_error("Cannot call generateSubTree for base class Statement");
}

void Expression::generateSubTree(std::vector<Token>& tokenization, int& index)
{

}

void Expression2::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	
}

void Expression3::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	
}

void Expression4::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	
}

Node* generateAST(std::vector<Token>& tokenization)
{
	Node* root = getNodeInstanceByKeyword(tokenization[0]);
	int index = 0;
	root->generateSubTree(tokenization, index);
	return root;
}

static Statement* getNodeInstanceByKeyword(Token token)
{
	if (token.type != TokenType::Keyword)
		throw std::runtime_error("Invalid token type");
}

void Epsilon::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	return;
}