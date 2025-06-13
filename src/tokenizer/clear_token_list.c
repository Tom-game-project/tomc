#include "list.h"
#include "token_data.h"
#include <stdlib.h>
#include <unistd.h>

#include "test_tools.h"

int clear_token_list(t_token_list **lst);

void clear_token(t_token *token)
{
	//char *contents_str;
	//char *token_type_str;
	//t_anytype elem;
        //
        //
	//elem.token = token;
        //
	//get_token_str(elem, &contents_str, &token_type_str);
	//debug_dprintf(STDERR_FILENO, "%s %s \n", token_type_str, contents_str);

	switch (token->token_type)
	{
		case e_token_type_comment: //           char * not null: 
			free(token->contents.str);
			break;
		case e_token_type_string:  // "string"  char * not null:
			free(token->contents.str);
			break;
		case e_token_type_char:    // 'c'       char * not null:
			free(token->contents.str);
			break ;
		case e_token_type_word:    // string    char * not null
			free(token->contents.str);
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
			clear_token_list(&token->contents.token_list);
			break;
		case e_token_type_bracket:      // []
			clear_token_list(&token->contents.token_list);
			break;
		case e_token_type_paren:        // ()
			clear_token_list(&token->contents.token_list);
			break;
	}
	free(token);
}


static void clear_token_wrap(t_anytype elem)
{
	clear_token(elem.token);
}

int clear_token_list(t_token_list **lst)
{
	return (void_list_clear(lst, clear_token_wrap));
}
