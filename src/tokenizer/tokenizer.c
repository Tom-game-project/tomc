#include "tokenizer.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"

enum e_ptr_state
{
	e_ptr_state_in_single_quotation,
	e_ptr_state_in_double_quotation,
	e_ptr_state_in_oneline_comment,
	e_ptr_state_in_multiline_comment,
	e_ptr_state_in_word,
	e_ptr_state_out
};
typedef enum e_ptr_state t_ptr_state;


bool is_space(char c)
{
	return (c == ' ' || c == '	'  || c == '\n');
}

int push_operator(t_token_list **lst, t_operator token_type)
{
	t_anytype elem;

	elem.token = init_token_by_ope(
			e_token_type_operator,
			token_type
	);		
	return (void_list_push(lst, elem));
}

static void set_operator_str(char buf[3], char *str)
{
	buf[0] = str[0];
	if (str[1] == '\0')
	{
		buf[1] = str[1];
		buf[2] = '\0';
	}
	else 
	{
		buf[1] = str[1];
		buf[2] = str[2];
	}
}

bool cmp_operator_str(char buf[3], const char a1, const char a2, const char a3)
{
	return (buf[0] == a1 && buf[1] == a2 && buf[2] == a3);
}

size_t match_token(char *str, t_token_list **lst)
{
	char buf[3];

	struct {
		char buf[3];
		size_t size;
		t_operator operator;
	} str_operator_conv_table[29] = {
		{{'+', '+', '\0'},2, e_operator_incr},
		{{'+', '=', '\0'},2, e_operator_add_assignment},
		{{'+', '\0', '\0'},1, e_operator_add},
		{{'-', '-', '\0'},2, e_operator_decr},
		{{'-', '=', '\0'},2, e_operator_sub_assignment},
		{{'-', '\0', '\0'},1, e_operator_sub},
		{{'*', '=', '\0'},2, e_operator_mul_assignment},
		{{'*', '\0', '\0'},1, e_operator_mul},
		{{'/', '=', '\0'},2, e_operator_div_assignment},
		{{'/', '\0', '\0'},1, e_operator_div},
		{{'<', '<', '='},3, e_operator_bitshift_left_assignment},
		{{'<', '<', '\0'},2, e_operator_bitshift_left},
		{{'<', '=', '\0'},2, e_operator_le},
		{{'<', '\0', '\0'},1, e_operator_lt},
		{{'>', '>', '='},3, e_operator_bitshift_right_assignment},
		{{'>', '>', '\0'},2, e_operator_bitshift_right},
		{{'-', '>', '\0'},2, e_operator_arrow},
		{{'>', '=', '\0'},2, e_operator_ge},
		{{'>', '\0', '\0'},1, e_operator_gt},
		{{'&', '&', '\0'},2, e_operator_and},
		{{'&', '=', '\0'},2, e_operator_and_assignment},
		{{'&', '\0', '\0'},1, e_operator_logic_and},
		{{'|', '|', '\0'},2, e_operator_or},
		{{'|', '=', '\0'},2, e_operator_or_assignment},
		{{'|', '\0', '\0'},1, e_operator_logic_and},
		{{'^', '=', '\0'},2, e_operator_xor_assignment},
		{{'^', '\0', '\0'},2, e_operator_logic_xor},
		{{'!', '=', '\0'},2, e_operator_not_assignment},
		{{'!', '\0', '\0'},1, e_operator_not},
	};

	set_operator_str(buf, str);
	for (int i = 0; i < 26; i++)
	{
		if (cmp_operator_str(
			buf,
		       	str_operator_conv_table->buf[0],
		       	str_operator_conv_table->buf[1],
		       	str_operator_conv_table->buf[2]))
		{
			push_operator(lst, str_operator_conv_table->operator);
			return str_operator_conv_table -> size;
		}
	}
	return (0);
}



/// return next state
/// if error -> return 0
size_t case_ptr_state_out(char *str,t_ptr_state *ptr_state, t_token_list **lst)
{
	if (*str == '"')
	{
		*ptr_state = e_ptr_state_in_double_quotation;
		return (1);
	}
	else if  (*str == '\'')
	{
		*ptr_state = e_ptr_state_in_single_quotation;
		return (1);
	}
	else if (ft_isalnum(*str) || *str == '_')
	{
		*ptr_state = e_ptr_state_in_word;
		return (1);
	}
	else if (is_space(*str))
	{
		// don't need to change status
		return (1);
	}
	else if (str[0] == '/')
	{
		if (str[1] == '/')
		{
			*ptr_state = e_ptr_state_in_oneline_comment;
			return (2);
		}
		else if (str[1] == '*')
		{
			*ptr_state = e_ptr_state_in_multiline_comment;
			return (2);
		}
	}
	//// 上のelse ifチェーンとは繋げない
	return (match_token(str, lst));
}

t_token_list *tokenizer(char *str)
{
	t_token_list *lst;
	t_ptr_state ptr_state;
	size_t slide;

	lst = NULL;
	ptr_state = e_ptr_state_out;
	while (*str != '\0')
	{
		switch (ptr_state)
		{
			case e_ptr_state_out:
				slide = case_ptr_state_out(str, &ptr_state, &lst);
			break;
			case e_ptr_state_in_word:
			break;
			case e_ptr_state_in_double_quotation:
			break;
			case e_ptr_state_in_single_quotation:
			break;
			case e_ptr_state_in_oneline_comment:
			break;
			case e_ptr_state_in_multiline_comment:
			break;
		}
		if (slide == 0)
		{
			// listをクリアにする
			return (NULL);
		}
		str += slide; // TODO
	}
	return lst;
}
