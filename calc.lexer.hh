
#pragma once

#include "calc.parser.hh"


#ifndef YY_DECL
#define YY_DECL calc::CalcParser::token_type                         \
        calc::CalcLexer::yylex(calc::CalcParser::semantic_type* yylval,    \
        calc::CalcParser::location_type* yylloc, \
        calc::Calculator& calculator)
# endif


#ifndef __FLEX_LEXER_H
#define yyFlexLexer calcFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif


namespace calc
{
    class CalcLexer : public calcFlexLexer
    {
        public:
            CalcLexer();

            virtual ~CalcLexer();

            virtual CalcParser::token_type yylex(CalcParser::semantic_type* yylval,
                                                 CalcParser::location_type* yylloc,
                                                 Calculator& calculator);

            void set_debug(bool b);
    };
}


