/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/10 15:52:34 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int				quote(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			while (str[i] != '"' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int				check_char(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

int				separators(char	c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ') // espace separateur
		return (1);
	return (0);
}

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
		while (separators(str[i]) == 0 && str[i] != '\0')
			i++;
		while (ft_iswhitespace(str[i]))
			i++;
		while (check_char(str[i]) && separators(str[i]) == 0)
			i++;
		cpt++;
		if (separators(str[i]))
			cpt++;
		i++;
	}
	return (cpt);
}

int				init_tab(char **tab, char *str)
{
	int		x;
	int		i;
	int		size_line;

	x = 0;
	i = 0;
	size_line = 0;

	while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
	while (x < cpt(str))
	{
		size_line = 0;
		while (separators(str[i]) && str[i] != '\0')
			i++;
		while (ft_iswhitespace(str[i]))
			i++;
		if (separators(str[i]))
			size_line++;
		while (check_char(str[i]) && separators(str[i]) == 0)
		{
			size_line++;
			i++;
		}
		printf("%d\n", size_line);
		if (!(tab[x] = (char *)malloc(sizeof(char) * (size_line + 1))))
			return (0);
		x++;
	}
	return (1);
}

char			**token(char *str)
{
	char	**tab;
	int		i;
	int		x;

	x = 0;
	i = 0;
	tab = NULL;
	/*if (!(quote(str)))
		return (NULL);*/
	if (cpt(str) == 0)
		return (NULL);
	//printf("%d", cpt(str));
	if (!(str) || !(tab = malloc(sizeof(char *) * (cpt(str) + 1))))
		return (0);
	init_tab(tab, str);
	while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
	return (tab);
}

/*static void	print_tab(char **tab)
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
}*/

int main()
{
	char	**lexer;

	//printf("%d", quote);
	lexer = token("ls | cat"); // spaces at the end bugged
	//print_tab(lexer);
	return (1);
}

/// separateurs à gérer :			; ' "" > < >> '