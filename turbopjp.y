// BISON PARSER
%{
    
    #define YYDEBUG 1
    #define MAX_CHILDREN 10 // Maximum number of children for any node

    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    #include "ast.c"

    typedef struct ASTNode ASTNode; // Forward declaration


    void yyerror(char*);
    ASTNode* programNode;
    ASTNode* newLeaf;
    int childCount = 0;
%}

%union {

    int ival;
    char *sval;
    struct ASTNode* ast;
}

%token T_PROGRAM T_LPAREN T_RPAREN T_COMMA T_SEMICOLON T_COLON T_DOT T_VAR T_BEGIN T_END T_ASSIGN T_MUL T_ADD T_GT T_INT T_SUB T_DIV
%token <ival> T_CHAR T_NUMBER
%token <sval> T_ID
%type <sval> untyped_id_list
%type <ast> program id_list statement expression term factor block statement_list


%left T_ADD T_SUB
%left T_MUL T_DIV


// grammar rules
%%

program:
    T_PROGRAM T_ID 
    {
        printf("Found program: %s\n", $2);

        // set the identifier of the program 
        programNode->nodeType = NODE_PROGRAM;
        programNode->identifier = strdup($2);
    }
    T_LPAREN untyped_id_list T_RPAREN T_SEMICOLON
    declaration block
    T_DOT
    { 
        printf("Parsed successfuly...\n");
    }
    ;

block:
    T_BEGIN statement_list T_END {
        /* Create a new AST node for the block */
        // ASTNode* blockNode = new_ast_node(NODE_BEGIN);
        // blockNode->children[0] = $2; // The list of statements in the block
        // blockNode->children_count = 1;
        // $$ = blockNode; // The result of this rule is the created block node
    }
;

statement_list:
    statement_list statement { 
        // /* Add the new statement to the existing list */
        // ASTNode* listNode = $1;
        // listNode->children[listNode->children_count++] = $2;
        // $$ = listNode;
    }
  | statement { 
        /* The first statement in the list */
        // ASTNode* listNode = new_ast_node(NONE_NODE);
        // listNode->children[0] = $1;
        // listNode->children_count = 1;
        // $$ = listNode;
    }
;

declaration:
    /* Match a list of IDs followed by ':', then 'integer', then a semicolon */
    T_VAR id_list T_COLON T_INT T_SEMICOLON { 
        printf("*** PARSER *** Found declaration of integer variables\n");
        
        // walk newLeaf node and change the type of all children to INT
        printf("Setting type of all children to INT\n");
        setASTType(newLeaf, NODE_INTEGER);
        add_child(programNode, newLeaf); // add the newLeaf to the programNode

    }
    | T_VAR id_list T_COLON T_CHAR T_SEMICOLON {
        // this is a declaration of char variables
    }
    | /* empty */
;

id_list:
    /* Match a single ID */
    T_ID { 
        /* Create a new node with the ID as the identifier */
        printf("*** PARSER *** Found identifier: %s\n", $1);
        newLeaf = new_ast_node(NODE_DECLARATION);
        newLeaf->nodeType = NODE_DECLARATION;
        ASTNode* tempNode = new_ast_node(NODE_VAR);
        tempNode->identifier = strdup($1);
        /* Add the new node to the list of identifiers */
        add_child(newLeaf, tempNode);
    }
    /* Match a comma followed by another ID */
  | id_list T_COMMA T_ID { 
        printf("*** PARSER *** Found identifier (2): %s\n", $3);
        ASTNode* tempNode = new_ast_node(NODE_VAR);
        tempNode->identifier = strdup($3);
        add_child(newLeaf, tempNode);

        /* Add the new identifier to the existing list */
    }
;

