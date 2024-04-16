/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:52:56 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 22:23:06 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t			c;
	unsigned char	*d;
	unsigned char	*s;

	c = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (c < n)
	{
		d[c] = s[c];
		c++;
	}
	return (dst);
}

// int main ()
// {
//     char a[6] = "hello\0";
//     char b[6] = "12345\0";

//     ft_memcpy(a,b,3);
//     printf("%s",a);
// }
