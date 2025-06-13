#include "ast2.h"
#include "list.h"

int clear_ast(t_expr *expr)
{
	switch (expr->type_of_expr) {
		case e_expr_normal:
			clear_ast(expr->contents.normal->left_expr);
			clear_ast(expr->contents.normal->right_expr);
			break;
		case e_expr_unary:
			clear_ast(expr->contents.unary->right_expr);
			break;
		case e_expr_cast:
			clear_ast(expr->contents.cast->inner_expr);
			break;
		case e_expr_postfix:
			clear_ast(expr->contents.postfix->left_expr);
			clear_ast(expr->contents.postfix->right_expr);
			break;
		case e_expr_token: // 文法的にそれ以上解釈不可

			switch (expr->contents.ident->token_type) {
			
case :
			}
			//clear_ast(expr->contents.ident->contents);
			break;
	}
	return 0;
}
