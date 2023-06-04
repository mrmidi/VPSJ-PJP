#ifndef AST_H
#define AST_H

typedef enum {
    NODE_CONST,
    NODE_IDENTIFIER,
    NODE_PROGRAM,
    NODE_VAR,
    NODE_INTEGER,
    NODE_CHARACTER,
    NODE_BEGIN,
    NODE_END,
    NODE_IF,
    NODE_THEN,
    NODE_ELSE,
    NODE_WHILE,
    NODE_DO,
    NODE_ASSIGNMENT,
    NODE_DECLARATION,
    NODE_UNARY,
    NODE_BINARY,
    NONE_NODE
} NodeType;

typedef enum {
    ADD_OPERATOR,
    SUB_OPERATOR,
    MUL_OPERATOR,
    DIV_OPERATOR,
    MOD_OPERATOR,
    NEBO_OPERATOR,
    AND_OPERATOR,
    NOT_OPERATOR,
    EQUAL_OPERATOR,
    GREATER_OPERATOR,
    LESS_OPERATOR,
    GREATER_EQUAL_OPERATOR,
    LESS_EQUAL_OPERATOR,
    OR_OPERATOR,
    NONE_OPERATOR
} BinaryOperator;

typedef enum {
    NEG_OPERATOR,
    POS_OPERATOR,
    NONE_UNARY_OPERATOR
} UnaryOperator;

typedef enum {
    INT,
    CHAR,
    NONE
} Type;

typedef struct Token {
    char* lexeme;
} Token;

typedef struct ASTNode {
    // token token;                        /* The token, if this is a leaf node */
    Token* token;
    NodeType nodeType;                  /* The type of the node */
    BinaryOperator operator;            /* The operator, if this is an operator node */
    // Type type;                          /* The type of the expression, if this is an expression node */
    char* identifier;                   /* The identifier, if this is a declaration or reference node */
    struct ASTNode* left;               /* The left child, if any */
    struct ASTNode* right;              /* The right child, if any */
    struct ASTNode** children;          /* The children, if this is a program, declaration or compound statement node */
    int children_count;                 /* The count of children nodes */
    union {                             /* The value, if this is a constant node */
        int intValue;
        char charValue;
    } value;
} ASTNode;

void print_ast(ASTNode* node, int depth);
ASTNode* new_ast_node(NodeType type);

#endif  // AST_H
