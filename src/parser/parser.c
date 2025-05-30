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
t_expr *abstract_parse_operator( // 中置演算用
	t_void_list **lst,
	int (*search_func)(t_void_list *), /* seatch function */
	t_expr *(*notfound_func)(t_void_list **),
	t_expr *(*left_parse_func)(t_void_list **), /* */
	t_expr *(*right_parse_func)(t_void_list **) /* */
);

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

static bool is_inclusive_or_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return (token->contents.ope == e_operator_logic_or); // "|"
}

static bool is_exclusive_or_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return (token->contents.ope == e_operator_logic_xor); // "^"
}

static bool is_logical_and_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return (token->contents.ope == e_operator_logic_and); // "&"
}


static bool is_equality_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return (token->contents.ope == e_operator_eq || token->contents.ope == e_operator_ne);

}

static bool is_relational_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return 
			token->contents.ope == e_operator_gt || \
			token->contents.ope == e_operator_ge || \
			token->contents.ope == e_operator_lt || \
			token->contents.ope == e_operator_le;
}

static bool is_shift_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return 
			token->contents.ope == e_operator_bitshift_left || \
			token->contents.ope == e_operator_bitshift_right;
}


static bool is_additive_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return
			token->contents.ope == e_operator_add || \
			token->contents.ope == e_operator_sub;
}


static bool is_multiplicative_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return
			token->contents.ope == e_operator_mul || \
			token->contents.ope == e_operator_div || \
			token->contents.ope == e_operator_mod;
}

/* ===================================================== */


/// 右優先
static int 
search_assignment_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index(lst, resolve_anytype, is_assignment_operator));
}

static int
search_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_or_operator));
}

static int
search_and_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_and_operator));
}


static int search_inclusive_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_inclusive_or_operator));
}

static int search_exclusive_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_exclusive_or_operator));
}

static int search_logical_and_operator_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_logical_and_operator));
}

static int search_equality_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_equality_operator));
}

static int search_relational_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_relational_operator));
}

static int search_shift_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_shift_operator));
}

static int search_additive_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_additive_operator));
}

static int search_multiplicative_index(
	t_void_list *lst /* token list */
)
{
	return (void_list_search_index_r(lst, resolve_anytype, is_multiplicative_operator));
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


/// ```bnf
/// <multiplicative_expression> ::= <cast_expression>
///                               | <multiplicative_expression> * <cast_expression>
///                               | <multiplicative_expression> / <cast_expression>
///                               | <multiplicative_expression> % <cast_expression>
/// ```
t_expr *parse_multiplicative_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_multiplicative_index,
		parse_ident_operator,
		parse_multiplicative_operator,
		parse_ident_operator
	);
}

/// ```bnf
/// <additive_expression> ::= <multiplicative_expression>
///                         | <additive_expression> + <multiplicative_expression>
///                         | <additive_expression> - <multiplicative_expression>
/// ```
t_expr *parse_additive_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_additive_index,
		parse_multiplicative_operator,
		parse_additive_operator,
		parse_multiplicative_operator
	);
}

/// ```bnf
/// <shift_expression> ::= <additive_expression>
///                    | <shift_expression> << <additive_expression>
///                    | <shift_expression> >> <additive_expression>
/// ```
t_expr *parse_shift_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_shift_index,
		parse_additive_operator,
		parse_shift_operator,
		parse_additive_operator
	);
}

/// ```bnf
///<relational_expression> ::= <shift_expression>
///                          | <relational_expression> < <shift_expression>
///                          | <relational_expression> > <shift_expression>
///                          | <relational_expression> <= <shift_expression>
///                          | <relational_expression> >= <shift_expression>
/// ```
t_expr *parse_relational_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_relational_index,
		parse_shift_operator,
		parse_relational_operator,
		parse_shift_operator
	);
}


/// ```bnf
/// <equality_expression> ::= <relational_expression>
///                         | <equality_expression> == <relational_expression>
///                         | <equality_expression> != <relational_expression>
/// ```
t_expr *parse_equality_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_equality_index,
		parse_relational_operator,
		parse_equality_operator,
		parse_relational_operator
	);
}


/// ```bnf
/// <and_expression> ::= <equality_expression>
///                    | <and_expression> & <equality_expression>
/// ```
t_expr *parse_logical_and_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_logical_and_operator_index,
		parse_equality_operator,
		parse_logical_and_operator,
		parse_equality_operator
	);
}

/// ```bnf
/// <exclusive_or_expression> ::= <and_expression>
///                             | <exclusive_or_expression> ^ <and_expression>
/// ```
t_expr *parse_exclusive_or_operator(t_void_list **lst) 
{
	return abstract_parse_operator(
		lst,
		search_exclusive_or_operator_index, 
		parse_logical_and_operator,
		parse_exclusive_or_operator,
		parse_logical_and_operator
	);
}

/// ```bnf
/// <inclusive_or_expression> ::= <exclusive_or_expression>
///                             | <inclusive_or_expression> | <exclusive_or_expression>
/// ```
t_expr *parse_inclusive_or_operator(t_void_list **lst)
{
	return abstract_parse_operator(
		lst,
		search_inclusive_or_operator_index, 
		parse_exclusive_or_operator,
		parse_inclusive_or_operator,
		parse_exclusive_or_operator
	);
}

/// ```bnf
/// <logical_and_expression> ::= <inclusive_or_expression>
///                            | <logical_and_expression> && <inclusive_or_expression>
/// ```
t_expr *parse_and_operator(t_void_list **lst)
{
	return abstract_parse_operator(
		lst,
		search_and_operator_index, 
		parse_inclusive_or_operator,
		parse_and_operator,
		parse_inclusive_or_operator
	);
}

///
/// ```bnf
/// <logical_or_expression> ::= <logical_and_expression>
///                           | <logical_or_expression> || <logical_and_expression>
/// ```
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

/// 
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


/// 中置演算解釈の抽象的な形
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

