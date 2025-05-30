#include "ast2.h"
#include <unistd.h>

#include "list.h"
#include "test_tools.h"

int
print_depth(int depth)
{
	for (int i = 0; i < depth * 8; i++)
	{
		debug_dprintf(STDERR_FILENO, " ");
	}
	return 0;
}

int print_expr_ast(t_expr *expr_ast, int depth)
{
	char *contents_str;
	char *token_type_str;
	t_anytype elem;

	if (expr_ast == NULL)
	{
		print_depth(depth);
		debug_dprintf(STDERR_FILENO, "(NULL)\n");
		return 0;
	}
	switch (expr_ast->type_of_expr) {
		case e_expr_token:
			elem.token = expr_ast->contents.ident;
			get_token_str(elem, &contents_str, &token_type_str);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "[%s] [%s]\n", token_type_str, contents_str);
			break;
		case e_expr_normal:
			// normal
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".operator = \"%s\"\n", print_operator_as_string(expr_ast->contents.normal->ope));
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,".left_expr = \n");
			print_expr_ast(expr_ast->contents.normal->left_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,".right_expr = \n");
			print_expr_ast(expr_ast->contents.normal->right_expr, depth + 1);
			break;
		case e_expr_unary:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "operator, %s\n", print_operator_as_string(expr_ast->contents.unary->ope));
			print_expr_ast(expr_ast->contents.unary->right_expr, depth + 1);
			break;
		case e_expr_postfix:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "operator, %s\n", print_operator_as_string(expr_ast->contents.postfix->ope));
			print_expr_ast(expr_ast->contents.postfix->left_expr, depth + 1);
			break;
	}
	return 0;
}
