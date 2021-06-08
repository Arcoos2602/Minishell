#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int				separators(char c)
{
	int		i;

	i = 0;
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == ';')
		return (1);
	return (0);
}

int				check_char(char c)
{
	int		i;
	
	i = 0;
	if (c >= 33 && c <= 126 && separators(c) == 0 && c != '"' && c != 39)
		return (1);
	return (0);
}

int				not_handled(char *str)
{
	int		i;
	int		tmp;

	i = 0;
	while (str[i])
	{
		tmp = i;
		if (str[tmp] == '|')
		{
			while (ft_iswhitespace(str[++tmp]))
				;
			if (str[tmp] == '|')
				return (1);
			tmp = i;
		}
		if (str[tmp] == '>')
		{
			while (ft_iswhitespace(str[++tmp]))
				;
			if (str[tmp] == '<')
				return (1);
			tmp = i;
		}
		if (str[tmp] == '<' || str[tmp] == '>')
		{
			while (ft_iswhitespace(str[++tmp]))
				;
			if (str[tmp] == '|')
				return (1);
			tmp = i;
		}
		i++;
	}
	return (0);
}

void			cpt2(char *str, int *i, int *cpt)
{
	int		tmp;

	tmp = *i;
	while (ft_iswhitespace(str[tmp]) && str[tmp] != '\0')
		tmp++;
	if (separators(str[tmp]))
	{
		*i = tmp;
		++*cpt;
	}
	if (str[*i] == '<' && str[*i + 1] == '<')
		++*i;
	if (str[*i] == '>' && str[*i + 1] == '>')
		++*i;
}
