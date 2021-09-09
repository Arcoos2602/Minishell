/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:47:59 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/09 19:22:32 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	free_token(char	**token)
{
	int	i;

	i = 0;
	while (token[i] != NULL)
	{
		free(token[i]);
		i++;
	}
	free(token);
}
