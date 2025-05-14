/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:25:13 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/25 15:17:26 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		count;
	char	*strtmp;

	count = 0;
	strtmp = (char *)s;
	while (s[count])
		count++;
	if (!c)
		return (strtmp + count);
	while (count + 1)
	{
		if ((unsigned char) s[count] == (unsigned char) c)
			return (strtmp + count);
		count--;
	}
	return (NULL);
}
