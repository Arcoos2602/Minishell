/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:01:11 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/22 22:30:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	child(t_pipes *pipes, t_path *path, int pipe_fd[2], pid_t *pid_2)
{
	pipe_fd[2] = pipe_fd[2];
//	if (pipes->put[0] == 1)
//		ft_pipe(pipes, path, pid_2);
//	else 
	
	if (pipes->next != NULL)
		ft_pipe(pipes->next, path, pid_2);
}
