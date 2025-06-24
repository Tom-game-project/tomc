#include "ast.h"
#include "list.h"
#include "token_data.h"
#include "brackets.h"
#include "tokenizer.h"

#include "test_tools.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

t_expr *parse_expression(t_void_list **lst);
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
	return f(elem.token);
}

static bool is_assignment_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
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
		return false;
	else
		return token->contents.ope == e_operator_or;
}

static bool is_and_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return token->contents.ope == e_operator_and;
}

static bool is_inclusive_or_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return token->contents.ope == e_operator_logic_or; // "|"
}

static bool is_exclusive_or_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return token->contents.ope == e_operator_logic_xor; // "^"
}

static bool is_logical_and_operator(
	t_token *token
)
{
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return token->contents.ope == e_operator_logic_and; // "&"
}

static bool is_equality_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return token->contents.ope == e_operator_eq || token->contents.ope == e_operator_ne;

}

static bool is_relational_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
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
		return false;
	else
		return 
			token->contents.ope == e_operator_bitshift_left || \
			token->contents.ope == e_operator_bitshift_right;
}


static bool is_additive_operator(
	t_token *token
)
{
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return
			token->contents.ope == e_operator_add || \
			token->contents.ope == e_operator_sub;
}


static bool is_multiplicative_operator(t_token *token)
{
	if (token->token_type != e_token_type_operator)
		return false;
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
	return token->token_type == e_token_type_paren;
}

static bool is_pre_incr_decr_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
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
		return false;
	else
		return
			token->contents.ope == e_operator_addr ||
			token->contents.ope == e_operator_mul ||
			token->contents.ope == e_operator_add ||
			token->contents.ope == e_operator_sub ||
			token->contents.ope == e_operator_not; // TODO
							       // 演算子を網羅しきれていない
}


static bool is_postfix_operator(t_token *token)
{

	if (token->token_type == e_token_type_paren|| token->token_type == e_token_type_bracket)
	{
		return true;
	}
	else if (token->token_type == e_token_type_operator)
	{
		return 
			token->contents.ope == e_operator_arrow || 
			token->contents.ope == e_operator_dot ||
			token->contents.ope == e_operator_incr || 
			token->contents.ope == e_operator_decr;
	}
	else
	{
		return false;
	}
}

static bool is_comma_operator(void *data)
{
	t_token *token;

	token = (t_token *) data;
	if (token->token_type != e_token_type_operator)
		return false;
	else
		return
			token->contents.ope == e_operator_comma;
}

/* ===================================================== */

int search_context_operation_index(t_void_list *node, bool (*f)(t_token *))
{
	int i;
	t_void_list *pre_node;

	i = 0;
	pre_node = NULL;
	while (node != NULL)
	{
		if (f(node->ptr.token))
		{
			if (pre_node == NULL)
			{
			}
			if (pre_node->ptr.token->token_type != e_token_type_operator)
				return i;
		}
		pre_node = node;
		node = node->next;
		i += 1;
	}
	return -1;
}

int search_context_operation_index_r(t_void_list *node, bool (*f)(t_token *))
{
	int	i;
	int	rindex;
	t_void_list *pre_node;

	i = 0;
	rindex = -1;
	pre_node = NULL;
	while (node != NULL)
	{
		if (f(node->ptr.token))
		{
			if (pre_node == NULL)
			{
			}
			else if (pre_node->ptr.token->token_type != e_token_type_operator)
			{
				rindex = i;
			}
		}
		pre_node = node;
		node = node->next;
		i += 1;
	}
	return rindex;
}

/// castとして判定するために十分なコンテクストの条件を満たしている場所を探す
int search_context_cast_index(t_void_list *node)
{
	int i;
	t_void_list *post_node;

	i = 0;
	while (node != NULL)
	{
		post_node = node->next;
		if (is_cast_operator(node->ptr.token))
		{
			if (post_node == NULL)
			{
			}
			else if (post_node->ptr.token->token_type != e_token_type_operator)
				return i;
		}
		node = node->next;
		i += 1;
	}
	return -1;
}


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
	return search_context_operation_index_r(lst, is_logical_and_operator);
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
	return search_context_operation_index_r(lst, is_additive_operator);
}