/* Bison rule for an assignment statement */
statement:
    /* Match an ID, followed by ':=', then an expression, then a semicolon */
    T_ID T_ASSIGN expression  {
        /* Create a new AST node for the assignment statement */
        ASTNode* assignmentNode = new_ast_node(NODE_ASSIGNMENT);
        assignmentNode->identifier = strdup($1);

        /* Allocate space for the children array */
        assignmentNode->children = malloc(sizeof(ASTNode*) * MAX_CHILDREN);
        /* Make sure the allocation succeeded */
        if (assignmentNode->children == NULL) {
            fprintf(stderr, "Failed to allocate memory for children array\n");
            YYABORT;
        }
        
        assignmentNode->children[0] = $3; // Right-hand side of the assignment
        assignmentNode->children_count = 1;

        /* Link this assignment to the main program node */
        programNode->children[programNode->children_count++] = assignmentNode;
        printf("*** PARSER *** Found assignment statement: %s := <expression>\n", $1);
        $$ = assignmentNode; // The result of this rule is the created assignment node
    }
;

expression:
    /* Lowest precedence: addition and subtraction */
    expression T_ADD term { 
        // create a new node
        printf("\n*** PARSER *** Found addition expression\n");
        printf("L E F T:\n");
        print_ast_new($1, 0);
        printf("R I G H T:\n");
        print_ast_new($3, 0);
        ASTNode* addNode = create_binary_operation_node(ADD_OPERATOR, $1, $3);
        printf("N E W:\n");
        
        //print_ast_new(addNode, 0);
        $$ = addNode;

     }
  | expression T_SUB term { 
    $$ = create_binary_operation_node(SUB_OPERATOR, $1, $3); 
    }
  | expression T_GT term {
        printf("\n*** PARSER *** Found greater than expression\n");
     ASTNode* gtNode = create_binary_operation_node(GREATER_OPERATOR, $1, $3);
     $$ = gtNode;
     printf("\nL E F T:\n");
        //print_ast_new($1, 0);
    
        printf("\nR I G H T:\n");
        //print_ast_new($3, 0);

     printf("\nN E W:\n");
     //print_ast_new(gtNode, 0);

     }
  | term { $$ = $1; }
;

term:
    /* Higher precedence: multiplication and division */
    term T_MUL factor { $$ = create_binary_operation_node(MUL_OPERATOR, $1, $3); }
  | term T_DIV factor { $$ = create_binary_operation_node(DIV_OPERATOR, $1, $3); }
  | factor { $$ = $1; }
;

factor:
    /* Highest precedence: parentheses and identifiers */
    T_LPAREN expression T_RPAREN { $$ = $2; }  /* Parentheses */
  | T_ID { 
        printf("\n*** PARSER *** Found identifier: %s\n", $1);
        ASTNode* tempNode = new_ast_node(NODE_IDENTIFIER);
        tempNode->identifier = strdup($1);
        $$ = tempNode;
   }  /* Identifier */
  | T_NUMBER { 
        printf("\n*** PARSER *** Found number: %d\n", $1);
        ASTNode* tempNode = new_ast_node(NODE_CONST);
        tempNode->value.intValue = $1;
        $$ = tempNode;
   }  /* Number */
;

untyped_id_list:
    T_ID
    | untyped_id_list T_COMMA T_ID
    ;


/* slozeny_prikaz:						TOKEN_BEGIN volitelne_prikazy TOKEN_END
									;

volitelne_prikazy:					seznam_prikazu
									|  
									;

seznam_prikazu: 					prikaz
									| seznam_prikazu ';' prikaz
									;

prikaz:								promenna TOKEN_PRIRAZOVACI_OPERATOR vyraz 			{
																						printf("%s = %s\n", $1, $3); 
																						t=0; 
																					}
									| slozeny_prikaz
									| TOKEN_IF  vyraz  TOKEN_THEN prikaz else_cast 
									| TOKEN_WHILE  vyraz  TOKEN_DO prikaz 
									; */


%%

int main(int argc, char **argv) {
    yydebug = 0;

    programNode = new_ast_node(NODE_PROGRAM);
//    ASTNode* tempNode;
    yyparse();

    // print the AST
    //print_ast_new(programNode, 0);
    printf("\n\n");
    print_ast(programNode, 0);
    printf("\n\n");
    printf("TAC:\n");
    traverse_and_generate_TAC(programNode);
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

