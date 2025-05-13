/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:08:20 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:33:18 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rbuf;
	t_list	*unit;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	unit = lst;
	rbuf = ft_lstnew(f(unit->content));
	if (!rbuf)
		return (NULL);
	while (unit->next != NULL)
	{
		unit = unit -> next;
		tmp = ft_lstnew(f(unit -> content));
		if (tmp == NULL)
		{
			ft_lstclear(&rbuf, del);
			return (NULL);
		}
		ft_lstadd_back(&rbuf, tmp);
	}
	return (rbuf);
}