static int search_multiplicative_index(
	t_void_list *lst /* token list */
)
{
	return search_context_operation_index_r(lst, is_multiplicative_operator);
}

/// 右優先
//static int search_cast_index(
//	t_void_list *lst /* token list */
//)
//{
//
//	return void_list_search_index(lst, resolve_anytype, is_cast_operator);
//}

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

static int search_postfix_operator(t_void_list *lst)
{
	return search_context_operation_index_r(lst, is_postfix_operator);
}

static int search_comma_operator(t_void_list *lst)
{
	return void_list_search_index(lst, resolve_anytype, is_comma_operator);
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

/// <primary_expression> ::= <identifier>
///                        | <constant>
///                        | <string>
///                        | ( <expression> )
/// TODO 仮置きの関数
t_expr *parse_primary_expression(t_void_list **lst)
{
	t_expr *expr;
	t_anytype elem;
	int token_list_length;

	token_list_length = void_list_len(*lst);
	if (0 < token_list_length)
	{
		void_list_pop(lst, 0, &elem);
		if (elem.token->token_type == e_token_type_paren)
		{
			/// | ( <expression> )
			expr = parse_expression(&elem.token->contents.token_list);
			//expr->type_of_expr = e_expr_token; // TODO おそらくタイプが違う
			//clear_token_list(&elem.token->contents.token_list);
			free(elem.token);
		}
		else
		{
			expr = (t_expr*) malloc(sizeof(t_expr));
			expr->type_of_expr = e_expr_token;
			expr->contents.ident = elem.token;
		}
		return expr;
	}
	else
	{
		return NULL;
	}
}

/// 
/// ```bnf
/// <postfix_expression> ::= <primary_expression>
///                        | <postfix_expression> [ <expression> ]
///                        | <postfix_expression> ( {<assignment_expression>}* )      // 関数
///                        | <postfix_expression> . <identifier>
///                        | <postfix_expression> -> <identifier>
///                        | <postfix_expression> ++
///                        | <postfix_expression> --
/// ```
/// TODO 実装していない機能あり
t_expr *parse_postfix_expression(t_void_list **lst)
{
	int index;
	t_expr *expr;

	index = search_postfix_operator(*lst);
	if (index != -1) //postfix として解釈できる演算子が見つかった
	{
		t_anytype ope_token;
		t_void_list *left_list;
		t_void_list *right_list;
		t_postfix_expr *postfix_expr;

		left_list = void_list_cut(lst, index - 1);
		void_list_pop(lst, 0, &ope_token);
		right_list = *lst;

		if (ope_token.token->token_type == e_token_type_paren)
		{
			// 関数呼び出しなど
			// | <postfix_expression> ( {<assignment_expression>}* )
			expr = (t_expr *) malloc(sizeof(t_expr));
			postfix_expr = (t_postfix_expr *)malloc(sizeof(t_postfix_expr));
			expr->type_of_expr = e_expr_postfix;
			postfix_expr->ope = e_operator_funccall;
			postfix_expr->left_expr = parse_postfix_expression(&left_list);
			postfix_expr->right_expr = parse_expression(&ope_token.token->contents.token_list);
			expr->contents.postfix = postfix_expr;
			free(ope_token.token);
			return expr;
		}
		else if (ope_token.token->token_type == e_token_type_bracket)
		{
			// 配列アクセスなど
			// | <postfix_expression> [ <expression> ]
			expr = (t_expr *) malloc(sizeof(t_expr));

			postfix_expr = (t_postfix_expr *)malloc(sizeof(t_postfix_expr));
			expr->type_of_expr = e_expr_postfix;
			postfix_expr->ope =  e_operator_arr_index_access;
			postfix_expr->left_expr = parse_postfix_expression(&left_list);
			postfix_expr->right_expr = parse_expression(&ope_token.token->contents.token_list);
			expr->contents.postfix = postfix_expr;
			// ここで、right_lstの長さが0であることを確かめたい
			free(ope_token.token);
			return expr;
		}
		else if (ope_token.token->token_type == e_token_type_operator)
		{
			// 構造体アクセスなど
			// | <postfix_expression> . <identifier>
			// | <postfix_expression> -> <identifier>
			expr = (t_expr *) malloc(sizeof(t_expr));

			postfix_expr = (t_postfix_expr *)malloc(sizeof(t_postfix_expr));
			expr->type_of_expr = e_expr_postfix;
			postfix_expr->ope = ope_token.token->contents.ope;
			postfix_expr->left_expr = parse_postfix_expression(&left_list);
			postfix_expr->right_expr = parse_ident_operator(&right_list); // TODO
			expr->contents.postfix = postfix_expr;
			clear_token(ope_token.token);
			return expr;
		}
		else if (ope_token.token->token_type == e_token_type_operator)
		{
			// 後置インクリメント、デクリメント TODO
			// | <postfix_expression> ++
			// | <postfix_expression> --
			if (ope_token.token->contents.ope == e_operator_incr)
			{
				//
				//expr = (t_expr *) malloc(sizeof(t_expr));
				//expr->type_of_expr = e_expr_decr;
			}
			else if (ope_token.token->contents.ope == e_operator_decr)
			{
			}
			else 
			{
				// unreachable
				// error 
				return NULL;
			}
		}
		else 
		{
			// unreachable
			// error 
			return NULL;
		}
		return NULL;
	}
	else
	{
		// primary_expression
		expr = parse_primary_expression(lst);
		return expr;
	}
}

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
	return parse_postfix_expression(lst);
}

