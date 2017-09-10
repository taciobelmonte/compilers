%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include "codegen.h"

#define BUFFERMAX 2000
#define MAXCHAR 500

//Instancia variáveis
int yylex();
int yyparse();
int yyerror(const char *);
FILE *yyin;
FILE *yyout;
FILE *outrofile;
int globalexp = 0;
int COUNTER = 0;
int ERRORS  = 0;
int MAIN    = 0;
int args    = 0;
int args_total = 0;
int if_stmt_num = 0;
int while_stmt_num = 0;
char last_function[MAXCHAR] = {'m', 'a', 'i', 'n'};
int last_while = 0;

typedef enum typesList {
    INT,
    ID,
    AST
}type;

typedef enum varLocation {
    STACK,
    DEFINITION,
    NONDEF
}varLocation;

typedef enum varPurpose {
    LOADUSE,
    STORAGEUSE,
    NONPURP
}varPurpose;

typedef struct nodeSym {
    char name[MAXCHAR];
    varLocation location;
    int my_stack_position;
}nodeSym;

nodeSym tableSym[200];
int qtdSym = 0;

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
    GLOBLENDEXPRESSION,
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
    GLOBLTIPAGEM,
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
    int args_total;
    int if_stmt_num;
    int while_stmt_num;
    varPurpose purpose;
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
ASTNode *allocID(char string[MAXCHAR], varLocation l, varPurpose p);
ASTNode *allocTreeNode(int no_token, int nfilhos, ...);
void newSymbol(char string[MAXCHAR], varLocation l);
nodeSym findVarContext(char string[MAXCHAR]);
void declareVars();
void createNAryASTree(ASTNode *tree);
void createASTreeType(ASTNode *tree);

//Functions Denifitions
ASTNode *allocINT(int valor) {
    ASTNode *newnode = malloc(sizeof(ASTNode));
    newnode->tipo = INT;
    newnode->integer.integer = valor;
    return newnode;
}
ASTNode *allocID(char string[MAXCHAR], varLocation l, varPurpose p) {
    ASTNode *newnode = malloc(sizeof(ASTNode));
    newnode->tipo = ID;
    strcpy(newnode->id.name, string);
    newnode->purpose = p;
    if (l == DEFINITION || l == STACK)
        newSymbol(string, l);
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
    if(token == LDEF)
        newnode->args_total = args_total;
    if(token == LSTMTIF)
        newnode->if_stmt_num = if_stmt_num;
    if(token == LWHILE)
        newnode->while_stmt_num = while_stmt_num;

    for(i =0; i < totalkids; i++)
         newnode->tree.kids[i] = va_arg(list, ASTNode*);

    va_end(list);
    return newnode;
}

void newSymbol(char string[MAXCHAR], varLocation l)
{
    nodeSym newnode;
    newnode.location = l;
    newnode.my_stack_position = args;
    strcpy(newnode.name, string);
    tableSym[qtdSym] = newnode;
    qtdSym++;
    //printf("qtdSym == %d\n", qtdSym);
    //printf("degub: alocou %s do tipo ", string);
    //if(l == DEFINITION)
        //printf("DEFINITION\n");
    //else
        //printf("STACK\n");
}

nodeSym findVarContext(char string[MAXCHAR])
{
    //printf("debug: estou procurando %s\n", string);
    int i;
    //TODO conferir quando tem mais de uma variavel com mesmo nome
    for(i=0; i<qtdSym && strcmp(string, tableSym[i].name); i++);
    return tableSym[i];

}

void essaEhMinhaTabela() {
    int i;
    for(i=0; i<qtdSym; i++){
        if(tableSym[i].location == DEFINITION)
            printf("definição");
        if(tableSym[i].location == STACK)
            printf("stack");
        if(tableSym[i].location == NONDEF)
            printf("nondef");
        printf("\n");
    }
}

void declareVars()
{
    int i;
    //printf("qtdSym == %d\n", qtdSym);
    for(i=0; i<qtdSym; i++){
        //printf("i == %d\n", i);
        if(tableSym[i].location == DEFINITION)
            fprintf(yyout, codegen_variable, tableSym[i].name);
    }
}

