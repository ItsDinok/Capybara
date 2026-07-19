#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tokens.h"
#include "lexer.h"

std::string read_file(const std::string &path)
{
	std::ifstream file(path);
	std::string source(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);
	return source;
}

int main(int argc, char* argv[]) 
{
	std::string source;
	if (argc > 1)
	{
		source = read_file(argv[1]);
		std::cout << "Source size: " << source.size() << std::endl;
		Lexer lexer(source);
		std::vector<Token> tokens = lexer.tokenise();
		std::cout << "Tokens: " << tokens.size() << std::endl;
		for (size_t i = 0; i < tokens.size(); ++i)
		{
			tokens[i].show();
		}
	}
}
