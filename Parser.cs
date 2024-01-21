using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace Capybara_Language
{
    public class Parser
    {
        private Token[] ?Tokens;

        public Program ProduceAST(string sourceCode)
        {
            Lexer lexer = new();
            Tokens = [.. lexer.Tokenise(sourceCode)];

            Program program = new();
            // Keeping the compiler happy
            if (program.Body == null) return new Program();

            while (NotEOF())
            {
                program.Body.Add(ParseStatement());
            }

            return program;
        }

        private bool NotEOF()
        {
            if (Tokens == null) return false;
            return Tokens[0].Type != TokenType.EOF;
        }

        private Statement ParseStatement()
        {
            return ParseExpression();
        }

        private Expression ParseExpression()
        {
            return new Expression();
        }

        private Expression ParsePrimaryExpression()
        {
            if (Tokens == null) return new Expression();

            Token token = Tokens[0];

            return new Expression();
        }

#pragma warning disable CS8602
        private Token At => Tokens[0];
#pragma warning restore CS8602
    }
}
