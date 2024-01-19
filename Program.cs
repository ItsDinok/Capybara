// See https://aka.ms/new-console-template for more information
using Capybara_Language;

Console.WriteLine("Hello, World!");

Lexer lexer = new();

List<Token> tokens = lexer.Tokenise("let x = 5");
for (int i = 0; i < tokens.Count; i++)
{
    Console.WriteLine(tokens[i].Type.ToString());
}

Console.ReadLine();
