/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:39:10 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/24 15:05:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	count_quote(char *str, int *i)
{
	if (str[*i] == '"')
	{
		while (str[*i] != '\0' && str[++*i] != '"')
			;
	if (str[*i] == '\0')
		return (-1);
	}
	else if (str[*i] == '\'')
	{
		while (str[*i] != '\0' && str[++*i] != '\'')
			;
		if (str[*i] == '\0')
			return (-1);
	}
	return (1);
}

void	fill_quote(char **tab, char *str, int *i, int *x) // si $ "" interpreter si '' j'interprete pas
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

int	check_end(char *str)
{
	if (token(str[ft_strlen(str) - 1])
		&& ft_iswhitespace(str[ft_strlen(str) - 1]) == 0
		&& str[ft_strlen(str) - 1] != ';')
		return (-1);
	return (1);
}

int	check_quotes(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		++*i;
		while (str[*i] != '\0' && str[*i] != '\'')
			++*i;
		if (str[*i] == '\0')
			return (0);
	}
	if (str[*i] == '"')
	{
		++*i;
		while (str[*i] != '\0' && str[*i] != '"')
			++*i;
		if (str[*i] == '\0')
			return (0);
	}
	return (1);
}

int	check_multi(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (ft_iswhitespace(str[i]))
				++i;
			if (str[i] == '\0')
				return (-1);
		}
		if (!(check_quotes(str, &i)))
			return (-1);
		i++;
	}
	return (1);
}
