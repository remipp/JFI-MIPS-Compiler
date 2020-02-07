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

void Node::parseSubTree(std::vector<Token>& tokenization, int& index)
{
	throw std::runtime_error("Cannot call parseSubTree for base class Node");
}

void IntDeclaration::parseSubtree(std::vector<Token>& tokenization, int& index)
{
	if (tokenization[++index].type != TokenType::Identifier)
		throw std::runtime_error("Expected an identifier after int");

	leafs.push_back(new Variable(tokenization[index].s));
}

Node* parseTokenization(std::vector<Token>& tokenization)
{
	return nullptr;
}

static Node* getNodeInstanceByKeyword(Token token)
{
	if (token.type != TokenType::Keyword)
		throw std::runtime_error("Invalid token type");
}