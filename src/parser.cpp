#include "parser.h"

#include <stdexcept>
#include <map>
#include <vector>

static Node* getNodeInstanceByKeyword(Token token);

Node::Node()
{}

Node::Node(std::string value)
	: value{value}
{}

void Node::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	throw std::runtime_error("Cannot call generateSubTree for base class Node");
}

void IntDeclaration::generateSubTree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization[++index].type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier after int");

	leafs.push_back(new Variable(tokenization[++index].s));

	if (tokenization[index].s == "=") //Direct Assignment
	{
		
	}
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