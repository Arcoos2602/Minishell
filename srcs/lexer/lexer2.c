/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:14:20 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 10:50:45 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

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
