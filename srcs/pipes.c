/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/10/02 17:28:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	ft_fork(t_path *path, int buf[2])
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		ft_close(-1, -1, path->pipe_in, pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		path->pipe_in = pipe_fd[0];
		path->dont = 1;
		path->father = 0;
		return (pid);
	}
	else
	{
		ft_close(buf[0], buf[1], path->pipe_out, pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		path->pipe_out = pipe_fd[1];
		path->father = 1;
		return (pid);
	}
}

int	test_fork(t_path *path)
{
	if (path->starting == 1)
	{
		path->starting = 0;
		return (0);
	}
	return (1);
}

int	ft_pipe(t_pipes *pipes, t_path *path, int buf_fd[2])
{
	int		buf[2];
	pid_t	pid[2];

	pipes->put[0] = -1;
	pipes->put[1] = -1;
	buf[0] = -1;
	buf[1] = -1;
	
	
	if (path->starting == 1 && pipes->next == NULL && pipes->builtin == 1)
	{
		ft_dup_redi(pipes, buf);
		ft_close(buf[1], buf[0], path->pipe_in, path->pipe_out);
		check_builtins(pipes, path, path->path);
		return (5);
	}
	pid[0] = 0;
	if (test_fork(path))
		pid[0] = ft_fork(path, buf);
	if (pid[0] == 0)
	{
		if (pipes->next != NULL)
		{
		//	ft_close(buf_fd[0], buf_fd[1], -1, -1);
			ft_pipe(pipes->next, path, buf_fd);
		}
		if (path->exec == 0)
		{	pipes->error = init_redi(path, pipes, buf);
			pid[1] = father_0(pipes, path, buf);
		}
	}
	return (5);
}

void	init_path_shell(t_path *path)
{
	path->first[0] = 0;
	path->pipe_in = -1;
	path->pipe_out = -1;
	path->starting = 1;
	path->dont = 0;
	path->exec = 0;
	path->father = 1;
	path->buffer_fd[0] = -1;
	path->buffer_fd[1] = -1;
}

int	ft_shell(t_parser *parser, t_path *path)
{
	int	buffer_fd[2];
	int	status;

	buffer_fd[0] = -1;
	buffer_fd[1] = -1;
	init_path_shell(path);
	if (parser->pipe != NULL)
		ft_pipe(parser->pipe, path, buffer_fd);
	ft_close(-1, -1, path->pipe_out, path->pipe_in);
	dup2(path->out_fd, 1);
	dup2(path->in_fd, 0);
	dup2(0, STDOUT_FILENO);
	dup2(1, STDIN_FILENO);
	waitpid(-1, &status, 0);
	status = WEXITSTATUS(status);
	if (path->father == 1 && parser->pipe->next != NULL)
		path->exit_status = status;
	if (path->dont != 0)
	{	
		ft_free(path->parser, path);
		exit(path->exit_status % 255);
	}
	waitpid(0, &status, 0);
	path->exit_status %= 255;
	if (parser->next != NULL)
		ft_shell(parser->next, path);
	return (1);
}
