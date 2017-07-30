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
     BINOP = 258,
     UNOP = 259,
     SYM = 260,
     DEC = 261,
     DEF = 262,
     RETURN = 263,
     LET = 264,
     IF = 265,
     ELSE = 266,
     WHILE = 267,
     ASSIGN = 268,
     CONTINUE = 269,
     BREAK = 270,
     OPENPAR = 271,
     CLOSEPAR = 272,
     OPENBLOCK = 273,
     ENDEXPRESSION = 274,
     SEPARADOR = 275,
     CLOSEBLOCK = 276,
     ID = 277
   };
#endif
/* Tokens.  */
#define BINOP 258
#define UNOP 259
#define SYM 260
#define DEC 261
#define DEF 262
#define RETURN 263
#define LET 264
#define IF 265
#define ELSE 266
#define WHILE 267
#define ASSIGN 268
#define CONTINUE 269
#define BREAK 270
#define OPENPAR 271
#define CLOSEPAR 272
#define OPENBLOCK 273
#define ENDEXPRESSION 274
#define SEPARADOR 275
#define CLOSEBLOCK 276
#define ID 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 66 "sintatico.y"
{
    char *string;
    int intval;
}
/* Line 1529 of yacc.c.  */
#line 98 "sintatico.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

