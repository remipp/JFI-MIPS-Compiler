#include "parser.h"

#include <stdexcept>
#include <map>
#include <vector>

static Node* getNodeInstanceByKeyword(Token token);

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

	if (tokenization[index].s == "=")
	{

	}
}

void Variable::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	name = tokenization[index++].s;
}

void Number::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	value = std::stoi(tokenization[index++].s);
}

Node* generateAST(std::vector<Token>& tokenization)
{
	Node* root = getNodeInstanceByKeyword(tokenization[0]);
	int index = 0;
	root->generateSubTree(tokenization, index);
	return root;
}

static Node* getNodeInstanceByKeyword(Token token)
{
	if (token.type != TokenType::Keyword)
		throw std::runtime_error("Invalid token type");
}