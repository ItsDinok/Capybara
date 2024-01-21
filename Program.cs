using Capybara_Language;

Parser parser = new();
Console.WriteLine("Capybara 0.0.1 \n\n");

while (true)
{
    Console.Write("> ");
    string? input = Console.ReadLine();

    if (input == null) continue;
    if (input.Contains("exit")) Environment.Exit(0);

    // TODO: Rename ProgramStatements
    ProgramStatements AST = parser.ProduceAST(input);
    Console.WriteLine(AST);
}
