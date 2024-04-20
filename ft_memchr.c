/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:46:29 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 14:56:06 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*strtmp;

	i = 0;
	strtmp = (char *)s;
	while (i < n)
	{
		if (strtmp[i] == c)
			return (strtmp + i);
		i++;
	}
	return (NULL);
}
