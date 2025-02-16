#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) {
	this->Tokens = tokens;
}

BlockStatement Parser::Parse(std::vector<Token> tokens) {
	std::vector<Statement*> body;
	Parser parser(tokens);	

	while (parser.HasTokens()) {
		body.push_back(ParseStatement());
	}

	std::vector<std::shared_ptr<Statement>> shared;
	for (Statement* statement : body) {
		shared.push_back(std::shared_ptr<Statement>(statement));
	}

	return BlockStatement(shared);
}

// Helper functions
static Token CurrentToken(Lexer *lexer) {
	return lexer->Tokens[lexer->Position];
}

static Token Advance(Lexer *lexer) {
	Token token = lexer->Tokens[lexer->Position];
	lexer->Position++;
	return token;
}

bool Parser::HasTokens() {
	return this->Position < this->Tokens.size() &&
		this->Tokens[this->Position].Type != TokenType::EOFTOKEN;
}

Statement* Parser::ParseStatement() {
	return std::make_shared<ExpressionStatement>().get();
}

void Led(TokenType type, BindingPowers bp, leftHandler ledHandler) {
	bpLU[type] = bp;
	ledLU[type] = ledHandler;
}

void Nud(TokenType type, BindingPowers bp, nudHandler nudFunction) {
	bpLU[type] = BindingPowers::PRIMARY;
	nudLU[type] = nudFunction;
}

void Stmt(TokenType type, statementHandler statementFunction) {
	bpLU[type] = BindingPowers::DEFAULT;
	statementLU[type] = statementFunction;
}

std::shared_ptr<Expression> ParsePrimaryExpression(Parser* parser) {
	switch(static_cast<int>(parser->Tokens[parser->Position].Type)) {
		case static_cast<int>(TokenType::NUMBER): {
			std::string value = parser->Tokens[parser->Position].Value;
			char* end;
			double number = std::strtod(value.c_str(), &end);
			return std::make_shared<NumberExpression>(number);
			break;
		}

		case static_cast<int>(TokenType::STRING): {
			return std::make_shared<StringExpression>(parser->Tokens[parser->Position].Value);
			break;
		}

		case static_cast<int>(TokenType::IDENTIFIER): {
			return std::make_shared<SymbolExpression>(parser->Tokens[parser->Position].Value);
			break;
		}
		
		default:
			std::cout << "AAAAAAAAAAA" << std::endl;
	}
	return nullptr;
}

void CreateTokenLookups() {
}
