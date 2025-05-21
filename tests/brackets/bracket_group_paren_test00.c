#include "brackets.h"
#include "test_tools.h"
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
	print_token_list(tkn_lst);

	debug_dprintf(STDERR_FILENO, "================================================\n");

	group_paren(&tkn_lst);
	return 0;
}
