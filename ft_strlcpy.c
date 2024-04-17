/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:36 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/17 12:52:38 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(	char *restrict dst, \
					const char *restrict src, \
					size_t dstsize)
{
	unsigned int	i;
	unsigned int	src_len;
	char			*tmp;

	i = 0;
	src_len = ft_strlen((char *)src);
	tmp = dst;
	while (i < dstsize)
	{
		if (src_len < i)
			dst[i] = '\0';
		else
			dst[i] = src[i];
		i++;
	}
	return (dstsize);
}

//test function
#include <unistd.h>

void	ft_putchar(char a)
{
	write(1, &a, 1);
}

void test(char *a, size_t size)
{
	for (size_t i = 0;i < size;i++)
	{
		if (a[i])
		{
			ft_putchar(a[i]);
		}
		else
		{
			ft_putchar('*');
		}
		ft_putchar(',');
	}
	ft_putchar('\n');
}

int main(){
	char a[6] = "hello\0";
	char c[6] = "hello\0";

	int ar = strlcpy(a,"abc",3);
	int cr = strlcpy(c,"a"  ,1);
	test(a, 6);
	test(c, 6);
	printf("ar %d\n",ar);
	printf("cr %d\n",cr);

	char ft_a[6] = "hello\0";
	char ft_c[6] = "hello\0";
	int ft_ar = strlcpy(ft_a,"abc",3);
	int ft_cr = strlcpy(ft_c,"a"  ,1);
	test(ft_a, 6);
	test(ft_c, 6);
	printf("ar %d\n",ft_ar);
	printf("cr %d\n",ft_cr);	
    return (0);
}