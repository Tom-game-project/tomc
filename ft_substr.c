/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:11:07 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 16:21:41 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;

	buf = (char *)malloc((len + 1) * sizeof(char));
	i = 0;
	while (i < len && start < ft_strlen((char *)s))
	{
		if (!s[start + i])
		{
			buf[i] = '\0';
			return (buf);
		}
		buf[i] = s[start + i];
		i++;
	}
	buf[start + i] = '\0';
	return (buf);
}
