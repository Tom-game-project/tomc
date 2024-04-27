/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:46:04 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 23:23:58 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*unit;
	t_list	*pre;

	unit = lst;
	pre = NULL;
	while (unit)
	{
		pre = unit;
		unit = unit -> next;
		if (unit == (t_list *) del)
		{
			if (pre)
				pre -> next = unit -> next;
			else
			{
				lst = NULL;
			}
			free(unit -> content);
			//free(unit -> next);
			free(unit);
			break ;
		}
	}
}
