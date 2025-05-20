#include "list.h"

/// start: index
/// end: index
t_void_list *void_list_drain(t_void_list **lst, int start, int end)
{
	t_void_list *head;
	t_void_list *end_head;
	t_void_list *start_head;

	end_head = *lst;
	*lst = void_list_cut(&end_head, end - 1);
	start_head = *lst;
	head = void_list_cut(&start_head, start - 1);
	void_list_concat(&head, end_head);
	*lst = head;
	return (start_head);
}
