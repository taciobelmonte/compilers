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

{ws}                                                                                                                    /*Ignora*/
{digito}+                                                                                       {fprintf(yyout,"DEC \"%s\" %d \n", yytext, lineNumber);}
let|def|if|else|while|return|break|continue                                                     {fprintf(yyout,"KEY \"%s\" %d \n", yytext, lineNumber);}
"("|")"|"{"|"}"|"["|"]"|"="|","|";"|"<="|">="|"=="|"!="|"&&"|"||"|"!"|"+"|"-"|"*"|"/"|"<"|">"	{fprintf(yyout,"SYM \"%s\" %d \n", yytext, lineNumber);}
{ID}                                                                                            {fprintf(yyout,"ID \"%s\" %d \n", yytext, lineNumber);}
\n                                                                                              {++lineNumber;}
{ws}+                                                                                           /*Remove espaços em branco*/
"//".*                                                                                          /*Remove comentarios de uma linha*/
.                                                                                               {return -2;}
{errodiferente}                                                                                 {return -2;}
<<EOF>>                                                                                         {return -1;}

%%
int yywrap();

int main(int argc, char** argv){
    int num = 0;
    int token = -1;

    yyin  = fopen( argv[1], "r" );
    yyout = fopen( argv[2], "w" );

    do{
        token = yylex();

        if(token == -1){
            break;
        }else if(token == -2){

            //Imprime em caso de erro
            fprintf(yyout,"ERROR \"%s\" %d \n", yytext, lineNumber);
            return 0;
        }
        else if(yyleng == 0){
            //printf("\n[ERRO] Lexema não pertence a linguagem.");
        }
    }while( token != EOF);

    fclose(yyout);
    fclose(yyin);
    return 0;
}

int yywrap(){
    return 1;
}
