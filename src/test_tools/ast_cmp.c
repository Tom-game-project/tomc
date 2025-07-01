#include "ast.h"
#include "libft.h"
#include "list.h"
#include "token_data.h"
#include <stdbool.h>
#include <string.h>

bool token_list_eq(t_token_list *lst1, t_token_list *lst2);

bool token_eq(t_token *token1, t_token *token2);

bool expr_eq(t_expr *ast1, t_expr *ast2)
{	
	if (ast1->type_of_expr == ast2->type_of_expr)
	{
		switch (ast1->type_of_expr) {
			case e_expr_token:
				if (!token_eq(ast1->contents.ident, ast2->contents.ident))
					return false;
				break;
			case e_expr_normal:
				if (ast1->contents.normal->ope != ast2->contents.normal->ope)
					return false;
				if (!expr_eq(ast1->contents.normal->right_expr, ast2->contents.normal->right_expr))
					return false;
				if (!expr_eq(ast1->contents.normal->left_expr, ast2->contents.normal->left_expr))
					return false;
				break;
			case e_expr_unary:
				if (ast1->contents.unary->ope != ast2->contents.unary->ope)
					return false;
				if (!expr_eq(ast1->contents.unary->right_expr, ast2->contents.unary->right_expr))
					return false;
				break;
			case e_expr_postfix:
				if (ast1->contents.postfix->ope != ast2->contents.postfix->ope)
					return false;
				if (!expr_eq(ast1->contents.postfix->right_expr, ast2->contents.postfix->right_expr))
					return false;
				if (!expr_eq(ast1->contents.postfix->left_expr, ast2->contents.postfix->left_expr))
					return false;
				break;
			case e_expr_cast:
				// TODO: cast typeが同等のものかを比較できる関数を作成する
				if (!expr_eq(ast1->contents.cast->inner_expr, ast2->contents.cast->inner_expr))
					return false;
				break;
		}
	}
	else 
	{
		return false;
	}
	return true;
}

/// if list has same contents this function return true otherwise false.
bool token_list_eq(t_token_list *lst1, t_token_list *lst2)
{
	while (lst1 != NULL && lst2 != NULL)
	{
		if (!token_eq(lst1->ptr.token, lst2->ptr.token))
		{
			return false;
		}
		lst1 = lst1->next;
		lst2 = lst2->next;
	}
	return lst1 == NULL && lst2 == NULL;
}

bool token_eq(t_token *token1, t_token *token2)
{
	if (token1->token_type != token2->token_type)
		return false;
	switch (token1->token_type)
	{
		case e_token_type_comment: //           char * not null: 
		case e_token_type_string:  // "string"  char * not null:
		case e_token_type_char:    // 'c'       char * not null:
			return ft_streq(token1->contents.str, token2->contents.str);
		case e_token_type_word:    // string    char * not null
			return ft_streq(token1->contents.str, token2->contents.str);
		case e_token_type_open_brace: //        char * null
		case e_token_type_close_brace://        char * null
		case e_token_type_open_paren: //        char * null
		case e_token_type_close_paren://        char * null
		case e_token_type_open_bracket://       char * null
		case e_token_type_close_bracket://      char * null
		case e_token_type_semi_colon:   //      char * null
		case e_token_type_colon:        //      char * null
			break;
		case e_token_type_operator:     //      char * not null;
			return token1->contents.ope == token2->contents.ope;
		case e_token_type_brace:        // {}
		case e_token_type_bracket:      // []
		case e_token_type_paren:        // ()
			return token_list_eq(
						token1->contents.token_list, 
						token2->contents.token_list			
			);
	}
	return true;
}
