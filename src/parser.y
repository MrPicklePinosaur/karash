%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char* e);
%}

%token INT

%%
root: INT { printf("found integer"); }
%%

void
yyerror(const char* e)
{
    fprintf(stderr, "yyerror %s\n", e);
}
