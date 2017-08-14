%{
#include <stdio.h>

#include "god.h"
#include "y.tab.h"
%}

%%
"+"	return T_ADD;
"-"	return T_SUB;
"*"	return T_MUL;
"/"	return T_DIV;
"%"	return T_MOD;

"("	return T_LP;
")"	return T_RP;

([1-9][0-9]*)|0 {
	sscanf(yytext, "%d", &yylval.int_val);

	return T_INT;
}

"\n"    return T_CR;

[ \t]	;

. {
	printf("解析失败：%s \n", yytext);

	exit(0);
}
%%
