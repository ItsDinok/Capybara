#pragma once
#include <unordered_map>
#include <string_view>
#include <iostream>
#include <vector>
#include <string>

/*
	ADDING NEW TOKENS
	When a new token is added the following steps need to be taken as a checklist:
	- Add token to enum class
	- Add token to dictionary
	- If token is a keyword, add it to that keyword
	- Check the tokeniser function for a branch that uses the new token
	- Make one if needed, make it guarded to avoid unnecessary complications
	- Write tests for it that check tokenisation and syntax
*/

// TODO: Structure and expand
// TODO: Consider exponentiation
enum class TokenType
{
	LEFT_PARENTHESIS,	// (
	RIGHT_PARENTHESIS,	// )
	PLUS,				// +
	MINUS,				// -
	EQUALITY,			// ==
	NOT_EQUALITY,		// !=
	ASSIGNMENT,			// =
	INCREMENT,			// ++
	DECREMENT,			// --
	MODULO,				// %
	ASSIGNMODULO,		// %=
	ASSIGNPLUS,			// +=
	ASSIGNMINUS,		// -=
	STAR,				// *
	ASSIGNSTAR,			// *=
	SLASH,				// /
	ASSIGNSLASH,		// /=
	BOOLEAN,			// true false
	COMMENT,			// // !! ?? >> ?! (Capybara supports comment types)
	NUMBER,				// 123
	STRING,				// "xxx"
	IDENTIFIER,			// varname
	EXPONENT,			// ^

	SEMICOLON,			// ;
	LEFT_BRACE,			// {
	RIGHT_BRACE,		// }
	LEFT_TYPE,			// <
	RIGHT_TYPE,			// >
	COMMA,				// ,
	LEFT_ACCESS,		// [
	RIGHT_ACCESS,		// ]

	OR,					// ||
	AND,				// &&
	NOT,				// !
	GREATER,			// >
	GREATER_EQUAL,		// >=
	LESSER,				// <
	LESSER_EQUAL,		// <=

	T_STRING,			// string
	T_INT,				// int
	T_FLOAT,			// float
	T_DOUBLE,			// double
	T_BOOL,				// bool
	T_VOID,				// void
	T_CHAR,				// char

	IF,					// if
	ELSE,				// else
	WHILE,				// while
	FOR,				// for
	BREAK,				// break
	CONTINUE,			// continue
	RETURN,				// return

	EOF_TOKEN,
};

inline const std::unordered_map<std::string_view, TokenType> reserved_keywords
{
	{"if", TokenType::IF},
	{"else", TokenType::ELSE},
	{"while", TokenType::WHILE},
	{"for", TokenType::FOR},
	{"break", TokenType::BREAK},
	{"continue", TokenType::CONTINUE},
	{"return", TokenType::RETURN},
	{"true", TokenType::BOOLEAN},
	{"false", TokenType::BOOLEAN},
	{"string", TokenType::T_STRING},
	{"int", TokenType::T_INT},
	{"float", TokenType::T_FLOAT},
	{"double", TokenType::T_DOUBLE},
	{"bool", TokenType::T_BOOL},
	{"void", TokenType::T_VOID},	
	{"char", TokenType::T_CHAR},
};

inline const std::unordered_map<TokenType, std::string_view> token_type_names
{
	{ TokenType::LEFT_PARENTHESIS,	"LEFT_PARENTHESIS" },
	{ TokenType::RIGHT_PARENTHESIS,	"RIGHT_PARENTHESIS" },
	{ TokenType::PLUS,				"PLUS" },
	{ TokenType::MINUS,				"MINUS" },
	{ TokenType::EQUALITY,			"EQUALITY" },
	{ TokenType::NOT_EQUALITY,		"NOT_EQUALITY" },
	{ TokenType::ASSIGNMENT,		"ASSIGNMENT" },
	{ TokenType::INCREMENT,			"INCREMENT" },
	{ TokenType::DECREMENT,			"DECREMENT" },
	{ TokenType::MODULO,			"MODULO" },
	{ TokenType::ASSIGNMODULO,		"ASSIGNMODULO" },
	{ TokenType::ASSIGNPLUS,		"ASSIGNPLUS" },
	{ TokenType::ASSIGNMINUS,		"ASSIGNMINUS" },
	{ TokenType::STAR,				"STAR" },
	{ TokenType::ASSIGNSTAR,		"ASSIGNSTAR" },
	{ TokenType::SLASH,				"SLASH" },
	{ TokenType::ASSIGNSLASH,		"ASSIGNSLASH" },
	{ TokenType::BOOLEAN,			"BOOLEAN" },
	{ TokenType::COMMENT,			"COMMENT" },
	{ TokenType::NUMBER,			"NUMBER" },
	{ TokenType::STRING,			"STRING" },
	{ TokenType::IDENTIFIER,		"IDENTIFIER" },
	{ TokenType::T_STRING,			"T_STRING" },
	{ TokenType::T_INT,				"T_INT" },
	{ TokenType::T_FLOAT,			"T_FLOAT" },
	{ TokenType::T_DOUBLE,			"T_DOUBLE" },
	{ TokenType::T_BOOL,			"T_BOOL" },
	{ TokenType::T_VOID,			"T_VOID" },
	{ TokenType::T_CHAR,			"T_CHAR" },
	{ TokenType::IF,				"IF" },
	{ TokenType::ELSE,				"ELSE" },
	{ TokenType::WHILE,				"WHILE" },
	{ TokenType::FOR,				"FOR" },
	{ TokenType::BREAK,				"BREAK" },
	{ TokenType::CONTINUE,			"CONTINUE" },
	{ TokenType::RETURN,			"RETURN" },
	{ TokenType::EOF_TOKEN,			"EOF_TOKEN" },
	{ TokenType::LEFT_ACCESS,		"LEFT_ACCESS" },
	{ TokenType::RIGHT_ACCESS,		"RIGHT_ACCESS" },
	{ TokenType::LEFT_BRACE,		"LEFT_BRACE" },
	{ TokenType::RIGHT_BRACE,		"RIGHT_BRACE" },
	{ TokenType::SEMICOLON,			"SEMICOLON" },
	{ TokenType::LESSER,			"LESSER" },
	{ TokenType::LESSER_EQUAL,		"LESSER_EQUAL" },
	{ TokenType::GREATER,			"GREATER" },
	{ TokenType::GREATER_EQUAL,		"GREATER_EQUAL" },
	{ TokenType::COMMA,				"COMMA" },
	{ TokenType::OR,				"OR" },
	{ TokenType::AND,				"AND" },
	{ TokenType::EXPONENT,			"EXPONENT"},
};

struct Token
{
	std::string value;
	TokenType type;
	size_t line;
	size_t column;

	Token(std::string value, TokenType type, size_t row, size_t column);
	void show();
};
