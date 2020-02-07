#pragma once

#include <vector>
#include <string>

#include "token.h"

class Node
{
public:
	std::vector<Node*> leafs;
	std::string value;

	Node();
	Node(std::string value);

	virtual void parseSubTree(std::vector<Token>& tokenization, int& index);
	
};

class IntDeclaration : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};

class Variable : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};

class Number : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};

class Expression : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};

class Expression2 : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};

class Expression3 : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};

class Expression4 : public Node
{
	using Node::Node;

public:
	void parseSubtree(std::vector<Token>& tokenization, int& index);
};