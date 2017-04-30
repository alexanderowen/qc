/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "grammar.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 191 "grammar.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 216 "grammar.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   184

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNRULES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,    25,    23,    31,    24,    27,    26,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,    34,
      20,    22,    21,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    20,    21,    24,
      25,    28,    32,    33,    37,    42,    50,    51,    54,    55,
      58,    59,    62,    66,    70,    74,    80,    84,    87,    91,
      92,    95,    99,   100,   103,   105,   109,   111,   113,   115,
     119,   123,   127,   131,   135,   139,   143,   147,   151,   155,
     159,   163,   166,   173,   178,   179,   181,   182,   185,   186
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    48,    -1,    -1,    37,    38,    -1,
      39,    44,    -1,     6,     5,    28,    41,    29,    40,    -1,
      -1,     8,     5,    -1,    -1,    42,    43,    -1,     5,    30,
       5,    -1,    -1,    43,    31,    42,    -1,    32,    48,    46,
      33,    -1,     7,     5,    28,    41,    29,    47,    49,    -1,
      -1,    46,    45,    -1,    -1,    30,     5,    -1,    -1,    48,
      50,    -1,    32,    48,    33,    -1,    51,    52,    54,    -1,
      12,    56,    49,    -1,    55,    47,    22,    56,    34,    -1,
      13,    57,    34,    -1,    56,    34,    -1,     9,    56,    49,
      -1,    -1,    52,    53,    -1,    10,    56,    49,    -1,    -1,
      11,    49,    -1,     5,    -1,    56,    27,     5,    -1,     4,
      -1,     3,    -1,    55,    -1,    56,    23,    56,    -1,    56,
      24,    56,    -1,    56,    25,    56,    -1,    56,    26,    56,
      -1,    28,    56,    29,    -1,    56,    16,    56,    -1,    56,
      15,    56,    -1,    56,    20,    56,    -1,    56,    14,    56,
      -1,    56,    21,    56,    -1,    56,    17,    56,    -1,    56,
      18,    56,    -1,    19,    56,    -1,    56,    27,     5,    28,
      58,    29,    -1,     5,    28,    58,    29,    -1,    -1,    56,
      -1,    -1,    56,    59,    -1,    -1,    59,    31,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    95,    95,    99,   100,   104,   108,   112,   113,   117,
     118,   122,   126,   127,   131,   134,   138,   139,   143,   144,
     148,   149,   153,   157,   158,   159,   160,   161,   165,   169,
     170,   174,   178,   179,   183,   184,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   209,   210,   214,   215,   219,   220
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LIT", "STRING_LIT", "IDENT",
  "CLASS", "DEF", "EXTENDS", "IF", "ELIF", "ELSE", "WHILE", "RETURN",
  "ATLEAST", "ATMOST", "EQUALS", "AND", "OR", "NOT", "'<'", "'>'", "'='",
  "'+'", "'-'", "'*'", "'/'", "'.'", "'('", "')'", "':'", "','", "'{'",
  "'}'", "';'", "$accept", "program", "class_star", "class",
  "class_signature", "extends_option", "formal_args", "formal_arg",
  "extra_formal_args_star", "class_body", "method", "method_star",
  "ident_option", "statement_star", "statement_block", "statement",
  "if_clause", "elif_star", "elif_clause", "else_option", "l_expr",
  "r_expr", "r_expr_option", "actual_args", "extra_actual_args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      60,    62,    61,    43,    45,    42,    47,    46,    40,    41,
      58,    44,   123,   125,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    39,    40,    40,    41,
      41,    42,    43,    43,    44,    45,    46,    46,    47,    47,
      48,    48,    49,    50,    50,    50,    50,    50,    51,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    58,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     6,     0,     2,     0,
       2,     3,     0,     3,     4,     7,     0,     2,     0,     2,
       0,     2,     3,     3,     3,     5,     3,     2,     3,     0,
       2,     3,     0,     2,     1,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     6,     4,     0,     1,     0,     2,     0,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    20,     1,     0,     4,     0,     2,     0,    20,
       5,    37,    36,    34,     0,     0,    54,     0,     0,    21,
      29,    38,     0,     9,    16,    56,    38,     0,     0,    55,
       0,    51,     0,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,     0,
       0,    12,     0,    58,     0,    20,    28,    24,    26,    43,
       0,     0,    30,    23,    19,     0,    47,    45,    44,    49,
      50,    46,    48,    39,    40,    41,    42,    35,     0,     7,
      10,     0,    14,    17,    57,    53,     0,     0,    33,     0,
      56,    11,     0,     6,     0,     0,     0,    22,    31,    25,
       0,     8,    13,     9,    59,    52,     0,    18,     0,    15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    93,    50,    51,    80,    10,
      83,    52,    35,     7,    56,    19,    20,    33,    62,    63,
      26,    22,    30,    54,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -24
