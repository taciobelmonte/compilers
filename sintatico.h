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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 409 "sintatico.y"
{
    ASTNode *ASTp;
    char *string;
    int intval;
}
/* Line 1529 of yacc.c.  */
#line 123 "sintatico.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

