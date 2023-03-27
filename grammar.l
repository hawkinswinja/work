%{
#include <stdio.h>
#include "grammar.tab.h"
%}

%%
a       { yylval.count++; }
b       {}
\n      { return EOL; }
.       { yyerror("invalid character"); }
%%

int yywrap() {
    return 1;
}
