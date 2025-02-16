#pragma once
#include "Token.h"
#include <string>
#include <iostream>
#include <regex>
#include <functional>

// Forward declaration for use in handler
struct Lexer;

// Define handler
using RegexHandler = std::function<void(Lexer*, const std::regex&)>;

// This is used to minimise stress in implementation
// It is still cursed
struct RegexPattern {
	RegexPattern(std::string expression, RegexHandler handler);

	std::regex Expression;
	RegexHandler Handler;
};

// Handle specific cases
RegexHandler DefaultHandler(TokenType type, std::string value);
RegexHandler NumberHandler();
RegexHandler SkipHandler();
RegexHandler StringHandler();
RegexHandler SymbolHandler();

struct Lexer {
	std::vector<Token> Tokens;
	std::string SourceCode;
	int Position;
	// These handle automatic tokenisation
	std::regex DefaultRegex = std::regex(R"(\[)");
	std::vector<RegexPattern> Patterns;

	Lexer(std::string& sourceCode);
	void Tokenise();
	void AdvanceDefined(int positions);
	char At();
	bool AtEof();
	std::string Remainder();
	int GetTokenSize();
};
