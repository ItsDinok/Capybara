using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Reflection.Metadata.Ecma335;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;

namespace Capybara_Language.Frontend
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
            return ParseAdditiveExpression();
        }

        // Handle orders of precedence
        // AssignmentExpression -> MemberExpression -> FunctionCall -> Logical
        // -> Comparitive -> Additive -> Multiplicative -> Unary -> PrimaryExpression
        // Parse higher orders last

        private Expression ParseAdditiveExpression()
        {
            // Left hand precedence
            Expression left = ParseMultiplicativeExpression();

            // Checks multiplication first
            while (At().Value == "+" || At().Value == "-")
            {
                string op = Eat().Value;
                Expression right = ParseMultiplicativeExpression();
                left = new BinaryExpression(left, right, op);
            }

            return left;
        }

        private Expression ParseMultiplicativeExpression()
        {
            Expression left = ParsePrimaryExpression();

            // Recursively work through multiplicative statements
            while (At().Value == "*" || At().Value == "/" || At().Value == "%")
            {
                string op = Eat().Value;
                Expression right = ParsePrimaryExpression();
                left = new BinaryExpression(left, right, op);
            }

            return left;
        }

        private Expression ParsePrimaryExpression()
        {
            TokenType token = At().Type;

            switch (token)
            {
                case TokenType.Identifier: return new Identifier(Eat().Value);
                case TokenType.Number: return new NumericLiteral(double.Parse(Eat().Value));
                case TokenType.OpenParenthesis:
                    Eat(); // Eat opening bracket
                    Expression value = ParseExpression();
                    Expect(TokenType.CloseParenthesis, "Unexpected token type found, expected )"); // Eat closing parenthesis
                    return value;
                case TokenType.Null:
                    Eat(); // Advance past null
                    return new NullLiteral();
                default:
                    // Unhandled token
                    Console.WriteLine("Unexpected token found during parsing {0}", At().Value);
                    Environment.Exit(1);
                    // Unreachable code
                    return null;
            }
        }

        private Token Eat()
        {
            // Simple shift implementation
            Token toReturn = At();
            Tokens.RemoveAt(0);
            return toReturn;
        }

        private Token Expect(TokenType expected, string error)
        {
            Token token = Eat();
            if (token.Type != expected)
            {
                Console.WriteLine(error);
                Environment.Exit(1);
            }

            return token;
        }

        private Token At() => Tokens[0];
    }
}
