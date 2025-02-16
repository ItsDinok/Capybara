#include "Token.h"

void Token::Debug(Token *token) {
	std::vector<TokenType> expectedTypes = {
		TokenType::IDENTIFIER,
		TokenType::NUMBER,
		TokenType::STRING
	};

	if (token->IsOneOfMany(&expectedTypes)) {
		
		std::cout << token->TokenTypeString() << token->Value << std::endl;
	}
	else {
		std::cout << token->TokenTypeString() << std::endl;
	}
}

// Returns string value of token
std::string Token::TokenTypeString() {
	// Isn't C++ elegant?
	auto iterator = TokenTypeValues.find(this->Type);
	return iterator->second;
}

Token::Token(TokenType kind, std::string value) : Type(kind), Value(value) {}

// Used in debugging
bool Token::IsOneOfMany(std::vector<TokenType>* expectedTypes) {
	for (int i = 0; i < expectedTypes->size(); ++i) {
		if ((*expectedTypes)[i] == this->Type) {
			return true;
		}
	}
	return false;
}
