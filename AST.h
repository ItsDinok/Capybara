#pragma once
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <vector>

class Statement {
public:
	virtual void Stmt() = 0;
	virtual ~Statement() = default;
};

class Expression {
public:
	virtual void Expr() = 0;
	virtual ~Expression() = default;
};

// Literal Expression
struct NumberExpression : public Expression {
	NumberExpression(double value) : Value(value) {};
	virtual ~NumberExpression() {};
	double Value;
	void Expr() override;
};

struct StringExpression : public Expression {
	std::string Value;
	StringExpression(std::string value) : Value(value) {};
	virtual ~StringExpression() {};
	void Expr() override;
};

struct SymbolExpression : public Expression {
	std::string Value;
	SymbolExpression(std::string value) : Value(value) {};
	virtual ~SymbolExpression() {};
	void Expr() override;
};

// Complex Expression
struct BinaryExpression : public Expression {
	std::shared_ptr<Expression> Left;
	std::shared_ptr<Expression> Right;
	Token Operator;
	void Expr() override;
};


// Statements
struct BlockStatement : public Statement {
	std::vector<std::shared_ptr<Statement>> Statements;
	void Stmt() override;
	BlockStatement(std::vector<std::shared_ptr<Statement>> body);
};

struct ExpressionStatement : public Statement {
	std::shared_ptr<Expression> Expr;
	void Stmt() override;
	ExpressionStatement();
};

