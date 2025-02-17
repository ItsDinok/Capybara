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

std::shared_ptr<Expression> ParseBinaryExpression(Parser* parser, std::shared_ptr<Expression> left, BindingPowers bp) {
	Token = Advance(parser);
	return nullptr;
}

void CreateTokenLookups() {
	// Logical expressions
	Led(TokenType::AND, BindingPowers::LOGICAL, ParseBinaryExpression);
	Led(TokenType::OR, BindingPowers::LOGICAL, ParseBinaryExpression);
	// NOTE: DOTDOT operator requires very low precedence in order to function
	Led(TokenType::DOTDOT, BindingPowers::LOGICAL, ParseBinaryExpression);

	// Relational
	Led(TokenType::LESS, BindingPowers::RELATIONAL, ParseBinaryExpression);	
	Led(TokenType::LESSEQUALS, BindingPowers::RELATIONAL, ParseBinaryExpression);	
	Led(TokenType::GREATER, BindingPowers::RELATIONAL, ParseBinaryExpression);	
	Led(TokenType::GREATEREQUALS, BindingPowers::RELATIONAL, ParseBinaryExpression);	
	Led(TokenType::EQUALTO, BindingPowers::RELATIONAL, ParseBinaryExpression);	
	Led(TokenType::NOTEQUAL, BindingPowers::RELATIONAL, ParseBinaryExpression);	

	// Additive and Multiplicative
	Led(TokenType::PLUS, BindingPowers::ADDITIVE, ParseBinaryExpression);
	Led(TokenType::MINUS, BindingPowers::ADDITIVE, ParseBinaryExpression);

	Led(TokenType::STAR, BindingPowers::MULTIPLICATIVE, ParseBinaryExpression);
	Led(TokenType::SLASH, BindingPowers::MULTIPLICATIVE, ParseBinaryExpression);
	Led(TokenType::MOD, BindingPowers::MULTIPLICATIVE, ParseBinaryExpression);

	// Literals and Symbols
	Nud(TokenType::NUMBER, BindingPowers::PRIMARY, ParsePrimaryExpression);
	Nud(TokenType::STRING, BindingPowers::PRIMARY, ParsePrimaryExpression);
	Nud(TokenType::IDENTIFIER, BindingPowers::PRIMARY, ParsePrimaryExpression);
}
