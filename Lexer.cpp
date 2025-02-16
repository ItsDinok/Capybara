#include "Lexer.h"

// Lexer code
Lexer::Lexer(std::string& sourceCode) {
	this->SourceCode = sourceCode;
	this->Position = 0;
	
	// XXX: Not a fan of adding to this at runtime
	this->Patterns = {
		{ RegexPattern(R"([a-zA-Z_][a-zA-Z0-9_]*)", SymbolHandler()) },
		{ RegexPattern(R"([0-9]+(\.[0-9]+)?)", NumberHandler()) },	
		{ RegexPattern(R"(\s+)",	SkipHandler()) },
		{ RegexPattern(R"("[^"]*")",StringHandler())},
		{ RegexPattern(R"(\/\/.*)",	SkipHandler())},
		{ RegexPattern(R"(\[)",		DefaultHandler(TokenType::OPENSQUARE, "[")) },
		{ RegexPattern(R"(\])",		DefaultHandler(TokenType::CLOSESQUARE, "]")) },
		{ RegexPattern(R"(\{)",		DefaultHandler(TokenType::OPENCURLY, "{")) },
		{ RegexPattern(R"(\})",		DefaultHandler(TokenType::CLOSECURLY, "}")) },
		{ RegexPattern(R"(\()",		DefaultHandler(TokenType::OPENPARENTHESIS, "(")) },
		{ RegexPattern(R"(\))",		DefaultHandler(TokenType::CLOSEPARENTHESIS, ")")) },
		{ RegexPattern(R"(==)",		DefaultHandler(TokenType::EQUALTO, "==")) },
		{ RegexPattern(R"(!=)",		DefaultHandler(TokenType::NOTEQUAL, "!=")) },
		{ RegexPattern(R"(=)",		DefaultHandler(TokenType::ASSIGNMENT, "=")) },
		{ RegexPattern(R"(!)",		DefaultHandler(TokenType::NOT, "!")) },
		{ RegexPattern(R"(<=)",		DefaultHandler(TokenType::LESSEQUALS, "<=")) },
		{ RegexPattern(R"(<)",		DefaultHandler(TokenType::LESS, "<")) },
		{ RegexPattern(R"(>=)",		DefaultHandler(TokenType::GREATEREQUALS, ">=")) },
		{ RegexPattern(R"(>)",		DefaultHandler(TokenType::GREATER, ">")) },
		{ RegexPattern(R"(\|\|)",	DefaultHandler(TokenType::OR, "||")) },
		{ RegexPattern(R"(&&)",		DefaultHandler(TokenType::AND, "&&")) },
		{ RegexPattern(R"(\.\.)",	DefaultHandler(TokenType::DOTDOT, "..")) },
		{ RegexPattern(R"(\.)",		DefaultHandler(TokenType::DOT, ".")) },
		{ RegexPattern(R"(;)",		DefaultHandler(TokenType::SEMICOLON, ";")) },
		{ RegexPattern(R"(:)",		DefaultHandler(TokenType::COLON, ":")) },
		{ RegexPattern(R"(\?\?\=)", DefaultHandler(TokenType::NULLISHASSIGNMENT, "?""?=")) },
		{ RegexPattern(R"(\?)",		DefaultHandler(TokenType::QUESTION, "?")) },
		{ RegexPattern(R"(,)",		DefaultHandler(TokenType::COMMA, ",")) },
		{ RegexPattern(R"(\+\+)",	DefaultHandler(TokenType::INCREMENT, "++")) },
		{ RegexPattern(R"(--)",		DefaultHandler(TokenType::DECREMENT, "--")) },
		{ RegexPattern(R"(\+=)",	DefaultHandler(TokenType::PLUSEQUALS, "+=")) },
		{ RegexPattern(R"(-=)",		DefaultHandler(TokenType::MINUSEQUALS, "-=")) },
		{ RegexPattern(R"(\+)",		DefaultHandler(TokenType::PLUS, "+")) },
		{ RegexPattern(R"(-)",		DefaultHandler(TokenType::MINUS, "-")) },
		{ RegexPattern(R"(/)",		DefaultHandler(TokenType::SLASH, "/")) },
		{ RegexPattern(R"(\*)",		DefaultHandler(TokenType::STAR, "*")) },
		{ RegexPattern(R"(%)",		DefaultHandler(TokenType::MOD, "%")) }	
	};

	Tokenise();
}

// TODO: Look into removing this
int Lexer::GetTokenSize() {
	return this->Tokens.size();
}

void Lexer::Tokenise() {
	while (!this->AtEof()) {
		// This variable is used in debug
		bool matched = false;
		std::string remainder = this->Remainder();

		// TODO: Update this to be ranged based syntax
		// Checks against every regex pattern to see if it is matching
		for (int i = 0; i < this->Patterns.size(); ++i) {
			int start = -1;
			std::smatch match;
			if (std::regex_search(remainder, match, Patterns[i].Expression)) {
				start = match.position();
			}

			if (start != 0) {
				continue;
			}
		
			Patterns[i].Handler(this, Patterns[i].Expression);
			matched = true;
			break;
		}
		// DEBUG
		if (!matched) {
			std::cout << "Undefined token at position" << this->Position << std::endl;
			std::cout << this->At() << std::endl;
		}
	}

	this->Tokens.push_back(Token(TokenType::EOFTOKEN, "EOF"));
}

// Moves a certain amount
void Lexer::AdvanceDefined(int positions) {
	this->Position += positions;
}

// Checks what is at the position value
char Lexer::At() {
	return this->SourceCode[this->Position];
}

// Gets remainder of string, including position
std::string Lexer::Remainder() {
	return this->SourceCode.substr(this->Position);
}

// Determines if EOF has been reached
bool Lexer::AtEof() {
	return this->Position >= this->SourceCode.size();
}

// Cursed Regex Stuff
RegexPattern::RegexPattern(std::string expression, RegexHandler handler) {
	this->Expression = std::regex(expression);
	this->Handler = handler;
}

// Adds current character as token
RegexHandler DefaultHandler(TokenType type, std::string value) {
	return [type, value](Lexer* lexer, const std::regex& regex) {
		lexer->AdvanceDefined(value.size());
		lexer->Tokens.push_back(Token(type, value));
	};
}

// Adds number token
RegexHandler NumberHandler() {
	return [](Lexer* lexer, const std::regex& regex) {
		std::smatch match;
		std::string remainder = lexer->Remainder();

		if (std::regex_search(remainder, match, regex)) {
			lexer->Tokens.push_back(Token(TokenType::NUMBER, match.str()));
			lexer->AdvanceDefined(match.str().size());
		}
		else {
			std::cout << "No number, apparently." << std::endl;
		}
	};
}

// Skips whitespace
RegexHandler SkipHandler() {
	return [](Lexer* lexer, const std::regex& regex) {
		std::smatch match;
		std::string remainder = lexer->Remainder();

		if (std::regex_search(remainder, match, regex)) {
			lexer->AdvanceDefined(match.str().size());
		}
	};
}

RegexHandler StringHandler() {
	return [](Lexer* lexer, const std::regex& regex) {
		std::smatch match;
		std::string remainder = lexer->Remainder();

		if (std::regex_search(remainder, match, regex)) {
			// Remove beginning and end quotation marks
			std::string text = match.str();
			text.erase(0,1);
			text.erase(text.size() -1);

			lexer->Tokens.push_back(Token(TokenType::STRING, text));
			lexer->AdvanceDefined(match.str().size());
		}
	};
}

RegexHandler SymbolHandler() {
	return [](Lexer* lexer, const std::regex& regex) {
		std::smatch match;
		std::string remainder = lexer->Remainder();

		if (std::regex_search(remainder, match, regex)) {
			// It returns .end() if it does not exist
			if (RESERVEDKEYWORDS.find(match.str()) != RESERVEDKEYWORDS.end()) {
				// This simply adds a reserved keyword with token type in dictionary
				// C++ syntax is making it bad
				TokenType type = RESERVEDKEYWORDS.find(match.str())->second;
				lexer->Tokens.push_back(Token(type, match.str()));
				lexer->AdvanceDefined(match.str().size());
			}
			else {
				lexer->Tokens.push_back(Token(TokenType::IDENTIFIER, match.str()));
				lexer->AdvanceDefined(match.str().size());
			}
		}
	};
}

