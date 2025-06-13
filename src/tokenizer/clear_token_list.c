#include "list.h"
#include "token_data.h"
#include <stdlib.h>

int clear_token_list(t_token_list **lst);

static void clear_token(t_anytype elem)
{
	switch (elem.token->token_type)
	{
		case e_token_type_comment:
			free(elem.token->contents.str);
			break;
			 //           char * not null: 
		case e_token_type_string:  // "string"  char * not null:
			free(elem.token->contents.str);
			break;
		case e_token_type_char:    // 'c'       char * not null:
			break ;
		case e_token_type_word:    // string    char * not null
			free(elem.token->contents.str);
			break;
		case e_token_type_open_brace: //        char * null
			break;
		case e_token_type_close_brace://        char * null
			break;
		case e_token_type_open_paren: //        char * null
			break;
		case e_token_type_close_paren://        char * null
			break;
		case e_token_type_open_bracket://       char * null
			break;
		case e_token_type_close_bracket://      char * null
			break;
		case e_token_type_operator:     //      char * not null;
			break;
		case e_token_type_semi_colon:   //      char * null
			break;
		case e_token_type_colon:        //      char * null
			break;
		case e_token_type_brace:        // {}
			clear_token_list(&elem.token->contents.token_list);
			break;
		case e_token_type_bracket:      // []
			clear_token_list(&elem.token->contents.token_list);
			break;
		case e_token_type_paren:        // ()
			clear_token_list(&elem.token->contents.token_list);
			break;
	}
	free(elem.token);
}

int clear_token_list(t_token_list **lst)
{
	return (void_list_clear(lst, clear_token));
}
