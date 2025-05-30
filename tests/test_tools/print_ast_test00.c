#include "ast2.h"
#include "test_tools.h"
#include "token_data.h"

/// ```bash
/// make test TEST_FILE=tests/test_tools/print_ast_test00.c
int main()
{
	t_expr *expr;

	expr = &(t_expr) {
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
	print_expr_ast(expr, 0);
	return 0;
}
