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
int MAIN    = 0;
int ARRAY[1000];
int countArray = 0;

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
            fprintf(yyout, "]"); 
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
%token <string>PRINTAOLA
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
%type <ASTp> loopargs2

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

programa    :inicio                                                    {
																			//printf("-[program])\n ");
                                                                            createNAryASTree($1);
                                                                            ARRAY[countArray] = 1;
														 					countArray++;
                                                                            COUNTER++;
                                                                        }
            ;
inicio      : decvar inicio                                             {
                                                                            //printf("2 (Decvar)\n ");
                                                                            
                                                                            $$ = allocTreeNode(LSTMT,2,$1,$2);
                                                                            COUNTER++;
                                                                            
                                                                            ARRAY[countArray] = 2;
														 					countArray++;
                                                                        }
            | decfunc inicio                                            {
                                                                           printf("3- [decfunc]\n ");
                                                                           $$ = allocTreeNode(LSTMT, 2, $1, $2);
                                                                           COUNTER++;
                                                                           
                                                                           ARRAY[countArray] = 3;
														 				   countArray++;
                                                                        }
            |                                                           {$$ = NULL;}
            ;
decvar      : LET IDENTIFIER loopatrib ENDEXPRESSION                    {
                                                                          printf("4 (let ) \n");
                                                                          $$ = allocTreeNode(LTIPAGEM, 2, allocID($2), $3);
                                                                          COUNTER++;
                                                                          
                                                                          
                                                                        }
            ;
loopatrib   : ASSIGN exp                                                {
                                                                            printf("4 (let x = ) \n");
                                                                            $$ = allocTreeNode(LENDEXPRESSION, 1, $2);
                                                                            COUNTER++;
                                                                            
                                                                           ARRAY[countArray] = 4;
														 				   countArray++;
                                                                        }
            |                                                           {
                                                                        printf("4 (let x;)\n");
                                                                        $$ = NULL;
                                                                        }
            ;
decfunc     : DEF PRINTAOLA OPENPAR paramlist CLOSEPAR bloco            {
                                                                          yyerror("print");
                                                                        }
            | DEF IDENTIFIER OPENPAR paramlist CLOSEPAR bloco           {
                                                                        printf("6-(decfunc (%s)) \n", $2);
                                                                        $$ = allocTreeNode(LDEF,3, allocID($2), $4, $6);
                                                                        
                                                                        if(strcmp("main", $2) == 0){
                                                                            MAIN++;
                                                                        }
                                                                        
                                                                        COUNTER++;
                                                                        }
            ;
paramlist   :
             IDENTIFIER looparams                                       {
                                                                        printf("8-(paramlist loop)\n");
                                                                        $$ = allocTreeNode(LPARAM, 2, allocID($1),$2);
                                                                        COUNTER++;
                                                                        }
            |                                                           {
                                                                        printf("8-(no paramlist)\n");
                                                                        $$ = NULL;
                                                                        }
            ;
looparams   : SEPARADOR IDENTIFIER looparams                            {
                                                                        //printf("9-(,ID looparams) \n");
                                                                        $$ = allocTreeNode(LCOMPPARAM, 2, allocID($2),$3);
                                                                        COUNTER++;
                                                                        }
            |                                                           {$$ = NULL ;}
            ;
bloco       :OPENBLOCK loopdecvar loopstmts CLOSEBLOCK                  {
                                                                        printf("10- [bloco] \n");
                                                                        $$ = allocTreeNode(LBLOCK, 3, $2, $3);
                                                                        COUNTER++;
                                                                        }
            ;
