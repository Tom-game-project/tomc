#include "ast.h"
#include "parser.h"
#include "token_data.h"
#include "tokenizer.h"
#include "test_tools.h"

#include <stdlib.h>
#include <unistd.h>

int show_expr_ast_parsing_proc(char *str, t_expr *ans_expr)
{
	t_token_list *tkn_lst;
	t_expr *expr_ast;

	tkn_lst = tokenizer(str);
	expr_ast = parse_expression(&tkn_lst);

	if (expr_ast == NULL)
	{
		debug_dprintf(STDERR_FILENO, "something wrong with while parsing\n");
		return 1;
	}
	//print_expr_ast_struct(expr_ast, 0);
	if (expr_eq(expr_ast, ans_expr))
	{
		debug_dprintf(STDERR_FILENO, "\e[0;32mOK!\e[0m\n");
	}
	else 
	{
		debug_dprintf(STDERR_FILENO, "\e[0;32mERR!\e[0m\n");
	}
	clear_ast(expr_ast);
	return 0;
}

/// ```bash
/// make vtest TEST_FILE=tests/parser/formal_parser_test00.c
/// ```
int main()
{
	char *str_arr[20] = {
		"a = x && y || z",
		"a = b + c * d - 1",
		"a = w << x | y << z",
		"a = b",
		"a = 0 <= x || x <= 10",
		"a = w + x + y + z",
		"a = x * y * z * w",
		"p = ***a",
		"p = *a + **b",
		"p = *a * **b",
		"p = *a * b[42]",
		"p = *a * b[42 + i + j + k + l + m]",
		"p = lst[y][x]",
		"expr->contents.postfix->left_expr",
		"player->vec.x = lst[x]",
		"*p = 1 + x",
		"p = (1 + x) * y",
	};

	t_expr *expr_set[20] = {
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
		}
		,
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
			.ope=e_operator_sub,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_add,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="b"
					}
					}
				,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_normal,
					.contents.normal=
					&(t_normal_expr){
					.ope=e_operator_mul,
					.left_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="c"
						}
						}
					,
					.right_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="d"
						}
						}
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
				.contents.str="1"
				}
				}
			}
			}
		}
		}
		,
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
			.ope=e_operator_logic_or,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_bitshift_left,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="w"
					}
					}
				,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="x"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_bitshift_left,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="y"
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
			}
		}
		}
		,
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
			.type_of_expr=e_expr_token,
			.contents.ident=
			&(t_token){
			.token_type=e_token_type_word,
			.contents.str="b"
			}
			}
		}
		}
		,
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
				.ope=e_operator_le,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="0"
					}
					}
				,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="x"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_le,
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
					.contents.str="10"
					}
					}
				}
				}
			}
			}
		}
		}
		,
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
			.ope=e_operator_add,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_add,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_normal,
					.contents.normal=
					&(t_normal_expr){
					.ope=e_operator_add,
					.left_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="w"
						}
						}
					,
					.right_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="x"
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
		}
		,
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
			.ope=e_operator_mul,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_mul,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_normal,
					.contents.normal=
					&(t_normal_expr){
					.ope=e_operator_mul,
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
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="w"
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_unary,
			.contents.unary=
			&(t_unary_expr){
			.ope=e_operator_mul,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_unary,
					.contents.unary=
					&(t_unary_expr){
					.ope=e_operator_mul,
					.right_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="a"
						}
						}
					}
					}
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_add,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="a"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_unary,
					.contents.unary=
					&(t_unary_expr){
					.ope=e_operator_mul,
					.right_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="b"
						}
						}
					}
					}
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_mul,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="a"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_unary,
					.contents.unary=
					&(t_unary_expr){
					.ope=e_operator_mul,
					.right_expr=
						&(t_expr) {
						.type_of_expr=e_expr_token,
						.contents.ident=
						&(t_token){
						.token_type=e_token_type_word,
						.contents.str="b"
						}
						}
					}
					}
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_mul,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="a"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_postfix,
				.contents.postfix=
				&(t_postfix_expr) {
				.ope=e_operator_arr_index_access,
				.left_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="b"
					}
					}
				,
				.right_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="42"
					}
					}
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_mul,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_unary,
				.contents.unary=
				&(t_unary_expr){
				.ope=e_operator_mul,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="a"
					}
					}
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_postfix,
				.contents.postfix=
				&(t_postfix_expr) {
				.ope=e_operator_arr_index_access,
				.left_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="b"
					}
					}
				,
				.right_expr =
					&(t_expr) {
					.type_of_expr=e_expr_normal,
					.contents.normal=
					&(t_normal_expr){
					.ope=e_operator_add,
					.left_expr=
						&(t_expr) {
						.type_of_expr=e_expr_normal,
						.contents.normal=
						&(t_normal_expr){
						.ope=e_operator_add,
						.left_expr=
							&(t_expr) {
							.type_of_expr=e_expr_normal,
							.contents.normal=
							&(t_normal_expr){
							.ope=e_operator_add,
							.left_expr=
								&(t_expr) {
								.type_of_expr=e_expr_normal,
								.contents.normal=
								&(t_normal_expr){
								.ope=e_operator_add,
								.left_expr=
									&(t_expr) {
									.type_of_expr=e_expr_normal,
									.contents.normal=
									&(t_normal_expr){
									.ope=e_operator_add,
									.left_expr=
										&(t_expr) {
										.type_of_expr=e_expr_token,
										.contents.ident=
										&(t_token){
										.token_type=e_token_type_word,
										.contents.str="42"
										}
										}
									,
									.right_expr=
										&(t_expr) {
										.type_of_expr=e_expr_token,
										.contents.ident=
										&(t_token){
										.token_type=e_token_type_word,
										.contents.str="i"
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
									.contents.str="j"
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
								.contents.str="k"
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
							.contents.str="l"
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
						.contents.str="m"
						}
						}
					}
					}
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_postfix,
			.contents.postfix=
			&(t_postfix_expr) {
			.ope=e_operator_arr_index_access,
			.left_expr =
				&(t_expr) {
				.type_of_expr=e_expr_postfix,
				.contents.postfix=
				&(t_postfix_expr) {
				.ope=e_operator_arr_index_access,
				.left_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="lst"
					}
					}
				,
				.right_expr =
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
			.right_expr =
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="x"
				}
				}
			}
			}
		}
		}
		,
		&(t_expr) {
		.type_of_expr=e_expr_postfix,
		.contents.postfix=
		&(t_postfix_expr) {
		.ope=e_operator_arrow,
		.left_expr =
			&(t_expr) {
			.type_of_expr=e_expr_postfix,
			.contents.postfix=
			&(t_postfix_expr) {
			.ope=e_operator_dot,
			.left_expr =
				&(t_expr) {
				.type_of_expr=e_expr_postfix,
				.contents.postfix=
				&(t_postfix_expr) {
				.ope=e_operator_arrow,
				.left_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="expr"
					}
					}
				,
				.right_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="contents"
					}
					}
				}
				}
			,
			.right_expr =
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="postfix"
				}
				}
			}
			}
		,
		.right_expr =
			&(t_expr) {
			.type_of_expr=e_expr_token,
			.contents.ident=
			&(t_token){
			.token_type=e_token_type_word,
			.contents.str="left_expr"
			}
			}
		}
		}
		,
		&(t_expr) {
		.type_of_expr=e_expr_normal,
		.contents.normal=
		&(t_normal_expr){
		.ope=e_operator_assignment,
		.left_expr=
			&(t_expr) {
			.type_of_expr=e_expr_postfix,
			.contents.postfix=
			&(t_postfix_expr) {
			.ope=e_operator_dot,
			.left_expr =
				&(t_expr) {
				.type_of_expr=e_expr_postfix,
				.contents.postfix=
				&(t_postfix_expr) {
				.ope=e_operator_arrow,
				.left_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="player"
					}
					}
				,
				.right_expr =
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="vec"
					}
					}
				}
				}
			,
			.right_expr =
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="x"
				}
				}
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_postfix,
			.contents.postfix=
			&(t_postfix_expr) {
			.ope=e_operator_arr_index_access,
			.left_expr =
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="lst"
				}
				}
			,
			.right_expr =
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="x"
				}
				}
			}
			}
		}
		}
		,
		&(t_expr) {
		.type_of_expr=e_expr_normal,
		.contents.normal=
		&(t_normal_expr){
		.ope=e_operator_assignment,
		.left_expr=
			&(t_expr) {
			.type_of_expr=e_expr_unary,
			.contents.unary=
			&(t_unary_expr){
			.ope=e_operator_mul,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="p"
				}
				}
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_add,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="1"
				}
				}
			,
			.right_expr=
				&(t_expr) {
				.type_of_expr=e_expr_token,
				.contents.ident=
				&(t_token){
				.token_type=e_token_type_word,
				.contents.str="x"
				}
				}
			}
			}
		}
		}
		,
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
			.contents.str="p"
			}
			}
		,
		.right_expr=
			&(t_expr) {
			.type_of_expr=e_expr_normal,
			.contents.normal=
			&(t_normal_expr){
			.ope=e_operator_mul,
			.left_expr=
				&(t_expr) {
				.type_of_expr=e_expr_normal,
				.contents.normal=
				&(t_normal_expr){
				.ope=e_operator_add,
				.left_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="1"
					}
					}
				,
				.right_expr=
					&(t_expr) {
					.type_of_expr=e_expr_token,
					.contents.ident=
					&(t_token){
					.token_type=e_token_type_word,
					.contents.str="x"
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
				.contents.str="y"
				}
				}
			}
			}
		}
		}
	};

	for (int i = 0; i < 17; i++)
	{
		show_expr_ast_parsing_proc(str_arr[i], expr_set[i]);
	}
	//show_expr_ast_parsing_proc(str_arr[14]);
	return (0);
}
