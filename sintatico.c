%{
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
    LSTMTFUNCCALL,
    LFUNCNARGLIST,
    LOPENPAR,
    LFUNCNNARGLIST,
    LFUNCCALL,
    LLABELCONTINUE,
    LSTMTELSE,
    LVOLTASTMT,
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

    //    printf("criou node %d\n ", token);
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
        if(tree->tipo == AST)
            createASTreeType(tree);
        if(tree->tipo == ID)
            fprintf(yyout," [%s]", tree->id.name);
        if(tree->tipo == INT)
            fprintf(yyout," [%d]", tree->integer.integer);	
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
            caseExpression(tree, "-",0, 1);
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
        case LLABELFUNCCALL:
            caseExpression(tree, "funccall",0, 1);
            break;
         case LSTMTIF:
            caseExpression(tree, "if", 2, 1);
            break;
        case LIF:
            caseExpression(tree, "", 1, 0);
            if(tree->tree.totalkids>2)
                createNAryASTree(tree->tree.kids[2]);
            break;
        case LSTMT:
            if(tree->tree.totalkids>=2){ 
                if(tree->tree.kids[0]!= NULL) {
                    caseExpression(tree, "", 1, 0);
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
                    fprintf(yyout, " [decvar [%s]] ", tree->tree.kids[0]->id.name);
                }
            }
            break;
        case LDEF:
                fprintf(yyout, " [decfunc [%s] ",tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                if(tree->tree.kids[1] == NULL)
                    fprintf(yyout, "[paramlist]");
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
         case LVOLTASTMT:
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
         case LSTMTFUNCCALL:
                fprintf(yyout," [funccall ");
                createNAryASTree(tree->tree.kids[0]); 
                fprintf(yyout,"]");
                break;
         case LFUNCNARGLIST:
                caseExpression(tree, "arglist",1, 1);
                break;
          case LOPENPAR:
            createNAryASTree(tree->tree.kids[0]);
            break;
         case LFUNCNNARGLIST:
            caseExpression(tree, "",1, 0);
            break;
         case LFUNCCALL:
            if(tree->tree.kids[1] != NULL) {
                fprintf(yyout,"[%s]", tree->tree.kids[0]->id.name); 
                createNAryASTree(tree->tree.kids[1]); 
            }
            else {
                fprintf(yyout,"[%s]", tree->tree.kids[0]->id.name); 
                fprintf(yyout,"[arglist]");
            }
         break;
    }
}

/*######## HELPER FUNCTIONS ##########*/
%}

//Define types
%union{
    ASTNode *ASTp;  
    char *string;
    int intval;
};

//TERMINALS
%token <intval>DEC
%token <string>DEF 
%token <string>RETURN 
%token <string>LET 
%token <string>IF 
%token <string>ELSE 
%token <string>WHILE 
%token <string>ASSIGN 
%token <string>CONTINUE 
%token <string>BREAK
%token <string>OPENPAR 
%token <string>CLOSEPAR 
%token <string>OPENBLOCK 
%token <string>CLOSEBLOCK
%token <string>ENDEXPRESSION 
%token <string>SEPARADOR 
%token <string>IDENTIFIER
%token <string>OR
%token <string>AND 
%token <string>EQUAL 
%token <string>DIFF 
%token <string>LESS 
%token <string>LESSEQUAL 
%token <string>GREATEQUAL 
%token <string>GREAT 
%token <string>PLUS 
%token <string>MINUS 
%token <string>MULT 
%token <string>DIV 
%token <string>NOT 

//NON TERMINALS
%type <ASTp> inicio 
%type <ASTp> exp 
%type <ASTp> programa 
%type <ASTp> decvar 
%type <ASTp> loopdecvar 
%type <ASTp> decfunc 
%type <ASTp> paramlist 
%type <ASTp> looparams 
%type <ASTp> bloco
%type <ASTp> loopstmts 
%type <ASTp> assign 
%type <ASTp> stmt 
%type <ASTp> funccall
%type <ASTp> arglist 
%type <ASTp> loopargs 
%type <ASTp> loopatrib 
%type <ASTp> loopexp 
%type <ASTp> declaracao

//Define Tokens that has been generated from Lexical Analyser
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

programa    :inicio                                                     { 
                                                                           // printf("1 ");
                                                                            createNAryASTree($1);  
                                                                        }   
            ;
