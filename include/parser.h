#pragma once
#include <vector>
#include "tokens.h"
#include "ast.h"

// TODO: Error tracking in parser

struct Parser
{
	Parser();
	AST::BlockStatement parse(std::vector<Token> tokens);

	std::vector<Token> tokens;
	size_t position;
};
