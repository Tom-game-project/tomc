/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:14:50 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 20:06:08 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// compile
// ccw ft_isalnum.c ft_isalpha.c ft_is_digit.c

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_digit(c))
		return (1);
	return (0);
}

//test function
// int	main()
// {
// 	int	a = 'a';
// 	int	b = '1';
// 	int	c = '@';
//     printf("%d",ft_isalnum(a));
//     printf("%d",ft_isalnum(b));
//     printf("%d",ft_isalnum(c));
// 	return (0);
// }