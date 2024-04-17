/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:36 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/17 15:11:39 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(	char *restrict dst, \
					const char *restrict src, \
					size_t dstsize)
{
	unsigned int	i;
	unsigned int	src_len;
	char			*tmp;

	i = 0;
	src_len = ft_strlen((char *)src);
	tmp = dst;
	while (i < dstsize)
	{
		if (src_len < i)
			dst[i] = '\0';
		else
			dst[i] = src[i];
		i++;
	}
	return (dstsize);
}
