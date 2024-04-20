/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:08:57 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 12:20:15 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	*tmps;

	tmps = (char *)s;
	while (*tmps)
	{
		if (*tmps == c)
			return (tmps);
		tmps++;
	}
	if (!c)
		return (tmps);
	return (NULL);
}
