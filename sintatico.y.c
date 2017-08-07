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
     PRINTAOLA = 275,
     OR = 276,
     AND = 277,
     EQUAL = 278,
     DIFF = 279,
     LESS = 280,
     LESSEQUAL = 281,
     GREATEQUAL = 282,
     GREAT = 283,
     PLUS = 284,
     MINUS = 285,
     MULT = 286,
     DIV = 287,
     NOT = 288,
     UMINUS = 289
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
#define PRINTAOLA 275
#define OR 276
#define AND 277
#define EQUAL 278
#define DIFF 279
#define LESS 280
#define LESSEQUAL 281
#define GREATEQUAL 282
#define GREAT 283
#define PLUS 284
#define MINUS 285
#define MULT 286
#define DIV 287
#define NOT 288
#define UMINUS 289




/* Copy the first part of user declarations.  */
#line 1 "sintatico.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#define BUFFERMAX 2000
#define MAXCHAR 500

//Instancia variáveis
int yylex();
int yyparse();
int yyerror(const char *);
FILE *yyin;
FILE *yyout;
int COUNTER = 0;
int ERRORS  = 0;

typedef enum typesList {
    INT,
    ID,
    AST
}type;

/*################ AST DEFINITIONS #####################*/
#define BUFFERMAX 2000
#define MAXCHAR 500

//Keys to pass info to createNode in the AST
typedef enum keyList{
    LPLUS,
    LMINUS,
    LMULT,
    LDIV,
    LUMINUS,
    LAND,
    LOR,
    LNOT    ,
    LGREAT,
    LGREATEQUAL      ,
    LLESSEQUAL  ,
    LLESS,
    LEQUAL,
    LDIFF      ,
    LWHILE,
    LLABELRETURN,
    LLABELFUNCCALL,
    LSTMT,
    LIF,
    LSTMTIF,
    LASSIGN,
    LENDEXPRESSION,
    LDECVAR,
    LEXP,
    LSTMTSTMT,
    LSTATEMENTFUNCCALL,
    LFUNCNARGLIST,
    LOPENPAR,
    LFUNCNNARGLIST,
    LFUNCCALL,
    LLABELCONTINUE,
    LSTMTELSE,
    LBACK,
    LCOMPASSIGN,
    LLABELBREAK,
    LASSIGNSTMT,
    LBLOCK,
    LCOMPPARAM,
    LPARAM,
    LDEF,
    LTIPAGEM
}keys;

/*################## AST STRUCTURE #################*/
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
    type tipo;
    union {
        nodeINT integer;
        nodeID id;
        ASTree tree;
    };
}ASTNode;
/*################## AST STRUCTURE #################*/


/*################## HELPER FUNCTIONS #################*/
//Estrutura para gerar um buffer de Strings
typedef struct stringBuffer{
    char palavra[BUFFERMAX];
    struct stringBuffer* prox;
}stringBuffer;

