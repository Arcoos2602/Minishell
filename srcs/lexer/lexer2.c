/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 12:14:20 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 09:59:57 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	token(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}

void	cpt2(char *str, int *i, int *cpt)
{
	int		tmp;

	tmp = *i;
	while (ft_iswhitespace(str[tmp]) && str[tmp] != '\0')
		tmp++;
	if (token(str[tmp]))
	{
		*i = tmp;
		++*cpt;
	}
	if (str[*i] == '<' && str[*i + 1] == '<')
		++*i;
	if (str[*i] == '>' && str[*i + 1] == '>')
		++*i;
}
