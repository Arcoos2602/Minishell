/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/05 13:33:29 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int				check_char(char	c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}

static char		*ft_free(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int		separators(char c, char c_next) // str to check >>
{
	if (c == '|' || c == '>' || c == '<' || c == '"' || (c == '>' && c_next == '>'))
		return (1);
	return (0);
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
		while (check_char(str[i]))
			i++;
		if (separators(str[i], str[i + 1]))
			
			
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
	/*while (x < cpt(str))
	{
		y = 0;
		while (ft_iswhitespace(str[i++]) && str[i] != '\0')
			;
		while (str[i] != '\0' && check_char(str[i]) && no_separators(str[i], str[i + 1]))
		{
			y++;
			i++;
		}
		if (!(tab[x] = (char*)malloc(sizeof(char) * (y + 1))))
			ft_free(tab, i);
		x++;
	}*/
	tab[x] = 0;
	return (1);
}

char			**token(char *str) // needs ton handle "" >> ''
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
	printf("%d", cpt(str) + 1);
	//quote(str);
	if (!(str) || !(tab = malloc(sizeof(char *) * (cpt(str) + 1))))
		return (0);
	init_tab(tab, str);
	/*while (ft_iswhitespace(str[i]) && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		y = 0;
		check = 0;
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		if (no_separators(str[i], str[i + 1]) == 0) // fonctionne pas pour ">>"
		{
			tab[x][y] = str[i];
			y++;
			i++;
		}
		while (str[i] != '\0' && check_char(str[i]) && no_separators(str[i], str[i + 1]))
		{
			tab[x][y++] = str[i++];
		}
		if (ft_iswhitespace(str[i - 1]))
			;
		tab[x++][y] = '\0';
	}*/
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

	lexer = token("ls | cat cdawdwa|dwadwa"); // espace à la fin bugged
	print_tab(lexer);
	return (1);
}

/// separateurs à gérer :			; ' "" > < >> '
