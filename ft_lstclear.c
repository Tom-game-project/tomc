

#include <stdlib.h>
#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
    t_list *unit;

    unit = *lst;
    while (unit != NULL)
    {
        unit->content = NULL;
        del(unit->content);
        unit = unit -> next;
        del(unit->next);
        unit->next = NULL;
        del(unit);
    }
}