inicio      : decvar inicio                                             {
                                                                            //printf("2 ");
                                                                            $$ = allocTreeNode(LSTMT,2,$1,$2);
                                                                        }
            | decfunc inicio                                            { 
                                                                           // printf("3 ");
                                                                            $$ = allocTreeNode(LSTMT, 2, $1, $2);
                                                                        }
            |                                                           {$$ = NULL;}
            ;
decvar      : LET IDENTIFIER loopatrib ENDEXPRESSION                    { 
                                                                         // printf("4 ");
                                                                          $$ = allocTreeNode(LTIPAGEM, 2, allocID($2), $3); 
                                                                        }
            ;
loopatrib   : ASSIGN exp                                                {
                                                                            $$ = allocTreeNode(LENDEXPRESSION, 1, $2); 
                                                                        }
            |                                                           {$$ = NULL;}
            ;
decfunc     : DEF IDENTIFIER OPENPAR paramlist CLOSEPAR bloco           { 
                                                                        //printf("6-DEFFUNC ");
                                                                        $$ = allocTreeNode(LDEF, 3, allocID($2), $4, $6);
                                                                        }
            ;
paramlist   :
             IDENTIFIER looparams                                       { 
                                                                        //printf("8 ");
                                                                        $$ = allocTreeNode(LPARAM, 2, allocID($1),$2);
                                                                        }
            |                                                           {$$ = NULL;}
            ;
looparams   : SEPARADOR IDENTIFIER looparams                            {
                                                                        //printf("9 ");
                                                                        $$ = allocTreeNode(LCOMPPARAM, 2, allocID($2),$3);
                                                                        }
            |                                                           {$$ = NULL ;}    
            ;
bloco       :OPENBLOCK loopdecvar loopstmts CLOSEBLOCK                  {
                                                                        //printf("10 ");
                                                                        $$ = allocTreeNode(LBLOCK, 3, $2, $3);
                                                                        }
            ;
loopdecvar  : decvar loopdecvar                                         {//printf("11 ");
                                                                        $$ = allocTreeNode(LDECVAR, 2, $1, $2);
                                                                        }
            |                                                           {$$ = NULL ;}
            ;
loopstmts   : stmt loopstmts                                            {//printf("12 "); 
                                                                        $$ = allocTreeNode(LVOLTASTMT, 2, $1, $2);
                                                                        }
            |                                                           {$$ = NULL ;}

stmt        : declaracao ENDEXPRESSION                                  {
                                                                        //printf("220 ");
                                                                        $$ = allocTreeNode(LSTMTFUNCCALL, 1, $1);
                                                                        }     
            | IF OPENPAR exp CLOSEPAR bloco                             {
                                                                        //printf("15 ");
                                                                        $$ = allocTreeNode(LSTMTIF, 3, $3, $5);
                                                                        }
            | IF OPENPAR exp CLOSEPAR ELSE bloco                        {
                                                                        //printf("15 ");
                                                                        $$ = allocTreeNode(LSTMTIF, 3, $3, $5, $6);
                                                                        }
             
            | WHILE OPENPAR exp CLOSEPAR bloco                          {
                                                                        //printf("16 ");
                                                                        $$ = allocTreeNode(LWHILE, 2, $3, $5); 
                                                                        }
            | RETURN loopexp ENDEXPRESSION                              {
                                                                        //printf("17 ");
                                                                        $$ = allocTreeNode(LLABELRETURN, 1, $2);
                                                                        }
            | BREAK ENDEXPRESSION                                       {
                                                                        $$ = allocTreeNode(LLABELBREAK, 2, $1, $2);
                                                                        }
            | CONTINUE ENDEXPRESSION                                    {
                                                                        //printf("20 ");
                                                                        $$ = allocTreeNode(LLABELCONTINUE,2,$1, $2); 
                                                                        }   
            ; 
declaracao: assign                                                      {
                                                                        //printf("ASSIGN ");
                                                                        $$ = allocTreeNode(LASSIGNSTMT, 1, $1);
                                                                        }
            | funccall                                                  {
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, $1);
                                                                        }
         ;
loopexp: exp                                                            {$$ = allocTreeNode(LEXP, 1, $1);}
        |                                                               {$$=NULL;}
        ;