void createNAryASTree(ASTNode *tree)
{
    if(tree != NULL) {
        if(tree->tipo == AST){
            createASTreeType(tree);
        }else if(tree->tipo == ID){
            //fprintf(yyout," [%s]", tree->id.name);
            //TODO refazer pra quando x esta na definição, e pra essa caso de pilha trocar o 4 por qdt de saltos pra cada
            nodeSym no;
            no = findVarContext(tree->id.name);
            if(no.location == DEFINITION)
                fprintf(yyout, load_var, tree->id.name);
            else
                fprintf(yyout, load_x, 4*no.my_stack_position);
            //printf("load %s\n", tree->id.name);
        }else if(tree->tipo == INT){
            //fprintf(yyout," [%d]", tree->integer.integer);
            fprintf(yyout, load_int, tree->integer.integer);
            //printf("load %d\n", tree->integer.integer);
        }
    }
}

/**
 * @param ASTNode tree
 * @param item
 * @param type - 0 for BINOP ? 1 for UNOP ? 2 for 3 children
 */
void caseExpression(ASTNode *tree, char* item, int type, int label){

    //if(label){
    //    fprintf(yyout, " [");
    //    fprintf(yyout, "%s", item);
    //}
    //Create tree for first node
    createNAryASTree(tree->tree.kids[0]);

    //Create tree for second node if is binop operation
    if(!type)
        createNAryASTree(tree->tree.kids[1]);

    //if(label)
    //    fprintf(yyout, "]");
}

void nodeExpression(ASTNode *tree, char* item, int type){

    //Create tree for first node
    createNAryASTree(tree->tree.kids[0]);

    //Create tree for second node if is binop operation
    if(!type){
        fprintf(yyout, push_a0);
        createNAryASTree(tree->tree.kids[1]);
        fprintf(yyout, top_t1);
        fprintf(yyout, pop);
    }
}

