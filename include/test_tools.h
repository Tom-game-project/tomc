/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuranak <tmuranak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:19:48 by tmuranak          #+#    #+#             */
/*   Updated: 2025/04/30 19:46:24 by tmuranak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_TOOLS_H
# define TEST_TOOLS_H

/// this file is for debug mode
///
/// function can use while develop even if it forbidden

int	debug_dprintf(\
	int fd, const char *format, ...) __attribute__((format(printf, 2, 3)));

int	debug_getpid(void);

int	debug_getppid(void);

#endif
