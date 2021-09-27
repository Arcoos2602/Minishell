/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:15:05 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 02:09:40 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	ft_env(char **path)
{
	int		i;

	i = -1;
	while (path[++i] != NULL)
	{
		ft_putstr_fd(path[i], 1);
		ft_putchar_fd('\n', 1);
	}
}
