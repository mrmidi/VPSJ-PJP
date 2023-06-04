%{
#include "turbopjp.tab.h"
// Add additional required includes here
%}

%option noyywrap
%option yylineno

%%
(?i:PROGRAM)    { return T_PROGRAM; }
(?i:VAR)        { printf("*** LEXER *** VAR TOKEN\n");  return T_VAR; }
(?i:INTEGER)    { printf("*** LEXER *** INTEGER TOKEN"); return T_INT; }
(?i:BEGIN)      { printf("*** LEXER *** BEGIN TOKEN"); return T_BEGIN; }
(?i:END)        { printf("*** LEXER *** END TOKEN"); return T_END; }
":="            { return T_ASSIGN; }    
[a-zA-Z][a-zA-Z0-9]* {  // print the token
                        printf("*** LEXER *** TOKEN ID > %s\n", yytext);
                        yylval.sval = strdup(yytext);
                        return T_ID; }
[0-9]+          { yylval.ival = atoi(yytext); return T_NUMBER; }
"("             { return T_LPAREN; }
")"             { return T_RPAREN; }
";"             { return T_SEMICOLON; }
","             { return T_COMMA; }
":"             { return T_COLON; }
"."             { return T_DOT; }
"*"             { return T_MUL; }
"+"             { return T_ADD; }
">"             { return T_GT; }

[\t\n\r ]+ { /* Ignore whitespace */ }
.         { /* Ignore any other characters */ }
%%

