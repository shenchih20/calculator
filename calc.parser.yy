%require "2.4"
%language "C++"
%locations
%defines
%debug
%define api.namespace {calc}
%define api.parser.class {CalcParser}
%parse-param {Calculator &calculator}
%lex-param {Calculator &calculator}
%define parse.error verbose

%defines "calc.parser.hh"
%output "calc.parser.cc"

%{     /* PARSER */

#include "calc.parser.hh"
#include "calc.lexer.hh"

#define yylex calculator.lexer_->yylex
%}

%code requires
{
  #include <iostream>
  #include "calculator.hpp"
  #include "location.hh"
  #include "position.hh"
}

%code provides
{
  namespace calc
  {
    // Forward declaration of the Calculator class
    class Calculator;

    inline void
    yyerror (const char* msg)
    {
      std::cerr << msg << std::endl;
    }
  }
}

%union
{
AstNode* ast;
double value;
char oper;
}

/* Tokens */
%token <value> NUMBER

%token ADD // '+'
%token SUB // '-'
%token MUL // '*'
%token DIV // '/'
%token LEFT_P // '('
%token RIGHT_P // ')'


%token ENDLINE 

%type <ast> primary_expression
%type <ast> unary_expression
%type <oper> unary_operator
%type <ast> cast_expression
%type <ast> multiplicative_expression
%type <ast> additive_expression
%type <ast> expression


/* Entry point of grammar */
%start start

%%

start
  : expression ENDLINE { calculator.eval($1); }
  ;

primary_expression
  : NUMBER { $$ = calculator.creator_.Number($1); }
  | LEFT_P expression RIGHT_P { $$ = $2; }
  ;

unary_expression
  : primary_expression { $$ = $1;}
  | unary_operator cast_expression { $$ = calculator.creator_.UnaryOp($1, $2);}
  ;

unary_operator
  : ADD   {$$ = '+';}
  | SUB   {$$ = '-';}
  ;

cast_expression
  : unary_expression {$$=$1;}
  ;

multiplicative_expression
  : cast_expression { $$ = $1; }
  | multiplicative_expression MUL cast_expression { $$ = calculator.creator_.BinaryOp($1, '*', $3); }
  | multiplicative_expression DIV cast_expression { $$ = calculator.creator_.BinaryOp($1, '/', $3); }
  ;

additive_expression
  : multiplicative_expression { $$ = $1; }
  | additive_expression ADD multiplicative_expression { $$ = calculator.creator_.BinaryOp($1, '+', $3); }
  | additive_expression SUB multiplicative_expression { $$ = calculator.creator_.BinaryOp($1, '-', $3); }
  ;

expression
	: additive_expression  { $$=$1;}		
	;

%%

namespace calc
{
    void CalcParser::error(const location& l, const std::string& m)
    {
        std::cerr << l << ": " << m << std::endl;
        calculator.error_ = (calculator.error_ == 127 ? 127 : calculator.error_ + 1);
    }
}
