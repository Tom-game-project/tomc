#ifndef AST_H
#define AST_H

#include "list.h"

struct s_translation_unit {
    enum {
        e_translation_unit_case_0
    } type_of_contents;

	t_void_list *external_declaration_list; // Vec<external_declaration> Repeat more than 0 times(*)
} t_translation_unit;


struct s_external_declaration {
    enum {
        e_external_declaration_case_0,
        e_external_declaration_case_1
    } type_of_contents;

    union {
        struct s_function_definition * function_definition;
        struct s_declaration * declaration;
    } contents;

} ;


struct s_function_definition {
    enum {
        e_function_definition_case_0
    } type_of_contents;


        struct  {
                t_void_list *declaration_specifier_list; // Vec<declaration_specifier> Repeat more than 0 times(*)
                struct s_declarator * declarator;
                t_void_list *declaration_list; // Vec<declaration> Repeat more than 0 times(*)
                struct s_compound_statement * compound_statement;
        } case_0;

} ;


struct s_declaration_specifier {
    enum {
        e_declaration_specifier_case_0,
        e_declaration_specifier_case_1,
        e_declaration_specifier_case_2
    } type_of_contents;

    union {
        struct s_storage_class_specifier * storage_class_specifier;
        struct s_type_specifier * type_specifier;
        struct s_type_qualifier * type_qualifier;
    } contents;

} ;


struct s_storage_class_specifier {
    enum {
        e_storage_class_specifier_case_0,
        e_storage_class_specifier_case_1,
        e_storage_class_specifier_case_2,
        e_storage_class_specifier_case_3,
        e_storage_class_specifier_case_4
    } type_of_contents;

    union {
        // "auto" TODO
        // "register" TODO
        // "static" TODO
        // "extern" TODO
        // "typedef" TODO
    } contents;

} ;


struct s_type_specifier {
    enum {
        e_type_specifier_case_0,
        e_type_specifier_case_1,
        e_type_specifier_case_2,
        e_type_specifier_case_3,
        e_type_specifier_case_4,
        e_type_specifier_case_5,
        e_type_specifier_case_6,
        e_type_specifier_case_7,
        e_type_specifier_case_8,
        e_type_specifier_case_9,
        e_type_specifier_case_10,
        e_type_specifier_case_11
    } type_of_contents;

    union {
        // "void" TODO
        // "char" TODO
        // "short" TODO
        // "int" TODO
        // "long" TODO
        // "float" TODO
        // "double" TODO
        // "signed" TODO
        // "unsigned" TODO
        struct s_struct_or_union_specifier * struct_or_union_specifier;
        struct s_enum_specifier * enum_specifier;
        struct s_typedef_name * typedef_name;
    } contents;

} ;


struct s_struct_or_union_specifier {
    enum {
        e_struct_or_union_specifier_case_0,
        e_struct_or_union_specifier_case_1,
        e_struct_or_union_specifier_case_2
    } type_of_contents;

    union {
        
        struct  {
                struct s_struct_or_union * struct_or_union;
                struct s_identifier * identifier;
                // "{" TODO
                t_void_list *struct_declaration_list; // Vec<struct_declaration> Repeat one or more times(+)
                // "}" TODO
        } case_0;

        
        struct  {
                struct s_struct_or_union * struct_or_union;
                // "{" TODO
                t_void_list *struct_declaration_list; // Vec<struct_declaration> Repeat one or more times(+)
                // "}" TODO
        } case_1;

        
        struct  {
                struct s_struct_or_union * struct_or_union;
                struct s_identifier * identifier;
        } case_2;

    } contents;

} ;


struct s_struct_or_union {
    enum {
        e_struct_or_union_case_0,
        e_struct_or_union_case_1
    } type_of_contents;

    union {
        // "struct" TODO
        // "union" TODO
    } contents;

} ;


struct s_struct_declaration {
    enum {
        e_struct_declaration_case_0
    } type_of_contents;


        struct  {
                t_void_list *specifier_qualifier_list; // Vec<specifier_qualifier> Repeat more than 0 times(*)
                struct s_struct_declarator_list * struct_declarator_list;
        } case_0;

} ;


