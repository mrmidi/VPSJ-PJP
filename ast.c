#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* create_program_node(const char* programName, Node* varList, Node* assignStmt, const char* endId) {
    // Function implementation
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = programName;
    node->child1 = create_leaf_node()

}

Node* create_var_list_node(const char* id, Node* varList) {
    // Function implementation
}

Node* create_assign_node(const char* id, Node* expr) {
    // Function implementation
}

Node* create_expr_node(const char* id, Node* expr, int number) {
    // Function implementation
}

Node* create_leaf_node(const char* name, const char* value) {
    // Function implementation
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = name;
    node->value = value;
    node->child1 = NULL;
    node->child2 = NULL;
    node->child3 = NULL;
    node->child4 = NULL;
}

Node* create_leaf_node_number(const char* name, int value) {
    // Function implementation
}
