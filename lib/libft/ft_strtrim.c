/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:21:20 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:10:40 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	in_set(char c, char const *set)
{
	char	*tmpset;

	tmpset = (char *)set;
	while (*tmpset)
	{
		if (c == *tmpset)
			return (1);
		tmpset++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*strtmp;
	int		length;

	if (!s1 || !set)
		return (NULL);
	start = (char *) s1;
	end = start + ft_strlen(start) - 1;
	length = end - start + 1;
	while (*end != '\0' && *start != '\0' && start <= end)
	{
		end -= in_set(*end, set);
		start += in_set(*start, set);
		if (length == end - start + 1)
			break ;
		length = end - start + 1;
	}
	strtmp = (char *)malloc(sizeof(char) * (length + 1));
	if (!strtmp)
		return (NULL);
	ft_strlcpy(strtmp, start, length + 1);
	return (strtmp);
}
