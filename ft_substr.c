/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:11:07 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 20:05:37 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	i;

	buf = malloc(len * sizeof(char));
	i = 0;
	while (i < len)
	{
		buf[i] = s[start + i];
		if (!s[start + i])
			return (buf);
		i++;
	}
	return (buf);
}
