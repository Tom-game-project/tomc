
#include "list.h"
#include "test_tools.h"
#include "tokenizer.h"
#include <unistd.h>

/// ```
/// make test TEST_FILE=tests/tokenizer/token_list_print_test02.c
/// ```
int main()
{
	char *str = \
		"int c = *hello + a[42] **constant + func(a, b, c); /* \n"
		"hello world\n"
		"\n"
		"*/\n"
		"int c = *hello + a[42] **constant; // hello world\n"
		"char *str = \"this is \\\"string\";";
	t_token_list *tkn_lst;

	debug_dprintf(STDERR_FILENO, "test case:\nstart>>>>>>>>\n%s\n<<<<<<<<end\n", str);
	debug_dprintf(STDERR_FILENO, "%s\n", "tokenize...");
	tkn_lst = tokenizer(str);
	debug_dprintf(STDERR_FILENO, "%s\n", "DONE");
	if (tkn_lst == NULL)
		debug_dprintf(STDERR_FILENO, "failed to tokenize\n");
	print_token_list_ln(tkn_lst);
	clear_token_list(&tkn_lst);
	return 0;
}
