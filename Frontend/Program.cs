using Capybara_Language.Frontend;

Parser parser = new();
Console.WriteLine("Capybara 0.1");

while (true)
{
    Console.Write("> ");
    string? input = Console.ReadLine();

    if (input == null) continue;
    if (input.Contains("exit")) Environment.Exit(0);

    // TODO: Rename ProgramStatements
    ProgramStatements AST = parser.ProduceAST(input);
    if (AST.Body == null) continue;
    for (int i = 0; i < AST.Body.Count; i++)
    {
        Console.WriteLine(AST.Body[i].ToString());
    }
}
