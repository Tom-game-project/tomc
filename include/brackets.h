#ifndef BRACKETS_H
#define BRACKETS_H

#include "list.h"

int
group_paren(
	t_void_list **lst,
	t_token_type token_type_open,
	t_token_type token_type_close,
	t_token_type token_type_name
);

#endif
