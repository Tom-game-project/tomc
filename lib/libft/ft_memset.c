/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:52:07 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 21:40:51 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t	c;
	char	*str;

	c = 0;
	str = buf;
	while (c < n)
	{
		str[c] = ch;
		c++;
	}
	return (buf);
}
