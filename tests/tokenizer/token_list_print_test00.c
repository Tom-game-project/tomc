#include "list.h"
#include "test_tools.h"
#include "tokenizer.h"
#include <unistd.h>

int main()
{
	char *str = "*hello + a[42] **constant";
	t_token_list *tkn_lst;

	debug_dprintf(STDERR_FILENO, "%s\n", "tokenize...");
	tkn_lst = tokenizer(str);
	debug_dprintf(STDERR_FILENO, "%s\n", "DONE");
	if (tkn_lst == NULL)
		debug_dprintf(STDERR_FILENO, "failed to tokenize\n");
	print_token_list(tkn_lst);
	return 0;
}
