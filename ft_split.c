/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:19:21 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/22 13:12:27 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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

char	**ft_split(char const *s, char c)
{
	char			**rbuf;
	char			*unitstr;
	unsigned int	i;
	unsigned int	counter;

	rbuf = (char **)malloc(sizeof(char *) * (char_counter((char *)s, c) + 1));
	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
            unitstr = (char *)malloc(sizeof(char) * (counter + 1));
			while (counter != 0)
			{
				unitstr[counter] = s[i - counter];
				printf("%c\n",s[i - counter]);
				counter--;
			}
			*rbuf = unitstr;
			rbuf++;
			counter = 0;
		}
		i++;
		counter++;
	}
	return (rbuf);
}
