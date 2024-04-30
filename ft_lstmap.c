/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:08:20 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:17:11 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rbuf;
	t_list	*unit;
	t_list	*tmp;

	rbuf = (t_list *) malloc(sizeof(t_list *) * ft_lstsize(lst));
	if (!rbuf)
		return (NULL);
	unit = lst;
	while (unit != NULL)
	{
		tmp = ft_lstnew(f(unit -> content));
		if (tmp == NULL)
		{
			ft_lstclear(&rbuf, del);
			return (NULL);
		}
        //printf("hello %p %s\n",tmp,tmp->content);
		ft_lstadd_back(&rbuf, tmp);
		unit = unit -> next;
	}
	return (rbuf);
}
