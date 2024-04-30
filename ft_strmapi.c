/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:50:33 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/30 15:19:16 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rbuf;
	char			*tmps;
	unsigned int	i;

	if (!s)
		return (NULL);
	rbuf = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!rbuf)
		return (NULL);
	i = 0;
	tmps = (char *)s;
	while (tmps[i])
	{
		rbuf[i] = f(i, tmps[i]);
		i++;
	}
	rbuf[i] = '\0';
	return (rbuf);
}
