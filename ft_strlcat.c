/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:08:51 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 11:18:30 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat( char *restrict dst, \
					const char *restrict src, \
					size_t dstsize)
{
	size_t				i;
	int					flag;
	unsigned char		*srctmp;

	srctmp = (unsigned char *)src;
	i = 0;
	flag = 0;
	while (*dst){
		i++;
        dst++;    
    }
	while (*srctmp)
	{
		if (i < dstsize - 1)
			*dst = *srctmp;
		else if (flag == 0)
		{
			flag = 1;
			*dst = '\0';
		}
		srctmp++;
		i++;
        dst++;
	}
	return (i);
}

int main ()
{
    char a[6] = "hello\0";
    char b[6] = "world\0";
    int ar = strlcat(a,b,sizeof(a));
    printf("result a:%s :%d\n",a,ar);

    char c[11] = "hello\0";
    char d[6] = "world\0";
    int cr = strlcat(c,d,sizeof(c));
    printf("result c:%s :%d\n",c,cr);

    char e[6] = "hello\0";
    char f[6] = "world\0";
    int fr = ft_strlcat(e,f,sizeof(e));
    printf("result a:%s :%d\n",e,fr);

    char g[11] = "hello\0";
    char h[6] = "world\0";
    int hr = ft_strlcat(g,h,sizeof(g));
    printf("result c:%s :%d\n",g,hr);

    return (0);
}