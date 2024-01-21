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
        private List<Token> Tokens = [];

        public ProgramStatements ProduceAST(string sourceCode)
        {
            Lexer lexer = new();
            Tokens = [.. lexer.Tokenise(sourceCode)];

            ProgramStatements program = new();
            // Keeping the compiler happy
            if (program.Body == null) return new ProgramStatements();

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
            return ParsePrimaryExpression();
        }

        private Expression ParsePrimaryExpression()
        {
            if (Tokens == null) return new Expression();

            TokenType token = At.Type;

            switch (token)
            {
                case TokenType.Identifier: return new Identifier(Eat().Value);
                case TokenType.Number: return new NumericLiteral(double.Parse(Eat().Value));
                case TokenType.OpenParenthesis:
                    break;
                case TokenType.CloseParenthesis:
                    break;
                case TokenType.BinaryOperator:
                    break;
                case TokenType.Let:
                    break;
                case TokenType.EOF:
                    break;
                default:
                    // Unhandled token
                    Console.WriteLine("Unexpected token found during parsing {0}", At.Value);
                    Environment.Exit(1);
                    // Unreachable code
                    return null;
            }
            return new Expression();
        }

        private Token Eat()
        {
            // Simple shift implementation
            Token toReturn = At;
            Tokens.RemoveAt(0);
            return toReturn;
        }

        private Token At => Tokens[0];
    }
}
