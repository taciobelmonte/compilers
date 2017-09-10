
/*################ AST DEFINITIONS #####################*/
#define BUFFERMAX 2000
#define MAXCHAR 500

//Keys to pass info to createNode in the AST
typedef enum keyList{
    TIPAGEM,
    STMT,
    COMPPARAM,
    PARAM ,
    BLOCK,
    DECVAR,        
    ASSIGNSTMT,
    COMPASSIGN,
    EXP,
    LABELRETURN,
    LABELBREAK,
    LABELCONTINUE,
    STMTSTMT,
    LABELFUNCCALL,
    VOLTASTMT, 
    STMTIF,
    STMTELSE,
    STMTFUNCCALL,
    FUNCCALL,
    FUNCNARGLIST,
    FUNCNNARGLIST,
    FUNCARGLIST 
}keys;


typedef enum typesList {
    INT,
    ID,
    AST
}type;

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