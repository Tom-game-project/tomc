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

#include "list.h"

int	debug_dprintf(\
	int fd, const char *format, ...) __attribute__((format(printf, 2, 3)));

int	debug_getpid(void);

int	debug_getppid(void);

int print_token_list_ln(t_token_list *token_list);

char *print_operator_as_string(t_operator operator);

void get_token_str(t_anytype token, 
	char **contents_str,
	char **token_type_str
);

#include "ast.h"
int print_expr_ast(t_expr *expr_ast, int depth);

bool expr_eq(t_expr *ast1, t_expr *ast2);

#endif
