#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>

// TODO: Structure this
enum class TokenType {
	// Basic
	NUMBER,				// 123
	STRING,				// abc
	IDENTIFIER,
	NULLTOKEN,			// null
	TRUE,				// True
	FALSE,				// False
	EOFTOKEN,

	// Grouping
	OPENPARENTHESIS,	// (
	CLOSEPARENTHESIS,	// )
	OPENCURLY,			// {
	CLOSECURLY,			// }
	OPENSQUARE,			// [
	CLOSESQUARE,		// ]

	// Equivalence
	ASSIGNMENT,
	EQUALTO,
	NOTEQUAL,
	NOT,

	// Conditional
	LESS,
	LESSEQUALS,
	GREATER,
	GREATEREQUALS,

	// Logical
	OR,
	AND,

	// Symbols
	DOT,
	DOTDOT,
	SEMICOLON,
	COLON,
	QUESTION,
	COMMA,

	// Shorthand
	INCREMENT,
	DECREMENT,
	PLUSEQUALS,
	MINUSEQUALS,
	NULLISHASSIGNMENT,

	// Maths
	PLUS,
	MINUS,
	STAR,
	MOD,
	SLASH,

	// Reserved keywords
	LET, CONST, CLASS, NEW, FROM, FUNC,
	IF, ELSE, FOREACH, WHILE, FOR, EXPORT,
	TYPEOF, FLOAT, INT, BOOLEAN, IMPORT, STRINGTYPE, IN
};

// All token types and string match
const std::map<TokenType, std::string> TokenTypeValues = {
	{TokenType::NUMBER, "NUMBER"},
	{TokenType::STRING, "STRING"},
	{TokenType::IDENTIFIER, "IDENTIFIER"},
	{TokenType::NULLTOKEN, "NULLTOKEN"},
	{TokenType::TRUE, "TRUE"},
	{TokenType::FALSE, "FALSE"},
	{TokenType::EOFTOKEN, "EOFTOKEN"},

	{TokenType::OPENPARENTHESIS, "OPENPARENTHESIS"},
	{TokenType::CLOSEPARENTHESIS, "CLOSEPARENTHESIS"},
	{TokenType::OPENCURLY, "OPENCURLY"},
	{TokenType::CLOSECURLY, "CLOSECURLY"},
	{TokenType::OPENSQUARE, "OPENSQUARE"},
	{TokenType::CLOSESQUARE, "CLOSESQUARE"},

	{TokenType::ASSIGNMENT, "ASSIGNMENT"},
	{TokenType::EQUALTO, "EQUALTO"},
	{TokenType::NOTEQUAL, "NOTEQUAL"},
	{TokenType::NOT, "NOT"},

	{TokenType::LESS, "LESS"},
	{TokenType::LESSEQUALS, "LESSEQUALS"},
	{TokenType::GREATER, "GREATER"},
	{TokenType::GREATEREQUALS, "GREATEREQUALS"},

	{TokenType::OR, "OR"},
	{TokenType::AND, "AND"},

	{TokenType::DOT, "DOT"},
	{TokenType::DOTDOT, "DOTDOT"},
	{TokenType::SEMICOLON, "SEMICOLON"},
	{TokenType::COLON, "COLON"},
	{TokenType::QUESTION, "QUESTION"},
	{TokenType::COMMA, "COMMA"},

	{TokenType::INCREMENT, "INCREMENT"},
	{TokenType::DECREMENT, "DECREMENT"},
	{TokenType::PLUSEQUALS, "PLUSEQUALS"},
	{TokenType::MINUSEQUALS, "MINUSEQUALS"},
	{TokenType::NULLISHASSIGNMENT, "NULLISHASSIGNMENT"},

	{TokenType::PLUS, "PLUS"},
	{TokenType::MINUS, "MINUS"},
	{TokenType::STAR, "STAR"},
	{TokenType::MOD, "MOD"},
	{TokenType::SLASH, "SLASH"}	
};

const std::map<std::string, TokenType> RESERVEDKEYWORDS = {
	{"string", TokenType::STRINGTYPE},
	{"int", TokenType::INT},
	{"bool", TokenType::BOOLEAN},
	{"float", TokenType::FLOAT},
	{"class", TokenType::CLASS},
	{"new", TokenType::NEW},
	{"import", TokenType::IMPORT},
	{"from", TokenType::FROM},
	{"if", TokenType::IF},
	{"else", TokenType::ELSE},
	{"foreach", TokenType::FOREACH},
	{"while", TokenType::WHILE},
	{"for", TokenType::FOR},
	{"export", TokenType::EXPORT},
	{"typeof", TokenType::TYPEOF},
	{"func", TokenType::FUNC},
	{"in", TokenType::IN}
};

struct Token {
	std::string Value;
	TokenType Type;

	std::string TokenTypeString();
	void Debug(Token *token);
	bool IsOneOfMany(std::vector<TokenType>* expectedTypes);
	Token(TokenType kind, std::string value);
};
