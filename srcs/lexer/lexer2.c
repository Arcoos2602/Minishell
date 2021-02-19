/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/19 14:24:17 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int				separators(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ' || c == ';')
		return (1);
	return (0);
}

int				check_char(char c)
{
	if (c >= 33 && c <= 126 && separators(c) == 0 && c != '"' && c != 39)
		return (1);
	return (0);
}

int				not_handled(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>')
		{
			while (ft_iswhitespace(str[i++]))
				;
			if (str[i] == '|' || str[i] == '<')
				return (1);	
		}
		if (str[i] == '<')
		{
			while (ft_iswhitespace(str[i++]))
				;
			if (str[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

void			cpt2(char *str, int *i, int *cpt)
{
	int		tmp;

	tmp = *i;
	while (ft_iswhitespace(str[tmp]))
		tmp++;
	if (separators(str[tmp]))
	{
		*i = tmp;
		++*cpt;
	}
	if (str[*i] == '>' && str[*i + 1] == '>')
		++*i;
}
