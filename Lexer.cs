using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Capybara_Language
{
    public enum TokenType
    {
        Equals,
        OpenParenthesis,
        CloseParenthesis,
        BinaryOperator,

        // Keywords
        Let,

        // Literals
        Identifier,
        Number,

        EOF // End of file
    }

    public struct Token(string value, TokenType type)
    {
        public string Value = value;
        public TokenType Type = type;
    }

    public class Lexer
    {
        public readonly Dictionary<string, TokenType> KEYWORDS = new()
        {
            {"let", TokenType.Let }
        };


        private List<Token> ?Tokens;
        private static readonly char[] SkippableArray = ['\n', '\t', ' '];

        public List<Token> Tokenise(string source)
        {
            Tokens = [];
            List<string> sourceCode = source.Select(c => c.ToString()).ToList();

            while(sourceCode.Count > 0)
            {
                switch(sourceCode[0])
                {
                    case "=":
                        Tokens.Add(new Token(sourceCode[0], TokenType.Equals));
                        sourceCode.RemoveAt(0); break;
                    case "(":
                        Tokens.Add(new Token(sourceCode[0], TokenType.OpenParenthesis));
                        sourceCode.RemoveAt(0); break;
                    case ")":
                        Tokens.Add(new Token(sourceCode[0], TokenType.CloseParenthesis));
                        sourceCode.RemoveAt(0); break;
                    case "*":
                    case "+":
                    case "-":
                    case "/":
                        Tokens.Add(new Token(sourceCode[0], TokenType.BinaryOperator));
                        sourceCode.RemoveAt(0); break;
                    default:
                        // Must be multicharacter
                        if (char.IsLetter(char.Parse(sourceCode[0])))
                        {
                            Token toAdd = HandleMultiCharString(sourceCode);
                            // TODO: test this
                            Tokens.Add(toAdd);
                            for (int i = 0; i < toAdd.Value.Length - 1; i++)
                            {
                                if (sourceCode.Count == 0) break;
                                sourceCode.RemoveAt(0);
                            }
                        }
                        else if (IsNumber(sourceCode[0]))
                        {
                            Token toAdd = HandleMultiCharNumber(sourceCode);
                            Tokens.Add(toAdd);
                            for (int i = 0; i < toAdd.Value.Length -1; i++)
                            {
                                if (sourceCode.Count == 0) break;
                                sourceCode.RemoveAt(0);
                            }
                        }
                        else if (IsSkippable(sourceCode[0]))
                        {
                            sourceCode.RemoveAt(0);
                        }
                        break;
                }
            }

            Tokens.Add(new Token("EOF", TokenType.EOF));
            return Tokens;
        }

        private static bool IsSkippable(string source) => SkippableArray.Contains(source[0]);
        private static bool IsNumber(string source) => int.TryParse(source[0].ToString(), out int _);

        private static Token HandleMultiCharNumber(List<string> sourceCode)
        {
            Token toReturn = new();
            string toTokenise = "";

            while(sourceCode.Count > 0 && IsNumber(sourceCode[0].ToString()))
            {
                toTokenise += sourceCode[0].ToString();
                sourceCode.RemoveAt(0);
            }

            toReturn.Value = toTokenise; toReturn.Type = TokenType.Number;
            return toReturn;
        }

        private Token HandleMultiCharString(List<string> sourceCode)
        {
            Token toReturn = new();
            string toTokenise = "";

            while(sourceCode.Count > 0 && char.IsLetter(char.Parse(sourceCode[0].ToString()))) {
                toTokenise += sourceCode[0];
                sourceCode.RemoveAt(0);
            }

            toReturn.Value = toTokenise;

            // Check to see if token is a keyword
            if (KEYWORDS.TryGetValue(toTokenise, out TokenType value)) toReturn.Type = value;
            else toReturn.Type = TokenType.Identifier;

            return toReturn;
        }
    }

}
