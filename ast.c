#include "ast.h"

// define NULL as nullptr if not already defined
#ifndef NULL

#define NULL nullptr

#endif

    char* t = 0;

ASTNode* new_ast_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->nodeType = type;
    node->operator = NONE_OPERATOR;
    node->identifier = NULL;
    node->left = NULL;
    node->right = NULL;
    node->children = NULL;
    node->children_count = 0;
    return node;
}

// create a leaf node

ASTNode* new_ast_leaf_node(NodeType type, int value) {
    ASTNode* node = new_ast_node(type);
    node->value.intValue = value;
    return node;
}

void add_child(ASTNode* parent, ASTNode* child) {
    parent->children_count++;
    parent->children = (ASTNode**)realloc(parent->children, parent->children_count * sizeof(ASTNode*));
    parent->children[parent->children_count - 1] = child;
}


void setType(ASTNode* node, Type type) {
    printf("New type: %d\n", type);
    node->nodeType = type;
}

void setASTType(ASTNode* node, Type type) {
    // walk the tree and set the type of all the nodes
    if (node == NULL) {
        return;
    }
    node->nodeType = type;
    
    for (int i = 0; i < node->children_count; i++) {
        printf("Setting type of child %d\n", i);
        printf("Old type of child %d: %d\n", i, node->children[i]->nodeType);
        node->children[i]->nodeType = type;
        printf("New type of child %d: %d\n", i, node->children[i]->nodeType);
        setASTType(node->children[i], type);
    }
}


ASTNode* create_binary_operation_node(BinaryOperator op, ASTNode* left, ASTNode* right) {
    ASTNode* node = new_ast_node(NODE_BINARY);
    node->operator = op;
    node->left = left;
    node->right = right;
    // printf("Created binary node\n");
    
    // if (node->left != NULL) {
    //     printf("Left: %s\n", node->left->identifier);
    // } else {
    //     printf("Left: NULL\n");
    // }

    // if (node->right != NULL) {
    //     printf("Right: %s\n", node->right->identifier);
    // } else {
    //     printf("Right: NULL\n");
    // }

    return node;
}

ASTNode* create_assiegment_node(ASTNode* left, ASTNode* right) {
    ASTNode* node = new_ast_node(NODE_ASSIGNMENT);
    node->left = left;
    node->right = right;
    return node;
}



// ASTNode* create_unary_operation_node(UnaryOperator op, ASTNode* child) {
//     ASTNode* node = new_ast_node(UNARY);
//     node->operator = op;
//     node->left = child;
//     return node;
// }
void create_assignment_node(ASTNode* node, ASTNode* left, ASTNode* right) {
    node->nodeType = NODE_ASSIGNMENT;
    node->left = left;
    node->right = right;
}

void print_ast_new(ASTNode* node, int depth) {
    /* Print indentation */
    char* spaces = (char*)malloc(sizeof(char) * (depth * 2 + 1));
    for (int i = 0; i < depth; i++) {
        printf("  ");
        spaces[i * 2] = ' ';
    }
    switch (node->nodeType) {
        case NODE_PROGRAM: printf("Node type: PROGRAM\n");
                      printf("TOKEN: %s\n", node->identifier);
        break;
        case NODE_VAR: printf("Node type: VAR\n"); break;
        case NODE_DECLARATION: printf("Node type: DECLARATION\n"); break;
        case NODE_INTEGER: printf("Node type: INTEGER\n"); break;
        case NODE_BEGIN: printf("Node type: BEGIN\n"); break;
        case NODE_END: printf("Node type: END\n"); break;
        case NODE_ASSIGNMENT: printf("Node type: ASSIGNMENT\n"); break;
        case NODE_IDENTIFIER: printf("Node type: IDENTIFIER\n"); break;
        case NODE_BINARY: 
            printf("Node type: BINARY OPERATOR");
            switch (node->operator) {
                case ADD_OPERATOR: printf(" Node type: ADD\n"); 
                    print_binary(node);
                    break;
                case SUB_OPERATOR: printf("Node type: SUB\n"); break;
                case MUL_OPERATOR: printf("Node type: MUL\n"); break;
                case DIV_OPERATOR: printf("Node type: DIV\n"); break;
                // Add more as needed...
                default: break;
            }
            break;
        case NONE_NODE: 
            printf("Node type: IDENTIFIER\n");
            break;
        default: 
            printf("Node type: UNKNOWN (ID: %d)\n", node->nodeType);
            break;
    }
    /* Print children */
    for (int i = 0; i < node->children_count; i++) {
        print_ast_new(node->children[i], depth + 1);
    }
}

