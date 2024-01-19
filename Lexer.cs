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
        Let,
        BinaryOperator,
        Identifier,
        Number
    }

    public struct Token
    {
        public Token(string value, TokenType type)
        {
            Value = value; Type = type;
        }

        public string Value;
        public TokenType Type;
    }

    public class Lexer
    {
        public readonly Dictionary<string, TokenType> KEYWORDS = new()
        {
            {"let", TokenType.Let }
        };


        private List<Token> ?Tokens;

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
                            sourceCode.RemoveRange(0, toAdd.Value.Length - 1);
                        }
                        else if (IsNumber(sourceCode[0]))
                        {
                            Token toAdd = HandleMultiCharNumber(sourceCode);
                            Tokens.Add(toAdd);
                            sourceCode.RemoveRange(0, toAdd.Value.Length - 1);
                        }
                        else if (IsSkippable(sourceCode[0]))
                        {
                            sourceCode.RemoveAt(0);
                        }
                        break;
                }
            }

            return Tokens;
        }

        private static bool IsSkippable(string source)
        {
            return (source[0] == ' ' || source[0] == '\t' || source[0] == '\n');
        }

        private static bool IsNumber(string source)
        {
            return int.TryParse(source[0].ToString(), out _);
        }

        private Token HandleMultiCharNumber(List<string> sourceCode)
        {
            Token toReturn = new Token();
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
            Token toReturn = new Token();
            string toTokenise = "";

            while(sourceCode.Count > 0 && char.IsLetter(char.Parse(sourceCode[0].ToString()))) {
                toTokenise += sourceCode[0];
                sourceCode.RemoveAt(0);
            }

            toReturn.Value = toTokenise;

            // Check to see if token is a keyword
            if (KEYWORDS.ContainsKey(toTokenise)) toReturn.Type = KEYWORDS[toTokenise];
            else toReturn.Type = TokenType.Identifier;

            return toReturn;
        }
    }

}
