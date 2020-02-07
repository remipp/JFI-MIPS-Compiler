#pragma once

#include <vector>

#include "token.h"
#include "ast.h"

Node* generateAST(std::vector<Token>& tokenization);