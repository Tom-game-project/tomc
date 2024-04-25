/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:08:51 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/25 11:49:22 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

// size_t	ft_strlcat( char *restrict dst, \
// 					const char *restrict src, \
// 					size_t dstsize)
// {
// 	size_t				i;
// 	int					flag;
// 	unsigned char		*srctmp;

// 	srctmp = (unsigned char *)src;
// 	i = 0;
// 	flag = 0;
// 	while (dst[i])
// 		i++;
// 	while (*srctmp)
// 	{
// 		if (i < dstsize - 1)
// 			dst[i] = *srctmp;
// 		else if (flag == 0)
// 		{
// 			flag = 1;
// 			dst[i] = '\0';
// 		}
// 		srctmp++;
// 		i++;
// 	}
// 	return (i);
// }

size_t	ft_strlcat( char *dst, \
					const char *src, \
					size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen((char *)src);
	i = 0;
	if (src == NULL || dst == NULL || dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen)
		return (srclen + dstlen);
	while (i < srclen)
	{
		if (dstlen + i < dstsize - 1)
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		else
		{
			i++;
			break;
		}
	}
	dst[dstlen + i] = '\0';
	return (srclen + dstlen);
}
