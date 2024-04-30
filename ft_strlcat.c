/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:08:51 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 17:05:34 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat( char *dst, \
					const char *src, \
					size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	max;
	size_t	i;

	dstlen = ft_strlen(dst);
	if (!src || !dstsize || *src == '\0'){
		if (dstsize < dstlen)
			return (ft_strlen((char *)src) + dstsize);
		else
			return (ft_strlen((char *)src) + dstlen);}
	i = 0;
	srclen = ft_strlen((char *)src);
	max = dstsize - dstlen - 1;
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (i < max && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + max] = '\0';
	return (srclen + dstlen);
}
