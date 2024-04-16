/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:24:44 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 17:53:09 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_digit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

// test function
// int	main ()
// {
// 	int a = 'a';
// 	int b = '4';
// 	printf("%d",ft_digit(a));
// 	printf("%d",ft_digit(b));
// 	return (0);
// }