using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;

namespace Capybara_Language
{
    enum NodeType
    {
        Program,
        NumericLiteral,
        Identifier,
        BinaryExpression,
        CallExpression,
        UnaryExpression,
        FunctionDeclaration
    }

    // Statements do not return values
    public class Statement
    {
        NodeType Kind { get; }
    }

    public class ProgramStatements : Statement
    {
        public ProgramStatements()
        {
            Kind = NodeType.Program;
            Body = [];
        }

        readonly NodeType Kind = NodeType.Program;
        public List<Statement> ?Body { get; }
    }

    public class Expression : Statement
    {
        
    }

    public class BinaryExpression(Expression left, Expression right, string op) : Expression
    {
        readonly NodeType Kind = NodeType.BinaryExpression;
        Expression Left = left;
        Expression Right = right;
        string Operator = op;
    }

    public class Identifier (string symbol) : Expression
    {
        readonly NodeType Kind = NodeType.Identifier;
        string Symbol = symbol;
    }

    public class NumericLiteral (double value): Expression
    {
        readonly NodeType Kind = NodeType.NumericLiteral;
        double Value = value;
    }
}
