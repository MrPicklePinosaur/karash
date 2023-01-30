%{
#include <stdio.h>
  
%}

%token EOL
%token <value> INTEGER 

%union {
  int value;
}

%%
root:
exp EOL { printf("%d\n", $1); }
| EOL;

exp:
INTEGER { $$ = $1 }
| exp PLUS INTEGER { $$ = $1 + $3 }
;
%%
