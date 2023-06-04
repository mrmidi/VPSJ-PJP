#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* create_program_node(const char* programName, Node* varList, Node* assignStmt, const char* endId) {
    // Function implementation
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = programName;
    node->child1 = create_leaf_node("ProgramName", programName);
    node->child2 = varList;
    node->child3 = assignStmt;
    node->child4 = create_leaf_node("EndId", endId);
    return node;
}

Node* create_var_list_node(const char* id, Node* varList) {
    // Function implementation
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = id;
    node->child1 = create_leaf_node("Id", id);
    node->child2 = varList;
    node->child3 = NULL;
    node->child4 = NULL;
    return node;
}

Node* create_assign_node(const char* id, Node* expr) {
    // Function implementation
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = id;
    node->child1 = create_leaf_node("Id", id);
    node->child2 = expr;
    node->child3 = NULL;
    node->child4 = NULL;
    return node;
}

Node* create_expr_node(const char* id, Node* expr, int number) {
    // Function implementation
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = id;
    node->child1 = create_leaf_node("Id", id);
    node->child2 = expr;
    node->child3 = create_leaf_node_number("Number", number);
    node->child4 = NULL;
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
        Node* leafNode = (Node*)malloc(sizeof(Node));
    leafNode->name = name;
    leafNode->child1 = NULL;
    leafNode->child2 = NULL;
    leafNode->child3 = NULL;
    leafNode->child4 = NULL;
    leafNode->number = value;
    return leafNode;
}
