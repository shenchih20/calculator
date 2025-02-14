%option debug
%option c++
%option noyywrap
%option never-interactive
%option yylineno
%option nounput
%option batch
%option prefix="calc"
%option outfile="calc.lexer.cc"

%{                                                            /* -*- C++ -*- */

#include "calc.parser.hh"
#include "calc.lexer.hh"
#include "calculator.hpp"

/*  Defines some macros to update locations */


#define STEP()                                      \
  do {                                              \
    yylloc->step ();                      \
  } while (0)

#define COL(Col)				                            \
  yylloc->columns (Col)

#define LINE(Line)				                          \
  do{						                                    \
    yylloc->lines (Line);		              \
 } while (0)

#define YY_USER_ACTION				                      \
  COL(yyleng);


typedef calc::CalcParser::token token;
typedef calc::CalcParser::token_type token_type;

#define yyterminate() return token::YYEOF;

%}



/*
%option stack
*/

/* Abbreviations.  */

blank   [ \t]+
eol     [\n\r]+

%%

 /* The rules.  */
%{
  STEP();
%}

[0-9]+ {
    yylval->value = atof(yytext);	  
	  return token::NUMBER; 
}

[0-9]+"."[0-9]+ {
    yylval->value = atof(yytext);	  
	  return token::NUMBER; 
}

" " { } // ignore space
"+" { return token::ADD; }
"-" { return token::SUB; }
"*" { return token::MUL; }
"/" { return token::DIV; }
"(" { return token::LEFT_P; }
")" { return token::RIGHT_P; }

[\n] {return token::ENDLINE;}

.             {

                std::cerr << *yylloc << " Unexpected token : " << *yytext << std::endl;                
                return token::YYerror;

              }

%%


/*

   CUSTOM C++ CODE

*/

namespace calc
{

    CalcLexer::CalcLexer()
    : calcFlexLexer()
    {
    }

    CalcLexer::~CalcLexer()
    {
    }

    void CalcLexer::set_debug(bool b)
    {
        yy_flex_debug = b;
    }
}

#ifdef yylex
# undef yylex
#endif

int calcFlexLexer::yylex()
{
  std::cerr << "call calcFlexLexer::yylex()!" << std::endl;
  return 0;
}
