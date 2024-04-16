/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:11:51 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 13:21:01 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//test module
#include <stdio.h>

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	else
		return (0);
}

// test function
int main()
{
    char a = 'a';
    printf("%d",ft_isalpha(a));
}