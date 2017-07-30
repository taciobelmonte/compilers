/*
    Universidade Federal da Bahia
    MATA61 - Compiladores
    Professor: Roberto Parente
    Alunos: Tácio Belmonte e Marino Souza
    Analisador Léxico
*/


%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sintatico.h"

int lineNumber = 1;

%}

digito          [0-9]
letra           [a-zA-Z]
ID              ({letra})(_|{letra}|{digito})*
whitespace      [ ]
delimitador     [\t]
ws			    ({delimitador}|{whitespace})
errodiferente   ({digito})+(_|{letra}|{digito})*

%%

{ws}                                                                                                                /*Ignora*/
{digito}+                                                                                                           {
                                                                                                                        yylval.intval = atoi(yytext);
                                                                                                                        return DEC;
                                                                                                                    }
"+" | "-" | "*" | "/" | "<" | "<=" | ">" | ">=" | "==" | "!=" | "&&" | "||"                             	    {return BINOP;}
"-" | "!"                                                                                                	    {return UNOP;}
def                                                                                                                 {return DEF;}
return                                                                                                              {return RETURN;}
let                                                                                                                 {return LET;}
if                                                                                                                  {return IF;}
else                                                                                                                {return ELSE;}
while                                                                                                               {return WHILE;}
"="                                                                                                                 {return ASSIGN;}
continue                                                                                                            {return CONTINUE;}
";"                                                                                                                 {return ENDEXPRESSION;}
","                                                                                                                 {return SEPARADOR;}
break                                                                                                               {return BREAK;}
"("                                                                                                                 {return OPENPAR;}
")"                                                                                                                 {return CLOSEPAR;}
"{"                                                                                                                 {return OPENBLOCK;}
"}"                                                                                                                 {return CLOSEBLOCK;}
{ID}                                                                                                                {
                                                                                                                    yylval.string = malloc(strlen(yytext));
                                                                                                                    strncpy(yylval.string, yytext, strlen(yytext));
                                                                                                                    return(ID);
                                                                                                                    }
\n                                                                                                                  {++lineNumber;}
{ws}+                                                                                                               /*Remove espaços em branco*/
"//".*                                                                                                              /*Remove comentarios de uma linha*/
.                                                                                                                   {return -2;}
{errodiferente}                                                                                                     {return -2;}
<<EOF>>                                                                                                             {return -1;}

%%
int yywrap();

int yywrap(){
    return 1;
}
