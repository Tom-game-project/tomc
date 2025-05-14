
// isspace()
//      checks for white-space characters.  In the "C" and "POSIX" locales, these are: space, form-feed ('\f'), newline ('\n'), carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
int ft_isspace(char c)
{
	return (
		c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
	);
}