struct s_specifier_qualifier {
    enum {
        e_specifier_qualifier_case_0,
        e_specifier_qualifier_case_1
    } type_of_contents;

    union {
        struct s_type_specifier * type_specifier;
        struct s_type_qualifier * type_qualifier;
    } contents;

} ;


struct s_struct_declarator_list {
    enum {
        e_struct_declarator_list_case_0,
        e_struct_declarator_list_case_1
    } type_of_contents;

    union {
        struct s_struct_declarator * struct_declarator;
        
        struct  {
                struct s_struct_declarator_list * struct_declarator_list;
                // "," TODO
                struct s_struct_declarator * struct_declarator;
        } case_1;

    } contents;

} ;


struct s_struct_declarator {
    enum {
        e_struct_declarator_case_0,
        e_struct_declarator_case_1,
        e_struct_declarator_case_2
    } type_of_contents;

    union {
        struct s_declarator * declarator;
        
        struct  {
                struct s_declarator * declarator;
                // ":" TODO
                struct s_constant_expression * constant_expression;
        } case_1;

        
        struct  {
                // ":" TODO
                struct s_constant_expression * constant_expression;
        } case_2;

    } contents;

} ;


struct s_declarator {
    enum {
        e_declarator_case_0
    } type_of_contents;


        struct  {
                struct s_pointer * pointer; // ?
                struct s_direct_declarator * direct_declarator;
        } case_0;

} ;


struct s_pointer {
    enum {
        e_pointer_case_0
    } type_of_contents;


        struct  {
                // "*" TODO
                t_void_list *type_qualifier_list; // Vec<type_qualifier> Repeat more than 0 times(*)
                struct s_pointer * pointer; // ?
        } case_0;

} ;


struct s_type_qualifier {
    enum {
        e_type_qualifier_case_0,
        e_type_qualifier_case_1
    } type_of_contents;

    union {
        // "const" TODO
        // "volatile" TODO
    } contents;

} ;


struct s_direct_declarator {
    enum {
        e_direct_declarator_case_0,
        e_direct_declarator_case_1,
        e_direct_declarator_case_2,
        e_direct_declarator_case_3,
        e_direct_declarator_case_4
    } type_of_contents;

    union {
        struct s_identifier * identifier;
        
        struct  {
                // "(" TODO
                struct s_declarator * declarator;
                // ")" TODO
        } case_1;

        
        struct  {
                struct s_direct_declarator * direct_declarator;
                // "[" TODO
                struct s_constant_expression * constant_expression; // ?
                // "]" TODO
        } case_2;

        
        struct  {
                struct s_direct_declarator * direct_declarator;
                // "(" TODO
                struct s_parameter_type_list * parameter_type_list;
                // ")" TODO
        } case_3;

        
        struct  {
                struct s_direct_declarator * direct_declarator;
                // "(" TODO
                t_void_list *identifier_list; // Vec<identifier> Repeat more than 0 times(*)
                // ")" TODO
        } case_4;

    } contents;

} ;


struct s_constant_expression {
    enum {
        e_constant_expression_case_0
    } type_of_contents;

struct s_conditional_expression * conditional_expression;
} ;


struct s_conditional_expression {
    enum {
        e_conditional_expression_case_0,
        e_conditional_expression_case_1
    } type_of_contents;

    union {
        struct s_logical_or_expression * logical_or_expression;
        
        struct  {
                struct s_logical_or_expression * logical_or_expression;
                // "?" TODO
                struct s_expression * expression;
                // ":" TODO
                struct s_conditional_expression * conditional_expression;
        } case_1;

    } contents;

} ;


struct s_logical_or_expression {
    enum {
        e_logical_or_expression_case_0,
        e_logical_or_expression_case_1
    } type_of_contents;

    union {
        struct s_logical_and_expression * logical_and_expression;
        
        struct  {
                struct s_logical_or_expression * logical_or_expression;
                // "||" TODO
                struct s_logical_and_expression * logical_and_expression;
        } case_1;

    } contents;

} ;


struct s_logical_and_expression {
    enum {
        e_logical_and_expression_case_0,
        e_logical_and_expression_case_1
    } type_of_contents;

    union {
        struct s_inclusive_or_expression * inclusive_or_expression;
        
