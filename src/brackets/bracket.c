#include "list.h"
#include "test_tools.h"
#include "token_data.h"
#include <stdlib.h>
#include <unistd.h>


int
group_paren(
	t_void_list **lst,
	t_token_type token_type_open,
	t_token_type token_type_close,
	t_token_type token_type_name
)
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
		if (node->ptr.token->token_type == token_type_open)
		{
			if (depth == 0)
			{
				start_index = index;
			}
			depth += 1;
		}
		else if (node->ptr.token->token_type == token_type_close)
		{
			depth -= 1;			
			if (depth == 0)
			{
				t_anytype open_paren_token;
				t_void_list *putting_node;
				t_void_list *drained_node;

				end_index = index;
				drained_node = void_list_drain(lst,
					start_index,
				       	end_index
				);
				void_list_pop(&drained_node, 0, &open_paren_token);
				free(open_paren_token.token);
				//print_token_list_ln(drained_node);
				putting_node = void_list_get_elem(*lst, start_index);
				// setting_token
				putting_node->ptr.token->token_type = token_type_name;
				putting_node->ptr.token->contents.token_list = drained_node;
				index = start_index;
			}
		}
		index += 1;
	}
	return 0;
}