void createASTreeType(ASTNode *tree){
    switch(tree->tree.token) {
        case LPLUS:
            //TODO revisar codegen_exp
            nodeExpression(tree, "+",0);
            fprintf(yyout, cgen_add);
        break;
        case LMINUS:
            nodeExpression(tree, "-",0);
            fprintf(yyout, cgen_sub);
        break;
        case LMULT:
            nodeExpression(tree, "*",0);
            fprintf(yyout, cgen_mul);
            break;
        case LDIV:
            nodeExpression(tree, "/",0);
            fprintf(yyout, cgen_div);
            break;
        case LUMINUS:
            nodeExpression(tree, "-",1);
            fprintf(yyout, cgen_unminus);
            break;
        case LAND:
            nodeExpression(tree, "&&",0);
            fprintf(yyout, cgen_and);
            break;
        case LOR:
            nodeExpression(tree, "||",0);
            fprintf(yyout, cgen_or);
            break;
        case LNOT:
            nodeExpression(tree, "!",1);
            fprintf(yyout, cgen_not);
            break;
        case LGREAT:
            nodeExpression(tree, ">",0);
            fprintf(yyout, cgen_sgt);
            break;
        case LGREATEQUAL:
            nodeExpression(tree, ">=",0);
            fprintf(yyout, cgen_sge);
            break;
        case LLESSEQUAL:
            nodeExpression(tree, "<=",0);
            fprintf(yyout, cgen_sle);
            break;
        case LLESS:
            nodeExpression(tree, "<",0);
            fprintf(yyout, cgen_slt);
            break;
        case LEQUAL:
            nodeExpression(tree, "==",0);
            fprintf(yyout, cgen_seq);
            break;
        case LDIFF:
            nodeExpression(tree, "!=",0);
            fprintf(yyout, cgen_sneq);
            break;
        case LWHILE:
            last_while = tree->while_stmt_num;
            //printf("começando a while %d\n", last_while);
            fprintf(yyout, codegen_while_def, last_while);
            //evaluate exp
            createNAryASTree(tree->tree.kids[0]);
            //printf("fez a exp cond do while %d\n", last_while);
            last_while = tree->while_stmt_num;
            fprintf(yyout, codegen_while_comp, last_while);
            //evaluate block
            createNAryASTree(tree->tree.kids[1]);
            //printf("gerou o bloco do while %d\n", last_while);
            last_while = tree->while_stmt_num;
            fprintf(yyout, codegen_endwhile, last_while, last_while);
            //caseExpression(tree, "while",0, 1);
            break;
        case LLABELRETURN:
            caseExpression(tree, "return",1, 1);
            fprintf(yyout, codegen_return_token, last_function);
            break;
        case LSTMTIF:
            //printf("começando codegen de if%d\n", tree->if_stmt_num);
            createNAryASTree(tree->tree.kids[0]);
            //printf("codegenerou a comp exp de if%d\n", tree->if_stmt_num);
            fprintf(yyout, codegen_if_comp, tree->if_stmt_num);
            //check if else tree is null before call its codegen
            if (tree->tree.kids[2] != NULL){
                //printf("antes do else de if%d\n", tree->if_stmt_num);
                fprintf(yyout, codegen_false_branch, tree->if_stmt_num);
                createNAryASTree(tree->tree.kids[2]);
                fprintf(yyout, codegen_b_endif, tree->if_stmt_num);
                //printf("codegenerou o else de if%d\n", tree->if_stmt_num);
            }
            //printf("antes do trueb de if%d\n", tree->if_stmt_num);
            fprintf(yyout, codegen_true_branch, tree->if_stmt_num, tree->if_stmt_num);
            createNAryASTree(tree->tree.kids[1]);
            //printf("codegenerou o trueb de if%d\n", tree->if_stmt_num);
            fprintf(yyout, codegen_endif, tree->if_stmt_num);
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
             //aquitbm
             //fprintf(yyout, "]");
            break;
        case GLOBLENDEXPRESSION:
             createNAryASTree(tree->tree.kids[0]);
             //aquitbm
             //fprintf(yyout, "]");
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
                    //aquitbm
                    //fprintf(yyout, " [decvar [%s]", tree->tree.kids[0]->id.name);
                    createNAryASTree(tree->tree.kids[1]);
                    //("\tsw $a0, var_%s\n", tree->tree.kids[0]->id.name)
                    fprintf(yyout, save_var, tree->tree.kids[0]->id.name);
                } else {
                    //aquitbm
                    //fprintf(yyout, " [decvar [%s]]", tree->tree.kids[0]->id.name);
                }
            }
            break;
        case GLOBLTIPAGEM:
            globalexp = 1;
            if( tree->tree.totalkids>=2){
                if(tree->tree.kids[1]!= NULL) {
                    FILE *tempfile;
                    tempfile = yyout;
                    yyout = outrofile;
                    createNAryASTree(tree->tree.kids[1]);
                    fprintf(yyout, save_var, tree->tree.kids[0]->id.name);
                    yyout = tempfile;
                } else {
                    //aquitbm
                    //fprintf(yyout, " [decvar [%s]]", tree->tree.kids[0]->id.name);
                }
            }
            break;
        case LDEF:
                //fprintf(yyout, " [decfunc [%s]",tree->tree.kids[0]->id.name);
                strcpy(last_function, tree->tree.kids[0]->id.name);
                //printf("começando a definir %s\n", last_function);
                fprintf(yyout, codegen_decfunc, tree->tree.kids[0]->id.name);
                //TODO proper codegen for paramlist of a function
                createNAryASTree(tree->tree.kids[1]);
                //printf("codegenerei os params de %s\n", last_function);
                //if(tree->tree.kids[1] == NULL)
                //    fprintf(yyout, " [paramlist]");
                createNAryASTree(tree->tree.kids[2]);
                //fprintf(yyout, "]");
                fprintf(yyout, codegen_decfunc_sufix, tree->tree.kids[0]->id.name, 8 + tree->args_total * 4);
                //printf("terminei de definir %s\n", last_function);
                break;
        case LPARAM:
                //fprintf(yyout, " [paramlist [%s]",tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                //fprintf(yyout, "]");
                break;
        case LCOMPPARAM:
                //fprintf(yyout, " [%s]",tree->tree.kids[0]->id.name);
                createNAryASTree(tree->tree.kids[1]);
                break;
        case LBLOCK:
                //fprintf(yyout, " [block");
                //TODO codegen_decvar
                if(tree->tree.kids[0] != NULL)
                    createNAryASTree(tree->tree.kids[0]);
                //TODO codegen_stmts
                if(tree->tree.kids[1] != NULL)
                        createNAryASTree(tree->tree.kids[1]);
                //fprintf(yyout, "]");
                break;
         case LASSIGNSTMT:
                //fprintf(yyout, " [assign ");
                createNAryASTree(tree->tree.kids[0]);
                break;
         case LCOMPASSIGN:
                createNAryASTree(tree->tree.kids[1]);
                //TODO %s = $a0, tem q refazer pra quando %s está declarada, ao invés de pilha, além do numero de saltos
                //fprintf(yyout, save_x, 4);
                nodeSym no;
                no = findVarContext(tree->tree.kids[0]->id.name);
                if(no.location == DEFINITION)
                    fprintf(yyout, save_var, no.name);
                else
                    fprintf(yyout, save_x, 4*no.my_stack_position);
                //fprintf(yyout, save_var, tree->tree.kids[0]->id.name);
                //fprintf(yyout, "[%s] ", tree->tree.kids[0]->id.name);
                //fprintf(yyout, "]");
                //TODO IMPORTANTE
                //antes estava assim: gera o lado esquerdo do assign e depois a exp a ser salva
                //  fprintf(yyout, "[%s] ", tree->tree.kids[0]->id.name);
                //  createNAryASTree(tree->tree.kids[1]);
                //  fprintf(yyout, "]");
                //e passou a ser: gera a exp a ser salva e depois gera o lado esquerdo do assign
                //  createNAryASTree(tree->tree.kids[1]);
                //  fprintf(yyout, "[%s] ", tree->tree.kids[0]->id.name);
                //  fprintf(yyout, "]");
                //ver se o caso das chamadas de função dentro dos argumentos não resolve de forma semelhante
                break;
         case LBACK:
                createNAryASTree(tree->tree.kids[0]);
                 if(tree->tree.kids[1] != NULL)
                    createNAryASTree(tree->tree.kids[1]);
                break;
         case LLABELBREAK:
                //fprintf(yyout, " [break]");
                //printf("fiz um break\n");
                fprintf(yyout, codegen_break, last_while);
                break;
         case LSTMTELSE:
                createNAryASTree(tree->tree.kids[0]);
                break;
         case LLABELCONTINUE:
                //fprintf(yyout," [continue]");
                break;


         case LSTATEMENTFUNCCALL:
                //fprintf(yyout," [funccall ");
                createNAryASTree(tree->tree.kids[0]);
                //fprintf(yyout,"]");
                //TODO tentar melhorar a chamada/definicao usada aqui, está mt verboso
                break;

        case LLABELFUNCCALL:
            caseExpression(tree, "funccall",0, 1);
            break;

        case LFUNCCALL:
            if(tree->tree.kids[1] != NULL) {
                fprintf(yyout, codegen_funccall);
                //fprintf(yyout,"[%s]", tree->tree.kids[0]->id.name);
                //TODO deal with this arglist
                createNAryASTree(tree->tree.kids[1]);
                fprintf(yyout, codegen_funccall_sufix, tree->tree.kids[0]->id.name);
            }else {
                fprintf(yyout, codegen_funccall);
                fprintf(yyout, codegen_funccall_sufix, tree->tree.kids[0]->id.name);
                //fprintf(yyout,"[%s] ", tree->tree.kids[0]->id.name);
                //fprintf(yyout,"[arglist]");
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
            fprintf(yyout, push_a0); //TODO conferir com tacio se está certo
            /*
            if (tree->tree.kids[0]->tipo == ID)
                //printf("debug [%s]\n", tree->tree.kids[0]->id.name);
            if (tree->tree.kids[0]->tipo == INT)
                //printf("debug [%d]\n", tree->tree.kids[0]->integer.integer);
            if (tree->tree.kids[0]->tipo == AST)
                //printf("debug ast\n");
            */

            //quando chega no LFUNCNNARGLIST é pq tem pelomenos um argumento, aí so empilha o primeiro, se tiver mais
            //a recussão da conta por si só
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
%type <ASTp> globaldecvar
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
%type <ASTp> globalloopatrib
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

programa    :inicio                                                     {
                                                                        //printf("debug [program])\n ");
                                                                            declareVars();
                                                                            //essaEhMinhaTabela();
                                                                            //printf("consegui declarar\n");
                                                                            //fclose(yyout);
                                                                            fprintf(yyout, mips_head);
                                                                            fprintf(yyout, deff_print);
                                                                            createNAryASTree($1);
                                                                            COUNTER++;
                                                                        }
            ;
inicio      : globaldecvar inicio                                             {
                                                                        //printf("debug 2 (Decvar)\n ");
                                                                            $$ = allocTreeNode(LSTMT,2,$1,$2);
                                                                            COUNTER++;
                                                                        }
            | decfunc inicio                                            {
                                                                        //printf("debug 3- [decfunc]\n ");
                                                                           $$ = allocTreeNode(LSTMT, 2, $1, $2);
                                                                           COUNTER++;
                                                                        }
            |                                                           {$$ = NULL;}
            ;
globaldecvar : LET IDENTIFIER globalloopatrib ENDEXPRESSION        {
                                                                        //printf("debug 4 (let ) \n");
                                                                          $$ = allocTreeNode(GLOBLTIPAGEM, 2, allocID($2, DEFINITION, NONPURP), $3);
                                                                          COUNTER++;
                                                                        }
            ;
globalloopatrib : ASSIGN exp                                                {
                                                                        //printf("debug 4 (let x = ) \n");
                                                                            $$ = allocTreeNode(GLOBLENDEXPRESSION, 1, $2);
                                                                            COUNTER++;
                                                                        }
            |                                                           {
                                                                        //printf("debug 4 (let x;)\n");
                                                                        $$ = NULL;
                                                                        }
            ;
decvar      : LET IDENTIFIER loopatrib ENDEXPRESSION                    {
                                                                        //printf("debug 4 (let ) \n");
                                                                          $$ = allocTreeNode(LTIPAGEM, 2, allocID($2, DEFINITION, NONPURP), $3);
                                                                          COUNTER++;
                                                                        }
            ;
loopatrib   : ASSIGN exp                                                {
                                                                        //printf("debug 4 (let x = ) \n");
                                                                            $$ = allocTreeNode(LENDEXPRESSION, 1, $2);
                                                                            COUNTER++;
                                                                        }
            |                                                           {
                                                                        //printf("debug 4 (let x;)\n");
                                                                        $$ = NULL;
                                                                        }
            ;
decfunc     : DEF PRINTAOLA OPENPAR paramlist CLOSEPAR bloco            {
                                                                          yyerror("print");
                                                                        }
            | DEF IDENTIFIER OPENPAR paramlist CLOSEPAR bloco           {
                                                                        //printf("debug 6-(decfunc (%s)) \n", $2);
                                                                        args_total = args;
                                                                        args=0;
                                                                        $$ = allocTreeNode(LDEF,3, allocID($2, NONDEF, NONPURP), $4, $6);

                                                                        if(strcmp("main", $2) == 0){
                                                                            MAIN++;
                                                                        }

                                                                        COUNTER++;
                                                                        }
            ;
paramlist   :
             IDENTIFIER looparams                                       {
                                                                        //printf("debug 8-(paramlist loop)\n");
                                                                        args++;
                                                                        $$ = allocTreeNode(LPARAM, 2, allocID($1, STACK, NONPURP), $2);
                                                                        COUNTER++;
                                                                        }
            |                                                           {
                                                                        //printf("debug 8-(no paramlist)\n");
                                                                        $$ = NULL;
                                                                        }
            ;
looparams   : SEPARADOR IDENTIFIER looparams                            {
                                                                        //printf("debug 9-(,ID looparams) \n");
                                                                        args++;
                                                                        $$ = allocTreeNode(LCOMPPARAM, 2, allocID($2, STACK, NONPURP), $3);
                                                                        COUNTER++;
                                                                        }
            |                                                           {$$ = NULL ;}
            ;
bloco       :OPENBLOCK loopdecvar loopstmts CLOSEBLOCK                  {
                                                                        //printf("debug 10- [bloco] \n");
                                                                        $$ = allocTreeNode(LBLOCK, 3, $2, $3);
                                                                        COUNTER++;
                                                                        }
            ;
loopdecvar  : decvar loopdecvar                                         {
                                                                        //printf("debug 11- (loopdecvar) \n");
                                                                        $$ = allocTreeNode(LDECVAR, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            |                                                           {$$ = NULL ;}
            ;
loopstmts   : stmt loopstmts                                            {
                                                                        //printf("debug 12- (loop stmts)\n ");
                                                                        $$ = allocTreeNode(LBACK, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            |                                                           {$$ = NULL ;}

stmt        : funccall ENDEXPRESSION                                    {
                                                                        //printf("debug 220- (funccall ;) \n");
                                                                        $$ = allocTreeNode(LSTATEMENTFUNCCALL, 1, $1);
                                                                        COUNTER++;
                                                                        }
            | assign ENDEXPRESSION                                      {
                                                                        $$ = allocTreeNode(LASSIGNSTMT, 1, $1);
                                                                        //printf("debug 220- (assign ;) \n");
                                                                        COUNTER++;
                                                                        }

            | IF OPENPAR exp CLOSEPAR bloco                             {
                                                                        //printf("debug 15- if(exp){} \n");
                                                                        if_stmt_num++;
                                                                        $$ = allocTreeNode(LSTMTIF, 2, $3, $5);
                                                                        COUNTER++;
                                                                        }
            | IF OPENPAR exp CLOSEPAR bloco ELSE bloco                  {
                                                                        //printf("debug 15- if(exp)else{} \n");
                                                                        if_stmt_num++;
                                                                        $$ = allocTreeNode(LSTMTIF, 3, $3, $5, $7);
                                                                        COUNTER++;
                                                                        }
            | IF OPENPAR exp CLOSEPAR ELSE bloco                        {
                                                                        //printf("debug 15- if(exp)else{} \n");
                                                                        if_stmt_num++;
                                                                        $$ = allocTreeNode(LSTMTIF, 3, $3, $5, $6);
                                                                        COUNTER++;
                                                                        }

            | WHILE OPENPAR exp CLOSEPAR bloco                          {
                                                                        //printf("debug 16- while(exp){} \n");
                                                                        while_stmt_num++;
                                                                        $$ = allocTreeNode(LWHILE, 2, $3, $5);
                                                                        COUNTER++;
                                                                        }
            | RETURN loopexp ENDEXPRESSION                              {
                                                                        //printf("debug 17- return loopexp; \n");
                                                                        $$ = allocTreeNode(LLABELRETURN, 1, $2);
                                                                        COUNTER++;
                                                                        }
            | BREAK ENDEXPRESSION                                       {
                                                                        //printf("debug 20 -break; \n");
                                                                        $$ = allocTreeNode(LLABELBREAK, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            | CONTINUE ENDEXPRESSION                                    {
                                                                        //printf("debug 20 -continue; \n");
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
                                                                        //printf("debug 23 x=exp \n");
                                                                        //$$ = allocTreeNode(LASSIGNSTMT, 1, $1);
                                                                        $$ = allocTreeNode(LCOMPASSIGN, 2, allocID($1, NONDEF, STORAGEUSE), $3);
                                                                        COUNTER++;
                                                                        }
            ;
funccall    : IDENTIFIER OPENPAR arglist CLOSEPAR                       {
                                                                        //printf("debug 24- %s() \n", $1);
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, allocID($1, NONDEF, NONPURP), $3);
                                                                        COUNTER++;
                                                                        }
            | PRINTAOLA OPENPAR arglist CLOSEPAR                        {
                                                                        //printf("debug 24- id() \n");
                                                                        $$ = allocTreeNode(LFUNCCALL, 2, allocID($1, NONDEF, NONPURP), $3);
                                                                        COUNTER++;
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
                                                                        //printf("debug 26 - [] \n");
                                                                        $$ = allocTreeNode(LFUNCNNARGLIST, 2, $1, $2);
                                                                        COUNTER++;
                                                                        }
            ;
loopargs2    : SEPARADOR exp loopargs2                                  {
                                                                         //printf("27 - (, [%d]) \n", $2);
                                                                         $$ = allocTreeNode(LFUNCNNARGLIST, 2, $2, $3);
                                                                         COUNTER++;
                                                                        }
            |                                                           {$$=NULL;}
            ;
exp         : exp PLUS exp                                              {
                                                                        //printf("debug 28 - exp + exp \n");
                                                                        $$ = allocTreeNode(LPLUS, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp MINUS exp                                             {
                                                                        //printf("debug 29 - exp - exp \n");
                                                                        $$ = allocTreeNode(LMINUS, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp MULT exp                                              {
                                                                        //printf("debug 30 - exp * exp \n");
                                                                        $$ = allocTreeNode(LMULT, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp DIV exp                                               {
                                                                        //printf("debug 31 - exp / exp \n");
                                                                        $$ = allocTreeNode(LDIV, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp LESS exp                                              {
                                                                        //printf("debug 32 - exp < exp \n");
                                                                        $$ = allocTreeNode(LLESS, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp LESSEQUAL exp                                         {
                                                                        //printf("debug 33 - exp <= exp \n");
                                                                        $$ = allocTreeNode(LLESSEQUAL, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp GREAT exp                                             {
                                                                        //printf("debug 34 - exp > exp \n");
                                                                        $$ = allocTreeNode(LGREAT, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp GREATEQUAL exp                                        {
                                                                        //printf("debug 35 - exp >= exp \n");
                                                                        $$ = allocTreeNode(LGREATEQUAL, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp EQUAL exp                                             {
                                                                        //printf("debug 36 - exp = exp \n");
                                                                        $$ = allocTreeNode(LEQUAL, 2, $1, $3);
                                                                        COUNTER++;
                                                                        }
            | exp DIFF exp                                              {
                                                                        //printf("debug 37 - exp != exp \n");
                                                                        $$ = allocTreeNode(LDIFF, 2, $1, $3);COUNTER++;
                                                                        }
            | exp AND exp                                               {
                                                                        //printf("debug 38 - exp && exp \n");
                                                                        $$ = allocTreeNode(LAND, 2, $1, $3);COUNTER++;
                                                                        }
            | exp OR exp                                                {
                                                                        //printf("debug 39 - exp || exp \n");
                                                                        $$ = allocTreeNode(LOR, 2, $1, $3);COUNTER++;
                                                                        }
            | MINUS exp %prec UMINUS                                    {
                                                                        //printf("debug 40 - exp \n");
                                                                        $$ = allocTreeNode(LUMINUS, 1, $2);COUNTER++;
                                                                        }
            | NOT exp                                                   {
                                                                        //printf("debug 41 - !exp \n");
                                                                        $$ = allocTreeNode(LNOT, 1, $2);COUNTER++;
                                                                        }
            | OPENPAR exp CLOSEPAR                                      {
                                                                        //printf("debug 42 - (exp) \n");
                                                                        $$ = allocTreeNode(LOPENPAR, 1, $2);COUNTER++;
                                                                        }
            | funccall                                                  {
                                                                        //printf("debug 43 - funccall\n");
                                                                        $$ = allocTreeNode(LLABELFUNCCALL, 2, $1);
                                                                        COUNTER++;
                                                                        }
            | DEC                                                       {
                                                                        //printf("debug 44 dec\n ");
                                                                        $$ = allocINT($1);
                                                                        COUNTER++;
                                                                        }
            | IDENTIFIER                                                {
                                                                        //printf("debug 45 id\n ");
                                                                        $$ = allocID($1, NONDEF, LOADUSE);
                                                                        COUNTER++;
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
    outrofile = fopen("secundario", "w");

    yyin = input;
    yyout = output;

    fprintf(yyout, mips_datas);

    yyparse();

    fclose(outrofile);
    fprintf(yyout, call_main1);

    if(globalexp){
        outrofile = fopen("secundario", "r");
        fseek(outrofile, 0, SEEK_END);
        long input_file_size = ftell(outrofile);
        rewind(outrofile);
        char *file_contents;
        file_contents = malloc(input_file_size * (sizeof(char)));
        fread(file_contents, sizeof(char), input_file_size, outrofile);
        fclose(outrofile);
        fprintf(yyout, file_contents);
    }

    fprintf(yyout, call_main2);

    fclose(input);
    fclose(output);

    //If errors, clear file
    if(ERRORS != 0 || COUNTER==1 || (MAIN==0 || MAIN>1)){
        FILE *output = fopen(argv[2], "w");
        fclose(output);
    }
    return 0;
}
