/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:10:47 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 16:49:34 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	char	*haystack_tmp;
	char	*needle_tmp;

	if (!haystack)
		return (NULL);
	haystack_tmp = (char *)haystack;
	i = 0;
	if (!*needle)
		return (haystack_tmp);
	while (i < len)
	{
		j = 0;
		needle_tmp = (char *)needle;
		while (needle_tmp[j])
		{
			if (haystack_tmp[i + j] != needle_tmp[j])
				break ;
			j++;
		}
		if (needle_tmp[j] == '\0' && i + j <= len)
			return (haystack_tmp + i);
		i++;
	}
	return (NULL);
}
