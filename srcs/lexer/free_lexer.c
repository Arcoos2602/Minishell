/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:47:59 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 09:59:42 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	free_token(char	**token)
{
	int	i;

	i = 0;
	if (token != NULL)
	{
		while (token[i] != NULL)
		{
			free(token[i]);
			i++;
		}
		free(token);
	}
	token = NULL;
}