        struct  {
                struct s_logical_and_expression * logical_and_expression;
                // "&&" TODO
                struct s_inclusive_or_expression * inclusive_or_expression;
        } case_1;

    } contents;

} ;


struct s_inclusive_or_expression {
    enum {
        e_inclusive_or_expression_case_0,
        e_inclusive_or_expression_case_1
    } type_of_contents;

    union {
        struct s_exclusive_or_expression * exclusive_or_expression;
        
        struct  {
                struct s_inclusive_or_expression * inclusive_or_expression;
                // "|" TODO
                struct s_exclusive_or_expression * exclusive_or_expression;
        } case_1;

    } contents;

} ;


struct s_exclusive_or_expression {
    enum {
        e_exclusive_or_expression_case_0,
        e_exclusive_or_expression_case_1
    } type_of_contents;

    union {
        struct s_and_expression * and_expression;
        
        struct  {
                struct s_exclusive_or_expression * exclusive_or_expression;
                // "^" TODO
                struct s_and_expression * and_expression;
        } case_1;

    } contents;

} ;


struct s_and_expression {
    enum {
        e_and_expression_case_0,
        e_and_expression_case_1
    } type_of_contents;

    union {
        struct s_equality_expression * equality_expression;
        
        struct  {
                struct s_and_expression * and_expression;
                // "&" TODO
                struct s_equality_expression * equality_expression;
        } case_1;

    } contents;

} ;


struct s_equality_expression {
    enum {
        e_equality_expression_case_0,
        e_equality_expression_case_1,
        e_equality_expression_case_2
    } type_of_contents;

    union {
        struct s_relational_expression * relational_expression;
        
        struct  {
                struct s_equality_expression * equality_expression;
                // "==" TODO
                struct s_relational_expression * relational_expression;
        } case_1;

        
        struct  {
                struct s_equality_expression * equality_expression;
                // "!=" TODO
                struct s_relational_expression * relational_expression;
        } case_2;

    } contents;

} ;


struct s_relational_expression {
    enum {
        e_relational_expression_case_0,
        e_relational_expression_case_1,
        e_relational_expression_case_2,
        e_relational_expression_case_3,
        e_relational_expression_case_4
    } type_of_contents;

    union {
        struct s_shift_expression * shift_expression;
        
        struct  {
                struct s_relational_expression * relational_expression;
                // "<" TODO
                struct s_shift_expression * shift_expression;
        } case_1;

        
        struct  {
                struct s_relational_expression * relational_expression;
                // ">" TODO
                struct s_shift_expression * shift_expression;
        } case_2;

        
        struct  {
                struct s_relational_expression * relational_expression;
                // "<=" TODO
                struct s_shift_expression * shift_expression;
        } case_3;

        
        struct  {
                struct s_relational_expression * relational_expression;
                // ">=" TODO
                struct s_shift_expression * shift_expression;
        } case_4;

    } contents;

} ;


struct s_shift_expression {
    enum {
        e_shift_expression_case_0,
        e_shift_expression_case_1,
        e_shift_expression_case_2
    } type_of_contents;

    union {
        struct s_additive_expression * additive_expression;
        
        struct  {
                struct s_shift_expression * shift_expression;
                // "<<" TODO
                struct s_additive_expression * additive_expression;
        } case_1;

        
        struct  {
                struct s_shift_expression * shift_expression;
                // ">>" TODO
                struct s_additive_expression * additive_expression;
        } case_2;

    } contents;

} ;


struct s_additive_expression {
    enum {
        e_additive_expression_case_0,
        e_additive_expression_case_1,
        e_additive_expression_case_2
    } type_of_contents;

    union {
        struct s_multiplicative_expression * multiplicative_expression;
        
        struct  {
                struct s_additive_expression * additive_expression;
                // "+" TODO
                struct s_multiplicative_expression * multiplicative_expression;
        } case_1;

        
        struct  {
                struct s_additive_expression * additive_expression;
                // "-" TODO
                struct s_multiplicative_expression * multiplicative_expression;
        } case_2;

    } contents;

} ;


