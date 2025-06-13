#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "list.h"
#include "token_data.h"

t_token *init_token_by_str(
	t_token_type token_type,
	char *str
);

t_token *init_token_by_ope(
	t_token_type token_type,
	t_operator ope
);

t_token_list *tokenizer(char *str);

int clear_token_list(t_token_list **lst);

#endif
