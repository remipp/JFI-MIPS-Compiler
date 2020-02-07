#include "debug.h"

#include <iostream>

std::string Node::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "Node {}";
	return ret;
}

std::string Variable::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "Variable {" + name + "}\n";
	return ret;
}

std::string Number::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "Number {" + std::to_string(value) + "}\n";
	return ret;
}

std::string Expression4::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "e4 {\n";

	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Expression3::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "e3 {\n";
	
	if (negation)
		ret += '-';
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Expression2::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "e2 {\n";

	ret += next->printDebug(depth + 1);
	if (optional)
		ret += optional->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Expression::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "e {\n";

	ret += next->printDebug(depth + 1);
	if (optional)
		ret += optional->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Statement::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "s {}\n";
	return ret;
}

std::string IntDeclaration::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "int {\n";

	ret += variable->printDebug(depth + 1);
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Assignment::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "int {\n";

	ret += variable->printDebug(depth + 1);
	ret += expression->printDebug(depth + 1);
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Epsilon::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "epsilon {}\n";
	return ret;
}

std::ostream& operator<<(std::ostream& os, const Node& root)
{
	os << root.printDebug(0);
	return os;
}