struct s_multiplicative_expression {
    enum {
        e_multiplicative_expression_case_0,
        e_multiplicative_expression_case_1,
        e_multiplicative_expression_case_2,
        e_multiplicative_expression_case_3
    } type_of_contents;

    union {
        struct s_cast_expression * cast_expression;
        
        struct  {
                struct s_multiplicative_expression * multiplicative_expression;
                // "*" TODO
                struct s_cast_expression * cast_expression;
        } case_1;

        
        struct  {
                struct s_multiplicative_expression * multiplicative_expression;
                // "/" TODO
                struct s_cast_expression * cast_expression;
        } case_2;

        
        struct  {
                struct s_multiplicative_expression * multiplicative_expression;
                // "%" TODO
                struct s_cast_expression * cast_expression;
        } case_3;

    } contents;

} ;


struct s_cast_expression {
    enum {
        e_cast_expression_case_0,
        e_cast_expression_case_1
    } type_of_contents;

    union {
        struct s_unary_expression * unary_expression;
        
        struct  {
                // "(" TODO
                struct s_type_name * type_name;
                // ")" TODO
                struct s_cast_expression * cast_expression;
        } case_1;

    } contents;

} ;


struct s_unary_expression {
    enum {
        e_unary_expression_case_0,
        e_unary_expression_case_1,
        e_unary_expression_case_2,
        e_unary_expression_case_3,
        e_unary_expression_case_4,
        e_unary_expression_case_5
    } type_of_contents;

    union {
        struct s_postfix_expression * postfix_expression;
        
        struct  {
                // "++" TODO
                struct s_unary_expression * unary_expression;
        } case_1;

        
        struct  {
                // "--" TODO
                struct s_unary_expression * unary_expression;
        } case_2;

        
        struct  {
                struct s_unary_operator * unary_operator;
                struct s_cast_expression * cast_expression;
        } case_3;

        
        struct  {
                // "sizeof" TODO
                struct s_unary_expression * unary_expression;
        } case_4;

        
        struct  {
                // "sizeof" TODO
                struct s_type_name * type_name;
        } case_5;

    } contents;

} ;


struct s_postfix_expression {
    enum {
        e_postfix_expression_case_0,
        e_postfix_expression_case_1,
        e_postfix_expression_case_2,
        e_postfix_expression_case_3,
        e_postfix_expression_case_4,
        e_postfix_expression_case_5,
        e_postfix_expression_case_6
    } type_of_contents;

    union {
        struct s_primary_expression * primary_expression;
        
        struct  {
                struct s_postfix_expression * postfix_expression;
                // "[" TODO
                struct s_expression * expression;
                // "]" TODO
        } case_1;

        
        struct  {
                struct s_postfix_expression * postfix_expression;
                // "(" TODO
                t_void_list *assignment_expression_list; // Vec<assignment_expression> Repeat more than 0 times(*)
                // ")" TODO
        } case_2;

        
        struct  {
                struct s_postfix_expression * postfix_expression;
                // "." TODO
                struct s_identifier * identifier;
        } case_3;

        
        struct  {
                struct s_postfix_expression * postfix_expression;
                // "->" TODO
                struct s_identifier * identifier;
        } case_4;

        
        struct  {
                struct s_postfix_expression * postfix_expression;
                // "++" TODO
        } case_5;

        
        struct  {
                struct s_postfix_expression * postfix_expression;
                // "--" TODO
        } case_6;

    } contents;

} ;


struct s_primary_expression {
    enum {
        e_primary_expression_ident,
        e_primary_expression_constant,
        e_primary_expression_string,
        e_primary_expression_expr
    } type_of_contents;

    union {
        struct s_identifier * identifier;
        struct s_constant * constant;
        struct s_string * string;
        
        struct  {
                // "(" TODO
                struct s_expression * expression;
                // ")" TODO
        } case_3;
    } contents;

} ;


struct s_constant {
    enum {
        e_constant_case_0,
        e_constant_case_1,
        e_constant_case_2,
        e_constant_case_3
    } type_of_contents;

    union {
        struct s_integer_constant * integer_constant;
        struct s_character_constant * character_constant;
        struct s_floating_constant * floating_constant;
        struct s_enumeration_constant * enumeration_constant;
    } contents;

} ;


