/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:59:21 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 21:21:18 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*rbuf;

	rbuf = malloc(sizeof(t_list));
	if (!rbuf)
		return (NULL);
	rbuf -> content = content;
	rbuf -> next = NULL;
	return (rbuf);
}
