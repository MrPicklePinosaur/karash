%{
#include <stdio.h>
#include "parser.h"

extern void yyerror(const char* e);
extern int yylval;
%}

%option noyywrap

%%
[0-9]+ {
    yylval = atoi(yytext);
    return INT;
}

. {
    yyerror("invalid input");
}
%%
