/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:24:50 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/15 11:43:10 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	ft_pwd(char **path)
{
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strncmp(path[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(&path[i][4], 1);
			ft_putchar_fd('\n', 1);
		}	
		i++;
	}
	exit(EXIT_SUCCESS);
}