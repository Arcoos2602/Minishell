/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:15:05 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/12 12:27:10 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int		ft_env(char **path)
{
	int		i;

	i = -1;
	while (path[++i] != NULL)
	{
		ft_putstr_fd(path[i], 1);
		ft_putchar_fd('\n', 1);
	}
}