static const yytype_int16 yypact[] =
{
     -24,    17,    12,   -24,    31,   -24,     5,    56,    11,   -24,
     -24,   -24,   -24,    13,    16,    16,    16,    16,    16,   -24,
     -24,   -15,    73,    35,    56,    16,   -24,   103,   103,   138,
       8,   152,   122,    -1,    38,    23,    16,    16,    16,    16,
      16,    16,    16,    16,    16,    16,    16,    45,   -24,    24,
      26,   -24,     1,   138,    29,   -24,   -24,   -24,   -24,   -24,
      16,    30,   -24,   -24,   -24,    16,   157,   157,   157,   152,
     152,   157,   157,   -13,   -13,    39,    39,    42,    62,    63,
      43,    68,   -24,   -24,    47,   -24,    44,   103,   -24,    88,
      16,   -24,    74,   -24,    35,    52,    16,   -24,   -24,   -24,
      54,   -24,   -24,    35,   138,   -24,    57,    51,    30,   -24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,   -24,   -24,   -24,   -24,   -11,     7,   -24,   -24,
     -24,   -24,     3,    -3,   -23,   -24,   -24,   -24,   -24,   -24,
       9,   -14,   -24,    41,   -24
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -19
static const yytype_int8 yytable[] =
{
      27,    28,    29,    31,    32,    57,    24,   -18,    81,    60,
      61,    53,    45,    46,    47,    34,    21,     3,     4,    11,
      12,    13,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    21,    82,    17,     8,     9,    88,    23,
      49,    25,    58,    64,    18,    65,    87,    11,    12,    13,
      77,    89,    86,    14,    78,    79,    15,    16,    85,    11,
      12,    13,    55,    17,    98,    14,    47,    91,    15,    16,
      90,    92,    18,    95,    94,    17,    53,    97,    96,   101,
     103,    34,   104,   105,    18,   109,   107,    36,    37,    38,
      39,    40,   106,    41,    42,    21,    43,    44,    45,    46,
      47,   102,    36,    37,    38,    39,    40,    48,    41,    42,
     108,    43,    44,    45,    46,    47,     0,    36,    37,    38,
      39,    40,    99,    41,    42,     0,    43,    44,    45,    46,
      47,   100,     0,     0,     0,    55,    36,    37,    38,    39,
      40,     0,    41,    42,     0,    43,    44,    45,    46,    47,
       0,    59,    36,    37,    38,    39,    40,     0,    41,    42,
       0,    43,    44,    45,    46,    47,    36,    37,    38,     0,
       0,     0,    41,    42,     0,    43,    44,    45,    46,    47,
      43,    44,    45,    46,    47
};

static const yytype_int8 yycheck[] =
{
      14,    15,    16,    17,    18,    28,     9,    22,     7,    10,
      11,    25,    25,    26,    27,    30,     7,     0,     6,     3,
       4,     5,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    24,    33,    19,     5,    32,    61,    28,
       5,    28,    34,     5,    28,    22,    60,     3,     4,     5,
       5,    65,    55,     9,    30,    29,    12,    13,    29,     3,
       4,     5,    32,    19,    87,     9,    27,     5,    12,    13,
      28,     8,    28,     5,    31,    19,    90,    33,    31,     5,
      28,    30,    96,    29,    28,   108,    29,    14,    15,    16,
      17,    18,   103,    20,    21,    86,    23,    24,    25,    26,
      27,    94,    14,    15,    16,    17,    18,    34,    20,    21,
     107,    23,    24,    25,    26,    27,    -1,    14,    15,    16,
      17,    18,    34,    20,    21,    -1,    23,    24,    25,    26,
      27,    90,    -1,    -1,    -1,    32,    14,    15,    16,    17,
      18,    -1,    20,    21,    -1,    23,    24,    25,    26,    27,
      -1,    29,    14,    15,    16,    17,    18,    -1,    20,    21,
      -1,    23,    24,    25,    26,    27,    14,    15,    16,    -1,
      -1,    -1,    20,    21,    -1,    23,    24,    25,    26,    27,
      23,    24,    25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,     0,     6,    38,    39,    48,     5,    32,
      44,     3,     4,     5,     9,    12,    13,    19,    28,    50,
      51,    55,    56,    28,    48,    28,    55,    56,    56,    56,
      57,    56,    56,    52,    30,    47,    14,    15,    16,    17,
      18,    20,    21,    23,    24,    25,    26,    27,    34,     5,
      41,    42,    46,    56,    58,    32,    49,    49,    34,    29,
      10,    11,    53,    54,     5,    22,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,     5,    30,    29,
      43,     7,    33,    45,    59,    29,    48,    56,    49,    56,
      28,     5,     8,    40,    31,     5,    31,    33,    49,    34,
      58,     5,    42,    28,    56,    29,    41,    29,    47,    49
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 95 "grammar.y"
    {(yyval.pgm) = new Program((yyvsp[(1) - (2)].clsss), (yyvsp[(2) - (2)].stmts), (yyloc).first_line); (yyval.pgm)->setLineno((yyloc).first_line); root = (yyval.pgm);;}
    break;

  case 3:
#line 99 "grammar.y"
    {(yyval.clsss) = new std::list<Class *>();;}
    break;

  case 4:
#line 100 "grammar.y"
    {(yyval.clsss) = (yyvsp[(1) - (2)].clsss); (yyvsp[(1) - (2)].clsss)->push_back((yyvsp[(2) - (2)].cls));;}
    break;

  case 5:
#line 104 "grammar.y"
    {(yyval.cls) = new Class((yyvsp[(1) - (2)].clssig), (yyvsp[(2) - (2)].clsbdy)); (yyval.cls)->setLineno((yyloc).first_line);;}
    break;

  case 6:
#line 108 "grammar.y"
    {(yyval.clssig) = new ClassSignature((yyvsp[(2) - (6)].id), (yyvsp[(4) - (6)].fargs), (yyvsp[(6) - (6)].exop)); (yyval.clssig)->setLineno((yyloc).first_line);;}
    break;

  case 7:
#line 112 "grammar.y"
    {(yyval.exop) = new FalseExtendsOption(); (yyval.exop)->setLineno((yyloc).first_line);;}
    break;

  case 8:
#line 113 "grammar.y"
    {(yyval.exop) = new TrueExtendsOption((yyvsp[(2) - (2)].id)); (yyval.exop)->setLineno((yyloc).first_line);;}
    break;

  case 9:
#line 117 "grammar.y"
    {(yyval.fargs) = new std::list<FormalArg *>();;}
    break;

  case 10:
#line 118 "grammar.y"
    {(yyval.fargs) = (yyvsp[(2) - (2)].fargs); (yyvsp[(2) - (2)].fargs)->push_front((yyvsp[(1) - (2)].farg));;}
    break;

  case 11:
#line 122 "grammar.y"
    {(yyval.farg) = new FormalArg((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].id)); (yyval.farg)->setLineno((yyloc).first_line);;}
    break;

  case 12:
#line 126 "grammar.y"
    {(yyval.fargs) = new std::list<FormalArg *>();;}
    break;

  case 13:
#line 127 "grammar.y"
    {(yyval.fargs) = (yyvsp[(1) - (3)].fargs); (yyvsp[(1) - (3)].fargs)->push_back((yyvsp[(3) - (3)].farg));;}
    break;

  case 14:
#line 131 "grammar.y"
    {(yyval.clsbdy) = new ClassBody((yyvsp[(2) - (4)].stmts), (yyvsp[(3) - (4)].meths)); (yyval.clsbdy)->setLineno((yyloc).first_line);;}
    break;

  case 15:
#line 134 "grammar.y"
    {(yyval.meth) = new Method((yyvsp[(2) - (7)].id), (yyvsp[(4) - (7)].fargs), (yyvsp[(6) - (7)].idop), (yyvsp[(7) - (7)].stmts)); (yyval.meth)->setLineno((yyloc).first_line);;}
    break;

  case 16:
#line 138 "grammar.y"
    {(yyval.meths) = new std::list<Method *>();;}
    break;

  case 17:
#line 139 "grammar.y"
    {(yyval.meths) = (yyvsp[(1) - (2)].meths); (yyvsp[(1) - (2)].meths)->push_back((yyvsp[(2) - (2)].meth));;}
    break;

  case 18:
#line 143 "grammar.y"
    {(yyval.idop) = new FalseIdentOption(); (yyval.idop)->setLineno((yyloc).first_line);;}
    break;

  case 19:
#line 144 "grammar.y"
    {(yyval.idop) = new TrueIdentOption((yyvsp[(2) - (2)].id)); (yyval.idop)->setLineno((yyloc).first_line);;}
    break;

  case 20:
#line 148 "grammar.y"
    {(yyval.stmts) = new std::list<Statement *>();;}
    break;

  case 21:
#line 149 "grammar.y"
    {(yyval.stmts) = (yyvsp[(1) - (2)].stmts); (yyvsp[(1) - (2)].stmts)->push_back((yyvsp[(2) - (2)].stmt));;}
    break;

  case 22:
#line 153 "grammar.y"
    {(yyval.stmts) = (yyvsp[(2) - (3)].stmts);;}
    break;

  case 23:
#line 157 "grammar.y"
    {(yyval.stmt) = new IfBlock((yyvsp[(1) - (3)]._if), (yyvsp[(2) - (3)].elifs), (yyvsp[(3) - (3)]._else)); (yyval.stmt)->setLineno((yyloc).first_line);;}
    break;

  case 24:
#line 158 "grammar.y"
    {(yyval.stmt) = new WhileStatement((yyvsp[(2) - (3)].rexpr), (yyvsp[(3) - (3)].stmts)); (yyval.stmt)->setLineno((yyloc).first_line);;}
    break;

  case 25:
#line 159 "grammar.y"
    {(yyval.stmt) = new AssignmentStatement((yyvsp[(1) - (5)].lexpr), (yyvsp[(2) - (5)].idop), (yyvsp[(4) - (5)].rexpr)); (yyval.stmt)->setLineno((yyloc).first_line);;}
    break;

  case 26:
#line 160 "grammar.y"
    {(yyval.stmt) = new ReturnStatement((yyvsp[(2) - (3)].rexpr)); (yyval.stmt)->setLineno((yyloc).first_line);;}
    break;

  case 27:
#line 161 "grammar.y"
    {(yyval.stmt) = new RExprStatement((yyvsp[(1) - (2)].rexpr)); (yyval.stmt)->setLineno((yyloc).first_line);;}
    break;

  case 28:
#line 165 "grammar.y"
    {(yyval._if) = new IfClause((yyvsp[(2) - (3)].rexpr), (yyvsp[(3) - (3)].stmts)); (yyval._if)->setLineno((yyloc).first_line);;}
    break;

  case 29:
#line 169 "grammar.y"
    {(yyval.elifs) = new std::list<ElifClause *>();;}
    break;

  case 30:
#line 170 "grammar.y"
    {(yyval.elifs) = (yyvsp[(1) - (2)].elifs); (yyvsp[(1) - (2)].elifs)->push_back((yyvsp[(2) - (2)]._elif));;}
    break;

  case 31:
#line 174 "grammar.y"
    {(yyval._elif) = new ElifClause((yyvsp[(2) - (3)].rexpr), (yyvsp[(3) - (3)].stmts)); (yyval._elif)->setLineno((yyloc).first_line);;}
    break;

  case 32:
#line 178 "grammar.y"
    {(yyval._else) = new FalseElseOption(); (yyval._else)->setLineno((yyloc).first_line);;}
    break;

  case 33:
#line 179 "grammar.y"
    {(yyval._else) = new TrueElseOption((yyvsp[(2) - (2)].stmts)); (yyval._else)->setLineno((yyloc).first_line);;}
    break;

  case 34:
#line 183 "grammar.y"
    {(yyval.lexpr) = new IdentNode((yyvsp[(1) - (1)].id)); (yyval.lexpr)->setLineno((yyloc).first_line);;}
    break;

  case 35:
#line 184 "grammar.y"
    {(yyval.lexpr) = new ObjectFieldLExpr((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].id)); (yyval.lexpr)->setLineno((yyloc).first_line);;}
    break;

  case 36:
#line 188 "grammar.y"
    {(yyval.rexpr) = new StringNode((yyvsp[(1) - (1)].id)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 37:
#line 189 "grammar.y"
    {(yyval.rexpr) = new IntNode((yyvsp[(1) - (1)].integer)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 38:
#line 190 "grammar.y"
    {(yyval.rexpr) = new RExprToLExpr((yyvsp[(1) - (1)].lexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 39:
#line 191 "grammar.y"
    {(yyval.rexpr) = new PlusNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 40:
#line 192 "grammar.y"
    {(yyval.rexpr) = new MinusNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 41:
#line 193 "grammar.y"
    {(yyval.rexpr) = new TimesNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 42:
#line 194 "grammar.y"
    {(yyval.rexpr) = new DivideNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 43:
#line 195 "grammar.y"
    {(yyval.rexpr) = (yyvsp[(2) - (3)].rexpr);;}
    break;

  case 44:
#line 196 "grammar.y"
    {(yyval.rexpr) = new EqualsNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 45:
#line 197 "grammar.y"
    {(yyval.rexpr) = new AtMostNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 46:
#line 198 "grammar.y"
    {(yyval.rexpr) = new LessThanNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 47:
#line 199 "grammar.y"
    {(yyval.rexpr) = new AtLeastNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 48:
#line 200 "grammar.y"
    {(yyval.rexpr) = new GreaterThanNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 49:
#line 201 "grammar.y"
    {(yyval.rexpr) = new AndNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 50:
#line 202 "grammar.y"
    {(yyval.rexpr) = new OrNode((yyvsp[(1) - (3)].rexpr), (yyvsp[(3) - (3)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 51:
#line 203 "grammar.y"
    {(yyval.rexpr) = new NotNode((yyvsp[(2) - (2)].rexpr)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 52:
#line 204 "grammar.y"
    {(yyval.rexpr) = new DotRExpr((yyvsp[(1) - (6)].rexpr), (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].rexprs)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 53:
#line 205 "grammar.y"
    {(yyval.rexpr) = new ConstructorRExpr((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].rexprs)); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 54:
#line 209 "grammar.y"
    {(yyval.rexpr) = new EmptyRExpr(); (yyval.rexpr)->setLineno((yyloc).first_line);;}
    break;

  case 55:
#line 210 "grammar.y"
    {(yyval.rexpr) = (yyvsp[(1) - (1)].rexpr);;}
    break;

  case 56:
#line 214 "grammar.y"
    {(yyval.rexprs) = new std::list<RExpr *>();;}
    break;

  case 57:
#line 215 "grammar.y"
    {(yyval.rexprs) = new std::list<RExpr *>(); (yyval.rexprs)->push_back((yyvsp[(1) - (2)].rexpr)); (yyval.rexprs)->merge(*((yyvsp[(2) - (2)].rexprs)));;}
    break;

  case 58:
#line 219 "grammar.y"
    {(yyval.rexprs) = new std::list<RExpr *>();;}
    break;

  case 59:
#line 220 "grammar.y"
    {(yyval.rexprs) = (yyvsp[(1) - (3)].rexprs); (yyvsp[(1) - (3)].rexprs)->push_back((yyvsp[(3) - (3)].rexpr));;}
    break;


/* Line 1267 of yacc.c.  */
#line 1830 "grammar.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 221 "grammar.y"


/*
// main has been moved to it's own driver file
int main(int argc, char* argv[]) {}
*/