loopdecvar  : decvar loopdecvar                                         {
                                                                        printf("11- (loopdecvar) \n");
                                                                        $$ = allocTreeNode(LDECVAR, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            |                                                           {$$ = NULL ;}
            ;
loopstmts   : stmt loopstmts                                            {
                                                                        printf("12- (loop stmts)\n ");
                                                                        $$ = allocTreeNode(LBACK, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            |                                                           {$$ = NULL ;}

stmt        : funccall ENDEXPRESSION                                    {
                                                                        printf("4- (funccall ;) \n");
                                                                        $$ = allocTreeNode(LSTATEMENTFUNCCALL, 1, $1);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 4;
														 				countArray++;
                                                                        }
            | assign ENDEXPRESSION                                      {
                                                                        $$ = allocTreeNode(LASSIGNSTMT, 1, $1);
                                                                        printf("220- (assign ;) \n");
                                                                        COUNTER++;
                                                                        }

            | IF OPENPAR exp CLOSEPAR bloco                             {
                                                                        printf("15- if(exp){} \n");
                                                                        $$ = allocTreeNode(LSTMTIF, 3, $3, $5);
                                                                        COUNTER++;
                                                                        }
            | IF OPENPAR exp CLOSEPAR ELSE bloco                        {
                                                                        printf("15- if(exp)else{} \n");
                                                                        $$ = allocTreeNode(LSTMTIF, 3, $3, $5, $6);
                                                                        COUNTER++;
                                                                        }

            | WHILE OPENPAR exp CLOSEPAR bloco                          {
                                                                        printf("16- while(exp){} \n");
                                                                        $$ = allocTreeNode(LWHILE, 2, $3, $5);
                                                                        COUNTER++;
                                                                        }
            | RETURN loopexp ENDEXPRESSION                              {
                                                                        printf("17- return loopexp; \n");
                                                                        $$ = allocTreeNode(LLABELRETURN, 1, $2);
                                                                        COUNTER++;
                                                                        }
            | BREAK ENDEXPRESSION                                       {
                                                                        printf("20 -break; \n");
                                                                        $$ = allocTreeNode(LLABELBREAK, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            | CONTINUE ENDEXPRESSION                                    {
                                                                        printf("20 -continue; \n");
                                                                        $$ = allocTreeNode(LLABELCONTINUE,2,$1, $2);
                                                                        COUNTER++;
                                                                        }
            ;
loopexp: exp                                                            {
                                                                        $$ = allocTreeNode(LEXP, 1, $1);
                                                                        COUNTER++;
                                                                        }
        |                                                               {$$=NULL;}
        ;
assign      : IDENTIFIER ASSIGN exp                                     {
                                                                        printf("23 x=exp \n");
                                                                        
                                                                        $$ = allocTreeNode(LCOMPASSIGN, 2, allocID($1), $3);
                                                                        COUNTER++;
                                                                        }
            ;
funccall    : IDENTIFIER OPENPAR arglist CLOSEPAR                       {
                                                                        printf("24- id() \n");
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, allocID($1), $3);
                                                                        COUNTER++;
                                                                        }
            | PRINTAOLA OPENPAR arglist CLOSEPAR                        {
                                                                        printf("5- print() \n");
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, allocID($1), $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 5;
														 				countArray++;
                                                                        
                                                                        }
            ;
arglist:
                                                                       {$$=NULL;}
        | loopargs                                                     {
                                                                        $$ = allocTreeNode(LFUNCNARGLIST, 1, $1);
                                                                        COUNTER++;
                                                                       } 
        ;  
            
loopargs     : exp loopargs2                                            {
                                                                        printf("26 - [] \n");
                                                                        $$ = allocTreeNode(LFUNCNNARGLIST, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            ;
loopargs2    : SEPARADOR exp loopargs2                                  {
                                                                         $$ = allocTreeNode(LFUNCNNARGLIST, 2, $2, $3);
                                                                         COUNTER++;
                                                                        }
            |                                                           {$$=NULL;}
            ;
exp         : exp PLUS exp                                              {
                                                                        printf("28 - exp + exp \n");
                                                                        $$ = allocTreeNode(LPLUS, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 6;
														 				countArray++;
                                                                        }
            | exp MINUS exp                                             {
                                                                        printf("29 - exp - exp \n");
                                                                        $$ = allocTreeNode(LMINUS, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 7;
														 				countArray++;
                                                                        }
            | exp MULT exp                                              {
                                                                        printf("30 - exp * exp \n");
                                                                        $$ = allocTreeNode(LMULT, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 8;
														 				countArray++;
                                                                        }
            | exp DIV exp                                               {
                                                                        printf("31 - exp / exp \n");
                                                                        $$ = allocTreeNode(LDIV, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp LESS exp                                              {
                                                                        printf("32 - exp < exp \n");
                                                                        $$ = allocTreeNode(LLESS, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 9;
														 				countArray++;
                                                                        }
            | exp LESSEQUAL exp                                         {
                                                                        printf("33 - exp <= exp \n");
                                                                        $$ = allocTreeNode(LLESSEQUAL, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 10;
														 				countArray++;
                                                                        }
            | exp GREAT exp                                             {
                                                                        printf("34 - exp > exp \n");
                                                                        $$ = allocTreeNode(LGREAT, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 11;
														 				countArray++;
                                                                        }
            | exp GREATEQUAL exp                                        {
                                                                        printf("35 - exp >= exp \n");
                                                                        $$ = allocTreeNode(LGREATEQUAL, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 12;
														 				countArray++;
                                                                        }
            | exp EQUAL exp                                             {
                                                                        printf("36 - exp = exp \n");
                                                                        $$ = allocTreeNode(LEQUAL, 2, $1, $3);
                                                                        COUNTER++;
                                                                        
                                                                         ARRAY[countArray] = 13;
														 				countArray++;
                                                                        }
            | exp DIFF exp                                              {
                                                                        printf("37 - exp != exp \n");
                                                                        $$ = allocTreeNode(LDIFF, 2, $1, $3);COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 14;
														 				countArray++;
                                                                        }
            | exp AND exp                                               {
                                                                        printf("38 - exp && exp \n");
                                                                        $$ = allocTreeNode(LAND, 2, $1, $3);COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 15;
														 				countArray++;
                                                                        }
            | exp OR exp                                                {
                                                                        printf("39 - exp || exp \n");
                                                                        $$ = allocTreeNode(LOR, 2, $1, $3);COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 16;
														 				countArray++;
                                                                        }
            | MINUS exp %prec UMINUS                                    {
                                                                        printf("40 - exp \n");
                                                                        $$ = allocTreeNode(LUMINUS, 1, $2);COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 17;
														 				countArray++;
                                                                        }
            | NOT exp                                                   {
                                                                        printf("41 - !exp \n");
                                                                        $$ = allocTreeNode(LNOT, 1, $2);COUNTER++;
                                                                        ARRAY[countArray] = 18;
														 				countArray++;
                                                                        }
            | OPENPAR exp CLOSEPAR                                      {
                                                                        printf("42 - (exp) \n");
                                                                        $$ = allocTreeNode(LOPENPAR, 1, $2);COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 19;
														 				countArray++;
                                                                        }
            | funccall                                                  {
                                                                        printf("43 - funccall\n");
                                                                        $$ = allocTreeNode(LLABELFUNCCALL, 2, $1);
                                                                        COUNTER++;
                                                                        
                                                                        ARRAY[countArray] = 20;
														 				countArray++;
                                                                        }
            | DEC                                                       {
                                                                        printf("44 dec\n ");
                                                                        $$ = allocINT($1);
                                                                        COUNTER++;
                                                                        
                                                                         ARRAY[countArray] = 21;
														 				countArray++;
                                                                        }
            | IDENTIFIER                                                {
                                                                        printf("45 id\n ");
                                                                        $$ = allocID($1);
                                                                        COUNTER++;
                                                                        
                                                                         ARRAY[countArray] = 22;
														 				countArray++;
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
    fprintf(yyout,"]\n");
    
    for(int i = countArray-1 ; i > 0; i--){
        printf("%d",ARRAY[i]);
    }

    fclose(input);
    fclose(output);

    //If errors, clear file
    if(ERRORS != 0 || COUNTER==1 || (MAIN==0 || MAIN>1)){
        FILE *output = fopen(argv[2], "w");
        fclose(output);
    }
    return 0;
}