//Função Insere Início da Lista Encadeada
stringBuffer* insereLista(stringBuffer* l, char palavra[]){
    stringBuffer* novo = (stringBuffer*)malloc(sizeof(stringBuffer));
    int i;

    for (i=0; i<strlen(palavra); i++)
        novo->palavra[i] = palavra[i];

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
            }else{
                fprintf(yyout, "[%s] ", l->palavra);
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

//Declare functions
ASTNode *allocINT(int valor);
ASTNode *allocID(char string[MAXCHAR]);
ASTNode *allocTreeNode(int no_token, int nfilhos, ...);
void createNAryASTree(ASTNode *tree);
void createASTreeType(ASTNode *tree);

//Functions Denifitions
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
ASTNode *allocTreeNode(int token, int totalkids, ...) {
    int i = 0;
    va_list list;

    ASTNode *newnode = malloc(sizeof(ASTNode));

    newnode->tree.kids = malloc(totalkids*sizeof(ASTNode*));
    va_start( list, totalkids);

    newnode->tipo               = AST;
    newnode->tree.token         = token;
    newnode->tree.totalkids     = totalkids;

    for(i =0; i < totalkids; i++)
         newnode->tree.kids[i] = va_arg(list, ASTNode*);

    va_end(list);
    return newnode;
}

void createNAryASTree(ASTNode *tree)
{
    if(tree != NULL) {
        if(tree->tipo == AST){
            createASTreeType(tree);
        }else if(tree->tipo == ID){
            fprintf(yyout," [%s]", tree->id.name);
        }else if(tree->tipo == INT){
            fprintf(yyout," [%d]", tree->integer.integer);
        }
    }
}

/**
 * @param ASTNode tree
 * @param item
 * @param type - 0 for BINOP ? 1 for UNOP ? 2 for 3 children
 */
void caseExpression(ASTNode *tree, char* item, int type, int label){

    if(label){
        fprintf(yyout, " [");
        fprintf(yyout, "%s", item);
    }
    //Create tree for first node
    createNAryASTree(tree->tree.kids[0]);

    //Create tree for second node if is binop operation
    if(!type)
        createNAryASTree(tree->tree.kids[1]);

    if(label)
        fprintf(yyout, "]");
}


void createASTreeType(ASTNode *tree){
    switch(tree->tree.token) {
        case LPLUS:
            caseExpression(tree, "+",0, 1);
        break;
        case LMINUS:
            caseExpression(tree, "-",0, 1);
        break;
        case LMULT:
            caseExpression(tree, "*",0, 1);
            break;
        case LDIV:
            caseExpression(tree, "/",0, 1);
            break;
        case LUMINUS:
            caseExpression(tree, "-",1, 1);
            break;
        case LAND:
            caseExpression(tree, "&&",0, 1);
            break;
        case LOR:
            caseExpression(tree, "||",0, 1);
            break;
        case LNOT:
            caseExpression(tree, "!",1, 1);
            break;
        case LGREAT:
            caseExpression(tree, ">",0, 1);
            break;
        case LGREATEQUAL:
            caseExpression(tree, ">=",0, 1);
            break;
        case LLESSEQUAL:
            caseExpression(tree, "<=",0, 1);
            break;
        case LLESS:
            caseExpression(tree, "<",0, 1);
            break;
        case LEQUAL:
            caseExpression(tree, "==",0, 1);
            break;
        case LDIFF:
            caseExpression(tree, "!=",0, 1);
            break;
        case LWHILE:
            caseExpression(tree, "while",0, 1);
            break;
        case LLABELRETURN:
            caseExpression(tree, "return",1, 1);
            break;
         case LSTMTIF:
            fprintf(yyout, " [if");
            createNAryASTree(tree->tree.kids[0]); 
            createNAryASTree(tree->tree.kids[1]);
            createNAryASTree(tree->tree.kids[2]);
            fprintf(yyout, "] "); 
            break;
        case LIF:
            caseExpression(tree, "", 0, 0);
            if(tree->tree.totalkids>2)
                createNAryASTree(tree->tree.kids[2]);
            break;
        case LSTMT:
            if(tree->tree.totalkids>=2){
                if(tree->tree.kids[0]!= NULL) {
                    caseExpression(tree, "", 0, 0);
                }else {
                    createNAryASTree(tree->tree.kids[0]);
                }
            }
            break;
        case LASSIGN:
            createNAryASTree(tree->tree.kids[0]);
            fprintf(yyout, " [assign ");
            fprintf(yyout, "[%s]", tree->tree.kids[0]->id.name);
            fprintf(yyout, "]");
            break;
        case LENDEXPRESSION:
             createNAryASTree(tree->tree.kids[0]);
             fprintf(yyout, "]");
            break;
        case LDECVAR:
                createNAryASTree(tree->tree.kids[0]);
                if(tree->tree.kids[1] != NULL)
                    createNAryASTree(tree->tree.kids[1]);
                break;
        case LEXP:
            createNAryASTree(tree->tree.kids[0]);
            break;
        case LSTMTSTMT:
            createNAryASTree(tree->tree.kids[0]);
            break;
        case LTIPAGEM:
            if( tree->tree.totalkids>=2){
                if(tree->tree.kids[1]!= NULL) {
                    fprintf(yyout, " [decvar ");
                    fprintf(yyout, "[%s]", tree->tree.kids[0]->id.name);
                    createNAryASTree(tree->tree.kids[1]);
                } else {
                    fprintf(yyout, " [decvar [%s]]", tree->tree.kids[0]->id.name);
                }
            }
            break;
        case LDEF:
                fprintf(yyout, " [decfunc [%s]",tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                if(tree->tree.kids[1] == NULL)
                    fprintf(yyout, " [paramlist]");
                createNAryASTree(tree->tree.kids[2]);
                fprintf(yyout, "]");
                break;
        case LPARAM:
                fprintf(yyout, " [paramlist [%s]",tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                fprintf(yyout, "]");
                break;
        case LCOMPPARAM:
                fprintf(yyout, " [%s]",tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                break;
        case LBLOCK:
                fprintf(yyout, " [block");
                if(tree->tree.kids[0] != NULL)
                    createNAryASTree(tree->tree.kids[0]);
                if(tree->tree.kids[1] != NULL)
                        createNAryASTree(tree->tree.kids[1]);
                fprintf(yyout, "]");
                break;
         case LASSIGNSTMT:
                fprintf(yyout, " [assign ");
                createNAryASTree(tree->tree.kids[0]);
                break;
         case LCOMPASSIGN:
                fprintf(yyout, "[%s] ", tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                fprintf(yyout, "]");
                break;
         case LBACK:
                createNAryASTree(tree->tree.kids[0]);
                 if(tree->tree.kids[1] != NULL)
                    createNAryASTree(tree->tree.kids[1]);
                break;
         case LLABELBREAK:
                fprintf(yyout, " [break]");
                break;
         case LSTMTELSE:
                createNAryASTree(tree->tree.kids[0]);
                break;
         case LLABELCONTINUE:
                fprintf(yyout," [continue]");
                break;
                
                
         case LSTATEMENTFUNCCALL:
                fprintf(yyout," [funccall ");
                createNAryASTree(tree->tree.kids[0]);
                fprintf(yyout,"]");
                break;
        
        case LLABELFUNCCALL:
            caseExpression(tree, "funccall",0, 1);
            break;
        
        case LFUNCCALL:
            if(tree->tree.kids[1] != NULL) {
                fprintf(yyout,"[%s]", tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
            }else {
                fprintf(yyout,"[%s] ", tree->tree.kids[0]->id.name);
                fprintf(yyout,"[arglist]");
            }
         break;
            
        case LFUNCNARGLIST:
                caseExpression(tree, "arglist",1, 1);
                break;
          case LOPENPAR:
            createNAryASTree(tree->tree.kids[0]);
            break;
       
        case LFUNCNNARGLIST:
            createNAryASTree( tree->tree.kids[0] );
            createNAryASTree( tree->tree.kids[1] ); 
            break;
         
    }
}

/*######## HELPER FUNCTIONS ##########*/


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
#line 409 "sintatico.y"
{
    ASTNode *ASTp;
    char *string;
    int intval;
}
/* Line 193 of yacc.c.  */
#line 577 "sintatico.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 590 "sintatico.tab.c"

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  112

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    12,    17,    20,    21,
      28,    35,    38,    39,    43,    44,    49,    52,    53,    56,
      57,    60,    63,    69,    76,    82,    86,    89,    92,    94,
      95,    99,   104,   109,   110,   112,   115,   119,   120,   124,
     128,   132,   136,   140,   144,   148,   152,   156,   160,   164,
     168,   171,   174,   178,   180,   182
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    -1,    38,    37,    -1,    40,    37,
      -1,    -1,     6,    19,    39,    17,    -1,    10,    53,    -1,
      -1,     4,    20,    13,    41,    14,    43,    -1,     4,    19,
      13,    41,    14,    43,    -1,    19,    42,    -1,    -1,    18,
      19,    42,    -1,    -1,    15,    44,    45,    16,    -1,    38,
      44,    -1,    -1,    46,    45,    -1,    -1,    49,    17,    -1,
      48,    17,    -1,     7,    13,    53,    14,    43,    -1,     7,
      13,    53,    14,     8,    43,    -1,     9,    13,    53,    14,
      43,    -1,     5,    47,    17,    -1,    12,    17,    -1,    11,
      17,    -1,    53,    -1,    -1,    19,    10,    53,    -1,    19,
      13,    50,    14,    -1,    20,    13,    50,    14,    -1,    -1,
      51,    -1,    53,    52,    -1,    18,    53,    52,    -1,    -1,
      53,    29,    53,    -1,    53,    30,    53,    -1,    53,    31,
      53,    -1,    53,    32,    53,    -1,    53,    25,    53,    -1,
      53,    26,    53,    -1,    53,    28,    53,    -1,    53,    27,
      53,    -1,    53,    23,    53,    -1,    53,    24,    53,    -1,
      53,    22,    53,    -1,    53,    21,    53,    -1,    30,    53,
      -1,    33,    53,    -1,    13,    53,    14,    -1,    49,    -1,
       3,    -1,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   484,   484,   490,   495,   500,   502,   508,   513,   518,
     521,   528,   533,   538,   543,   545,   551,   556,   558,   563,
     565,   570,   576,   581,   587,   592,   597,   602,   608,   612,
     614,   621,   626,   633,   634,   640,   646,   651,   653,   658,
     663,   668,   673,   678,   683,   688,   693,   698,   702,   706,
     710,   714,   718,   722,   727,   732
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
  "PRINTAOLA", "OR", "AND", "EQUAL", "DIFF", "LESS", "LESSEQUAL",
  "GREATEQUAL", "GREAT", "PLUS", "MINUS", "MULT", "DIV", "NOT", "UMINUS",
  "$accept", "programa", "inicio", "decvar", "loopatrib", "decfunc",
  "paramlist", "looparams", "bloco", "loopdecvar", "loopstmts", "stmt",
  "loopexp", "assign", "funccall", "arglist", "loopargs", "loopargs2",
  "exp", 0
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
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    38,    39,    39,    40,
      40,    41,    41,    42,    42,    43,    44,    44,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    47,    47,
      48,    49,    49,    50,    50,    51,    52,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     4,     2,     0,     6,
       6,     2,     0,     3,     0,     4,     2,     0,     2,     0,
       2,     2,     5,     6,     5,     3,     2,     2,     1,     0,
       3,     4,     4,     0,     1,     2,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     0,     2,     5,     5,     0,     0,     8,
       1,     3,     4,    12,    12,     0,     0,    14,     0,     0,
      54,     0,    55,     0,     0,     0,    53,     7,     6,     0,
      11,     0,     0,     0,    33,    33,    50,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      14,    17,    10,     9,    52,     0,    34,    37,     0,    49,
      48,    46,    47,    42,    43,    45,    44,    38,    39,    40,
      41,    13,    17,    19,    31,     0,    35,    32,    16,    29,
       0,     0,     0,     0,     0,     0,    19,     0,     0,    37,
       0,    28,     0,     0,    27,    26,     0,    15,    18,    21,
      20,    36,    25,     0,     0,    30,     0,     0,     0,    22,
      24,    23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    16,     6,    18,    30,    52,    73,
      85,    86,    90,    87,    26,    55,    56,    76,    57
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
      -1,    -7,   -12,    14,   -72,    -1,    -1,    24,    25,    31,
     -72,   -72,   -72,    34,    34,    32,    33,    38,    29,    45,
     -72,    32,    48,    50,    32,    32,   -72,   130,   -72,    39,
     -72,    42,    42,    65,    32,    32,   -72,   -72,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      38,    74,   -72,   -72,   -72,    71,   -72,   118,    85,    44,
     140,   148,   148,   -13,   -13,   -13,   -13,   -11,   -11,   -72,
     -72,   -72,    74,    35,   -72,    32,   -72,   -72,   -72,    32,
      87,    88,    86,   101,    26,   104,    35,   102,   105,   118,
     106,   130,    32,    32,   -72,   -72,    32,   -72,   -72,   -72,
     -72,   -72,   -72,    84,   103,   130,    -4,    42,    42,   -72,
     -72,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,    43,   -50,   -72,   -72,    90,    52,   -24,    49,
      51,   -72,   -72,   -72,   -71,   146,   -72,    93,   -15
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      27,    72,    88,     1,   108,     2,    33,     9,    53,    36,
      37,    51,     7,     8,    10,    88,    46,    47,    48,    49,
      48,    49,    72,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    20,    96,    13,    14,    34,
      79,    15,    80,    31,    81,    21,    82,    83,    11,    12,
      28,    22,    23,    17,    84,    23,    29,    51,    50,    32,
      89,    34,    24,    35,    91,    25,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,   103,   104,    54,
       2,   105,   109,   110,   111,    74,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,   106,    77,
      92,    93,    71,    94,    19,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,   107,    95,    99,
      97,    78,   100,   102,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    75,    98,     0,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    42,    43,    44,    45,    46,    47,    48,
      49,    58,   101
};

static const yytype_int8 yycheck[] =
{
      15,    51,    73,     4,     8,     6,    21,    19,    32,    24,
      25,    15,    19,    20,     0,    86,    29,    30,    31,    32,
      31,    32,    72,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     3,    10,    13,    13,    13,
       5,    10,     7,    14,     9,    13,    11,    12,     5,     6,
      17,    19,    20,    19,    19,    20,    18,    15,    19,    14,
      75,    13,    30,    13,    79,    33,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    92,    93,    14,
       6,    96,   106,   107,   108,    14,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    14,    14,
      13,    13,    50,    17,    14,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    14,    17,    17,
      16,    72,    17,    17,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    18,    86,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    25,    26,    27,    28,    29,    30,    31,
      32,    35,    89
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     6,    36,    37,    38,    40,    19,    20,    19,
       0,    37,    37,    13,    13,    10,    39,    19,    41,    41,
       3,    13,    19,    20,    30,    33,    49,    53,    17,    18,
      42,    14,    14,    53,    13,    13,    53,    53,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      19,    15,    43,    43,    14,    50,    51,    53,    50,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    42,    38,    44,    14,    18,    52,    14,    44,     5,
       7,     9,    11,    12,    19,    45,    46,    48,    49,    53,
      47,    53,    13,    13,    17,    17,    10,    16,    45,    17,
      17,    52,    17,    53,    53,    53,    14,    14,     8,    43,
      43,    43
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
#line 484 "sintatico.y"
    {
                                                                            printf("-[program])\n ");
                                                                            createNAryASTree((yyvsp[(1) - (1)].ASTp));
                                                                            COUNTER++;
                                                                        ;}
    break;

  case 3:
#line 490 "sintatico.y"
    {
                                                                            //printf("2 (Decvar)\n ");
                                                                            (yyval.ASTp) = allocTreeNode(LSTMT,2,(yyvsp[(1) - (2)].ASTp),(yyvsp[(2) - (2)].ASTp));
                                                                            COUNTER++;
                                                                        ;}
    break;

  case 4:
#line 495 "sintatico.y"
    {
                                                                           printf("3- [decfunc]\n ");
                                                                           (yyval.ASTp) = allocTreeNode(LSTMT, 2, (yyvsp[(1) - (2)].ASTp), (yyvsp[(2) - (2)].ASTp));
                                                                           COUNTER++;
                                                                        ;}
    break;

  case 5:
#line 500 "sintatico.y"
    {(yyval.ASTp) = NULL;;}
    break;

  case 6:
#line 502 "sintatico.y"
    {
                                                                         // printf("4 (let ) \n");
                                                                          (yyval.ASTp) = allocTreeNode(LTIPAGEM, 2, allocID((yyvsp[(2) - (4)].string)), (yyvsp[(3) - (4)].ASTp));
                                                                          COUNTER++;
                                                                        ;}
    break;

  case 7:
#line 508 "sintatico.y"
    {
                                                                           // printf("4 (let x = ) \n");
                                                                            (yyval.ASTp) = allocTreeNode(LENDEXPRESSION, 1, (yyvsp[(2) - (2)].ASTp));
                                                                            COUNTER++;
                                                                        ;}
    break;

  case 8:
#line 513 "sintatico.y"
    {
                                                                         //printf("4 (let x;)\n");
                                                                        (yyval.ASTp) = NULL;
                                                                        ;}
    break;

  case 9:
#line 518 "sintatico.y"
    {
                                                                          yyerror("print");
                                                                        ;}
    break;

  case 10:
#line 521 "sintatico.y"
    {
                                                                       // printf("6-(decfunc (%s)) \n", $2);
                                                                        (yyval.ASTp) = allocTreeNode(LDEF,3, allocID((yyvsp[(2) - (6)].string)), (yyvsp[(4) - (6)].ASTp), (yyvsp[(6) - (6)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 11:
#line 528 "sintatico.y"
    {
                                                                       // printf("8-(paramlist loop)\n");
                                                                        (yyval.ASTp) = allocTreeNode(LPARAM, 2, allocID((yyvsp[(1) - (2)].string)),(yyvsp[(2) - (2)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 12:
#line 533 "sintatico.y"
    {
                                                                       // printf("8-(no paramlist)\n");
                                                                        (yyval.ASTp) = NULL;
                                                                        ;}
    break;

  case 13:
#line 538 "sintatico.y"
    {
                                                                        //printf("9-(,ID looparams) \n");
                                                                        (yyval.ASTp) = allocTreeNode(LCOMPPARAM, 2, allocID((yyvsp[(2) - (3)].string)),(yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 14:
#line 543 "sintatico.y"
    {(yyval.ASTp) = NULL ;;}
    break;

  case 15:
#line 545 "sintatico.y"
    {
                                                                        printf("10- [bloco] \n");
                                                                        (yyval.ASTp) = allocTreeNode(LBLOCK, 3, (yyvsp[(2) - (4)].ASTp), (yyvsp[(3) - (4)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 16:
#line 551 "sintatico.y"
    {
                                                                        //printf("11- (loopdecvar) \n");
                                                                        (yyval.ASTp) = allocTreeNode(LDECVAR, 2, (yyvsp[(1) - (2)].ASTp), (yyvsp[(2) - (2)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 17:
#line 556 "sintatico.y"
    {(yyval.ASTp) = NULL ;;}
    break;

  case 18:
#line 558 "sintatico.y"
    {
                                                                        //printf("12- (loop stmts)\n ");
                                                                        (yyval.ASTp) = allocTreeNode(LBACK, 2, (yyvsp[(1) - (2)].ASTp), (yyvsp[(2) - (2)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 19:
#line 563 "sintatico.y"
    {(yyval.ASTp) = NULL ;;}
    break;

  case 20:
#line 565 "sintatico.y"
    {
                                                                        printf("220- (funccall ;) \n");
                                                                        (yyval.ASTp) = allocTreeNode(LSTATEMENTFUNCCALL, 1, (yyvsp[(1) - (2)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 21:
#line 570 "sintatico.y"
    {
                                                                        (yyval.ASTp) = allocTreeNode(LASSIGNSTMT, 1, (yyvsp[(1) - (2)].ASTp));
                                                                        printf("220- (assign ;) \n");
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 22:
#line 576 "sintatico.y"
    {
                                                                        //printf("15- if(exp){} \n");
                                                                        (yyval.ASTp) = allocTreeNode(LSTMTIF, 3, (yyvsp[(3) - (5)].ASTp), (yyvsp[(5) - (5)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 23:
#line 581 "sintatico.y"
    {
                                                                        //printf("15- if(exp)else{} \n");
                                                                        (yyval.ASTp) = allocTreeNode(LSTMTIF, 3, (yyvsp[(3) - (6)].ASTp), (yyvsp[(5) - (6)].string), (yyvsp[(6) - (6)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 24:
#line 587 "sintatico.y"
    {
                                                                        //printf("16- while(exp){} \n");
                                                                        (yyval.ASTp) = allocTreeNode(LWHILE, 2, (yyvsp[(3) - (5)].ASTp), (yyvsp[(5) - (5)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 25:
#line 592 "sintatico.y"
    {
                                                                        //printf("17- return loopexp; \n");
                                                                        (yyval.ASTp) = allocTreeNode(LLABELRETURN, 1, (yyvsp[(2) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 26:
#line 597 "sintatico.y"
    {
                                                                        //printf("20 -break; \n");
                                                                        (yyval.ASTp) = allocTreeNode(LLABELBREAK, 2, (yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 27:
#line 602 "sintatico.y"
    {
                                                                        //printf("20 -continue; \n");
                                                                        (yyval.ASTp) = allocTreeNode(LLABELCONTINUE,2,(yyvsp[(1) - (2)].string), (yyvsp[(2) - (2)].string));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 28:
#line 608 "sintatico.y"
    {
                                                                        (yyval.ASTp) = allocTreeNode(LEXP, 1, (yyvsp[(1) - (1)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 29:
#line 612 "sintatico.y"
    {(yyval.ASTp)=NULL;;}
    break;

  case 30:
#line 614 "sintatico.y"
    {
                                                                        printf("23 x=exp \n");
                                                                        //$$ = allocTreeNode(LASSIGNSTMT, 1, $1);
                                                                        (yyval.ASTp) = allocTreeNode(LCOMPASSIGN, 2, allocID((yyvsp[(1) - (3)].string)), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 31:
#line 621 "sintatico.y"
    {
                                                                        printf("24- id() \n");
                                                                        (yyval.ASTp) = allocTreeNode(LFUNCCALL, 2, allocID((yyvsp[(1) - (4)].string)), (yyvsp[(3) - (4)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 32:
#line 626 "sintatico.y"
    {
                                                                        printf("24- id() \n");
                                                                        (yyval.ASTp) = allocTreeNode(LFUNCCALL, 2, allocID((yyvsp[(1) - (4)].string)), (yyvsp[(3) - (4)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 33:
#line 633 "sintatico.y"
    {(yyval.ASTp)=NULL;;}
    break;

  case 34:
#line 634 "sintatico.y"
    {
                                                                        (yyval.ASTp) = allocTreeNode(LFUNCNARGLIST, 1, (yyvsp[(1) - (1)].ASTp));
                                                                        COUNTER++;
                                                                       ;}
    break;

  case 35:
#line 640 "sintatico.y"
    {
                                                                        printf("26 - [] \n");
                                                                        (yyval.ASTp) = allocTreeNode(LFUNCNNARGLIST, 2, (yyvsp[(1) - (2)].ASTp), (yyvsp[(2) - (2)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 36:
#line 646 "sintatico.y"
    {
                                                                        // printf("27 - (, [%d]) \n", $2);
                                                                         (yyval.ASTp) = allocTreeNode(LFUNCNNARGLIST, 2, (yyvsp[(2) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                         COUNTER++;
                                                                        ;}
    break;

  case 37:
#line 651 "sintatico.y"
    {(yyval.ASTp)=NULL;;}
    break;

  case 38:
#line 653 "sintatico.y"
    {
                                                                        printf("28 - exp + exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LPLUS, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 39:
#line 658 "sintatico.y"
    {
                                                                        printf("29 - exp - exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LMINUS, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 40:
#line 663 "sintatico.y"
    {
                                                                        printf("30 - exp * exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LMULT, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 41:
#line 668 "sintatico.y"
    {
                                                                        printf("31 - exp / exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LDIV, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 42:
#line 673 "sintatico.y"
    {
                                                                        printf("32 - exp < exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LLESS, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 43:
#line 678 "sintatico.y"
    {
                                                                        printf("33 - exp <= exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LLESSEQUAL, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 44:
#line 683 "sintatico.y"
    {
                                                                        printf("34 - exp > exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LGREAT, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 45:
#line 688 "sintatico.y"
    {
                                                                        printf("35 - exp >= exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LGREATEQUAL, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 46:
#line 693 "sintatico.y"
    {
                                                                        printf("36 - exp = exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LEQUAL, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 47:
#line 698 "sintatico.y"
    {
                                                                        printf("37 - exp != exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LDIFF, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));COUNTER++;
                                                                        ;}
    break;

  case 48:
#line 702 "sintatico.y"
    {
                                                                        printf("38 - exp && exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LAND, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));COUNTER++;
                                                                        ;}
    break;

  case 49:
#line 706 "sintatico.y"
    {
                                                                        printf("39 - exp || exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LOR, 2, (yyvsp[(1) - (3)].ASTp), (yyvsp[(3) - (3)].ASTp));COUNTER++;
                                                                        ;}
    break;

  case 50:
#line 710 "sintatico.y"
    {
                                                                        printf("40 - exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LUMINUS, 1, (yyvsp[(2) - (2)].ASTp));COUNTER++;
                                                                        ;}
    break;

  case 51:
#line 714 "sintatico.y"
    {
                                                                        printf("41 - !exp \n");
                                                                        (yyval.ASTp) = allocTreeNode(LNOT, 1, (yyvsp[(2) - (2)].ASTp));COUNTER++;
                                                                        ;}
    break;

  case 52:
#line 718 "sintatico.y"
    {
                                                                        printf("42 - (exp) \n");
                                                                        (yyval.ASTp) = allocTreeNode(LOPENPAR, 1, (yyvsp[(2) - (3)].ASTp));COUNTER++;
                                                                        ;}
    break;

  case 53:
#line 722 "sintatico.y"
    {
                                                                        printf("43 - funccall\n");
                                                                        (yyval.ASTp) = allocTreeNode(LLABELFUNCCALL, 2, (yyvsp[(1) - (1)].ASTp));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 54:
#line 727 "sintatico.y"
    {
                                                                        printf("44 dec\n ");
                                                                        (yyval.ASTp) = allocINT((yyvsp[(1) - (1)].intval));
                                                                        COUNTER++;
                                                                        ;}
    break;

  case 55:
#line 732 "sintatico.y"
    {
                                                                        printf("45 id\n ");
                                                                        (yyval.ASTp) = allocID((yyvsp[(1) - (1)].string));
                                                                        COUNTER++;
                                                                        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2338 "sintatico.tab.c"
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


#line 738 "sintatico.y"


int yyerror(const char *s) {
  printf("yyerror : %s\n", s);
  ERRORS++;
  return 0;
}

int main(int argc, char** argv) {

    FILE *input  = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    yyin = input;
    yyout = output;

    fprintf(yyout,"[program");

    yyparse();
    fprintf(yyout,"]\n");

    fclose(input);
    fclose(output);

    //If errors, clear file
    if(ERRORS != 0 || COUNTER==1){
        FILE *output = fopen(argv[2], "w");
        fclose(output);
    }
    return 0;
}

