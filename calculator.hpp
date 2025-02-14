#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "ast.hpp"

namespace calc
{
    /// Forward declarations of classes
    class CalcParser;
    class CalcLexer;
    class location;

   

    class Calculator
    {
    public:
        Calculator();
        ~Calculator();
        
        int parse_string(std::string &path);

        void reset();

    private:
        void eval(AstNode *node);
        AstCreator creator_;
        CalcLexer* const lexer_ ;
        CalcParser* const parser_;
        int error_;

        /// Allows Parser and Scanner to access private attributes
        /// of the Driver class
        friend class CalcParser;
        friend class CalcLexer;
    };
}
