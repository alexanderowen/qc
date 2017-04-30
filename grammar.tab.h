/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LIT = 258,
     STRING_LIT = 259,
     IDENT = 260,
     CLASS = 261,
     DEF = 262,
     EXTENDS = 263,
     IF = 264,
     ELIF = 265,
     ELSE = 266,
     WHILE = 267,
     RETURN = 268,
     ATLEAST = 269,
     ATMOST = 270,
     EQUALS = 271,
     AND = 272,
     OR = 273,
     NOT = 274
   };
#endif
/* Tokens.  */
#define INT_LIT 258
#define STRING_LIT 259
#define IDENT 260
#define CLASS 261
#define DEF 262
#define EXTENDS 263
#define IF 264
#define ELIF 265
#define ELSE 266
#define WHILE 267
#define RETURN 268
#define ATLEAST 269
#define ATMOST 270
#define EQUALS 271
#define AND 272
#define OR 273
#define NOT 274




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 33 "grammar.y"
{
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
/* Line 1529 of yacc.c.  */
#line 113 "grammar.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
