/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:16:03 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:15:54 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*unit;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	unit = *lst;
	while (unit != NULL)
	{
		del(unit->content);
		tmp = unit -> next;
		free(unit);
		unit = tmp;
	}
	*lst = NULL;
}
