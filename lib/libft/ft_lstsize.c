/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:23:05 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 22:22:25 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		c;
	t_list	*unit;

	c = 0;
	if (!lst)
		return (0);
	unit = lst;
	while (unit)
	{
		unit = (unit -> next);
		c++;
	}
	return (c);
}
