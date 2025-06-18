#include "ast.h"
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
			debug_dprintf(STDERR_FILENO, "<e_expr_token>\n");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "[%s] [%s]\n", token_type_str, contents_str);
			break;
		case e_expr_normal:
			// normal
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "<e_expr_normal>\n");
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
			debug_dprintf(STDERR_FILENO, "<e_expr_unary>\n");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "operator = \"%s\"\n", print_operator_as_string(expr_ast->contents.unary->ope));
			print_expr_ast(expr_ast->contents.unary->right_expr, depth + 1);
			break;
		case e_expr_postfix:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "<e_expr_postfix>\n");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "operator = \"%s\"\n", print_operator_as_string(expr_ast->contents.postfix->ope));
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,".left_expr = \n");
			print_expr_ast(expr_ast->contents.postfix->left_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,".right_expr = \n");
			print_expr_ast(expr_ast->contents.postfix->right_expr, depth + 1);
			break;
		case e_expr_cast:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "<e_expr_cast>\n");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "cast\n");
			// TODO: cast typeを表示する部分も作成する
			print_expr_ast(expr_ast->contents.cast->inner_expr, depth + 1);
			break;
	}
	return 0;
}

/// print ast (c formatted structure)
int print_expr_ast_struct(t_expr *expr_ast, int depth)
{
	char *contents_str;
	char *token_type_str;
	t_anytype elem;

	print_depth(depth);
	debug_dprintf(STDERR_FILENO, "&(t_expr) {\n");
	/// &(t_expr) {
	if (expr_ast == NULL)
	{
		//print_depth(depth);
		//debug_dprintf(STDERR_FILENO, "(NULL)\n");
		return 0;
	}
	switch (expr_ast->type_of_expr) {
		case e_expr_token:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".type_of_expr=%s\n", "e_expr_token,"); // struct 
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".contents.ident=\n");                 // sturct
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "&(t_token){\n");                      // struct
			elem.token = expr_ast->contents.ident;
			get_token_struct_as_string(elem, &contents_str, &token_type_str);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".token_type=%s,\n", token_type_str);                      // struct
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".contents.str=\"%s\"\n", contents_str);                      // struct
			// .token_type=e_token_type_word,
			// .contents.str = "world"
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "}\n");
			break;
		case e_expr_normal:
			// normal
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".type_of_expr=%s,\n", "e_expr_normal"); // struct 
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".contents.normal=\n");                 // sturct
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "&(t_normal_expr){\n");                      // struct
			print_depth(depth);

			debug_dprintf(STDERR_FILENO, ".ope=%s,\n", get_operator_enum_as_string(expr_ast->contents.normal->ope));                      // struct

			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".left_expr=\n");
			print_expr_ast_struct(expr_ast->contents.normal->left_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ",\n");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".right_expr=\n");
			print_expr_ast_struct(expr_ast->contents.normal->right_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "}\n");
			break;
		case e_expr_unary:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".type_of_expr=%s,\n", "e_expr_unary");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "&(t_unary_expr){\n");                      // struct
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".ope=%s,\n", get_operator_enum_as_string(expr_ast->contents.unary->ope));                      // struct
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".right_expr=\n");
			print_expr_ast_struct(expr_ast->contents.unary->right_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "}\n");
			break;
		case e_expr_postfix:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".type_of_expr=%s,\n", "e_expr_postfix"); // struct 
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,"&(t_postfix_expr) {\n");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".ope=%s\n", get_operator_enum_as_string(expr_ast->contents.postfix->ope));                      // struct
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,".left_expr = \n");
			print_expr_ast_struct(expr_ast->contents.postfix->left_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO ,".right_expr = \n");
			print_expr_ast_struct(expr_ast->contents.postfix->right_expr, depth + 1);
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "}\n");
			break;
		case e_expr_cast:
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, ".type_of_expr=%s,\n", "e_expr_cast");
			print_depth(depth);
			debug_dprintf(STDERR_FILENO, "\e[0;32mERR!\e[0m\n");
			// 未実装部分
			// TODO: cast typeを表示する部分も作成する
			break;
	}
	print_depth(depth);
	debug_dprintf(STDERR_FILENO, "}\n");
	return 0;
}

