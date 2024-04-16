/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:21:32 by tmuranak          #+#    #+#             */
/*   Updated: 2024/04/16 22:16:17 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// test用
# include <stdio.h>

# include <string.h>


int		ft_isalpha(int c);
int		ft_digit(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
size_t	ft_strlen(char *s);
void	*ft_memset(void *buf, int ch, size_t n);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

#endif
