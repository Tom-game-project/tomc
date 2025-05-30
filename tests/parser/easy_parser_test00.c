#include "ast2.h"

#include "parser.h"
#include "tokenizer.h"

int main()
{
	char *str = "a = a && b || c";
	t_token_list *tkn_lst;
	t_expr *expr_ast;

	tkn_lst = tokenizer(str);
	ast = parse_assignment_operator(&tkn_lst);
	return 0;
}