void print_binary(ASTNode* node) {
    printf("Printing binary node\n");
    if (node == NULL) {
        return;
    }
    printf("Node type: %d\n", node->nodeType);
    printf("Node operator: %d\n", node->operator);
    printf("Node left: %d\n", node->left->nodeType);
    printf("Node right: %d\n", node->right->nodeType);
    printf("Node left token: %d\n", node->left->identifier);
    printf("Node right token: %d\n", node->right->identifier);

    if (node->nodeType == NODE_BINARY) {
        // walk left and right childrens
        print_binary(node->left);
        print_binary(node->right);
    } else {
        printf("Node type: %d\n", node->nodeType);
    }
}


void print_ast(ASTNode* node, int level) {
    // Indentation for hierarchy visualization
    for(int i = 0; i < level; i++) {
        printf("  ");
    }

    // If the node is NULL, it's the end of a branch
    if(node == NULL) {
        printf("(null)\n");
        return;
    }

    // Print the node type and value/identifier
    printf("Node type: %d\n", node->nodeType);
    
    // If it's a constant node, print its value
    if(node->nodeType == NODE_CONST) {
        printf("Value: %d\n", node->value.intValue);
    }
    
    // If it's an identifier or declaration node, print its identifier
    if(node->nodeType == NODE_DECLARATION || node->nodeType == NODE_IDENTIFIER) {
        printf("Identifier: %s\n", node->identifier);
    }

    // Print its operator if it's an operator node
    if(node->nodeType == NODE_BINARY) {
        printf("Operator: %d\n", node->operator);

        // Print left and right children
        printf("Left: \n");
        print_ast(node->left, level + 1);
        printf("Right: \n");
        print_ast(node->right, level + 1);
    } else {
        // Recurse for each child
        for(int i = 0; i < node->children_count; i++) {
            print_ast(node->children[i], level + 1);
        }
    }
}

char* binary_operator_to_string(BinaryOperator op) {
    switch (op) {
        case ADD_OPERATOR: return "+";
        case SUB_OPERATOR: return "-";
        case MUL_OPERATOR: return "*";
        case DIV_OPERATOR: return "/";
        case MOD_OPERATOR: return "%";
        case AND_OPERATOR: return "&&";
        case OR_OPERATOR: return "||";
        case GREATER_OPERATOR: return ">";
        case LESS_OPERATOR: return "<";
        case GREATER_EQUAL_OPERATOR: return ">=";
        case LESS_EQUAL_OPERATOR: return "<=";
        case EQUAL_OPERATOR: return "==";
        default: return "";
    }
}

char* itoa(int i) {
    char* str = (char*)malloc(sizeof(char) * 16);
    sprintf(str, "%d", i);
    return str;
}

char* generate_TAC(ASTNode* node) {


    if (node == NULL) {
        return "";
    }

    switch (node->nodeType) {
        case NODE_PROGRAM: 
            printf("Node type: PROGRAM\n");
            printf("TOKEN: %s\n", node->identifier);
            break;
        case NODE_BINARY: {
            // traverse left and right children
            char *lhs = generate_TAC(node->left);
            char *rhs = generate_TAC(node->right);
            char tmp_var[16];
            sprintf(tmp_var, "T%d", t++);
            printf("%s = %s %s %s\n", tmp_var, lhs, binary_operator_to_string(node->operator), rhs);
            //char* tmp_var = "T" + to_string(t++); // generate a new temporary variable name

            return strdup(tmp_var);
        }
        case NODE_IDENTIFIER:
            return node->identifier;
        
        case NODE_CONST:
            return itoa(node->value.intValue);


        default:
            return "";


    }
}

void traverse_and_generate_TAC(ASTNode* root) {
    if (root == NULL) {
        return;
    }

    if (root->nodeType == NODE_ASSIGNMENT) {
        char* rhs = generate_TAC(root->children[0]);  // Assuming right-hand side of the assignment is the first child
        printf("%s = %s\n", root->identifier, rhs);
    }

    // if your tree has more than one statement/assignment, you might also need to iterate through the children
    for (int i = 0; i < root->children_count; i++) {
        traverse_and_generate_TAC(root->children[i]);
    }
}