struct s_expression {
    enum {
        e_expression_case_0,
        e_expression_case_1
    } type_of_contents;

    union {
        struct s_assignment_expression * assignment_expression;
        
        struct  {
                struct s_expression * expression;
                // "," TODO
                struct s_assignment_expression * assignment_expression;
        } case_1;

    } contents;

} ;


struct s_assignment_expression {
    enum {
        e_assignment_expression_case_0,
        e_assignment_expression_case_1
    } type_of_contents;

    union {
        struct s_conditional_expression * conditional_expression;
        
        struct  { // example 
		  // ```c
		  //
		  // *a = 1 + 3;
		  // ```
                struct s_unary_expression * unary_expression;
                struct s_assignment_operator * assignment_operator;
                struct s_assignment_expression * assignment_expression;
        } case_1;

    } contents;

} ;


struct s_assignment_operator {
    enum {
        e_assignment_operator_case_0,
        e_assignment_operator_case_1,
        e_assignment_operator_case_2,
        e_assignment_operator_case_3,
        e_assignment_operator_case_4,
        e_assignment_operator_case_5,
        e_assignment_operator_case_6,
        e_assignment_operator_case_7,
        e_assignment_operator_case_8,
        e_assignment_operator_case_9,
        e_assignment_operator_case_10
    } type_of_contents;

    union {
        // "=" TODO
        // "*=" TODO
        // "/=" TODO
        // "%=" TODO
        // "+=" TODO
        // "_=" TODO
        // "<<=" TODO
        // ">>=" TODO
        // "&=" TODO
        // "^=" TODO
        // "|=" TODO
    } contents;

} ;


struct s_unary_operator {
    enum {
        e_unary_operator_case_0,
        e_unary_operator_case_1,
        e_unary_operator_case_2,
        e_unary_operator_case_3,
        e_unary_operator_case_4,
        e_unary_operator_case_5
    } type_of_contents;

    union {
        // "&" TODO
        // "*" TODO
        // "+" TODO
        // "-" TODO
        // "~" TODO
        // "!" TODO
    } contents;

} ;


struct s_type_name {
    enum {
        e_type_name_case_0
    } type_of_contents;


        struct  {
                t_void_list *specifier_qualifier_list; // Vec<specifier_qualifier> Repeat one or more times(+)
                struct s_abstract_declarator * abstract_declarator; // ?
        } case_0;

} ;


struct s_parameter_type_list {
    enum {
        e_parameter_type_list_case_0,
        e_parameter_type_list_case_1
    } type_of_contents;

    union {
        struct s_parameter_list * parameter_list;
        
        struct  {
                struct s_parameter_list * parameter_list;
                // "," TODO
                // "..." TODO
        } case_1;

    } contents;

} ;


struct s_parameter_list {
    enum {
        e_parameter_list_case_0,
        e_parameter_list_case_1
    } type_of_contents;

    union {
        struct s_parameter_declaration * parameter_declaration;
        
        struct  {
                struct s_parameter_list * parameter_list;
                // "," TODO
                struct s_parameter_declaration * parameter_declaration;
        } case_1;

    } contents;

} ;


struct s_parameter_declaration {
    enum {
        e_parameter_declaration_case_0,
        e_parameter_declaration_case_1,
        e_parameter_declaration_case_2
    } type_of_contents;

    union {
        
        struct  {
                t_void_list *declaration_specifier_list; // Vec<declaration_specifier> Repeat one or more times(+)
                struct s_declarator * declarator;
        } case_0;

        
        struct  {
                t_void_list *declaration_specifier_list; // Vec<declaration_specifier> Repeat one or more times(+)
                struct s_abstract_declarator * abstract_declarator;
        } case_1;

        t_void_list *declaration_specifier_list; // Vec<declaration_specifier> Repeat one or more times(+)
    } contents;

} ;


struct s_abstract_declarator {
    enum {
        e_abstract_declarator_case_0,
        e_abstract_declarator_case_1,
        e_abstract_declarator_case_2
    } type_of_contents;

    union {
        struct s_pointer * pointer;
        
        struct  {
                struct s_pointer * pointer;
                struct s_direct_abstract_declarator * direct_abstract_declarator;
        } case_1;

