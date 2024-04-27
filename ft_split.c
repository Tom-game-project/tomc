/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:19:21 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 13:30:27 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static int	return_size(char *s,char c)
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

char	**ft_split(char const *s, char c)
{
	char	**rbuf;
	int		i;
	char	*start;
	char	*end;

	i = 0;
	// printf("return size:%d\n",return_size((char *)s, c));
	rbuf = (char **) malloc(sizeof(char *) * return_size((char *)s, c));
	if (!rbuf)
		return (NULL);
	start = (char *)s;
	end = (char *)s;
	while (*start && *end)
	{
		start = (char *) end;
		while (*start == c && *start != '\0')
			start++;
		end = (char *) start;
		while (*end != c && *end != '\0')
			end++;
		//printf("str (%s) (%s)\n",start,end);
		if (end - start == 0)
			break ;
		//printf("%ld %zu\n",start - s, (size_t)(end - start));
		rbuf[i] = ft_substr(s, start - s, (size_t)(end - start));
		if (rbuf[i] == NULL)
			return (free_all(rbuf, i));
		printf("(%p) (%s)\n",rbuf[i],rbuf[i]);
		i++;
	}
	rbuf[i] = NULL;
	printf("--------------\n");
	for (int n= 0;n < return_size((char *)s,c) - 1;n++)
		printf("%p %s\n",rbuf[n],rbuf[n]);
	return (rbuf);
}
