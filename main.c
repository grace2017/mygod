#include <stdio.h>
#include <stdlib.h>

#include "god.h"

int
yyerror(char const *str)
{
        extern char *yytext;

        fprintf(stderr, "parse error: %s \n", yytext);

        return 0;
}

int
yywrap(void)
{
	return 1;
}

int
main(void)
{
	extern int yyparse();
	extern FILE *yyin;

	yyin = stdin;
	if(yyparse()) {
		printf("error! end! \n");
	}

	return 0;
}
