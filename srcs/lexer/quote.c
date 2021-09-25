/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:39:10 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/25 10:09:41 by user42           ###   ########.fr       */
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
			return (display_error_token(str[*i]));
	}
	else if (str[*i] == '\'')
	{
		while (str[*i] != '\0' && str[++*i] != '\'')
			;
		if (str[*i] == '\0')
			return (display_error_token(str[*i]));
	}
	return (1);
}
