// define types of AST nodes

typedef enum {
    PROGRAM,
    FUNCTION,
    BLOCK,
    DECLARATION,
    ASSIGNMENT,
    IF,
    WHILE,
    RETURN,
    CALL,
    BINARY,
    UNARY,
    IDENTIFIER,
    INTEGER,
    FLOAT,
    STRING,
    TYPE,
    ARGUMENTS,
    ARGUMENT,
    NONE
} NodeType;

typedef enum {
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    MODULO,
    AND,
    OR,
    EQ,
    NEQ,
    LT,
    GT,
    LEQ,
    GEQ,
    NOT,
    NEG,
    NONE
} BinaryOperator;

typedef enum {
    INT,
    FLOAT,
    STRING,
    BOOL,
    VOID,
    NONE
} Type;

typedef struct _Node {
    NodeType type;
    union {
        struct {
            struct _Node *declarations;
            struct _Node *functions;
        } program;
        struct {
            Type type;
            char *name;
            struct _Node *arguments;
            struct _Node *body;
        } function;
        struct {
            struct _Node *declarations;
            struct _Node *statements;
        } block;
        struct {
            Type type;
            char *name;
        } declaration;
        struct {
            char *name;
            struct _Node *value;
        } assignment;
        struct {
            struct _Node *condition;
            struct _Node *if_body;
            struct _Node *else_body;
        } if_statement;
        struct {
            struct _Node *condition;
            struct _Node *body;
        } while_statement;
        struct {
            struct _Node *value;
        } return_statement;
        struct {
            char *name;
            struct _Node *arguments;
        } call;
        struct {
            BinaryOperator operator;
            struct _Node *left;
            struct _Node *right;
        } binary;
        struct {
            BinaryOperator operator;
            struct _Node *operand;
        } unary;
        struct {
            char *name;
        } identifier;
        struct {
            int value;
        } integer;
        struct {
            float value;
        } float_number;
        struct {
            char *value;
        } string;
        struct {
            Type type;
        } type;
        struct {
            struct _Node *arguments;
        } arguments;
        struct {
            struct _Node *argument;
            struct _Node *arguments;
        } argument;
    };
} Node;