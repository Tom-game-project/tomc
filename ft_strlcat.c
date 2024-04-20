/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:08:51 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 11:32:47 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat( char *restrict dst, \
					const char *restrict src, \
					size_t dstsize)
{
	size_t				i;
	int					flag;
	unsigned char		*srctmp;

	srctmp = (unsigned char *)src;
	i = 0;
	flag = 0;
	while (dst[i])
		i++;
	while (*srctmp)
	{
		if (i < dstsize - 1)
			dst[i] = *srctmp;
		else if (flag == 0)
		{
			flag = 1;
			dst[i] = '\0';
		}
		srctmp++;
		i++;
	}
	return (i);
}
