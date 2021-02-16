/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:39:10 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/16 14:51:29 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void			count_quote(char *str, int *i, int *cpt)
{
	while (str[*i] != '"' && str[*i] != 39)
		++*i;
	++*cpt;
}

int				check_multi(char *str)
{
	int		i;
	int		first;
	int		second;

	first = 0;
	second = 0;
	i = 0;
	while (str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	if (first == second)
		return (1);
	else
		return (-1);
}
