/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:13:44 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/18 10:42:07 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"\

int				cpt(char *str)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		if (str[i] == '"' || str[i] == 39)
			count_quote(str, &i, &cpt);
		if (check_char(str[i]))
		{
			while (check_char(str[i]))
				i++;
			cpt++;
		}
		cpt2(str, &i, &cpt);
		if (not_handled(str[i], str[i + 1]))
			return (-1);
		if (str[i])
		i++;
	}
	return (cpt);
}

void			fill_tab2(char **tab, char *str, int *i, int *x)
{
	int		size_line;
	int		tmp;

	size_line = 0;
	if (separators(str[*i]) && ft_iswhitespace(str[*i]) == 0)
	{
		tab[*x] = ft_strndup(&str[*i], 1);
		++*i;
		++*x;
	}
	if (check_char(str[*i]) && str[*i] != '\0')
	{
		tmp = *i;
		while (check_char(str[*i]) && str[*i] != '\0')
		{
			size_line++;
			++*i;
		}
		tab[*x] = ft_strndup(&str[tmp], size_line);
		++*x;
	}
}

int				fill_tab(char **tab, char *str)
{
	int		x;
	int		i;
	int		size_line;

	x = 0;
	i = 0;
	size_line = 0;
	while (x < cpt(str))
	{
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		if (str[i] == '"' || str[i] == 39)
			fill_quote(tab, str, &i, &x);
		if (str[i] == '>' && str[i + 1] == '>')
		{
			tab[x] = ft_strndup(&str[i], 2);
			i += 2;
			x++;
		}
		fill_tab2(tab, str, &i, &x);
	}
	tab[x] = NULL;
	return (1);
}

char			**token(char *str)
{
	char	**tab;
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	tab = NULL;
	i = 0;
	if (check_multi(str) == -1)
	{
		ft_putstr_fd("Multilines not handled", 1);
		return (tab);
	}
	if (cpt(str) < 1)
	{
		ft_putstr_fd("Tokens not handled", 1);
		return (tab);
	}
	printf("%d\n", cpt(str));
	if (!(str) || !(tab = malloc(sizeof(char *) * (cpt(str) + 1))))
		return (0);
	fill_tab(tab, str);
	return (tab);
}

void			print_tab(char **tab)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (tab[x] != NULL)
	{
		y = 0;
		ft_putchar_fd('[', 1);
		while (tab[x][y] != '\0')
		{
			ft_putchar_fd(tab[x][y], 1);
			y++;
		}
		ft_putchar_fd(']', 1);
		x++;
	}
}

int				main(void)
{
	char	**lexer;

	(void)lexer;
	lexer = token("ls a| cat\0");
	if (lexer != NULL)
		print_tab(lexer);
	ft_putchar_fd('\n', 1);
}
