#include "tokens.h"

Token::Token(std::string value, TokenType type, size_t row, size_t column)
{
	this->value = value;
	this->type = type;
	this->line = row;
	this->column = column;
}

void Token::show()
{
	std::cout << "\nType: " << token_type_names.find(type)->second << std::endl;
	std::cout << "Value: " << value << std::endl;
	std::cout << "Line, Column: " << line << ", " << column << std::endl; 
}

