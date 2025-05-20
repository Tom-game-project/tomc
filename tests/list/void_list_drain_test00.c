#include "list.h"
#include "test_tools.h"
#include <stdlib.h>
#include <unistd.h>

/// ```bash
/// make test TEST_FILE=tests/list/void_list_drain_test00.c
/// ```
int main()
{
	t_void_list *lst;
	t_void_list *result;

	lst = NULL;
	int_list_push(&lst, 1);
	int_list_push(&lst, 2);
	int_list_push(&lst, 3);
	int_list_push(&lst, 4);
	int_list_push(&lst, 5);
	debug_dprintf(STDERR_FILENO, "orig lst\n");
	int_list_print(lst);
	result = void_list_drain(&lst, 1, 4);
	debug_dprintf(STDERR_FILENO, "result\n");
	int_list_print(result);
	debug_dprintf(STDERR_FILENO, "lst\n");
	int_list_print(lst);
	return (0);
}
