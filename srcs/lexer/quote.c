/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:39:10 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/09 19:23:31 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	count_quote(char *str, int *i, int *cpt)
{
	if (str[*i] == '"')
		while (str[++*i] != '"')
			;
	else
		while (str[++*i] != 39)
			;
	++*cpt;
}

void	fill_quote(char **tab, char *str, int *i, int *x)
{
	int		size_line;
	int		tmp;

	size_line = 0;
	tmp = *i + 1;
	if (str[*i] == '"')
		while (str[++*i] != '"')
			size_line++;
	else
		while (str[++*i] != 39)
			size_line++;
	++*i;
	tab[*x] = ft_strndup(&str[tmp], size_line);
	while (ft_iswhitespace(str[*i]))
		++*i;
	++*x;
}

void	check_double(char *str, int *i, int *first, int *second)
{
	if (str[*i] == '"')
	{
		++*first;
		++*i;
		while (str[*i] != '"' && str[*i] != '\0')
			++*i;
		if (str[*i] != '\0')
			++*second;
	}
}

int	check_end(char *str)
{
	if (separators(str[ft_strlen(str) - 1])
		&& ft_iswhitespace(str[ft_strlen(str) - 1]) == 0
		&& str[ft_strlen(str) - 1] != ';')
		return (-1);
	return (1);
}

int	check_multi(char *str)
{
	int		i;
	int		first;
	int		second;

	first = 0;
	second = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			first++;
			i++;
			while (str[i] != 39 && str[i] != '\0')
				i++;
			if (str[i] != '\0')
				second++;
		}
		check_double(str, &i, &first, &second);
		i++;
	}
	if (first == second && check_end(str) == 1)
		return (1);
	else
		return (-1);
}
