%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
// include parser header file
#include "pjp++.tab.h"

extern int lineno;

typedef struct Symbol {
    char *name;
    int value;
    // add more attributes as needed
} Symbol;

#define MAX_SYMBOLS 100

Symbol symbolTable[MAX_SYMBOLS];
int numSymbols = 0;

Symbol* lookupSymbol(const char* name) {
    for (int i = 0; i < numSymbols; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return &symbolTable[i];
        }
    }
    return NULL;
}

Symbol* addSymbol(const char* name, TokenType type) {
    if (numSymbols >= MAX_SYMBOLS) {
        fprintf(stderr, "Symbol table full\n");
        exit(1);
    }
    symbolTable[numSymbols].name = strdup(name);
    symbolTable[numSymbols].type = type;
    return &symbolTable[numSymbols++];
}
%}

%%

(?i:PROGRAM) {
    Symbol* symbol = addSymbol(yytext, T_PROGRAM);
    printf("Added program symbol: %s\n", yytext);
    return T_PROGRAM;
}

[0-9]+ {
    Symbol* symbol = addSymbol(yytext, T_INT);
    symbol->value = atoi(yytext);
    printf("Added integer symbol: %s\n", yytext);
    return T_INT;
}

[a-zA-Z][a-zA-Z0-9]* {
    if (!lookupSymbol(yytext)) {
        addSymbol(yytext, T_ID);
        printf("Added identifier symbol: %s\n", yytext);
    }
    return T_ID;
}

";" {
    addSymbol(yytext, T_SEMICOLON);
    printf("Added semicolon symbol: %s\n", yytext);
    return T_SEMICOLON;
}

[ \t\n] {
    // ignore whitespace
}

.|\n {}

%%

// int main() {
//     yylex();
//     // print out the symbol table
//     for (int i = 0; i < numSymbols; i++) {
//         printf("Symbol: %s\n", symbolTable[i].name);
//     }
//     return 0;
// }
