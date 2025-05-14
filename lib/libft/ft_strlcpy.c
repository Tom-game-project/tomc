/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:36 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:33:49 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(	char *dst, \
					const char *src, \
					size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen((char *)src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (i < len)
	{
		if (i < dstsize - 1)
			dst[i] = src[i];
		else
			break ;
		i++;
	}
	dst[i] = '\0';
	return (len);
}
