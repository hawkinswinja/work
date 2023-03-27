%{
#include <stdio.h>
extern int yylex();
extern int yyerror(char*);
extern int yylineno;
int count = 0;
%}

%union {
    int count;
}

%token <count> EOL
%token A B

%start input

%%

input   : line EOL input
        | line EOL
        ;

line    : A         { count += $1.count; }
        | B
        ;

%%

int yyerror(char* msg) {
    fprintf(stderr, "line %d: %s\n", yylineno, msg);
    return 0;
}

int main() {
    yyparse();
    printf("Number of a's: %d\n", count);
    return 0;
}
