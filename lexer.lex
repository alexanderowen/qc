%option yylineno
%option header-file="lex.yy.h"
%option noyywrap

%{
/* Author: Alexander Owen
 * 
 * Flex lexer for the Quack programming language
 * Reads in a Quack file, performs lexical analysis to match tokens
 *
 */

#include <stdio.h>
#include "nodes.hpp"
#include "grammar.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

void yyerror(const char *msg)
{
    fprintf(stderr, "%d: %s (at '%s')\n", yylineno, msg, yytext);
}

const char* BAD_ESC_MSG =                                                                              
  "Illegal escape code; only \\\\, \\0, \\t, \\n, \\r, \\n are permitted";                             
const char* BAD_NL_STR =                                                                               
  "Unclosed string?  Encountered newline in quoted string.";
%}

%x comment
%x triplequotes

%%

"/*"         {BEGIN(comment);}
<comment>[^*\n]*         ;
<comment>"*"+[^*/\n]*    ;
<comment>\n              ;
<comment>"*"+"/"        {BEGIN(INITIAL);}

\/\/.*  {;}

\"{3}[^\"{3}]*\"{3} {yylval.id = strdup(yytext); return STRING_LIT;}

[ \n\t\r\v\f] {;}

class    {return CLASS;}
def      {return DEF;}
extends  {return EXTENDS;}
if       {return IF;}
elif     {return ELIF;}
else     {return ELSE;}
while    {return WHILE;}
return   {return RETURN;}
\>\=     {return ATLEAST;}
\<\=     {return ATMOST;}
\=\=     {return EQUALS;}
and      {return AND;}
or       {return OR;}
not      {return NOT;}
[0-9]+   {yylval.integer = atof(yytext); return INT_LIT;}

[(){}/*+\-!:;,\.=<>]                {return yytext[0];}
["](([\\][0btnrf"\\])|[^"\n\0\b\t\n\r\f\"\\])*["]   {yylval.id = strdup(yytext);       return STRING_LIT;}
["](([\\][^0btnrf"\\])|[^"\n])*["]  {yylval.id = strdup(yytext); yyerror(BAD_ESC_MSG); return STRING_LIT;}
["][^"\n]*[\n]                      {yylval.id = strdup(yytext); yyerror(BAD_NL_STR);  return STRING_LIT;}
[a-zA-Z_][a-zA-Z0-9_]*              {yylval.id = strdup(yytext); return IDENT;}
<<EOF>>  {return EOF;}

.  { fprintf(stderr, "*** %d: Unexpected character %d (%c)\n",                                      
                    yylineno, (int) yytext[0], yytext[0]); }  

%%


