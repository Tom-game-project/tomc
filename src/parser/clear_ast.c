#include "ast.h"
#include "tokenizer.h"
#include <stdlib.h>

int clear_ast(t_expr *expr)
{
	switch (expr->type_of_expr) {
		case e_expr_normal:
			clear_ast(expr->contents.normal->left_expr);
			clear_ast(expr->contents.normal->right_expr);
			free(expr->contents.normal);
			break;
		case e_expr_unary:
			clear_ast(expr->contents.unary->right_expr);
			free(expr->contents.unary);
			break;
		case e_expr_cast:
			clear_ast(expr->contents.cast->inner_expr);
			free(expr->contents.cast);
			break;
		case e_expr_postfix:
			clear_ast(expr->contents.postfix->left_expr);
			clear_ast(expr->contents.postfix->right_expr);
			free(expr->contents.postfix);
			break;
		case e_expr_token:
			clear_token(expr->contents.ident);
			//free(expr->contents.ident);
			break;
	}
	free(expr);
	return 0;
}
