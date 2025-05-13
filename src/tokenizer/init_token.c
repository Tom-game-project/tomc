#include "tokenizer.h"
#include <stdlib.h>

t_token *init_token_by_str(
	t_token_type token_type,
	char *str
)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->token_type = token_type;
	token->contents.str = str;
	return (token);
}

t_token *init_token_by_ope(
	t_token_type token_type,
	t_operator ope
)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->token_type = token_type;
	token->contents.ope = ope;
	return (token);
}