assign      : IDENTIFIER ASSIGN exp                                     {
                                                                        //printf("23 ");
                                                                        //$$ = allocTreeNode(LASSIGNSTMT, 1, $1);
                                                                        $$ = allocTreeNode(LCOMPASSIGN, 2, allocID($1), $3);
                                                                        }
            ; 
funccall    : IDENTIFIER OPENPAR arglist CLOSEPAR                       {
                                                                        //printf("24 ");
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, allocID($1), $3);
                                                                        }
            | IDENTIFIER OPENPAR CLOSEPAR                               {
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, allocID($1));
                                                                        }
            ;   
arglist     : exp loopargs                                              {
                                                                        //printf("26 ");
                                                                        $$ = allocTreeNode(LLABELFUNCCALL, 1, $1);
                                                                        }
            ;
loopargs    : SEPARADOR exp loopargs                                    {
                                                                         //printf("27 ");
                                                                         $$ = allocTreeNode(LLABELFUNCCALL, 2, $1, $2);
                                                                        }
            |                                                           {$$=NULL;}
            ;
exp         : exp PLUS exp                                              {
                                                                        //printf("28 ");
                                                                        $$ = allocTreeNode(LPLUS, 2, $1, $3);
                                                                        }
            | exp MINUS exp                                             {
                                                                        //printf("29 ");
                                                                        $$ = allocTreeNode(LMINUS, 2, $1, $3); 
                                                                        }
            | exp MULT exp                                              {
                                                                        //printf("30 ");
                                                                        $$ = allocTreeNode(LMULT, 2, $1, $3);
                                                                        }
            | exp DIV exp                                               {
                                                                        //printf("31 ");
                                                                        $$ = allocTreeNode(LDIV, 2, $1, $3);
                                                                        }
            | exp LESS exp                                              {
                                                                        //printf("32 ");
                                                                        $$ = allocTreeNode(LLESS, 2, $1, $3);
                                                                        }
            | exp LESSEQUAL exp                                         {
                                                                        //printf("33 ");
                                                                        $$ = allocTreeNode(LLESSEQUAL, 2, $1, $3); 
                                                                        }
            | exp GREAT exp                                             {
                                                                        //printf("34 ");
                                                                        $$ = allocTreeNode(LGREAT, 2, $1, $3);
                                                                        }
            | exp GREATEQUAL exp                                        {
                                                                        //printf("35 ");
                                                                        $$ = allocTreeNode(LGREATEQUAL, 2, $1, $3);
                                                                        }
            | exp EQUAL exp                                             {
                                                                        //printf("36 ");
                                                                        $$ = allocTreeNode(LEQUAL, 2, $1, $3);
                                                                        }
            | exp DIFF exp                                              {
//                                                                      printf("37 ");
                                                                        $$ = allocTreeNode(LDIFF, 2, $1, $3);
                                                                        }
            | exp AND exp                                               {
                                                                        //printf("38 ");
                                                                        $$ = allocTreeNode(LAND, 2, $1, $3);
                                                                        }
            | exp OR exp                                                {
                                                                        //printf("39 ");
                                                                        $$ = allocTreeNode(LOR, 2, $1, $3);
                                                                        }
            | MINUS exp %prec UMINUS                                    {
                                                                        //printf("40 ");
                                                                        $$ = allocTreeNode(LUMINUS, 1, $2);
                                                                        }
            | NOT exp                                                   {
                                                                        //printf("41 ");
                                                                        $$ = allocTreeNode(LNOT, 1, $2);
                                                                        }
            | OPENPAR exp CLOSEPAR                                      {
                                                                        //printf("42 ");
                                                                        $$ = allocTreeNode(LOPENPAR, 1, $2); 
                                                                        }
            | funccall                                                  {
                                                                        //printf("43 ");
                                                                        { $$ = allocTreeNode(LLABELFUNCCALL, 2, $1); }
                                                                        }
            | DEC                                                       {
                                                                        //printf("44 ");
                                                                        $$ = allocINT($1);
                                                                        }
            | IDENTIFIER                                                {
                                                                        //printf("45 ");
                                                                        $$ = allocID($1);
                                                                        }
            ;
%%

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
    fprintf(yyout,"]");
    
    fclose(input);
    fclose(output);
    
    //If errors, clear file
    if(ERRORS != 0){
        FILE *output = fopen(argv[2], "w");
        fclose(output);
    }
    return 0;
}