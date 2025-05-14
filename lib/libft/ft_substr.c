/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:11:07 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 19:15:32 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen((char *)s) < start)
		buf = (char *)malloc(sizeof(char));
	else if (len <= ft_strlen((char *)s) - start)
		buf = (char *)malloc((len + 1) * sizeof(char));
	else
		buf = (char *)malloc((ft_strlen((char *)s) - start + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	while (i < len && start + i < ft_strlen((char *)s))
	{
		if (s[start + i] == '\0')
			break ;
		buf[i] = s[start + i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
