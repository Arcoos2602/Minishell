/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/09 16:26:10 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

/*if (ft_iswhitespace(str[i]))
			{
				printf("check");
				while (ft_iswhitespace(str[i]) && str[i] != '\0')
				{
					i++;
				}
				cpt++;
}*/

int				separators(char	c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

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
		while (separators(str[i]) == 0 && str[i] != '\0')
		{
			if (ft_iswhitespace(str[i]))
			{
				while (ft_iswhitespace(str[i]))
					i++;
				cpt++;
			}
			i++;
		}
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
	y = 0;
	i = 0;
	size_line = 0;
	while (str[i++])
	{
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		while (separators(str[i]) == 0 && str[i] != '\0')
		{
			i++;
		}
		if (!(tab[x] = (char*)malloc(sizeof(char) * (size_line + 1))))
			return (0);
	}
	return (1);
}

char			**token(char *str)
{
	char	**tab;
	int		i;
	int		x;
	int		y;
	int		check;

	x = 0;
	y = 0;
	i = 0;
	tab = NULL;
	/*if (!(quote(str)))
		return (NULL);*/
	if (cpt(str) == 0)
		return (NULL);
	printf("%d", cpt(str));
	//mutli_pipe
	if (!(str) || !(tab = malloc(sizeof(char *) * (cpt(str) + 1))))
		return (0);
	init_tab(tab, str);
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

int main()
{
	char	**lexer;

	lexer = token("ls | cat");
	//print_tab(lexer);
	return (1);
}

/// separateurs à gérer :			; ' "" > < >> '
///// """"""