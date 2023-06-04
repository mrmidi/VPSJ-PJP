#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ASTNode* new_ast_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodeType = type;
    node->operator = NONE_OPERATOR;
    node->type = NONE;
    node->identifier = NULL;
    node->left = NULL;
    node->right = NULL;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

void print_ast(ASTNode* node, int depth) {
    /* Print indentation */
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    /* Print node type */
    switch (node->type) {
        case PROGRAM: printf("PROGRAM\n"); break;
        case VAR: printf("VAR\n"); break;
        case INTEGER: printf("INTEGER: %d\n", node->value); break;   // Print the value
        case BEGIN: printf("BEGIN\n"); break;
        case END: printf("END\n"); break;
        case ASSIGNMENT: printf("ASSIGNMENT\n"); break;
        case BINARY: 
            switch (node->operator) {
                case ADD_OPERATOR: printf("ADD\n"); break;
                case SUB_OPERATOR: printf("SUB\n"); break;
                case MUL_OPERATOR: printf("MUL\n"); break;
                case DIV_OPERATOR: printf("DIV\n"); break;
                // Add more as needed...
                default: break;
            }
            break;
        // Add more cases as needed...
        case NONE_NODE: 
            printf("IDENTIFIER: %s\n", node->identifier);
            break;
    }

    /* Recursively print children */
    for (int i = 0; i < node->children_count; i++) {
        print_ast(node->children[i], depth + 1);
    }
}


int main() {
    // Create declaration nodes for two integers
  /* Create the root node for the program */
ASTNode* programNode = new_ast_node(PROGRAM);
programNode->identifier = "PJP1";

/* Create the node for the variable declaration block */
ASTNode* varNode = new_ast_node(VAR);

/* Create the individual variable declaration nodes */
ASTNode* varVNode = new_ast_node(DECLARATION);
varVNode->identifier = "V";
varVNode->type = INT;

ASTNode* varSNode = new_ast_node(DECLARATION);
varSNode->identifier = "S";
varSNode->type = INT;

ASTNode* varPNode = new_ast_node(DECLARATION);
varPNode->identifier = "P";
varPNode->type = INT;

ASTNode* varJNode = new_ast_node(DECLARATION);
varJNode->identifier = "J";
varJNode->type = INT;

/* Attach the variable declaration nodes to the variable declaration block */
varNode->children_count = 4;
varNode->children = (ASTNode**)malloc(sizeof(ASTNode*) * varNode->children_count);
varNode->children[0] = varVNode;
varNode->children[1] = varSNode;
varNode->children[2] = varPNode;
varNode->children[3] = varJNode;

/* Attach the variable declaration block to the program node */
programNode->children_count = 1;
programNode->children = (ASTNode**)malloc(sizeof(ASTNode*) * programNode->children_count);
programNode->children[0] = varNode;

/* Create the nodes for the arithmetic expression */
ASTNode* mulNode = new_ast_node(BINARY);
mulNode->operator = MUL_OPERATOR;
mulNode->left = new_ast_node(NONE_NODE);   // Represents "P"
mulNode->left->identifier = "P";
mulNode->right = new_ast_node(NONE_NODE);  // Represents "J"
mulNode->right->identifier = "J";

ASTNode* addNode = new_ast_node(BINARY);
addNode->operator = ADD_OPERATOR;
addNode->left = mulNode;
addNode->right = new_ast_node(NONE_NODE);  // Represents "2022"
addNode->right->identifier = "2022";

ASTNode* greaterThanNode = new_ast_node(BINARY);
greaterThanNode->operator = GREATER_OPERATOR;
greaterThanNode->left = new_ast_node(NONE_NODE);  // Represents "S"
greaterThanNode->left->identifier = "S";
greaterThanNode->right = addNode;

/* Create the node for the assignment */
ASTNode* assignmentNode = new_ast_node(ASSIGNMENT);
assignmentNode->left = new_ast_node(NONE_NODE);  // Represents "V"
assignmentNode->left->identifier = "V";
assignmentNode->right = greaterThanNode;

/* Create the node for the begin-end block */
ASTNode* beginNode = new_ast_node(BEGIN);

/* Attach the assignment node to the begin-end block */
beginNode->children_count = 1;
beginNode->children = (ASTNode**)malloc(sizeof(ASTNode*) * beginNode->children_count);
beginNode->children[0] = assignmentNode;

/* Attach the begin-end block to the program node */
programNode->children_count = 2;
programNode->children = realloc(programNode->children, sizeof(ASTNode*) * programNode->children_count);
programNode->children[1] = beginNode;

print_ast(programNode, 0);

return 0;
}
