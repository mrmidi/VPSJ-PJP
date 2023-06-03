%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    T_INT,
    T_ID,
    T_PROGRAM,
    T_VAR,
    T_BEGIN,
    T_END,
    T_SEMICOLON,
    T_COLON,
    T_LEFT_BRACKET,
    T_RIGHT_BRACKET,
    T_COMMA,
    T_NUMBER,
    T_ASSIGN,
    T_GREATER_THAN,
    T_PLUS
    // add more token types as needed
} TokenType;

typedef struct Symbol {
    char *name;
    TokenType type;
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

[0-9]+ {
    Symbol* symbol = addSymbol(yytext, T_INT);
    symbol->value = atoi(yytext);
    printf("Added integer symbol: %s\n", yytext);
}

[a-zA-Z][a-zA-Z0-9]* {
    if (!lookupSymbol(yytext)) {
        addSymbol(yytext, T_ID);
        printf("Added identifier symbol: %s\n", yytext);
    }
}

.|\n {}

%%

int main() {
    yylex();
    return 0;
}
