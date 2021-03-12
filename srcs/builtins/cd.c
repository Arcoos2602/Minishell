/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 10:10:07 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/12 12:15:00 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int		ft_cd(t_pipes *pipes)
{
	printf("CD : %s\n", pipes->command[1]);
	if (chdir(pipes->command[1]) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (-1);
	}
	return (1);
}
