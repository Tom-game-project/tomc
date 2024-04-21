/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:21:20 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/21 12:05:44 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// for test
#include <stdio.h>

static unsigned int	size_counter(char const *s1, char const *set)
{
	char			*strtmp;
	unsigned int	counter;

	strtmp = (char *)s1;
	counter = 0;
	while (*strtmp)
	{
		if (!ft_strchr(set, (int)*strtmp))
			break ;
		strtmp++;
	}
	while (*strtmp)
	{
		if (ft_strchr(set, (int)*strtmp))
			break ;
		counter++;
		strtmp++;
	}
	return (counter);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtmp;
	char	*rbuf;
	int		i;

	strtmp = (char *)s1;
	printf("num %d\n", size_counter(s1, set));
	rbuf = (char *) malloc(sizeof(char) * size_counter(s1, set));
	i = 0;
	while (*strtmp)
	{
		if (!ft_strchr(set, (int)*strtmp))
			break ;
		strtmp++;
	}
	while (*strtmp)
	{
		if (ft_strchr(set, (int)*strtmp))
			break ;
		rbuf[i] = *strtmp;
		i++;
		strtmp++;
	}
	return (rbuf);
}
