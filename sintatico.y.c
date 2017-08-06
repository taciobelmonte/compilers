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
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEC = 258,
     DEF = 259,
     RETURN = 260,
     LET = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     ASSIGN = 265,
     CONTINUE = 266,
     BREAK = 267,
     OPENPAR = 268,
     CLOSEPAR = 269,
     OPENBLOCK = 270,
     CLOSEBLOCK = 271,
     ENDEXPRESSION = 272,
     SEPARADOR = 273,
     IDENTIFIER = 274,
     OR = 275,
     AND = 276,
     EQUAL = 277,
     DIFF = 278,
     LESS = 279,
     LESSEQUAL = 280,
     GREATEQUAL = 281,
     GREAT = 282,
     PLUS = 283,
     MINUS = 284,
     MULT = 285,
     DIV = 286,
     NOT = 287,
     UMINUS = 288
   };
#endif
/* Tokens.  */
#define DEC 258
#define DEF 259
#define RETURN 260
#define LET 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define ASSIGN 265
#define CONTINUE 266
#define BREAK 267
#define OPENPAR 268
#define CLOSEPAR 269
#define OPENBLOCK 270
#define CLOSEBLOCK 271
#define ENDEXPRESSION 272
#define SEPARADOR 273
#define IDENTIFIER 274
#define OR 275
#define AND 276
#define EQUAL 277
#define DIFF 278
#define LESS 279
#define LESSEQUAL 280
#define GREATEQUAL 281
#define GREAT 282
#define PLUS 283
#define MINUS 284
#define MULT 285
#define DIV 286
#define NOT 287
#define UMINUS 288




/* Copy the first part of user declarations.  */
#line 1 "sintatico.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
    
    
//Instancia variáveis
int yylex();
int yyparse();
FILE *yyin;
FILE *yyout;
int COUNTER = 0;

#define BUFFERMAX 2000
#define MAXCHAR 500

typedef enum typesList {
    INT,
    ID,
    AST
}type;

typedef struct {
    int integer;
}nodeINT;

typedef struct{
    char name[MAXCHAR];
}nodeID;

typedef struct {
    int token;
    int totalkids;                                      
    struct ASTNo **kids;	
}ASTree;

typedef struct ASTNo{
    union {
        nodeINT integer;   
        nodeID id;
        ASTree tree;        
    };
    type tipo;
}ASTNode;



//Function to print node info
//void printNodeInfo(ASTree *tree) {
    //printf("   Entrou no print_node_info\n");
    
    //printf("  %s\n", tree->name);
    
    //if (tree->kids && tree->siblings) {
      //  printf("%d, parent of %d and sibling of %d\n", tree->val, (tree->kids)->val, (tree->siblings)->val);
    //} else if (tree->kids) {
     //   printf("%d, parent of %d\n", tree->val, (tree->kids)->val);
    //} else if (tree->siblings) {
     //   printf("%d, sibling of %d\n", tree->val, (tree->siblings)->val);
   // } else printf("%d\n", tree->val);
//};

//Function to print Tree in Pre-order
//void printASTinOrder(ASTree *tree) {
   // printNodeInfo(tree);
    
   // printf("entrou no pre-order-print\n");
    //if (tree->kids) pre_order_print(tree->kids);
    //if (tree->siblings) pre_order_print(tree->siblings);
//};

