/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:29:33 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:00:22 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == new)
		*lst = (ft_lstnew(new));
	if (*lst != NULL && new != NULL)
	{
		last = ft_lstlast(*lst);
		last -> next = new;
		new -> next = NULL;
	}
	else if (new)
		*lst = new;
}
