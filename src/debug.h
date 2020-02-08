#pragma once

#include "ast.h"
#include "token.h"

std::ostream& operator<<(std::ostream& os, const Node& root);
std::ostream& operator<<(std::ostream& os, const Token& token);