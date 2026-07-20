#pragma once
#include <memory>
#include <string>
#include <vector>
#include "tokens.h"

namespace AST
{

class Expression;

enum class BindingPower : int
{
	None			= 0,
	Comma			= 5,
	Assignment		= 10,
	Or				= 20,
	And				= 30,
	Equality		= 40,
	Comparison		= 50,
	Additive		= 60,
	Multiplicative	= 70,
	Unary			= 80,
	Call			= 90,
	Member			= 100,
	Primary			= 110,
};

constexpr int val(BindingPower bp) 
{
	return static_cast<int>(bp);
};

// Educational notes about Pratt parsers:
/*
	Tokens can have a LUD handler, which means it expects nothing to its left
	Tokens can have a LED, which expect to be between or after some expression
		to its left. Binary expressions and infix expressions are examples
		Postfix expressions count for LED

	Pratt parsers use lookup tables alongside NUD/LED handler funcions. This means the 
	parser can be written without having to manually manage the recursion
*/


// AST DEFINITIONS

// STATEMENTS
class Statement
{
public:
	virtual ~Statement() = default;
};

class BlockStatement : public Statement
{
public:
	std::vector<std::unique_ptr<Statement>> body;
};

// Expression statements are a neat way to force semicolon termination
class ExpressionStatement : public Statement
{
public:
	std::unique_ptr<Expression> expression;
};

// EXPRESSIONS

class Expression
{
public:
	virtual ~Expression() = default;
};

// Complex expressions
class BinaryExpression : public Expression
{
public:
	std::unique_ptr<Expression> left, right;
	Token operand;
};

// Literal expressions
class NumberExpression : public Expression 
{
public: 
	float value;
};

class StringExpression : public Expression 
{
public:
	std::string value;
};

class SymbolExpression : public Expression
{
public:
	std::string value;
};

}
