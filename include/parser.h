#pragma once
#include <vector>
#include "tokens.h"
#include "ast.h"

// TODO: Error tracking in parser

class Parser
{
public:
	Parser(const std::vector<Token> &tokens);
	AST::BlockStatement parse();
	Token advance(size_t places);

private:
	Token current_token();
	TokenType current_token_type();
	bool is_eof();

	std::unique_ptr<AST::Statement> parse_statement();

	std::vector<Token> tokens;
	size_t position = 0;
};
