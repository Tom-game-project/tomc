/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:44:41 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 19:19:21 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	c;

	c = 0;
	while (*s)
	{
		c++;
		s++;
	}
	return (c);
}

// int main()
// {
//     char *a = "helloworld";
//     printf("str len;%zu", ft_strlen(a));
// }