        struct s_direct_abstract_declarator * direct_abstract_declarator;
    } contents;

} ;


struct s_direct_abstract_declarator {
    enum {
        e_direct_abstract_declarator_case_0,
        e_direct_abstract_declarator_case_1,
        e_direct_abstract_declarator_case_2
    } type_of_contents;

    union {
        
        struct  {
                // "" TODO
                // "(" TODO
                struct s_abstract_declarator * abstract_declarator;
                // ")" TODO
        } case_0;

        
        struct  {
                struct s_direct_abstract_declarator * direct_abstract_declarator; // ?
                // "[" TODO
                struct s_constant_expression * constant_expression; // ?
                // "]" TODO
        } case_1;

        
        struct  {
                struct s_direct_abstract_declarator * direct_abstract_declarator; // ?
                // "(" TODO
                struct s_parameter_type_list * parameter_type_list; // ?
                // ")" TODO
        } case_2;

    } contents;

} ;


struct s_enum_specifier {
    enum {
        e_enum_specifier_case_0,
        e_enum_specifier_case_1,
        e_enum_specifier_case_2
    } type_of_contents;

    union {
        
        struct  {
                // "enum" TODO
                struct s_identifier * identifier;
                // "{" TODO
                struct s_enumerator_list * enumerator_list;
                // "}" TODO
        } case_0;

        
        struct  {
                // "enum" TODO
                // "{" TODO
                struct s_enumerator_list * enumerator_list;
                // "}" TODO
        } case_1;

        
        struct  {
                // "enum" TODO
                struct s_identifier * identifier;
        } case_2;

    } contents;

} ;


struct s_enumerator_list {
    enum {
        e_enumerator_list_case_0,
        e_enumerator_list_case_1
    } type_of_contents;

    union {
        struct s_enumerator * enumerator;
        
        struct  {
                struct s_enumerator_list * enumerator_list;
                // "," TODO
                struct s_enumerator * enumerator;
        } case_1;

    } contents;

} ;


struct s_enumerator {
    enum {
        e_enumerator_case_0,
        e_enumerator_case_1
    } type_of_contents;

    union {
        struct s_identifier * identifier;
        
        struct  {
                struct s_identifier * identifier;
                // "=" TODO
                struct s_constant_expression * constant_expression;
        } case_1;

    } contents;

} ;


struct s_typedef_name {
    enum {
        e_typedef_name_case_0
    } type_of_contents;

struct s_identifier * identifier;
} ;


struct s_declaration {
    enum {
        e_declaration_case_0
    } type_of_contents;


        struct  {
                t_void_list *declaration_specifier_list; // Vec<declaration_specifier> Repeat one or more times(+)
                t_void_list *init_declarator_list; // Vec<init_declarator> Repeat more than 0 times(*)
                // ";" TODO
        } case_0;

} ;


struct s_init_declarator {
    enum {
        e_init_declarator_case_0,
        e_init_declarator_case_1
    } type_of_contents;

    union {
        struct s_declarator * declarator;
        
        struct  {
                struct s_declarator * declarator;
                // "=" TODO
                struct s_initializer * initializer;
        } case_1;

    } contents;

} ;


struct s_initializer {
    enum {
        e_initializer_case_0,
        e_initializer_case_1,
        e_initializer_case_2
    } type_of_contents;

    union {
        struct s_assignment_expression * assignment_expression;
        
        struct  {
                // "{" TODO
                struct s_initializer_list * initializer_list;
                // "}" TODO
        } case_1;

        
        struct  {
                // "{" TODO
                struct s_initializer_list * initializer_list;
                // "," TODO
                // "}" TODO
        } case_2;

    } contents;

} ;


struct s_initializer_list {
    enum {
        e_initializer_list_case_0,
        e_initializer_list_case_1
    } type_of_contents;

    union {
        struct s_initializer * initializer;
        
        struct  {
                struct s_initializer_list * initializer_list;
                // "," TODO
                struct s_initializer * initializer;
        } case_1;

    } contents;

} ;


struct s_compound_statement {
    enum {
        e_compound_statement_case_0
    } type_of_contents;


