#include "ast.h"
#include "test_tools.h"
#include <unistd.h>

/// ```
/// make test TEST_FILE=tests/test_tools/ast_eq_test00.c
/// ```
int main()
{
	t_expr *expr1;
	t_expr *expr2;
	t_expr *expr3;

	expr1 = &(t_expr) {
		.type_of_expr=e_expr_normal,
		.contents.normal= 
			&(t_normal_expr) {
				.ope=e_operator_eq,
				.left_expr = &(t_expr) {
					.type_of_expr = e_expr_token,
					.contents.ident = 
						&(t_token) {
							.token_type=e_token_type_word,
							.contents.str = "hello"
						}
				},
				.right_expr = &(t_expr) {
					.type_of_expr = e_expr_normal,
					.contents.normal = &(t_normal_expr){
						.ope = e_operator_add,
						.left_expr = &(t_expr) {
							.type_of_expr = e_expr_token,
							.contents.ident = 
								&(t_token) {
									.token_type=e_token_type_word,
									.contents.str = "world"
								}
						},
						.right_expr = &(t_expr) {
							.type_of_expr = e_expr_token,
							.contents.ident = 
								&(t_token) {
									.token_type=e_token_type_word,
									.contents.str = "tom"
								}
						},
					}
				}
			}
	};

	expr2 = &(t_expr) {
		.type_of_expr=e_expr_normal,
		.contents.normal= 
			&(t_normal_expr) {
				.ope=e_operator_eq,
				.left_expr = &(t_expr) {
					.type_of_expr = e_expr_token,
					.contents.ident = 
						&(t_token) {
							.token_type=e_token_type_word,
							.contents.str = "hello"
						}
				},
				.right_expr = &(t_expr) {
					.type_of_expr = e_expr_normal,
					.contents.normal = &(t_normal_expr){
						.ope = e_operator_add,
						.left_expr = &(t_expr) {
							.type_of_expr = e_expr_token,
							.contents.ident = 
								&(t_token) {
									.token_type=e_token_type_word,
									.contents.str = "world"
								}
						},
						.right_expr = &(t_expr) {
							.type_of_expr = e_expr_token,
							.contents.ident = 
								&(t_token) {
									.token_type=e_token_type_word,
									.contents.str = "tom"
								}
						},
					}
				}
			}
	};

	expr3 = 
		&(t_expr) {
		.type_of_expr=e_expr_normal,
		.contents.normal=
		&(t_normal_expr){
		.ope=e_operator_assignment,
		.left_expr=
			&(t_expr) {
			.type_of_expr=e_expr_token,
			.contents.ident=
			&(t_token){
			.token_type=e_token_type_word,
			.contents.str="a"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_or,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_and,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="x"
					}
					}
				,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="y"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="z"
				}
				}
			}
			}
		}
		};

	if (expr_eq(expr1, expr2))
	{
		debug_dprintf(STDERR_FILENO, "\e[0;32mOK!\e[0m\n");
	}
	else 
	{
		debug_dprintf(STDERR_FILENO, "\e[0;32mERR!\e[0m\n");
	}
	return 0;
}
