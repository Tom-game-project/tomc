/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:06:45 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/27 20:45:49 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rbuf;
	int		buf_size;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	buf_size = count * size;
	rbuf = malloc(buf_size);
	if (rbuf == NULL)
		return (NULL);
	ft_bzero(rbuf, buf_size);
	return (rbuf);
}
