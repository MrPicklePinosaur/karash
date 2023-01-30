%{
#include <stdio.h>
void error(void);
%}

integer ([0-9])+

%%
{integer} {
    yylval.num = atoi(yytext);
    return INT;
}
\n {
    return EOL;
}
. {}
%%

void error(void) {
    printf("an error occured");
}
