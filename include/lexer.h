#pragma once
#include "tokens.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>

/*
	Typically I wouldn't feel the need to use a class for this, it should just be a spider function
	But that being said it is a very complex bit of kit and I think internal methods and variables will
	help keep namespace clarity down the line. It also does kind of behave like an object so fuck it

	I am also aware that a lot of lexers use regex-based lexing to create tokens
	I find in C++ this introduces nightmarish complexity and unreadable code
	I will therefore use an iterative approach, which works out as similar speed to a regex engine anyway
*/

// TODO: Missing features:
/*
	- Char support
	- Float support
	- Syntax support for 123abc (should fail)
*/

class Lexer
{
public:
	explicit Lexer(const std::string &input);
	std::vector<Token> tokenise();

private:
	Token comment_handler();
	Token literal_handler();
	Token string_handler();
	Token char_handler();

	void token_diagnostics(const std::string &error_message);
	void advance(size_t spaces);

	std::string m_source;
	size_t m_position = 0;

	size_t m_line = 1;
	size_t m_column = 1;
};
