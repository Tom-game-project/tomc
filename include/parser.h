#ifndef PARSER_H
#define PARSER_H


///
/// コメント
///
/// 変数宣言
/// 宣言
///
/// 関数宣言
///
/// ```
///
/// func_call = func_name(<expr>, ...)
///
/// ope = "+" | "-" | "*" | "/"
///
/// value =
///     | 0x0123456789abcdefABCDEF
///     | 0123456789
///     | 0b01
///
/// expr = 
///     | <expr> <ope> <expr>
///     | <ope> <expr>
///     | <func_call>
///     | ( <expr> )
///     |
/// 
/// - prefix
/// ```
///
/// 右優先,左優先の違い
/// 掛け算 -> 左優先: a * b * c -> (a * b) * c
/// n乘 -> 右優先: a ** b ** c -> a ** (b ** c)
///
/// *   *   *   a
/// ptr(ptr(ptr(a)))
///
/// ```
/// int c = *a * *b;
///         ptr(a) * ptr(b)
///
///
/// ポインタとしての`*`は掛け算としての`*`より優先順位が高い
/// よって先にまとめるのは掛け算の方
///
/// 弱いものから順番
///
/// ```



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

#endif
