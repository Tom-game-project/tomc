#include "ast2.h"
#include "list.h"
#include "token_data.h"
#include "test_tools.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

t_expr *expr_parser(t_void_list **data);
t_expr *parse_assignment_operator(t_void_list **lst);
t_expr *parse_or_operator(t_void_list **lst);
t_expr *parse_and_operator(t_void_list **lst);

static bool resolve_anytype(t_anytype elem, bool (*f)(void *))
{
	return (f(elem.token));
}

static bool is_assignment_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else 
		return
			token->contents.ope == e_operator_assignment || \
			token->contents.ope == e_operator_add_assignment|| \
			token->contents.ope == e_operator_sub_assignment|| \
			token->contents.ope == e_operator_mul_assignment|| \
			token->contents.ope == e_operator_div_assignment|| \
			token->contents.ope == e_operator_bitshift_right_assignment|| \
			token->contents.ope == e_operator_bitshift_left_assignment|| \
			token->contents.ope == e_operator_and_assignment || \
			token->contents.ope == e_operator_or_assignment || \
			token->contents.ope == e_operator_not_assignment || \
			token->contents.ope == e_operator_xor_assignment;
}

static bool is_or_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return (token->contents.ope == e_operator_or);
}

static bool is_and_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return (token->contents.ope == e_operator_and);
}

/// return index of assignment operation
/// priority: right
///
/// a = (b = (c = d))
///
/// 最初に見つかる代入演算子を返却する
int 
search_assignment_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index(lst, resolve_anytype, is_assignment_operator));
}


/// return index of `||` operation
/// priority: right
///
/// ((a || b) || c)
///
/// 最後に見つかる代入演算子を返却する
int
search_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_or_operator));
}

/// return index of `&&` operation
/// priority: right
///
/// ((a && b) && c)
///
/// 最後に見つかる代入演算子を返却する
int
search_and_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_and_operator));
}


/* ============== for debug function ==============>>> */

/// TODO 仮置きの関数
t_expr *parse_ident_operator(t_void_list **lst)
{
	t_expr *expr;
	t_anytype elem;

	if (0 < void_list_len(*lst))
	{
		expr = (t_expr*) malloc(sizeof(t_token));
		expr->type_of_expr = e_expr_token;
		void_list_pop(lst, 0, &elem);
		expr->contents.ident = elem.token;
		return expr;
	}
	else
	{
		return (NULL);
	}
}


/* ============== for debug function ==============<<< */


t_expr *abstract_parse_operator( // 中置演算用
	t_void_list **lst,
	int (*search_func)(t_void_list *), /* seatch function */
	t_expr *(*notfound_func)(t_void_list **),
	t_expr *(*left_parse_func)(t_void_list **), /* */
	t_expr *(*right_parse_func)(t_void_list **) /* */
)
{
	t_expr *expr;
	t_normal_expr *normal_expr;

	int index = search_func(*lst);
	if (index == -1)
	{ 
		return (notfound_func(lst));
	}
	else
	{
		t_void_list *left_list;
		t_void_list *right_list;
		t_anytype ope_token;

		expr = malloc(sizeof(t_expr));
		normal_expr = malloc(sizeof(t_normal_expr));
		left_list = void_list_cut(lst, index - 1);
		void_list_pop(lst, 0, &ope_token);
		right_list = *lst;

		normal_expr->ope = ope_token.token->contents.ope;
		free(ope_token.token);
		normal_expr->left_expr = left_parse_func(&left_list);
		normal_expr->right_expr = right_parse_func(&right_list);

		expr->type_of_expr = e_expr_normal;
		expr->contents.normal = normal_expr;
		return expr;
	}
}


t_expr *parse_and_operator(t_void_list **lst)
{
	return abstract_parse_operator(
		lst,
		search_and_operator_index, 
		parse_ident_operator,
		parse_and_operator,
		parse_ident_operator
	);
}

t_expr *parse_or_operator(t_void_list **lst)
{
	return abstract_parse_operator(
		lst,
		search_or_operator_index,
		parse_and_operator,
		parse_or_operator,
		parse_and_operator
	);
}

t_expr *parse_assignment_operator(t_void_list **lst)
{
	return abstract_parse_operator(
		lst,
		search_assignment_operator_index,
		parse_or_operator,
		parse_assignment_operator, // TODO 左側は見直す必要あり
		parse_assignment_operator
	);
}

