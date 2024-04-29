

#include <stdlib.h>
#include "libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    t_list *unit;

    unit = lst;
    while (unit != NULL)
    {
        f(unit->content);
        unit = unit -> next;
    }
}
