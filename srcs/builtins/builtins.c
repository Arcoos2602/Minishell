/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:04 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/08 12:15:28 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"

int		ft_exit(t_pipes *pipes)
{
	ft_putstr_fd("daw", 2);
}

int		check_builtins(t_pipes	*pipes)
{
	if (ft_strncmp(pipes->command, "exit", 4) == 0)
		ft_exit(pipes);
	return (1);
}
