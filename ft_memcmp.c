/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:59:23 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/25 16:05:05 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	char		*strtmp1;
	char		*strtmp2;

	i = 0;
	strtmp1 = (char *)s1;
	strtmp2 = (char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (strtmp1[i] != strtmp2[i])
			return (strtmp1[i] - strtmp2[i]);
		i++;
	}
	return (strtmp1[i] - strtmp2[i]);
}
