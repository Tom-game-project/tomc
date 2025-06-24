#ifndef AST_H
#define AST_H

#include "token_data.h"
typedef struct s_ast t_ast;

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

typedef struct s_compound_stmt t_compound_stmt;




typedef struct s_decorator t_decorator; // TODO:あとで実装

/// ```bnf
/// <declaration> ::= {<declaration_specifier>}+ {<init_declarator>}* ;
/// ```
struct s_declaration
{
	t_void_list *declaration_specifier;
	t_decorator *init_decorator;
};


///
///
/// ```bnf
/// <statement> ::= <labeled_statement>
///                 <labeled_statement> ::= <identifier> : <statement>
///                                       | case <constant_expression> : <statement>
///                                       | default : <statement>
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
	s_compound_stmt,
	s_expr_stmt,
    } type_of_expr;
    union {

    } contents;
};

struct s_compound_stmt
{
	// declaration または statementを格納するリスト
	t_void_list *lst; // Vec<declaration|statement>
};

#endif
