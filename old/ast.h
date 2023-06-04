#ifndef AST_H
#define AST_H

typedef struct Node {
    char* name;
    struct Node* child1;
    struct Node* child2;
    struct Node* child3;
    struct Node* child4;
    char* value; // For leaf nodes like identifiers
    int number; // For leaf nodes like numbers
} Node;

Node* create_program_node(const char* programName, Node* varList, Node* assignStmt, const char* endId);
Node* create_var_list_node(const char* id, Node* varList);
Node* create_assign_node(const char* id, Node* expr);
Node* create_expr_node(const char* id, Node* expr, int number);
Node* create_leaf_node(const char* name, const char* value);
Node* create_leaf_node_number(const char* name, int value);

#endif  // AST_H
