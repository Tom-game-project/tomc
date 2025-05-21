#include "list.h"
#include "test_tools.h"
#include "token_data.h"
#include <stdlib.h>


int
group_paren(t_void_list **lst)
{
	int index = 0;
	int start_index = 0;
	int end_index = 0;
	t_void_list *node;
	int depth = 0;

	while (1)
	{
		node = void_list_get_elem(*lst, index);
		if (node == NULL)
			break;
		if (node->ptr.token->token_type == e_token_type_open_paren)
		{
			depth += 1;
			start_index = index;
		}
		else if (node->ptr.token->token_type == e_token_type_close_paren)
		{
			depth -= 1;
			end_index = index;
			if (depth == 0)
			{
				print_token_list(
					void_list_drain(lst,
					start_index,
				       	end_index
				));
				index = start_index;
			}
		}
		index += 1;
	}
	return (0);
}
