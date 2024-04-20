/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:24:52 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/20 21:56:53 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	char	*tmp1;
	char	*tmp2;
	int		i;

	tmp1 = (char *) s1;
	tmp2 = (char *) s2;
	buf = malloc((ft_strlen(tmp1) + ft_strlen(tmp2) + 1) * sizeof(char));
	i = 0;
	while (*tmp1)
		*(buf + i++) = *tmp1++;
	while (*tmp2)
		*(buf + i++) = *tmp2++;
	*(buf + i) = '\0';
	return (buf);
}
