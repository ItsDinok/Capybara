#include "lexer.h"
/*
	The tokeniser is very unwieldy and is constantly being iterated on. If anything 
	new gets added to it do your best to keep it clean.
*/

Lexer::Lexer(const std::string &input)
{
	m_source = input;
}

Token Lexer::char_handler()
{
	// Char has its own handler because it can be easily invalidated before parsing
	if (m_source[m_position + 1] == '\'')
	{
		advance(2);
		return Token("", TokenType::T_CHAR, m_line, m_column - 1);
	}
	else if (m_source[m_position + 2] == '\'')
	{
		std::string str_value = std::string(1, m_source[m_position + 1]);
		advance(3);
		return Token(str_value, TokenType::T_CHAR, m_line, m_column - 2);
	}
	else
	{
		token_diagnostics("Char pattern not adhered to!");
	}
	// Unreachable but makes compiler happy
	return Token("", TokenType::EOF_TOKEN, 0, 0);
}

Token Lexer::string_handler()
{
	// Start after the speech mark
	std::string buffer = "";
	advance(1);
	size_t start_line = m_line;
	size_t start_column = m_column;

	while (m_position < m_source.size() && m_source[m_position] != '"')
	{
		buffer += m_source[m_position];
		advance(1);
	}

	// Skip speech mark
	advance(1);
	return Token(buffer, TokenType::T_STRING, start_line, start_column);
}

Token Lexer::comment_handler()
{
	std::string buffer = "";
	size_t start_line = m_line;
	size_t start_column = m_column;

	// End of line comments are the only way
	while (m_position < m_source.size() &&  m_source[m_position] != '\n')
	{
		buffer += m_source[m_position];
		advance(1);
	}

	return Token(buffer, TokenType::COMMENT, start_line, start_column);
}

Token Lexer::literal_handler()
{
	// Numbers do not need to be
	std::string buffer = "";
	size_t start_line = m_line;
	size_t start_column = m_column;

	if (std::isdigit(static_cast<unsigned char>(m_source[m_position])))
	{
		// Start of number literal
		buffer += m_source[m_position];
		advance(1);

		while (std::isdigit(static_cast<unsigned char>(m_source[m_position])))
		{
			buffer += m_source[m_position];
			advance(1);
		}

		return Token(buffer, TokenType::NUMBER, start_line, start_column);
	}

	// Text literal
	while(std::isalnum(static_cast<unsigned char>(m_source[m_position])) || 
		  m_source[m_position] == '_' || m_source[m_position] == '$')
	{
		buffer += m_source[m_position];
		advance(1);
	}

	if (buffer == "")
	{
		token_diagnostics("Unknown character not accepted.");
	}

	// Check against keywords
	if (reserved_keywords.find(buffer) != reserved_keywords.end())
	{
		return Token(buffer, reserved_keywords.find(buffer)->second,
				start_line, start_column);
	}
	else
	{
		return Token(buffer, TokenType::IDENTIFIER,
			start_line, start_column);
	}
}

void Lexer::token_diagnostics(const std::string &error_message)
{
	std::cout << "Syntax error detected!" << std::endl;
	std::cout << "Capybara terminated: " << std::endl;
	std::cout << error_message << " at line: " << m_line << " column: " << m_column << std::endl;
	std::exit(EXIT_FAILURE);
}

// This is just used to reduce LoC and improve readbility
// If this isn't being used it should be
void Lexer::advance(size_t spaces)
{
	m_position += spaces;
	m_column += spaces;
}

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