/// TODO: キャスト変換は一旦飛ばして実装を進める
/// ```bnf
/// <cast_expression> ::= <unary_expression>
///                     | ( <type_name> ) <cast_expression>
/// ```
t_expr *parse_cast_expression(t_void_list **lst)
{
	// int index = search_cast_index(*lst);
	int index = search_context_cast_index(*lst);

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

/// ```bnf
/// <assignment_expression> ::= <conditional_expression>
///                           | <unary_expression> <assignment_operator> <assignment_expression>
///
/// # 未実装
/// <conditional_expression> ::= <logical_or_expression>
///                            | <logical_or_expression> ? <expression> : <conditional_expression>
/// ```
t_expr *parse_assignment_operator(t_void_list **lst)
{
	return abstract_parse_operator(
		lst,
		search_assignment_operator_index,
		parse_or_operator,
		parse_unary_expression,
		parse_assignment_operator
	);
}

/// リスト形式(カンマ区切りの情報)を処理する
t_expr *resolve_comma_list(t_void_list **lst)
{
	t_expr *expr;
	t_normal_expr *normal_expr;
	t_void_list *head;
	int index;

       	index = search_comma_operator(*lst);
	if (index == -1)
	{
		return (parse_assignment_operator(lst));
	}
	expr = (t_expr *) malloc(sizeof(t_expr));
	normal_expr = (t_normal_expr *) malloc(sizeof(t_normal_expr));
	expr->type_of_expr = e_expr_normal;
	head = void_list_cut(lst, index);
	normal_expr->ope = e_operator_comma;
	normal_expr->left_expr = parse_assignment_operator(&head);
	normal_expr->right_expr = resolve_comma_list(lst);
	expr->contents.normal = normal_expr;
	return expr;
}

/// ```bnf
/// <expression> ::= <assignment_expression>
///                | <expression> , <assignment_expression>
/// ```
t_expr *parse_expression(t_void_list **lst)
{
	// 括弧をまとめる
	group_paren(lst, e_token_type_open_paren, e_token_type_close_paren, e_token_type_paren);
	group_paren(lst, e_token_type_open_brace, e_token_type_close_brace, e_token_type_brace);
	group_paren(lst, e_token_type_open_bracket, e_token_type_close_bracket, e_token_type_bracket);
	//return parse_assignment_operator(lst);
	return resolve_comma_list(lst);
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
		free(ope_token.token);
		normal_expr->left_expr = left_parse_func(&left_list);
		normal_expr->right_expr = right_parse_func(&right_list);
		expr->type_of_expr = e_expr_normal;
		expr->contents.normal = normal_expr;
		return expr;
	}
}

