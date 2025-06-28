#ifndef AST_H
#define AST_H

#include "token_data.h"

// typedef struct s_ast t_ast;

typedef struct s_expr t_expr;
typedef struct s_normal_expr t_normal_expr;
typedef struct s_unary_expr t_unary_expr;
typedef struct s_postfix_expr t_postfix_expr;
typedef struct s_cast_expr t_cast_expr;

/// ========== expression ==========
struct s_expr
{
    enum {
        e_expr_normal,
	e_expr_unary,
	e_expr_cast,
	e_expr_postfix,
	e_expr_token, // 文法的にそれ以上解釈不可
    } type_of_expr;
    union  {
	t_normal_expr *normal;
	t_unary_expr *unary;
	t_cast_expr *cast;
	t_postfix_expr *postfix;
	t_token *ident;
    } contents;
};

struct s_normal_expr
{
	t_operator ope;
	t_expr *left_expr;
	t_expr *right_expr;
};

struct s_unary_expr
{
	t_operator ope; // operatorとは限らずcastの場合は更に再帰的に解析
	t_expr *right_expr;
};

struct s_postfix_expr
{
	t_operator ope;
	t_expr *left_expr;
	t_expr *right_expr;
};

// キャストの構造
// NULL or otherwise 
struct s_cast_expr 
{
	t_expr *type_expr; // TODO: タイプを格納する予定
	t_expr *inner_expr;
};

/// ======== statement ========

typedef struct s_stmt t_stmt;
typedef struct s_compound_stmt t_compound_stmt;
typedef struct s_expression_stmt t_expression_stmt;
typedef struct s_jump_stmt t_jump_stmt;
typedef struct s_decorator t_decorator;
typedef struct s_selection_stmt t_selection_stmt;
typedef struct s_iteration_stmt t_iteration_stmt;

/// ```bnf
/// <declaration> ::= {<declaration_specifier>}+ {<init_declarator>}* ;
/// ```
struct s_declaration
{
	t_void_list *declaration_specifier; // 必ず何らかの値を格納
	t_decorator *init_decorator;        // Option<init_declarator>
};

/// ```bnf
/// <statement> ::= <labeled_statement>
///                 <labeled_statement> ::= <identifier> :
///                                       | case <constant_expression> :
///                                       | default :
///               | <expression_statement>
///                 <expression_statement> ::= {<expression>}? ;
///               | <compound_statement>
///                 <compound_statement> ::= { {<declaration>}* {<statement>}* }
///               | <selection_statement>
///                 <selection_statement> ::= if ( <expression> ) <statement>
///                                         | if ( <expression> ) <statement> else <statement>
///                                         | switch ( <expression> ) <statement>
///               | <iteration_statement>
///                 <iteration_statement> ::= while ( <expression> ) <statement>
///                                         | do <statement> while ( <expression> ) ;
///                                         | for ( {<expression>}? ; {<expression>}? ; {<expression>}? ) <statement>
///               | <jump_statement>
///                 <jump_statement> ::= goto <identifier> ;
///                                    | continue ;
///                                    | break ;
///                                    | return {<expression>}? ;
/// ```
///
struct s_stmt
{
    enum {
	e_labeled_statement,
	e_compound_stmt,
	e_expr_stmt,
	e_selection_stmt,
	e_iteration_stmt,
	e_jump_stmt
    } type_of_expr;
    union {
	t_compound_stmt *compound_stmt;
	t_expression_stmt *expr_stmt;
	t_iteration_stmt *iteration_stmt;
	t_selection_stmt *selection_stmt;
	t_jump_stmt *jump_stmt_stmt;
    } contents;
};

struct s_compound_stmt
{
	// declaration または statementを格納するリスト
	t_void_list *lst; // Vec<declaration|statement>
};

struct s_expression_stmt
{
	t_expr *expr; // Option<t_expr>
};

/// ```bnf
/// <jump_statement> ::= goto <identifier> ;
///                    | continue ;
///                    | break ;
///                    | return {<expression>}? ;
/// ```
struct s_jump_stmt
{
	enum {
		// e_jump_type_goto,
		e_jump_type_continue,
		e_jump_type_break,
		e_jump_type_return,
	} jump_type;
	t_expr *expr; // Option<t_expr> return のときのみ
	t_stmt * stmt;
	t_stmt * else_stmt;
};

/// ```bnf
/// <selection_statement> ::= if ( <expression> ) <statement>
///                         | if ( <expression> ) <statement> else <statement>
///                         | switch ( <expression> ) <statement>
/// ```
/// TODO:
struct s_selection_stmt{
	enum {
		e_selection_type_if,
		e_selection_type_if_else,
		e_selection_type_switch,
	} selection_type;
	t_expr *expr;
	t_stmt *stmt1;
	t_stmt *stmt2; // Option<t_stmt>
};

/// ```bnf
/// <iteration_statement> ::= while ( <expression> ) <statement>
///                         | do <statement> while ( <expression> ) ;
///                         | for ( {<expression>}? ; {<expression>}? ; {<expression>}? ) <statement>
/// ```
/// TODO: 
struct s_iteration_stmt{
	enum {
		e_iteration_type_while,
		e_iteration_type_do_while,
		e_iteration_type_for,
	} iteration_type;
	t_expr *expr1; // Option<t_expr>
	t_expr *expr2; // Option<t_expr>
	t_expr *expr3; // Option<t_expr>
	t_stmt *stmt;
};

#endif
