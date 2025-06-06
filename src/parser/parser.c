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

t_expr *parse_cast_expression(t_void_list **lst);

t_expr *abstract_parse_operator( // 中置演算用
	t_void_list **lst,
	int (*search_func)(t_void_list *), /* seatch function */
	t_expr *(*notfound_func)(t_void_list **), /* もし何も見つからなかった場合の関数 */
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

static bool is_cast_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	return (token->token_type == e_token_type_paren);
}

static bool is_pre_incr_decr_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return
			token->contents.ope == e_operator_incr || \
			token->contents.ope == e_operator_decr;
}

static bool is_unary_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return (false);
	else
		return
			token->contents.ope == e_operator_addr ||
			token->contents.ope == e_operator_mul ||
			token->contents.ope == e_operator_add ||
			token->contents.ope == e_operator_sub ||
			token->contents.ope == e_operator_not; // TODO
							       // 演算子を網羅しきれていない
}

/* ===================================================== */

/// 右優先
static int 
search_assignment_operator_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index(lst, resolve_anytype, is_assignment_operator);
}

static int
search_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_or_operator);
}

static int
search_and_operator_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_and_operator);
}


static int search_inclusive_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_inclusive_or_operator);
}

static int search_exclusive_or_operator_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_exclusive_or_operator);
}

static int search_logical_and_operator_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_logical_and_operator);
}

static int search_equality_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_equality_operator);
}

static int search_relational_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_relational_operator);
}

static int search_shift_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_shift_operator);
}

static int search_additive_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_additive_operator);
}

static int search_multiplicative_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index_r(lst, resolve_anytype, is_multiplicative_operator);
}

/// 右優先
static int search_cast_index(
	t_void_list *lst /* token list */
)
{
	return void_list_search_index(lst, resolve_anytype, is_cast_operator);
}

/// 前置`++` `--`を先頭に見つけたとき
static bool has_pre_incr_decr(
	t_void_list *lst /* token list */
)
{
	return  void_list_search_index(lst, resolve_anytype, is_pre_incr_decr_operator) == 0;
}

/// `cast operation`を先頭に見つけたとき
static bool has_unary_operator(
	t_void_list *lst /* token list */
)
{
	return  void_list_search_index(lst, resolve_anytype, is_unary_operator) == 0;
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
		return NULL;
	}
}

/* ============== for debug function ==============<<< */

/// ```bnf
/// <unary_expression> ::= <postfix_expression>
///                      | ++ <unary_expression>
///                      | -- <unary_expression>
///                      | <unary_operator> <cast_expression>
///                      | sizeof <unary_expression>
///                      | sizeof <type_name>
///
/// <unary_operator> ::= &
///                    | *
///                    | +
///                    | -
///                    | ~
///                    | !
///  
/// ```
///
/// 問題になりがちなのは、`cast_expression` とりあえずここを飛ばして実装する
t_expr *parse_unary_expression(t_void_list **lst)
{
	// pre incr decr
	if (has_pre_incr_decr(*lst)) // 先頭が`++` `--`だった場合
					  //
	{
		t_unary_expr *unary_expr;
		t_expr *expr;
		t_anytype ope_token;

		unary_expr = (t_unary_expr *)malloc(sizeof(t_unary_expr));
		expr = (t_expr *)malloc(sizeof(t_expr));
		expr->type_of_expr = e_expr_unary;
		void_list_pop(lst, 0, &ope_token);
		unary_expr->ope = ope_token.token->contents.ope;
		unary_expr->right_expr = parse_unary_expression(lst);
		free(ope_token.token);
		expr->contents.unary = unary_expr;
		return expr;
	}
	else if (has_unary_operator(*lst)) // normal unary_operator 
	{
		t_unary_expr *unary_expr;
		t_expr *expr;
		t_anytype ope_token;

		unary_expr = (t_unary_expr *)malloc(sizeof(t_unary_expr));
		expr = (t_expr *)malloc(sizeof(t_expr));
		expr->type_of_expr = e_expr_unary;
		void_list_pop(lst, 0, &ope_token);
		unary_expr->ope = ope_token.token->contents.ope;
		unary_expr->right_expr = parse_cast_expression(lst);
		free(ope_token.token);
		expr->contents.unary = unary_expr;
		return expr;
	}
	// TODO :sizeof

	// unaryとして解釈される文法構造が見つからなかった場合
	// postfix_expressionの処理に移る
	return parse_ident_operator(lst);
}

/// TODO: キャスト変換は一旦飛ばして実装を進める
/// ```bnf
/// <cast_expression> ::= <unary_expression>
///                     | ( <type_name> ) <cast_expression>
/// ```
t_expr *parse_cast_expression(t_void_list **lst)
{
	int index = search_cast_index(*lst);

	if (index == 0) // 一番最初にみつかったら
	{
		return NULL; // TODO タイプのパースは後で実装する
	}
	else
	{
		t_expr *expr;

		expr = parse_unary_expression(lst);
		return expr;
	}
}

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
		parse_cast_expression,
		parse_multiplicative_operator,
		parse_cast_expression
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
	if (index == -1 || index == 0)
	{
		return notfound_func(lst);
	}
	else if (
		void_list_get_elem(*lst, index - 1)->ptr.token->token_type == e_token_type_operator)
		//(void_list_get_elem(*lst, index - 1))
	{
		return notfound_func(lst);
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
		//if (normal_expr->ope == e_operator_mul)
		//{
		//	debug_dprintf(STDERR_FILENO, "helloooo::log (index) %d \n", index);
		//}
		free(ope_token.token);
		normal_expr->left_expr = left_parse_func(&left_list);
		normal_expr->right_expr = right_parse_func(&right_list);
		expr->type_of_expr = e_expr_normal;
		expr->contents.normal = normal_expr;
		return expr;
	}
}

