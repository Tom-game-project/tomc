

#include <stdlib.h>
#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
    t_list *unit;
    t_list *tmp;

    unit = *lst;
    while (unit != NULL)
    {
        del(unit->content);
        // del(unit->next);
        tmp = unit -> next;
        free(unit);
        unit = tmp;
    }
    *lst = NULL;
}