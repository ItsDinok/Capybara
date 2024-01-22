using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Capybara_Language.Runtime
{
    // Runtime types are defined here
    enum ValueTypes
    {
        Null,
        Number
    }

    class RuntimeValue
    {
        public ValueTypes Kind;
    }

    class NullValue : RuntimeValue 
    { 
        NullValue()
        {
            this.Kind = ValueTypes.Null;
            string Value = "null";
        }
    }

    class NumberValue : RuntimeValue
    {
        public double Value;
        public NumberValue(double value)
        {
            Value = value;
            Kind = ValueTypes.Number;
        }
    }
}
