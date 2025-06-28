#ifndef PARSER_H
#define PARSER_H


// ---------- expr parser ----------
#include "list.h"
#include "ast.h"

//<constant> ::= <integer_constant>
//             | <character_constant>
//             | <floating_constant>
//             | <enumeration_constant>
//再帰はこれ以上進まない
//
enum e_constant
{
	e_integer_constant,
	e_character_constant,
	e_floating_constant,
	e_enumeration_constant
};
typedef enum e_constant t_constant;

struct s_constant
{
	t_constant token_type;
	char *str;
};


/// <constant_expression> ::= <conditional_expression>
typedef struct s_constant_expression t_constant_expression;
struct s_constant_expression
{

};

typedef struct s_assignment_expression t_assignment_expression;
struct s_assignment_expression
{

};

/// <expression> ::= <assignment_expression>
///               | <expression> , <assignment_expression>
typedef struct s_expression t_expression;
struct s_expression
{
	t_expression *expression;
	t_assignment_expression *assignment_expression;
};






// t_expr *parse_assignment_operator(t_void_list **lst);

t_expr *parse_expression(t_void_list **lst);

int clear_ast(t_expr *expr);

// ---------- stmt parser ----------
t_void_list *collect_declaration_specifier(
	t_void_list **lst, /* token list */
	t_void_list *declaration_specifier_lst /* declaration_specifier_lst */
);

#endif
