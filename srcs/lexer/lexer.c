/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:13:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 14:00:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	elem(char *str, int *cpt, int *i)
{
	while (str[*i] != '\0' && !ft_iswhitespace(str[*i]) && !token(str[*i]))
	{
		if (count_quote(str, i) == -1)
			return (-1);
		++*i;
	}
	++*cpt;
	return (1);
}

int	cpt(char *str)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		while (str[i] != '\0' && ft_iswhitespace(str[i]))
			i++;
		if (str[i] == '\0')
			return (cpt);
		if (str[i] != '\0' && !ft_iswhitespace(str[i]) && !token(str[i]))
		{
			if (elem(str, &cpt, &i) == -1)
				return (-1);
		}
		if (token(str[i]))
		{
			if (check_error(str, &i, &cpt) == -1)
				return (-1);
		}
	}
	return (cpt);
}

void	fill_token(char **tab, char *str, int *i, int *j)
{
	if (str[*i] == str[*i + 1])
	{
		tab[*j] = ft_strndup(&str[*i], 2);
		*i += 2;
		++*j;
	}
	else
	{
		tab[*j] = ft_strndup(&str[*i], 1);
		++*j;
		++*i;
	}
}

void	quotes(char *str, int *i, int *len)
{
	if (str[*i] == '"')
	{
		while (str[*i] != '\0' && str[++*i] != '"')
			++*len;
		++*len;
	}
	else if (str[*i] == '\'')
	{
		while (str[*i] != '\0' && str[++*i] != '\'')
			++*len;
		++*len;
	}
}

void	fill_tab(char **tab, char *str, int cpt_l)
{
	int	i;
	int	j;
	int	start;
	int	len;

	start = 0;
	i = 0;
	j = 0;
	len = 0;
	while (str[i] != '\0' && j < cpt_l)
	{
		len = 0;
		while (str[i] != '\0' && ft_iswhitespace(str[i]))
			i++;
		start = i;
		while (str[i] != '\0' && !token(str[i]) && !ft_iswhitespace(str[i]))
		{
			quotes(str, &i, &len);
			len++;
			i++;
		}
		if (len != 0&& (str[i] == '\0' || token(str[i]) || ft_iswhitespace(str[i])))
				tab[j++] = ft_substr(str, start, len);
		while (str[i] != '\0' && ft_iswhitespace(str[i]))
			i++;
		if (token(str[i]))
			fill_token(tab, str, &i, &j);
	}
	j = 0;
	while (tab[j] != NULL)
	{
		printf("|%s|\n", tab[j++]);
	}
}

void	print_tab(char **tab)
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

char	**tokenization(char *str, char **paths)
{
	char	**tab;
	int		cpt_l;

	(void)paths;
	printf("%s\n", str);
	tab = NULL;
	if (str == NULL)
		return (NULL);
	cpt_l = cpt(str);
	if (cpt_l < 0)
		return (NULL);
	//exit (EXIT_SUCCESS);
	tab = malloc(sizeof(char *) * (cpt_l + 1));
	if (tab == NULL)
		return (NULL);
	tab[cpt_l] = NULL;
	printf("cpt : %d\n", cpt_l);
	fill_tab(tab, str, cpt_l);
	//print_tab(tab);
	//exit (EXIT_SUCCESS);
	return (tab);
}
