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


int
main(int argc, char *argv[])
{
    yyparse();
    return EXIT_SUCCESS;
}

void
yyerror(const char* e)
{
    fprintf(stderr, "yyerror %s\n", e);
}
