/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:04:47 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/17 18:53:29 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t			c;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	c = 0;
	while (c < n)
	{
		if (src < dst)
			d[n - c - 1] = s[n - c - 1];
		else
			d[c] = s[c];
		c++;
	}
	return (dst);
}
