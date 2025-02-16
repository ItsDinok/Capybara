#pragma once

#include "Token.h"
#include "Lexer.h"
#include "AST.h"
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iostream>

enum class BindingPowers {
	DEFAULT,
	COMMA,
	ASSIGNMENT,
	LOGICAL,
	RELATIONAL,
	ADDITIVE,
	MULTIPLICATIVE,
	UNARY,
	CALL,
	MEMBER,
	PRIMARY
};

// TODO: Parse function needs to be refactored
struct Parser {
	std::vector<Token> Tokens;
	int Position;

	BlockStatement Parse(std::vector<Token> tokens);
	Parser(std::vector<Token> tokens);
	bool HasTokens();
	Statement* ParseStatement();

	const std::map<BindingPowers, int> Bindings = {
		{BindingPowers::DEFAULT, 0},
		{BindingPowers::COMMA, 1},
		{BindingPowers::ASSIGNMENT, 2},
		{BindingPowers::LOGICAL, 3},
		{BindingPowers::RELATIONAL, 4},
		{BindingPowers::ADDITIVE, 5},
		{BindingPowers::MULTIPLICATIVE, 6},
		{BindingPowers::UNARY, 7},
		{BindingPowers::CALL, 8},
		{BindingPowers::MEMBER, 9},
		{BindingPowers::PRIMARY, 10}
	};
};

using statementHandler = std::function<std::shared_ptr<Statement>(Parser*)>;
using nudHandler = std::function<std::shared_ptr<Expression>(Parser*)>;
using leftHandler = std::function<std::shared_ptr<Expression>(Parser*, Expression left, BindingPowers bindingPower)>;

using StatementLookup = std::map<TokenType, statementHandler>;
using NudLookup = std::map<TokenType, nudHandler>;
using LedLookup = std::map<TokenType, leftHandler>;
using bpLookup = std::map<TokenType, BindingPowers>;

StatementLookup statementLU;
NudLookup nudLU;
LedLookup ledLU;
bpLookup bpLU;

void Led(TokenType type, BindingPowers bp, leftHandler ledHandler);
void Nud(TokenType type, BindingPowers bp, nudHandler nudFunction);
void Stmt(TokenType type, statementHandler statementFunction);

void CreateTokenLookups();

std::shared_ptr<Expression> ParsePrimaryExpression(Parser* parser);
