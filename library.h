/*################ AST DEFINITIONS #####################*/
#define BUFFERMAX 2000
#define MAXCHAR 500

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