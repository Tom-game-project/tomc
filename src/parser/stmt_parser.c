#include "ast.h"
#include "list.h"
#include "token_data.h"
#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"

static bool streq(char *str1, char *str2)
{
	size_t len;

	len = ft_strlen(str1);
	return len == ft_strlen(str2) && ft_strncmp(str1, str2, len) == 0;
}

static bool is_declaration_specifier(t_token token, t_void_list *declaration_specifier_lst)
{
	if (token.token_type == e_token_type_word)
	{
		while (declaration_specifier_lst != NULL)
		{
			
			if (streq(declaration_specifier_lst->ptr.token->contents.str, token.contents.str))
			{
				return true;
			}
			declaration_specifier_lst = declaration_specifier_lst->next;
		}
		return false;
	}
	else
	{
		return false;
	}
}

static int infer_declaration_specifier_index(
	t_void_list *lst, /* token list */
	t_void_list *declaration_specifier_lst /* declaration_specifier_lst */
)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		if (is_declaration_specifier(*lst->ptr.token, declaration_specifier_lst))
		{
			lst = lst->next;
			i += 1;
		}
		else
		{
			break ;
		}
	}
	return i;
}

/// ```bnf
/// <declaration> ::= {<declaration_specifier>}+ {<init_declarator>}* ;
/// ```
///
/// 
/// ```c
/// {<declaration_specifier>}+ = collect_declaration_specifier(&tkn_lst, declaration_specifier_lst);
/// ```
///
t_void_list *collect_declaration_specifier(
	t_void_list **lst, /* token list */
	t_void_list *declaration_specifier_lst /* declaration_specifier_lst */
)
{
	int index;

	index = infer_declaration_specifier_index(*lst, declaration_specifier_lst);
	return void_list_cut(lst, index - 1);
}

