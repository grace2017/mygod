#include <stdio.h>
#include <stdlib.h>

#include "god.h"

PExpression
create_int_expr(int val)
{
	PExpression p = (PExpression)calloc(1, sizeof(Expression));
	if(NULL == p) {
		perror("calloc failed");

		exit(0);
	}

	p->type = INT_EXPRESSION;
	p->u.int_val = val;

	return p;
}

void
print_expr_tree(PExpression p)
{
	if(NULL == p) {
		return;
	}

	switch(p->type) {
		case INT_EXPRESSION:
			printf("%d", p->u.int_val);
			break;
		case ADD_EXPRESSION:
			printf("(");
			print_expr_tree(p->u.binary_expression.left);
			printf(" + ");
			print_expr_tree(p->u.binary_expression.right);
			printf(")");

			break;
		case SUB_EXPRESSION:
			printf("(");
			print_expr_tree(p->u.binary_expression.left);
			printf(" - ");
			print_expr_tree(p->u.binary_expression.right);
			printf(")");

			break;
		case MUL_EXPRESSION:
			printf("(");
			print_expr_tree(p->u.binary_expression.left);			
			printf(" * ");
			print_expr_tree(p->u.binary_expression.right);			
			printf(")");

			break;
		case DIV_EXPRESSION:
			printf("(");
			print_expr_tree(p->u.binary_expression.left);			
			printf(" / ");
			print_expr_tree(p->u.binary_expression.right);			
			printf(")");

			break;
		case MOD_EXPRESSION:
			printf("(");
			print_expr_tree(p->u.binary_expression.left);			
			printf(" 求余 ");
			print_expr_tree(p->u.binary_expression.right);			
			printf(")");

			break;
		default:
			break;
	}
}

static
int
run_add_expr(PExpression p)
{
	if(NULL == p) return 0;

	int v1 = p->u.binary_expression.left->u.int_val;
	int v2 = p->u.binary_expression.right->u.int_val;

	//将计算的结果写入保存+的Expression中
	p->u.int_val = v1 + v2;

	return v1 + v2;
}

static
int
run_sub_expr(PExpression p)
{
	if(NULL == p) return 0;

	int v1 = p->u.binary_expression.left->u.int_val;
	int v2 = p->u.binary_expression.right->u.int_val;

	//将计算的结果写入保存-的Expression中
	p->u.int_val = v1 - v2;

	return v1 - v2;
}

static
int
run_mul_expr(PExpression p)
{
	if(NULL == p) return 0;

	int v1 = p->u.binary_expression.left->u.int_val;
        int v2 = p->u.binary_expression.right->u.int_val;

	//将计算的结果写入保存*的Expression中
	p->u.int_val = v1 * v2;

	return v1 * v2;
}

static
int
run_div_expr(PExpression p)
{
	if(NULL == p) return 0;

	int v1 = p->u.binary_expression.left->u.int_val;
        int v2 = p->u.binary_expression.right->u.int_val;

	//将计算的结果写入保存/的Expression中
	p->u.int_val = v1 / v2;

	return v1 / v2;
}

static
int
run_mod_expr(PExpression p)
{
	if(NULL == p) return 0;

	int v1 = p->u.binary_expression.left->u.int_val;
        int v2 = p->u.binary_expression.right->u.int_val;

	//将计算的结果写入保存%的Expression中
	p->u.int_val = v1 % v2;

	return v1 % v2;
}

void
run_expr_tree(PExpression p, int *return_val)
{
	if(NULL == p) {
                return;
        }

        switch(p->type) {
                case ADD_EXPRESSION:
                        run_expr_tree(p->u.binary_expression.left, return_val);
                        run_expr_tree(p->u.binary_expression.right, return_val);
			*return_val = run_add_expr(p);

                        break;
                case SUB_EXPRESSION:
                        run_expr_tree(p->u.binary_expression.left, return_val);
                        run_expr_tree(p->u.binary_expression.right, return_val);
			*return_val = run_sub_expr(p);

                        break;
                case MUL_EXPRESSION:
                        run_expr_tree(p->u.binary_expression.left, return_val);
                        run_expr_tree(p->u.binary_expression.right, return_val);
			*return_val = run_mul_expr(p);

                        break;
                case DIV_EXPRESSION:
                        run_expr_tree(p->u.binary_expression.left, return_val);
                        run_expr_tree(p->u.binary_expression.right, return_val);
			*return_val = run_div_expr(p);

                        break;
                case MOD_EXPRESSION:
                        run_expr_tree(p->u.binary_expression.left, return_val);
                        run_expr_tree(p->u.binary_expression.right, return_val);
			*return_val = run_mod_expr(p);

                        break;
                default:
                        break;
        }
}

/*
        创建运算表达式（加、减、乘、除、求余）

        参数一：表达式类型
        参数二：左操作数
        参数三：右操作数
*/
PExpression
create_operation_expression(
	int type, 
	PExpression expr1_p, 
	PExpression expr2_p)
{
	PExpression p = (PExpression)calloc(1, sizeof(Expression));
	if(NULL == p) {
		perror("calloc failed");

		exit(0);
	}

	p->type = type;
	p->u.binary_expression.left = expr1_p;
	p->u.binary_expression.right = expr2_p;

	return p;
}

PExpression
create_add_expression(PExpression p1, PExpression p2)
{
	PExpression p = (PExpression)calloc(1, sizeof(Expression));
        if(NULL == p) {
                perror("calloc failed");

                exit(0);
        }

	p->type = ADD_EXPRESSION;
	p->u.binary_expression.left = p1;
	p->u.binary_expression.right = p2;

	return p;	
}
