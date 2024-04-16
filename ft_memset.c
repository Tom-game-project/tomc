/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:52:07 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 16:28:55 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>


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

// int main()
// {
//     char a[] = "hello world";
//     char b[] = "hello world";
//     char *or = memset   (b + 2,'1',3);
//     char *ft = ft_memset(a + 2,'1',3);
//     printf("%s\n",a);
//     printf("%s\n",b);
//     printf("or %s\n",or);
//     printf("ft %s\n",ft);
// }
