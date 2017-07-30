%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERMAX 2000

//Instancia variáveis
int yylex();
int yyparse();
FILE *yyin;
FILE *yyout;
int COUNTER = 0;

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

%}

%union{
    char *string;
    int intval;
}

//Define Tokens que foram gerados no Analisador Léxico
%token BINOP
%token UNOP
%token SYM
%token <intval> DEC
%token DEF
%token RETURN
%token LET
%token IF
%token ELSE
%token WHILE
%token ASSIGN
%token CONTINUE
%token BREAK
%token OPENPAR
%token CLOSEPAR
%token OPENBLOCK
%token ENDEXPRESSION
%token SEPARADOR
%token CLOSEBLOCK
%token <string> ID

%start Inicio
%%

Inicio:
    { fprintf(yyout, "[program\n"); }
    Programa
    { fprintf(yyout, "]"); }
    ;

Programa:
        //Statement
        | DeclaraVariavel      
        | DeclaraFuncao 
        //| Atribuicao
	;

DeclaraFuncao: 
        DEF ID                                      { fprintf(yyout, "  [decfunc\n      [%s]\n", $2); }
        OPENPAR                                     { fprintf(yyout, "      [paramlist "); }
        Parametros                                  { 
                                                        imprimeLista(lista); 
                                                        lista = NULL;
                                                        COUNTER = 0;
                                                    }
        CLOSEPAR                                    { fprintf(yyout, "] "); }
        Bloco 
        { fprintf(yyout, "  ]\n"); }
        ;

Bloco:
        OPENBLOCK                                   { fprintf(yyout, "\n      [block "); }   
        Conteudo
        CLOSEBLOCK                                  { fprintf(yyout, "\n      ]\n"); }  
        ;

Conteudo:
        | DeclaraVariavel                  
        | Statement
        ;

Parametros:
                                                    { lista  = insereLista(lista, ""); } 
        | ID Parametros                             { lista  = insereLista(lista, $1); } 
        | SEPARADOR ID Parametros                   { lista  = insereLista(lista, $2); }
        ;

DeclaraVariavel: 
        LET                                         {  fprintf(yyout, "\n          [decvar "); }  
        Variaveis                                   { 

                                                       imprimeLista(lista);    
                                                       lista = NULL;
                                                       COUNTER = 0;
                                                    }
        ENDEXPRESSION                               {fprintf(yyout, "]"); }  
        ;
        
//Recursao para identificar mais de uma variavel
Variaveis:
        ID                                          {lista  = insereLista(lista, $1);}  
        | ID SEPARADOR Variaveis                    {lista  = insereLista(lista, $1);}
        | ID SEPARADOR                              {lista  = insereLista(lista, $1);}
        ;

Statement:
     RETURN                                         { fprintf(yyout, "\n        [return "); }    
     | Expressao
     | ID                                           { fprintf(yyout, "\n        [return [%s]]", $1); }    
     ENDEXPRESSION
     //| Atribuicao ENDEXPRESSION   
     
     //| RETURN ENDEXPRESSION                         { fprintf(yyout, "\n        [return ] "); }   
     
     /*| chamadaFuncao ENDEXPRESSION
     | IF OPENPAR Expressao CLOSEPAR Bloco
     | IF OPENPAR Expressao CLOSEPAR Bloco ELSE Bloco
     | WHILE OPENPAR Expressao CLOSEPAR Bloco
     | RETURN ENDEXPRESSION                 { fprintf(yyout, "\n          [return "); }   
     | RETURN Expressao ENDEXPRESSION       { fprintf(yyout, "\n          [return "); }   
     | BREAK ENDEXPRESSION
     | CONTINUE ENDEXPRESSION*/
     ;

Atribuicao:
        //ID ASSIGN DEC ENDEXPRESSION                  { fprintf(yyout, "\n          [assign [%s] [%d]]", $1, $3); }   
         ID ASSIGN Expressao ENDEXPRESSION        { fprintf(yyout, "\n          [assign [%s]", $1); }
        ;
        
Expressao:
        | ID BINOP                             { fprintf(yyout, "\n     foi     [[%s]", $1); }
        | DEC BINOP DEC
        ENDEXPRESSION
        ;

/*chamadaFuncao:
        ID OPENPAR CLOSEPAR
        | ID OPENPAR ListaArgumentos CLOSEPAR
        ;*/

/*ListaArgumentos:
        Expressao
        | Expressao SEPARADOR Expressao
        ;

Expressao:
        Expressao BINOP Expressao       
        | UNOP Expressao
        | OPENPAR Expressao CLOSEPAR
        | chamadaFuncao
        | DEC                           { fprintf(yyout, "\n          [%d]", $1); }   
        | ID                            { fprintf(yyout, "\n          [%s]", $1); }   
        ;
*/

%%

int main(int argc, char** argv) {

    FILE *input  = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");  

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