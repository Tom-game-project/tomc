/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:41:09 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 13:31:48 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*strbuf;
	size_t	buf_size;

	buf_size = (ft_strlen((char *)s1) + 1) * sizeof(char);
	strbuf = malloc(buf_size);
	if (!strbuf)
		return (NULL);
	ft_memcpy(strbuf, s1, buf_size);
	return (strbuf);
}
