#include "AST.h"

BlockStatement::BlockStatement(std::vector<std::shared_ptr<Statement>> body) {
	this->Statements = body;
}

void BlockStatement::Stmt() {}
void ExpressionStatement::Stmt() {}

ExpressionStatement :: ExpressionStatement() {}
void NumberExpression :: Expr() {}
void StringExpression :: Expr() {}
void SymbolExpression :: Expr() {}

