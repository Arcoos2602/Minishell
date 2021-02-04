/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/04 11:12:47 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int		no_separators(const char *str, char c) // str to check >>
{
	if (c == '|' || c == '>' || c == '<')
		return (0);
	return (1);
}

static int		cpt(char const *str)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i] != '\0')
	{
		while (ft_iswhitespace(str[i++]))
			;
		while (ft_isalnum(str[i]) && no_separators(str, str[i])) // alnum temporaire
			i++;
		cpt++;
	}
	return (cpt);
}

static int		init_tab(char **tab, char const *str)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	y = 0;
	while (x < cpt(str))
	{
		y = 0;
		while (ft_iswhitespace(str[i++]) && str[i] != '\0')
			;
		while (str[i] != '\0' && ft_isalnum(str[i]) && no_separators(str, str[i]))
		{
			y++;
			i++;
		}
		if (!(tab[x] = (char*)malloc(sizeof(char) * (y + 1))))
			return (0);
		x++;
	}
	tab[x] = 0;
	return (1);
}

char			**token(char const *str)
{
	char	**tab;
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	i = 0;
	tab = NULL;
	//printf("%d\n", cpt(str) + 1);
	if (!(str) || !(tab = malloc(sizeof(char*) * (cpt(str) + 1)))) //+ 1 pour NULL
		return (0);
	init_tab(tab, str);
	while (ft_iswhitespace(str[i]) && str[i] != '\0')
		i++;
	while (str[i] != '\0') 
	{
		y = 0;
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		while (str[i] != '\0' && ft_isalnum(str[i]) && no_separators(str, str[i]))
		{
			tab[x][y] = str[i];
			y++;
			i++;	
		}
		tab[x][y] = '\0';
		printf("%s\n", tab[x]);
		x++;
		if (x == 3)
			exit(0);
	}
	return (tab);
}

static void	print_tab(char **tab)
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

int		main()
{
	char	**lexer;

	lexer = token("ls | cat"); // doit retourner [ls][|][cat][|][NULL]
	//print_tab(lexer);
	return (1);
}

/// separateurs à gérer :			; ' "" > < >> $