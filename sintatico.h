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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 400 "sintatico.y"
{
    ASTNode *ASTp;  
    char *string;
    int intval;
}
/* Line 1529 of yacc.c.  */
#line 121 "sintatico.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