std::vector<Token> Lexer::tokenise()
{
	std::vector<Token> tokens;

	// Iterate through every character and create tokens from it
	while (m_position < m_source.size())
	{
		switch (m_source[m_position])
		{
			// Empty space
			case '\n':
				++m_position;
				++m_line;
				m_column = 1;
				break;
			case ' ':
			case '\t':
				advance(1);
				break;

			// Simple symbols
			case ';':
				tokens.push_back(Token(";", TokenType::SEMICOLON, 
					m_line, m_column));
				advance(1);
				break;
			case '{':
				tokens.push_back(Token("{", TokenType::LEFT_BRACE,
					m_line, m_column));
				advance(1);
				break;
			case '}':
				tokens.push_back(Token("}", TokenType::RIGHT_BRACE,
					m_line, m_column));
				advance(1);
				break;
			case '[':
				tokens.push_back(Token("[", TokenType::LEFT_ACCESS,
					m_line, m_column));
				advance(1);
				break;
			case ']':
				tokens.push_back(Token("]", TokenType::RIGHT_ACCESS,
					m_line, m_column));
				advance(1);
				break;
			case ',':
				tokens.push_back(Token(",", TokenType::COMMA,
					m_line, m_column));
				advance(1);
				break;
			case '(':
				tokens.push_back(Token("(", TokenType::LEFT_PARENTHESIS,
					m_line, m_column));
				advance(1);
				break;
			case ')':
				tokens.push_back(Token(")", TokenType::RIGHT_PARENTHESIS,
					m_line, m_column));
				advance(1);
				break;
			case '"':
				tokens.push_back(string_handler());
				break;
			case '^':
				tokens.push_back(Token("^", TokenType::EXPONENT,
					m_line, m_column));
				advance(1);
				break;

			// Built symbols
			case '+':
				switch (m_source[m_position + 1])
				{
					case '+':
						tokens.push_back(Token("++", TokenType::INCREMENT,
							m_line, m_column));
						advance(2);
						break;
					case '=':
						tokens.push_back(Token("+=", TokenType::ASSIGNPLUS,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("+", TokenType::PLUS,
							m_line, m_column));
						advance(1);
						break;
				}
				break;
			
			case '-':
				switch (m_source[m_position + 1])
				{
					case '-':
						tokens.push_back(Token("--", TokenType::DECREMENT,
							m_line, m_column));
						advance(2);
						break;
					case '=':
						tokens.push_back(Token("-=", TokenType::ASSIGNMINUS,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("-", TokenType::MINUS,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '%':
				switch (m_source[m_position + 1])
				{
					case '=':
						tokens.push_back(Token("%=", TokenType::ASSIGNMODULO,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("%", TokenType::MODULO,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '*':
				switch (m_source[m_position + 1])
				{
					case '=':
						tokens.push_back(Token("*=", TokenType::ASSIGNSTAR,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("*", TokenType::STAR,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '/':
				switch (m_source[m_position + 1])
				{
					case '=':
						tokens.push_back(Token("/=", TokenType::ASSIGNSLASH,
							m_line, m_column));
						advance(2);
						break;
					case '/':
						tokens.push_back(comment_handler());
						break;
					default:
						tokens.push_back(Token("/", TokenType::SLASH,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '|':
				switch (m_source[m_position + 1])
				{
					case '|':
						tokens.push_back(Token("||", TokenType::OR,
							m_line, m_column));
						advance(2);
						break;
					default:
						// This case is an error. Capybara currently has no |
						token_diagnostics("Symbol | must be followed by another |.");
						break;
				}
				break;

			case '&':
				switch(m_source[m_position + 1])
				{
					case '&':
						tokens.push_back(Token("&&", TokenType::AND,
							m_line, m_column));
						advance(2);
						break;
					default:
						token_diagnostics("Symbol & must be followed by another &");
						break;
				}
				break;

			case '!':
				switch (m_source[m_position +1])
				{
					case '!':
						tokens.push_back(comment_handler());
						break;
					case '=':
						tokens.push_back(Token("!=", TokenType::NOT_EQUALITY,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("!", TokenType::NOT,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '>':
				switch (m_source[m_position + 1])
				{
					case '>':
						tokens.push_back(comment_handler());
						break;
					case '=':
						tokens.push_back(Token(">=", TokenType::GREATER_EQUAL,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token(">", TokenType::GREATER,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '<':
				switch (m_source[m_position + 1])
				{
					case '=':
						tokens.push_back(Token("<=", TokenType::LESSER_EQUAL,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("<", TokenType::LESSER,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			case '=':
				switch (m_source[m_position + 1])
				{
					case '=':
						tokens.push_back(Token("==", TokenType::EQUALITY,
							m_line, m_column));
						advance(2);
						break;
					default:
						tokens.push_back(Token("=", TokenType::ASSIGNMENT,
							m_line, m_column));
						advance(1);
						break;
				}
				break;

			// Char handler
			case '\'':
				tokens.push_back(char_handler());
				break;

			// Comment types
			case '?':
				switch (m_source[m_position + 1])
				{
					case '?':
					case '!':
						tokens.push_back(comment_handler());
						break;
					default:
						token_diagnostics("Comment demarcater must be followed by ! or ?");
						break;
				}
				break;

			default:
				tokens.push_back(literal_handler());
				break;
		}
	}

	tokens.push_back(Token("EOF", TokenType::EOF_TOKEN, m_line, m_column));
	return tokens;
}
