/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:08:57 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/25 15:05:08 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*tmps;

	tmps = (unsigned char *)s;
	while (*tmps)
	{
		if ((unsigned char) *tmps == (unsigned char)c)
			return ((char *)tmps);
		tmps++;
	}
	if (!(char)c)
		return ((char *)tmps);
	return (NULL);
}
