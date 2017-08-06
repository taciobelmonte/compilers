%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define BUFFERMAX 2000
#define MAXCHAR 500
    
//Instancia variáveis
int yylex();
int yyparse();
FILE *yyin;
FILE *yyout;
int COUNTER = 0;

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

%}

%union{
    char *string;
    int intval;
    ASTNode *ASTp;  
};

%token <string> DEC
%token DEF RETURN LET IF ELSE WHILE ASSIGN CONTINUE BREAK
%token OPENPAR CLOSEPAR OPENBLOCK CLOSEBLOCK
%token ENDEXPRESSION SEPARADOR
%token <string> IDENTIFIER
%token OR AND EQUAL DIFF LESS LESSEQUAL GREATEQUAL GREAT PLUS MINUS MULT DIV NOT

%type <ASTp> inicio
%type <ASTp> programa
%type <ASTp> decvar
%type <ASTp> decfunc
%type <ASTp> paramlist
%type <ASTp> exp 
%type <ASTp> bloco
%type <ASTp> looparams
%type <ASTp> loopdecvar
%type <ASTp> loopstmts
%type <ASTp> stmt
%type <ASTp> declaracao
%type <ASTp> assign
%type <ASTp> funccall
%type <ASTp> arglist
%type <ASTp> loopargs


//Define Tokens que foram gerados no Analisador Léxico
%left OR
%left AND
%left EQUAL DIFF
%left LESS LESSEQUAL GREATEQUAL GREAT 
%left PLUS MINUS//+
%left MULT DIV//*
%left NOT
%left UMINUS

%start programa

%error-verbose

%expect 0

%%

programa    :inicio                                         { 
                                                                //printf("1 ");
                                                                printf("[program  ");
                                                             
                                                            }   
            ;

inicio      : decvar inicio                                 {
                                                            printf("2 ");
                                                            }
            | decfunc inicio                                { 
                                                            //printf("3 ");
                                                            printf("[decfunc  ");
                                                              
                                                            }
            |                                               {/*printf("46 ");*/}
            ;

decvar      : LET IDENTIFIER ENDEXPRESSION                  { printf("4 ");/*fprintf(yyout, "  [%s]\n", $2); */}
            | LET IDENTIFIER ASSIGN exp ENDEXPRESSION       { printf("5 ");/*fprintf(yyout, "  [%s]\n", $2);*/ }
            ;

decfunc     : DEF IDENTIFIER OPENPAR paramlist CLOSEPAR bloco   { //printf("6 ");
                                                                  //printf("[ %s   ", $2);  
                                                                }
            | DEF IDENTIFIER OPENPAR CLOSEPAR bloco             {printf("7 ");}
            ;

paramlist   :
             IDENTIFIER looparams                           { //printf("8 ");/*lista  = insereLista(lista, $1); */
                                                              //printf("[%s] ", $1);    
                                                            }
            ;
          
looparams   : SEPARADOR IDENTIFIER looparams                {//printf("9 "); /*lista  = insereLista(lista, $2);*/
                                                            //printf("[%s] ", $2);
                                                            }
            |                                               {}    
            ;

bloco       :
            OPENBLOCK loopdecvar loopstmts CLOSEBLOCK       {//printf("10 ");
                                                             //printf("[%s\n ] ", $1);
                                                            }
            ;

loopdecvar  : decvar loopdecvar                             {printf("11 ");
                                                            }
            |                                               {}
            ;

loopstmts    : stmt loopstmts                               {printf("12 "); 
                                                            // printf("[%s] ", $1);
                                                            }
            |                                               {}

stmt        : declaracao ENDEXPRESSION                      {printf("13 ");}
            | IF OPENPAR exp CLOSEPAR bloco                 {printf("14 ");}
            | IF OPENPAR exp CLOSEPAR bloco ELSE bloco      {printf("15 ");}
            | WHILE OPENPAR exp CLOSEPAR bloco              {printf("16 ");}
            | RETURN exp ENDEXPRESSION                      {
                                                            printf("17 ");
                                                            printf("[return  ");
                                                            }
            | RETURN ENDEXPRESSION                          {printf("[return ] ");}
            | BREAK ENDEXPRESSION                           {printf("19 ");}
            | CONTINUE ENDEXPRESSION                        {printf("20 ");}
            ; 
 
declaracao  : assign                                        {printf("21 ");}
            | funccall                                      {printf("22 ");}
            ;

assign      : IDENTIFIER ASSIGN exp                         {printf("23 ");}
            ; 

funccall    : IDENTIFIER OPENPAR arglist CLOSEPAR           {printf("24 ");}
            | IDENTIFIER OPENPAR CLOSEPAR                   {printf("25 ");}
            ;

arglist     : exp loopargs                                  {printf("26 ");}
            ;

loopargs    : SEPARADOR exp loopargs                        {printf("27 ");}
            |                                               {}
            ;

exp         : exp PLUS exp                                  {
                                                            //printf("28 ");
                                                            //printf("[+] [%d][%d] ", $1,$3);
                                                            //$$ = $1 + $3;
                                                           // printf("%d", $$);
                                                            }
            | exp MINUS exp                                 {printf("29 ");}
            | exp MULT exp                                  {printf("30 ");}
            | exp DIV exp                                   {printf("31 ");}
            | exp LESS exp                                  {printf("32 ");}
            | exp LESSEQUAL exp                             {printf("33 ");}
            | exp GREAT exp                                 {printf("34 ");}
            | exp GREATEQUAL exp                            {printf("35 ");}
            | exp EQUAL exp                                 {printf("36 ");}
            | exp DIFF exp                                  {printf("37 ");}
            | exp AND exp                                   {printf("38 ");}
            | exp OR exp                                    {printf("39 ");}
            | MINUS exp %prec UMINUS                        {printf("40 ");}
            | NOT exp                                       {printf("41 ");}
            | OPENPAR exp CLOSEPAR                          {printf("42 ");}
            | funccall                                      {printf("43 ");}
            | DEC                                           {printf("44 ");}
            | IDENTIFIER                                    {
                                                            //printf("45 ");
                                                           // printf("[%s] ", $1);
                                                            }
            ;
%%

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