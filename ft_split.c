/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:19:21 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 21:15:59 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	return_size(char *s, char c)
{
	int	flag;
	int	count;

	flag = 1;
	count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else if (flag == 1)
		{
			flag = 0;
			count++;
		}
		s++;
	}
	return (count + 1);
}

static char	**free_all(char **buf, int index)
{
	while (index + 1)
	{
		free(buf[index]);
		index--;
	}
	return (NULL);
}

static char	**helper(char **rbuf, const char *s, char c)
{
	int		i;
	char	*start;
	char	*end;

	start = (char *)s;
	end = (char *)s;
	i = 0;
	while (*start && *end)
	{
		start = (char *) end;
		while (*start == c && *start != '\0')
			start++;
		end = (char *) start;
		while (*end != c && *end != '\0')
			end++;
		if (end - start == 0)
			break ;
		rbuf[i] = ft_substr(s, start - s, (size_t)(end - start));
		if (rbuf[i] == NULL)
			return (free_all(rbuf, i));
		i++;
	}
	rbuf[i] = NULL;
	return (rbuf);
}

char	**ft_split(char const *s, char c)
{
	char	**rbuf;

	rbuf = (char **) malloc(sizeof(char *) * return_size((char *)s, c));
	if (!rbuf)
		return (NULL);
	rbuf = helper(rbuf, s, c);
	if (!rbuf)
		return (NULL);
	return (rbuf);
}
