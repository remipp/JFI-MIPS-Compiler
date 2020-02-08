#include "debug.h"

#include <iostream>

std::string Node::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "node {}";
	return ret;
}

std::string Variable::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "variable {" + name + "}\n";
	return ret;
}

std::string Number::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "number {" + std::to_string(value) + "}\n";
	return ret;
}

std::string Boolean::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "boolean {";

	if(value)
		ret += "true";
	else
		ret += "false";

	ret += "}\n";
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

std::string Comparison::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "comp {\n";

	ret += a->printDebug(depth + 1);
	ret += comparator + "\n";
	ret += b->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string BoolExpression4::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "b4 {\n";

	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string BoolExpression3::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "b3 {\n";
	
	if (negation)
		ret += '!';
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string BoolExpression2::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "b2 {\n";

	ret += next->printDebug(depth + 1);
	if (optional)
		ret += optional->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string BoolExpression::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "b {\n";

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
	ret += "assign {\n";

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

std::string While::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "while {\n";

	ret += expression->printDebug(depth + 1);
	ret += body->printDebug(depth + 1);
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string If::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "if {\n";

	ret += expression->printDebug(depth + 1);
	ret += body->printDebug(depth + 1);
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Print::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "print {\n";

	ret += expression->printDebug(depth + 1);
	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Exit::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "exit {\n";

	ret += next->printDebug(depth + 1);

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::string Read::printDebug(int depth) const
{
	std::string ret;
	ret.resize(depth, ' ');
	ret += "read {\n";

	ret.resize(ret.size() + depth, ' ');
	ret += "}\n";
	return ret;
}

std::ostream& operator<<(std::ostream& os, const Node& root)
{
	os << root.printDebug(0);
	return os;
}
