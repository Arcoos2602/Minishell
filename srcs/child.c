/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:01:11 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/23 15:24:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	child(t_pipes *pipes, t_path *path, pid_t *pid_2)
{	
	if (pipes->next != NULL )
		ft_pipe(pipes->next, path, pid_2);
}	
