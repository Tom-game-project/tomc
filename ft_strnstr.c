/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:10:47 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 16:05:02 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	char	*haystack_tmp;
	char	*needle_tmp;

	haystack_tmp = (char *)haystack;
	i = 0;
	while (i < len)
	{
		j = 0;
		needle_tmp = (char *)needle;
		while (needle_tmp[j])
		{
			if (haystack_tmp[j + j] == '\0')
				return (NULL);
			if (haystack_tmp[i + j] != needle_tmp[j])
				break ;
			j++;
		}
		if (needle_tmp[j] == '\0')
			return (haystack_tmp + i);
		i++;
	}
	return (NULL);
}
