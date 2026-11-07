#include "lexer.h"
/*
	The tokeniser is very unwieldy and is constantly being iterated on. If anything 
	new gets added to it do your best to keep it clean.
*/

// BUG: String handler does not catch an unclosed string
// TODO: Compiler comments
// BUG: >> comment needs to start on FIRST whitespace of a newline

Lexer::Lexer(const std::string &input)
{
	m_source = input;
}

// This processes string escapes such as \n
std::string escape_handler(char next_)
{
	switch(next_)
	{
		case 't':
		case 'n':
		case '\\':
		case '0':
		case 'r':
		case '"':
			return "\\" + std::string(1, next_);
		default:
			return "-1";
	}
}

Token Lexer::char_handler()
{
	// Char has its own handler because it can be easily invalidated before parsing
	if (m_source[m_position + 1] == '\'')
	{
		token_diagnostics("Empty chars are not valid. For a blank char use ' '");
	} else if (m_position + 2 > m_source.size())
	{
		token_diagnostics("Char pattern not adhered to!");
	}
	// Typical case
	else if (m_source[m_position + 2] == '\'')
	{
		std::string str_value = std::string(1, m_source[m_position + 1]);
		advance(3);
		return Token(str_value, TokenType::CHAR, m_line, m_column - 2);
	}
	// Escape characters (\)
	else if (m_source[m_position + 1] == '\\')
	{
		std::string sequence = escape_handler(m_source[m_position + 2]);
		if (sequence == "-1")
		{
			token_diagnostics("Invalid escape character.");
			return Token("NULL", TokenType::EOF_TOKEN, 0, 0);
		}

		advance(4);
		return Token(sequence, TokenType::CHAR, m_line, m_column -3);
	}
	// Unreachable but it makes the compiler happy
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
		// Handle escape characters
		if (m_source[m_position] == '\\')
		{
			std::string sequence = escape_handler(m_source[m_position + 1]);
			if (sequence == "-1") 
			{
				token_diagnostics("Invalid escape character.");
				return Token("NULL", TokenType::EOF_TOKEN, 0, 0);
			}

			buffer += sequence;
			advance(2);
			continue;
		}

		buffer += m_source[m_position];
		advance(1);
	}

	// Skip speech mark
	advance(1);
	return Token(buffer, TokenType::STRING, start_line, start_column);
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

		bool is_dot = false;
		while (std::isdigit(static_cast<unsigned char>(m_source[m_position]))
			|| (m_source[m_position] == '.' && !is_dot))
		{
			if (m_source[m_position] == '.') is_dot = true;
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

// This checks to see if it is a one digit or multidigit token and then handles it accordingly
// TODO: Efficient error handling (table maybe?)
bool Lexer::emit(const char value, std::vector<Token>& tokens)
{
	std::string with_next = std::string (1, value) + m_source[m_position + 1];

	// Comment indicators
	if (comment_indicators.contains(with_next))
	{
		tokens.push_back(comment_handler());
		return true;
	}

	// Pair tokens
	if (pair_types.contains(with_next))
	{
		tokens.push_back(Token(with_next, pair_types.find(with_next)->second,
			m_line, m_column));
		advance(2);
		return true;
	}

	// Char/String handlers
	if (value == '"')
	{
		tokens.push_back(string_handler());
		return true;
	}
	if (value == '\'')
	{
		tokens.push_back(char_handler());
		return true;
	}

	// Single digit tokens
	if (single_char_types.contains(value))
	{
		tokens.push_back(Token(std::string(1, value), single_char_types.find(value)->second,
			m_line, m_column));
		advance(1);
		return true;
	}

	// Odd default edge cases
	switch (value)
	{
		case ' ':
		case '\t':
			advance(1);
			return true;
		case '\n':
			++m_position;
			++m_line;
			m_column = 1;
			return true;
	
		// NOTE: These must have passed their valid points
		case '|':
			token_diagnostics("| is not a valid symbol!");
			return false;
		case '&':
			token_diagnostics("& is not a valid symbol!");
			return false;
		default:
			break;
	}

	tokens.push_back(literal_handler());
	return true;
}

std::vector<Token> Lexer::tokenise()
{
	std::vector<Token> tokens;

	// Iterate through every character and create tokens from it
	while (m_position < m_source.size())
	{
		if (emit(m_source[m_position], tokens)) continue;
	}

	tokens.push_back(Token("EOF", TokenType::EOF_TOKEN, m_line, m_column));
	return tokens;
}
