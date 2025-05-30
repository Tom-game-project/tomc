#ifndef AST2_H
#define AST2_H


#include "token_data.h"
typedef struct s_ast t_ast;


typedef struct s_expr t_expr;
typedef struct s_normal_expr t_normal_expr;
typedef struct s_unary_expr t_unary_expr;
typedef struct s_postfix_expr t_postfix_expr;

struct s_expr
{
    enum {
        e_expr_normal,
	e_expr_unary,
	e_expr_postfix,
	e_expr_token, // 文法的にそれ以上解釈不可
    } type_of_expr;
    union  {
	t_normal_expr *normal;
	t_unary_expr *unary;
	t_postfix_expr *postfix;
	t_token *ident;
    } contents;
};


struct s_normal_expr
{
	t_operator ope;
	t_expr *left_expr;
	t_expr *right_expr;
};


struct s_unary_expr
{
	t_operator ope;
	t_expr *right_expr;
};


struct s_postfix_expr
{
	t_operator ope;
	t_expr *left_expr;
};

#endif

