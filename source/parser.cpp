#include "parser.h"

Parser::Parser(const std::vector<Token> &tokens)
{
	this->tokens = tokens;
}

Token Parser::current_token()
{
	return tokens[position];
}

Token Parser::advance(size_t places) 
{
	position += places;
	return tokens[position - 1];
}

TokenType Parser::current_token_type()
{
	return tokens[position].type;
}

bool Parser::is_eof()
{
	return (tokens[position].type == TokenType::EOF_TOKEN);
}

std::unique_ptr<AST::Statement> Parser::parse_statement()
{
	return std::make_unique<AST::Statement>(AST::ExpressionStatement{});
}

AST::BlockStatement Parser::parse ()
{
	AST::BlockStatement block;

	while (!is_eof())
	{
		block.body.push_back(parse_statement());
		advance(1);
	}

	return block;
}
