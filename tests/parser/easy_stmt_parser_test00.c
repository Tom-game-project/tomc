#include "list.h"
#include "test_tools.h"
#include "token_data.h"
#include "tokenizer.h"
#include "parser.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

/// ```bnf
/// <storage_class_specifier> ::= auto
///                             | register
///                             | static
///                             | extern
///                             | typedef
/// ```
void set_storage_class_specifier(
	t_token_list **declaration_specifier_lst
)
{
	
	t_token *token;
	t_anytype anytype_token;
	int i;

	char *str[5] = {
		"auto",
		"register",
		"static",
		"extern",
		"typedef" 
	};

	i = 0;
	while (i < 5)
	{
		token = malloc (sizeof(t_token));
		token->token_type = e_token_type_word;
		token->contents.str = ft_strdup(str[i]);
		anytype_token.token = token;
		void_list_push(
			declaration_specifier_lst,
			anytype_token
		);
		i += 1;
	}
}

/// ```bnf
/// <type_specifier> ::= void
///                    | char
///                    | short
///                    | int
///                    | long
///                    | float
///                    | double
///                    | signed
///                    | unsigned
///                    | <struct_or_union_specifier> // TODO
///                    | <enum_specifier>            // TODO
///                    | <typedef_name>              // TODO
/// ```
void set_type_specifier(
	t_token_list **type_specifier_lst
)
{
	t_token *token;
	t_anytype anytype_token;
	int i;

	char *str[9] = {
		"void",
		"char",
		"short",
		"int",
		"long",
		"float",
		"double",
		"signed",
		"unsigned"
	};
	i = 0;
	while (i < 9)
	{
		token = malloc (sizeof(t_token));
		token->token_type = e_token_type_word;
		token->contents.str = ft_strdup(str[i]);
		anytype_token.token = token;
		void_list_push(
			type_specifier_lst,
			anytype_token
		);
		i += 1;
	}
}

/// ```bash
/// make test TEST_FILE=tests/parser/easy_stmt_parser_test00.c
/// ```
///
/// ```bnf
/// <declaration> ::= {<declaration_specifier>}+ {<init_declarator>}* ;
/// ```
int main()
{
	t_token_list *tkn_lst;
	t_token_list *declaration_specifier_lst;
	t_token_list *declaration_specifier;
	
	char *str = "unsigned char *str = \"hello world\";";

	tkn_lst = tokenizer(str);

	// declaration_specifier_lst
	declaration_specifier_lst = NULL;
	set_type_specifier(&declaration_specifier_lst);
	set_storage_class_specifier(&declaration_specifier_lst);

	declaration_specifier = collect_declaration_specifier(&tkn_lst, declaration_specifier_lst);
	debug_dprintf(STDERR_FILENO, "declaration_specifier_lst\n");
	print_token_list_ln(declaration_specifier);
	debug_dprintf(STDERR_FILENO, "init_declarator\n");
	print_token_list_ln(tkn_lst);
	return 0;
}
