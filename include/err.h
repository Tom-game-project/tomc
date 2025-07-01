#ifndef ERR_H
#define ERR_H

typedef struct s_parse_err t_parse_err;
typedef enum e_error_type t_error_type;
typedef enum e_error_lvl t_error_lvl;

enum e_error_lvl
{
	e_error_lvl_warn,
	e_error_lvl_err,
};

enum e_error_type
{
	e_error_type_parser,
};

struct s_parse_err
{	
};

#endif