        struct  {
                // "{" TODO
                t_void_list *declaration_list; // Vec<declaration> Repeat more than 0 times(*)
                t_void_list *statement_list; // Vec<statement> Repeat more than 0 times(*)
                // "}" TODO
        } case_0;

} ;


struct s_statement {
    enum {
        e_statement_case_0,
        e_statement_case_1,
        e_statement_case_2,
        e_statement_case_3,
        e_statement_case_4,
        e_statement_case_5
    } type_of_contents;

    union {
        struct s_labeled_statement * labeled_statement;
        struct s_expression_statement * expression_statement;
        struct s_compound_statement * compound_statement;
        struct s_selection_statement * selection_statement;
        struct s_iteration_statement * iteration_statement;
        struct s_jump_statement * jump_statement;
    } contents;

} ;


struct s_labeled_statement {
    enum {
        e_labeled_statement_case_0,
        e_labeled_statement_case_1,
        e_labeled_statement_case_2
    } type_of_contents;

    union {
        
        struct  {
                struct s_identifier * identifier;
                // ":" TODO
                struct s_statement * statement;
        } case_0;

        
        struct  {
                // "case" TODO
                struct s_constant_expression * constant_expression;
                // ":" TODO
                struct s_statement * statement;
        } case_1;

        
        struct  {
                // "default" TODO
                // ":" TODO
                struct s_statement * statement;
        } case_2;

    } contents;

} ;


struct s_expression_statement {
    enum {
        e_expression_statement_case_0
    } type_of_contents;


        struct  {
                struct s_expression * expression; // ?
                // ";" TODO
        } case_0;

} ;


struct s_selection_statement {
    enum {
        e_selection_statement_case_0,
        e_selection_statement_case_1,
        e_selection_statement_case_2
    } type_of_contents;

    union {
        
        struct  {
                // "if" TODO
                // "(" TODO
                struct s_expression * expression;
                // ")" TODO
                struct s_statement * statement;
        } case_0;

        
        struct  {
                // "if" TODO
                // "(" TODO
                struct s_expression * expression;
                // ")" TODO
                struct s_statement * statement0;
                // "else" TODO
                struct s_statement * statement1;
        } case_1;

        
        struct  {
                // "switch" TODO
                // "(" TODO
                struct s_expression * expression;
                // ")" TODO
                struct s_statement * statement;
        } case_2;

    } contents;

} ;


struct s_iteration_statement {
    enum {
        e_iteration_statement_case_0,
        e_iteration_statement_case_1,
        e_iteration_statement_case_2
    } type_of_contents;

    union {
        
        struct  {
                // "while" TODO
                // "(" TODO
                struct s_expression * expression;
                // ")" TODO
                struct s_statement * statement;
        } case_0;

        
        struct  {
                // "do" TODO
                struct s_statement * statement;
                // "while" TODO
                // "(" TODO
                struct s_expression * expression;
                // ")" TODO
                // ";" TODO
        } case_1;

        
        struct  {
                // "for" TODO
                // "(" TODO
                struct s_expression * expression0; // ?
                // ";" TODO
                struct s_expression * expression1; // ?
                // ";" TODO
                struct s_expression * expression2; // ?
                // ")" TODO
                struct s_statement * statement;
        } case_2;

    } contents;

} ;


struct s_jump_statement {
    enum {
        e_jump_statement_case_0,
        e_jump_statement_case_1,
        e_jump_statement_case_2,
        e_jump_statement_case_3
    } type_of_contents;

    union {
        
        struct  {
                // "goto" TODO
                struct s_identifier * identifier;
                // ";" TODO
        } case_0;

        
        struct  {
                // "continue" TODO
                // ";" TODO
        } case_1;

        
        struct  {
                // "break" TODO
                // ";" TODO
        } case_2;

        
        struct  {
                // "return" TODO
                struct s_expression * expression; // ?
                // ";" TODO
        } case_3;

    } contents;

} ;


struct s_identifier {
	t_token *token;
} ;


struct s_string {
	t_token *token;
} ;


struct s_integer_constant {
	char *str;
} ;


struct s_character_constant {
	char *str;
} ;


struct s_floating_constant {
	char *str;
} ;


struct s_enumeration_constant {
	char *str;
} ;

#endif
 
