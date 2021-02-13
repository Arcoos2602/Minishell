/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:13:44 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/13 15:00:29 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int				cpt(char *str)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (ft_iswhitespace(str[i]) && str[i] != '\0')
		i++;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		while (check_char(str[i]) && separators(str[i]) == 0)
			i++;
		while (ft_iswhitespace(str[i]))
			i++;
		cpt++;
		if (separators(str[i]))
			cpt++;
		if (str[i] == '>' && str[i + 1] == '>')
			i++;
		if (not_handled(str[i], str[i + 1]))
			return (-1);
		i++;
	}
	return (cpt);
}

int				fill_tab(char **tab, char *str)
{
	int		x;
	int		i;
	int		tmp;
	int		size_line;

	x = 0;
	i = 0;
	size_line = 0;

	while (x < cpt(str))
	{
		size_line = 0;
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		if (str[i] == '>' && str[i + 1] == '>')
		{
			tab[x] = ft_strndup(&str[i], 2);
			i += 2;
			x++;
		}
		if (separators(str[i]) && ft_iswhitespace(str[i]) == 0)
		{
			tab[x] = ft_strndup(&str[i], 1);
			i++;
			x++;
		}
		if (ft_iswhitespace(str[i]) == 0)
		{
			tmp = i;
			while (check_char(str[i]) && str[i] != '\0')
			{
				size_line++;
				i++;
			}
			tab[x] = ft_strndup(&str[tmp], size_line);
			x++;
		}
	}
	tab[x] = NULL;
	return (1);
}

void	print_tab(char **tab)
{
	int		x = 0;
	int		y = 0;

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

char			**token(char *str)
{
	char	**tab;
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	i = 0;
	tab = NULL;
	/*if (!(quote(str))) // to do
		return (NULL);*/
	if (cpt(str) < 1)
	{
		ft_putstr_fd("Tokens not handled", 1);
		return (NULL);
	}
	if (!(str) || !(tab = malloc(sizeof(char *) * (cpt(str) + 1))))
		return (0);
	fill_tab(tab, str);
	return (tab);
}
