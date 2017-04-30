%{
/* Author: Alexander Owen
 *
 * Bison grammar for the Quack programming language
 * As input, takes tokens from Flex, parses tokens into an Abstract Syntax Tree
 * The root of the AST is stored in 'root'
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream>

#include "visitors.hpp"
#include "TypeTree.hpp"
#include "nodes.hpp"
#include "lex.yy.h"
#include "grammar.tab.h"

using namespace std;
using std::list;

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char *msg);

Program *root;
%}
%locations

%union {
    int integer;
    char *id;
    std::list<Statement *> *stmts;
    std::list<Class *>     *clsss; 
    std::list<RExpr *> *rexprs;
    std::list<ElifClause *> *elifs;
    std::list<FormalArg *> *fargs;
    std::list<Method *> *meths;
    Class *cls;
    ClassBody *clsbdy;
    ClassSignature *clssig;
    Statement *stmt;
    Method *meth;
    IfClause *_if;
    ElifClause *_elif;
    ElseOption *_else;
    IdentOption *idop;
    ExtendsOption *exop;
    FormalArg *farg;
    RExpr *rexpr;
    LExpr *lexpr;
    Program *pgm;

}

%token <integer> INT_LIT
%token <id>      STRING_LIT IDENT
%token CLASS DEF EXTENDS IF ELIF ELSE WHILE RETURN 
%token ATLEAST ATMOST EQUALS AND OR NOT 

%left AND OR NOT
%left '<' '>' '=' ATMOST ATLEAST EQUALS 
%left '+' '-'
%left '*' '/'
%left '.'

%type <pgm> program
%type <clsbdy> class_body
%type <clssig> class_signature
%type <stmt> statement
%type <stmts> statement_star
%type <stmts> statement_block
%type <meth> method
%type <meths> method_star
%type <farg> formal_arg
%type <fargs> formal_args
%type <fargs> extra_formal_args_star
%type <exop> extends_option
%type <_if> if_clause
%type <_elif> elif_clause
%type <_else> else_option
%type <elifs> elif_star
%type <rexpr> r_expr
%type <rexpr> r_expr_option
%type <lexpr> l_expr
%type <cls> class
%type <clsss> class_star 
%type <idop> ident_option
%type <rexprs> actual_args extra_actual_args
%%
program:
        class_star statement_star {$$ = new Program($1, $2, @$.first_line); $$->setLineno(@$.first_line); root = $$;}
        ;

class_star: 
            /* epsilon */    {$$ = new std::list<Class *>();}
          | class_star class {$$ = $1; $1->push_back($2);}
          ;

class:
     class_signature class_body {$$ = new Class($1, $2); $$->setLineno(@$.first_line);}
    ;

class_signature:
               CLASS IDENT '(' formal_args ')' extends_option  {$$ = new ClassSignature($2, $4, $6); $$->setLineno(@$.first_line);}
             ;

extends_option:
              /* epsilon */ {$$ = new FalseExtendsOption(); $$->setLineno(@$.first_line);}
            | EXTENDS IDENT {$$ = new TrueExtendsOption($2); $$->setLineno(@$.first_line);}
            ;

formal_args: 
             /* epsilon */  {$$ = new std::list<FormalArg *>();}
           | formal_arg extra_formal_args_star  {$$ = $2; $2->push_front($1);} 
           ;

formal_arg:
          IDENT ':' IDENT {$$ = new FormalArg($1, $3); $$->setLineno(@$.first_line);}
        ;

extra_formal_args_star: 
                  /* epsilon */ {$$ = new std::list<FormalArg *>();}
                | extra_formal_args_star ',' formal_arg {$$ = $1; $1->push_back($3);}  
                ;

class_body:
          '{' statement_star method_star '}' {$$ = new ClassBody($2, $3); $$->setLineno(@$.first_line);}

method:
       DEF IDENT '(' formal_args ')' ident_option statement_block {$$ = new Method($2, $4, $6, $7); $$->setLineno(@$.first_line);}
     ;

method_star:
          /* epsilon */      {$$ = new std::list<Method *>();}
        | method_star method {$$ = $1; $1->push_back($2);}
        ;

ident_option:
          /* epsilon */ {$$ = new FalseIdentOption(); $$->setLineno(@$.first_line);}
        | ':' IDENT     {$$ = new TrueIdentOption($2); $$->setLineno(@$.first_line);}
        ;

statement_star: 
          /* epsilon */            {$$ = new std::list<Statement *>();}
        | statement_star statement {$$ = $1; $1->push_back($2);} 
        ;

statement_block:
                '{' statement_star  '}' {$$ = $2;}
                ;

statement:
          if_clause elif_star else_option    {$$ = new IfBlock($1, $2, $3); $$->setLineno(@$.first_line);}
        | WHILE r_expr statement_block       {$$ = new WhileStatement($2, $3); $$->setLineno(@$.first_line);}
        | l_expr ident_option '=' r_expr ';' {$$ = new AssignmentStatement($1, $2, $4); $$->setLineno(@$.first_line);}
        | RETURN r_expr_option ';'           {$$ = new ReturnStatement($2); $$->setLineno(@$.first_line);}
        | r_expr ';'                         {$$ = new RExprStatement($1); $$->setLineno(@$.first_line);}
        ;

if_clause:
    IF r_expr statement_block {$$ = new IfClause($2, $3); $$->setLineno(@$.first_line);}
    ;

elif_star: 
          /* epsilon */         {$$ = new std::list<ElifClause *>();}
        | elif_star elif_clause {$$ = $1; $1->push_back($2);}
        ;
                
elif_clause:
          ELIF r_expr statement_block {$$ = new ElifClause($2, $3); $$->setLineno(@$.first_line);}
        ;

else_option: 
              /* epsilon */        {$$ = new FalseElseOption(); $$->setLineno(@$.first_line);}
            | ELSE statement_block {$$ = new TrueElseOption($2); $$->setLineno(@$.first_line);}
            ;

l_expr:
      IDENT            {$$ = new IdentNode($1); $$->setLineno(@$.first_line);}
    | r_expr '.' IDENT {$$ = new ObjectFieldLExpr($1, $3); $$->setLineno(@$.first_line);}
    ;

r_expr:
      STRING_LIT {$$ = new StringNode($1); $$->setLineno(@$.first_line);}
    | INT_LIT    {$$ = new IntNode($1); $$->setLineno(@$.first_line);}
    | l_expr     {$$ = new RExprToLExpr($1); $$->setLineno(@$.first_line);} 
    | r_expr '+' r_expr {$$ = new PlusNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr '-' r_expr {$$ = new MinusNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr '*' r_expr {$$ = new TimesNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr '/' r_expr {$$ = new DivideNode($1, $3); $$->setLineno(@$.first_line);}
    | '(' r_expr ')'    {$$ = $2;} 
    | r_expr EQUALS r_expr  {$$ = new EqualsNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr ATMOST r_expr  {$$ = new AtMostNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr '<' r_expr     {$$ = new LessThanNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr ATLEAST r_expr {$$ = new AtLeastNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr '>' r_expr     {$$ = new GreaterThanNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr AND r_expr     {$$ = new AndNode($1, $3); $$->setLineno(@$.first_line);}
    | r_expr OR r_expr      {$$ = new OrNode($1, $3); $$->setLineno(@$.first_line);}
    | NOT r_expr            {$$ = new NotNode($2); $$->setLineno(@$.first_line);}
    | r_expr '.' IDENT '(' actual_args ')' {$$ = new DotRExpr($1, $3, $5); $$->setLineno(@$.first_line);}
    | IDENT '(' actual_args ')' {$$ = new ConstructorRExpr($1, $3); $$->setLineno(@$.first_line);}
    ;

r_expr_option:
              /* epsilon */ {$$ = new EmptyRExpr(); $$->setLineno(@$.first_line);}
            | r_expr        {$$ = $1;}
            ;

actual_args:
           /* epsilon */            {$$ = new std::list<RExpr *>();}
        |  r_expr extra_actual_args {$$ = new std::list<RExpr *>(); $$->push_back($1); $$->merge(*($2));}
        ;

extra_actual_args:
                  /* epsilon */                {$$ = new std::list<RExpr *>();}
                | extra_actual_args ',' r_expr {$$ = $1; $1->push_back($3);}
%%

/*
// main has been moved to it's own driver file
int main(int argc, char* argv[]) {}
*/
