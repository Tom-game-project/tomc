#include "ast2.h"

#include "parser.h"
#include "tokenizer.h"

#include "test_tools.h"

#include <stdlib.h>
#include <unistd.h>

int
show_expr_ast_parsing_proc(char *str)
{
	t_token_list *tkn_lst;
	t_expr *expr_ast;


	debug_dprintf(STDERR_FILENO, "test case: \"%s\"\n", str);
	tkn_lst = tokenizer(str);
	print_token_list_ln(tkn_lst);
	expr_ast = parse_assignment_operator(&tkn_lst);

	if (expr_ast == NULL)
	{
		debug_dprintf(STDERR_FILENO, "something wrong with while parsing\n");
		return 1;
	}
	print_expr_ast(expr_ast, 0);
	return 0;

}



/// ```bash
/// make test TEST_FILE=tests/parser/easy_parser_test00.c
/// ```
int main()
{
	char *str_arr[10] = {
		"a = x && y || z",
		"a = b + c * d - 1",
		"a = w << x | y << z",
		"a = b",
		"a = 0 <= x || x <= 10",
		"a = x && y || z",
		"a = x && y || z",
		"a = x && y || z",
		"a = x && y || z",
		"a = x && y || z",
	};


	for (int i = 0; i < 5; i++){
		debug_dprintf(STDERR_FILENO, "===========================\n");
		show_expr_ast_parsing_proc(str_arr[i]);
	}
	return (0);
}
