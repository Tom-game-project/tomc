/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:23:05 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/23 22:15:56 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int		c;
	t_list	*unit;

	c = 0;
	unit = lst;
	while (unit)
	{
		printf("%p %p\n", unit, lst->next);
		unit = lst -> next;
		c++;
	}
	return (c);
}
