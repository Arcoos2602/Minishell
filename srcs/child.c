/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:01:11 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/09 15:04:06 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	child(t_pipes *pipes, t_path *path, int pipe_fd[2], pid_t *pid_2)
{
	path->pipe_out = pipe_fd[1];
	*pid_2 = 1;
	if (pipes->next != NULL || pipes->put[0] == 1)
	{
		if (pipe_fd[1] >= 0)
			close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
	path->start = 0;
	if (pipes->put[1] == 1)
		path->exit = 1;
	if (path->pipe_in >= 0)
		close(path->pipe_in);
	if (pipes->put[0] == 1)
		ft_pipe(NULL, pipes, path, pid_2);
	else if (pipes->next != NULL)
		ft_pipe(pipes, pipes->next, path, pid_2);
}
