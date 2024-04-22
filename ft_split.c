/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:19:21 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/22 15:15:52 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static unsigned int	char_counter(char *s, char c)
{
	unsigned int	counter;

	counter = 0;
	while (*s)
	{
		if (*s == c)
			counter++;
		s++;
	}
	return (counter);
}

static int	my_strchr(const char *s, int c)
{
	char	*tmps;
	int		i;

	tmps = (char *)s;
	i = 0;
	while (*tmps)
	{
		if (*tmps == c)
			return (i + 1);
		tmps++;
		i++;
	}
	if (!c)
		return (i);
	return (i + 1);
}

static char	*helper(char *s, int len)
{
	char	*rbuf;
	int		i;

	rbuf = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (i < len - 1)
	{
		rbuf[i] = s[i];
		i++;
	}
	rbuf[i] = '\0';
	return (rbuf);
}

char	**ft_split(char const *s, char c)
{
	char		**rbuf;
	char		*strtmp;
	int			step;
	size_t		i;

	rbuf = (char **)malloc(sizeof(char *) \
						* (char_counter((char *)s, c) + 1 + 1));
	if (!rbuf)
		return (NULL);
	strtmp = (char *)s;
	i = 0;
    while (i < char_counter((char *)s, c) + 1)
	{
		printf("step: %c\n", *strtmp);
		step = my_strchr(strtmp, c);
		printf("step: %d %c\n", step, *strtmp);
		rbuf[i] = helper(strtmp, step);
		printf("%s\n", rbuf[i]);
		strtmp += step;
		i++;
	}
	rbuf[i] = NULL;
	return (rbuf);
}
