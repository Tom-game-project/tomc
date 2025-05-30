#include "brackets.h"
#include "test_tools.h"
#include "token_data.h"
#include "tokenizer.h"
#include <unistd.h>


/// ```bash
///
/// make test TEST_FILE=tests/brackets/bracket_group_paren_test00.c
/// ```
int main()
{
	char *str = \
		"int c = *hello + a[42 + (a + b + *c)] **constant + func(a, (b0+b1)*10, c)\n";
	t_token_list *tkn_lst;

	debug_dprintf(STDERR_FILENO, "test case:\nstart>>>>>>>>\n%s\n<<<<<<<<end\n", str);
	debug_dprintf(STDERR_FILENO, "%s\n", "tokenize...");
	tkn_lst = tokenizer(str);
	debug_dprintf(STDERR_FILENO, "%s\n", "DONE");
	if (tkn_lst == NULL)
		debug_dprintf(STDERR_FILENO, "failed to tokenize\n");
	print_token_list_ln(tkn_lst);

	group_paren(&tkn_lst, e_token_type_open_paren, e_token_type_close_paren, e_token_type_paren);
	group_paren(&tkn_lst, e_token_type_open_brace, e_token_type_close_brace, e_token_type_brace);
	group_paren(&tkn_lst, e_token_type_open_bracket, e_token_type_close_bracket, e_token_type_bracket);
	debug_dprintf(STDERR_FILENO, "==========================================\n");
	
	print_token_list_ln(tkn_lst);
	return 0;
}