/*################ AST DEFINITIONS #####################*/
//ASTree *tree;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 78 "sintatico.y"
{
    char *string;
    int intval;
    ASTNode *ASTp;  
}
/* Line 193 of yacc.c.  */
#line 245 "sintatico.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 258 "sintatico.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   234

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNRULES -- Number of states.  */
#define YYNSTATES  105

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    12,    16,    22,    29,
      35,    38,    42,    43,    48,    51,    52,    55,    56,    59,
      65,    73,    79,    83,    86,    89,    92,    94,    96,   100,
     105,   109,   112,   116,   117,   121,   125,   129,   133,   137,
     141,   145,   149,   153,   157,   161,   165,   168,   171,   175,
     177,   179
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    36,    -1,    37,    36,    -1,    38,    36,
      -1,    -1,     6,    19,    17,    -1,     6,    19,    10,    50,
      17,    -1,     4,    19,    13,    39,    14,    41,    -1,     4,
      19,    13,    14,    41,    -1,    19,    40,    -1,    18,    19,
      40,    -1,    -1,    15,    42,    43,    16,    -1,    37,    42,
      -1,    -1,    44,    43,    -1,    -1,    45,    17,    -1,     7,
      13,    50,    14,    41,    -1,     7,    13,    50,    14,    41,
       8,    41,    -1,     9,    13,    50,    14,    41,    -1,     5,
      50,    17,    -1,     5,    17,    -1,    12,    17,    -1,    11,
      17,    -1,    46,    -1,    47,    -1,    19,    10,    50,    -1,
      19,    13,    48,    14,    -1,    19,    13,    14,    -1,    50,
      49,    -1,    18,    50,    49,    -1,    -1,    50,    28,    50,
      -1,    50,    29,    50,    -1,    50,    30,    50,    -1,    50,
      31,    50,    -1,    50,    24,    50,    -1,    50,    25,    50,
      -1,    50,    27,    50,    -1,    50,    26,    50,    -1,    50,
      22,    50,    -1,    50,    23,    50,    -1,    50,    21,    50,
      -1,    50,    20,    50,    -1,    29,    50,    -1,    32,    50,
      -1,    13,    50,    14,    -1,    47,    -1,     3,    -1,    19,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   127,   127,   134,   137,   142,   145,   146,   149,   152,
     156,   161,   164,   168,   173,   175,   178,   181,   183,   184,
     185,   186,   187,   191,   192,   193,   196,   197,   200,   203,
     204,   207,   210,   211,   214,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEC", "DEF", "RETURN", "LET", "IF",
  "ELSE", "WHILE", "ASSIGN", "CONTINUE", "BREAK", "OPENPAR", "CLOSEPAR",
  "OPENBLOCK", "CLOSEBLOCK", "ENDEXPRESSION", "SEPARADOR", "IDENTIFIER",
  "OR", "AND", "EQUAL", "DIFF", "LESS", "LESSEQUAL", "GREATEQUAL", "GREAT",
  "PLUS", "MINUS", "MULT", "DIV", "NOT", "UMINUS", "$accept", "programa",
  "inicio", "decvar", "decfunc", "paramlist", "looparams", "bloco",
  "loopdecvar", "loopstmts", "stmt", "declaracao", "assign", "funccall",
  "arglist", "loopargs", "exp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    36,    37,    37,    38,    38,
      39,    40,    40,    41,    42,    42,    43,    43,    44,    44,
      44,    44,    44,    44,    44,    44,    45,    45,    46,    47,
      47,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     3,     5,     6,     5,
       2,     3,     0,     4,     2,     0,     2,     0,     2,     5,
       7,     5,     3,     2,     2,     2,     1,     1,     3,     4,
       3,     2,     3,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     0,     2,     5,     5,     0,     0,     1,
       3,     4,     0,     0,     6,     0,    12,     0,    50,     0,
      51,     0,     0,    49,     0,    15,     9,     0,    10,     0,
       0,     0,    46,    47,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    17,    12,
       8,    48,    30,     0,    33,    45,    44,    42,    43,    38,
      39,    41,    40,    34,    35,    36,    37,    14,     0,     0,
       0,     0,     0,     0,     0,    17,     0,    26,    27,    11,
      29,     0,    31,    23,     0,     0,     0,    25,    24,     0,
      13,    16,    18,    33,    22,     0,     0,    28,    32,     0,
       0,    19,    21,     0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    17,    28,    26,    48,    74,
      75,    76,    77,    23,    53,    82,    24
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -43
static const yytype_int16 yypact[] =
{
      11,    -8,    -3,     3,   -43,    11,    11,    19,    -9,   -43,
     -43,   -43,    -7,    54,   -43,    24,    29,    35,   -43,    54,
      32,    54,    54,   -43,   118,    48,   -43,    36,   -43,    24,
      67,    27,   -43,   -43,   -43,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    48,   160,    29,
     -43,   -43,   -43,    44,   162,   185,   195,   203,   203,     7,
       7,     7,     7,    12,    12,   -43,   -43,   -43,    31,    49,
      52,    58,    59,     0,    45,   160,    60,   -43,   -43,   -43,
     -43,    54,   -43,   -43,   133,    54,    54,   -43,   -43,    54,
     -43,   -43,   -43,   162,   -43,    85,   103,   174,   -43,    24,
      24,    70,   -43,    24,   -43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,    47,   -16,   -43,   -43,    17,   -29,    33,     4,
     -43,   -43,   -43,   -42,   -43,   -11,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      50,    13,    30,     9,    32,    33,    78,    15,    14,    47,
      89,     7,    16,    31,    54,     1,     8,     2,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      18,    47,    12,    78,    18,    43,    44,    45,    46,    25,
      19,    52,    45,    46,    19,    31,    20,    27,    83,    29,
      20,    84,    10,    11,     2,    49,    21,    18,    80,    22,
      21,    90,    85,    22,    93,    86,    79,    19,    95,    96,
     101,   102,    97,    20,   104,    87,    88,    92,   103,    91,
      67,    51,    98,    21,     0,     0,    22,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    99,
       0,     0,     0,     0,     0,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,   100,     0,     0,
       0,     0,     0,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    34,     0,     0,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      94,     0,     0,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    68,     0,    69,     0,    70,
       0,    71,    72,     0,     0,     0,     0,     0,     0,    73,
      81,     0,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    39,    40,    41,
      42,    43,    44,    45,    46
};

