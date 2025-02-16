#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Lexer.h"

std::string ReadFile(std::string source) {
	std::ifstream file(source);
	std::string code(
		(std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>()
	);

	return code;
}

int main() {
	std::string code = ReadFile(
			"C:/Users/markd/Desktop/Capybara/Test.txt");
	Lexer lexer(code);
	for (int i = 0; i < lexer.GetTokenSize(); i++) {
		std::cout << lexer.Tokens[i].Value << std::endl;
	}
	return 0;
}
