/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/13 15:00:37 by tcordonn         ###   ########.fr       */
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

int				separators(char	c)
{
	if (c == '|' || c == '>' || c == '<' || c == ' ')
		return (1);
	return (0);
}

int				check_char(char c)
{
	if (c >= 33 && c <= 126 && separators(c) == 0)
		return (1);
	return (0);
}

int				not_handled(char c, char c_next)
{
	if (c == '|' && c_next == '|')
		return (1);
	return (0);
}