static const yytype_int8 yycheck[] =
{
      29,    10,    19,     0,    21,    22,    48,    14,    17,    25,
      10,    19,    19,    13,    31,     4,    19,     6,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
       3,    47,    13,    75,     3,    28,    29,    30,    31,    15,
      13,    14,    30,    31,    13,    13,    19,    18,    17,    14,
      19,    68,     5,     6,     6,    19,    29,     3,    14,    32,
      29,    16,    13,    32,    81,    13,    49,    13,    85,    86,
      99,   100,    89,    19,   103,    17,    17,    17,     8,    75,
      47,    14,    93,    29,    -1,    -1,    32,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    14,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    14,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    17,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      17,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,     5,    -1,     7,    -1,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    24,    25,    26,
      27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     6,    35,    36,    37,    38,    19,    19,     0,
      36,    36,    13,    10,    17,    14,    19,    39,     3,    13,
      19,    29,    32,    47,    50,    15,    41,    18,    40,    14,
      50,    13,    50,    50,    17,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    37,    42,    19,
      41,    14,    14,    48,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    42,     5,     7,
       9,    11,    12,    19,    43,    44,    45,    46,    47,    40,
      14,    18,    49,    17,    50,    13,    13,    17,    17,    10,
      16,    43,    17,    50,    17,    50,    50,    50,    49,    14,
      14,    41,    41,     8,    41
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


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


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

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

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 127 "sintatico.y"
    { 
                                                                //printf("1 ");
                                                                printf("[program  ");
                                                             
                                                            ;}
    break;

  case 3:
#line 134 "sintatico.y"
    {
                                                            printf("2 ");
                                                            ;}
    break;

  case 4:
#line 137 "sintatico.y"
    { 
                                                            //printf("3 ");
                                                            printf("[decfunc  ");
                                                              
                                                            ;}
    break;

  case 5:
#line 142 "sintatico.y"
    {/*printf("46 ");*/;}
    break;

  case 6:
#line 145 "sintatico.y"
    { printf("4 ");/*fprintf(yyout, "  [%s]\n", $2); */;}
    break;

  case 7:
#line 146 "sintatico.y"
    { printf("5 ");/*fprintf(yyout, "  [%s]\n", $2);*/ ;}
    break;

  case 8:
#line 149 "sintatico.y"
    { //printf("6 ");
                                                                  //printf("[ %s   ", $2);  
                                                                ;}
    break;

  case 9:
#line 152 "sintatico.y"
    {printf("7 ");;}
    break;

  case 10:
#line 156 "sintatico.y"
    { //printf("8 ");/*lista  = insereLista(lista, $1); */
                                                              //printf("[%s] ", $1);    
                                                            ;}
    break;

  case 11:
#line 161 "sintatico.y"
    {//printf("9 "); /*lista  = insereLista(lista, $2);*/
                                                            //printf("[%s] ", $2);
                                                            ;}
    break;

  case 12:
#line 164 "sintatico.y"
    {;}
    break;

  case 13:
#line 168 "sintatico.y"
    {//printf("10 ");
                                                             //printf("[%s\n ] ", $1);
                                                            ;}
    break;

  case 14:
#line 173 "sintatico.y"
    {printf("11 ");
                                                            ;}
    break;

  case 15:
#line 175 "sintatico.y"
    {;}
    break;

  case 16:
#line 178 "sintatico.y"
    {printf("12 "); 
                                                            // printf("[%s] ", $1);
                                                            ;}
    break;

  case 17:
#line 181 "sintatico.y"
    {;}
    break;

  case 18:
#line 183 "sintatico.y"
    {printf("13 ");;}
    break;

  case 19:
#line 184 "sintatico.y"
    {printf("14 ");;}
    break;

  case 20:
#line 185 "sintatico.y"
    {printf("15 ");;}
    break;

  case 21:
#line 186 "sintatico.y"
    {printf("16 ");;}
    break;

  case 22:
#line 187 "sintatico.y"
    {
                                                            printf("17 ");
                                                            printf("[return  ");
                                                            ;}
    break;

  case 23:
#line 191 "sintatico.y"
    {printf("[return ] ");;}
    break;

  case 24:
#line 192 "sintatico.y"
    {printf("19 ");;}
    break;

  case 25:
#line 193 "sintatico.y"
    {printf("20 ");;}
    break;

  case 26:
#line 196 "sintatico.y"
    {printf("21 ");;}
    break;

  case 27:
#line 197 "sintatico.y"
    {printf("22 ");;}
    break;

  case 28:
#line 200 "sintatico.y"
    {printf("23 ");;}
    break;

  case 29:
#line 203 "sintatico.y"
    {printf("24 ");;}
    break;

  case 30:
#line 204 "sintatico.y"
    {printf("25 ");;}
    break;

  case 31:
#line 207 "sintatico.y"
    {printf("26 ");;}
    break;

  case 32:
#line 210 "sintatico.y"
    {printf("27 ");;}
    break;

  case 33:
#line 211 "sintatico.y"
    {;}
    break;

  case 34:
#line 214 "sintatico.y"
    {
                                                            //printf("28 ");
                                                            //printf("[+] [%d][%d] ", $1,$3);
                                                            //$$ = $1 + $3;
                                                           // printf("%d", $$);
                                                            ;}
    break;

  case 35:
#line 220 "sintatico.y"
    {printf("29 ");;}
    break;

  case 36:
#line 221 "sintatico.y"
    {printf("30 ");;}
    break;

  case 37:
#line 222 "sintatico.y"
    {printf("31 ");;}
    break;

  case 38:
#line 223 "sintatico.y"
    {printf("32 ");;}
    break;

  case 39:
#line 224 "sintatico.y"
    {printf("33 ");;}
    break;

  case 40:
#line 225 "sintatico.y"
    {printf("34 ");;}
    break;

  case 41:
#line 226 "sintatico.y"
    {printf("35 ");;}
    break;

  case 42:
#line 227 "sintatico.y"
    {printf("36 ");;}
    break;

  case 43:
#line 228 "sintatico.y"
    {printf("37 ");;}
    break;

  case 44:
#line 229 "sintatico.y"
    {printf("38 ");;}
    break;

  case 45:
#line 230 "sintatico.y"
    {printf("39 ");;}
    break;

  case 46:
#line 231 "sintatico.y"
    {printf("40 ");;}
    break;

  case 47:
#line 232 "sintatico.y"
    {printf("41 ");;}
    break;

  case 48:
#line 233 "sintatico.y"
    {printf("42 ");;}
    break;

  case 49:
#line 234 "sintatico.y"
    {printf("43 ");;}
    break;

  case 50:
#line 235 "sintatico.y"
    {printf("44 ");;}
    break;

  case 51:
#line 236 "sintatico.y"
    {
                                                            //printf("45 ");
                                                           // printf("[%s] ", $1);
                                                            ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1847 "sintatico.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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


#line 241 "sintatico.y"


/*################ AST DEFINITIONS #####################*/


//Estrutura para gerar um buffer de Strings
typedef struct stringBuffer{
    char palavra[BUFFERMAX];
    struct stringBuffer* prox;
}stringBuffer;

//Função Insere Início da Lista Encadeada
stringBuffer* insereLista(stringBuffer* l, char palavra[]){
    stringBuffer* novo = (stringBuffer*)malloc(sizeof(stringBuffer));
    int i;

    for (i=0; i<strlen(palavra); i++) {
        novo->palavra[i] = palavra[i];
    }
    novo->palavra[strlen(palavra)] = '\0';
    novo->prox = l;
    COUNTER++;

    return novo;
}

//Função Imprime buffer de String
void imprimeLista(stringBuffer* l){
    int i = 1;
    do{
        
        if( l->prox != NULL){
            if(COUNTER-1 == i){
                fprintf(yyout, "[%s]", l->palavra);
                //printf("[%s]", l->palavra);
            }else{
                fprintf(yyout, "[%s] ", l->palavra);
                //printf("[%s]", l->palavra);
            }
        }else{
            
            if(strcmp("", l->palavra) != 0){
                fprintf(yyout, " [%s]", l->palavra);
            }
            
        }

        l= l->prox;
        i++;
    }while(l != NULL);
}

stringBuffer* lista     = NULL;

ASTNode *allocINT(int valor);
ASTNode *allocID(char string[MAXCHAR]);
ASTNode *allocaTreeNode(int no_token, int nfilhos, ...);

ASTNode *allocINT(int valor) {
    ASTNode *newnode = malloc(sizeof(ASTNode));

    newnode->tipo = INT;
    newnode->integer.integer = valor;

    return newnode;
}
ASTNode *allocID(char string[MAXCHAR]) {
    ASTNode *newnode = malloc(sizeof(ASTNode));

    newnode->tipo = ID;
    strcpy(newnode->id.name, string);

    return newnode;
}
ASTNode *allocaTreeNode(int token, int totalkids, ...) {
    va_list ap;
    
    ASTNode *newnode = malloc(sizeof(ASTNode));
    int i;

    newnode->tree.kids = malloc(totalkids * sizeof(ASTNode *));
    va_start(ap, totalkids);
    
    newnode->tipo               = AST;
    newnode->tree.token         = token;
    newnode->tree.totalkids     = totalkids;

    i = 0;
    while(i< totalkids){
        newnode->tree.kids[i] = va_arg(ap, ASTNode*);
        i++;
    }
    va_end(ap);
    return newnode;
}

int main(int argc, char** argv) {

    FILE *input  = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");  
    
    //Initialize Tree
    //tree = initializeNode();
    
    yyin = input;
    yyout = output;

    do{

        yyparse();

    }while(!feof(yyin));

    fclose(input);
    fclose(output);
    return 0;
}



int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}
