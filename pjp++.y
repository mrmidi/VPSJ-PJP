%{
#include <stdio.h>
#include <stdlib.h>
#include "pjp++.h"
#include "ast.h"

extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;
void yyerror(const char *s);
%}

%union {
    int number;
    char *string;
    node *ast;
}

%token <string> T_PROGRAM T_VAR T_INT T_END T_ID
%token <number> T_NUMBER
%token T_SEMICOLON T_COLON T_LEFT_BRACKET T_RIGHT_BRACKET T_COMMA T_ASSIGN T_GREATER_THAN T_PLUS
%token <ast> expr assign_stmt program

%%

program:
    T_PROGRAM T_ID T_SEMICOLON 
    T_VAR var_list T_COLON T_INT T_SEMICOLON 
    T_BEGIN assign_stmt T_END T_ID T_SEMICOLON
    {
        $$ = create_program_node($2, $5, $9, $12);
    }
;

var_list:
    T_ID T_COMMA var_list
    {
        $$ = create_var_list_node($1, $3);
    }
|   T_ID
    {
        $$ = create_var_list_node($1, NULL);
    }
;

assign_stmt:
    T_ID T_ASSIGN expr T_SEMICOLON
    {
        $$ = create_assign_node($1, $3);
    }
;

expr:
    T_ID T_GREATER_THAN expr T_PLUS T_NUMBER
    {
        $$ = create_expr_node($1, $3, $5);
    }
;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
