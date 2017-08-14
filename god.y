%{
#include <stdio.h>

#include "god.h"

#define YYDEBUG 1
%}

%union {
	int 		int_val;
	PExpression	pexpression;
}

%token T_ADD T_SUB T_MUL T_DIV T_MOD T_CR
%token T_LP T_RP

%token <pexpression> T_INT

%type <pexpression> primary_expression twice_expression expression

%%

line_list
	: line
	| line_list line
	;

line
	: expression T_CR
	{
		int result = 0;

		//打印抽象语法树
		print_expr_tree($1);

		//运行抽象语法树中的表达式
		run_expr_tree($1, &result);
		printf(" = %d \n", result);

		free($1);

		printf("\n");
        }
        ;

expression
	: twice_expression
	{
		//printf("第三次规约 %d \n", $1->u.int_val);
	}
	| expression T_ADD twice_expression
	{
		//printf("加法 %d %d \n", $1->u.int_val, $3->u.int_val);

		$$ = create_operation_expression(ADD_EXPRESSION, $1, $3);
	}
	;
	| expression T_SUB twice_expression
	{
		$$ = create_operation_expression(SUB_EXPRESSION, $1, $3);
	}
	;

twice_expression
	: primary_expression
	{
		//printf("第二次规约 %d \n", $1->u.int_val);
	}
	| twice_expression T_MUL primary_expression
        {
		$$ = create_operation_expression(MUL_EXPRESSION, $1, $3);
        }
	| twice_expression T_DIV primary_expression
        {
		$$ = create_operation_expression(DIV_EXPRESSION, $1, $3);
        }
	| twice_expression T_MOD primary_expression
        {
		$$ = create_operation_expression(MOD_EXPRESSION, $1, $3);
        }
	;

primary_expression
	: T_INT
	{
		//printf("第一次规约 %d \n", $1);

		$$ = create_int_expr(yylval.int_val);
	}	
	| T_LP expression T_RP
	{
		$$ = $2;	
	}
	;

%%
