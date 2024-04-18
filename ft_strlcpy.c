/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:36 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/18 18:05:24 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(	char *restrict dst, \
					const char *restrict src, \
					size_t dstsize)
{
	size_t			i;
	unsigned char	*srctmp;
	int				flag;

	i = 0;
	flag = 0;
	srctmp = (unsigned char *)src;
	while (*srctmp)
	{
		if (i < dstsize - 1)
			dst[i] = *srctmp;
		else if (flag == 0)
		{
			flag = 1;
			dst[i] = '\0';
		}
		i++;
		srctmp++;
	}
	if (flag == 0)
		dst[i] = '\0';
	return (i);
}
