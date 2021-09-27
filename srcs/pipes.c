/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 12:08:48 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	ft_close(int pipe_1, int pipe_2, int pipe_3, int pipe_4)
{
	if (pipe_1 >= 0)
		close(pipe_1);
	if (pipe_2 >= 0)
		close(pipe_2);
	if (pipe_3 >= 0)
		close(pipe_3);
	if (pipe_4 >= 0)
		close(pipe_4);
}

int	ft_fork(t_path *path)
{
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(-1, -1, path->pipe_in, pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		path->pipe_in = pipe_fd[0];
		path->dont = 1;
		path->father = 0;
		return (pid);
	}
	else
	{
		ft_close(-1, -1, path->pipe_out, pipe_fd[0]);
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

int	ft_pipe(t_pipes *pipes, t_path *path, pid_t *pid_2)
{
	int		buf[2];
	pid_t	pid[2];

	pipes->error = init_redi(path, pipes, buf);
	if (path->starting == 1 && pipes->next == NULL && pipes->builtin == 1)
	{
		ft_dup_redi(pipes, buf);
		check_builtins(pipes, path, path->path);
		ft_close(buf[1], buf[0], path->pipe_in, path->pipe_out);
		return (5);
	}
	pid[0] = 0;
	if (test_fork(path))
		pid[0] = ft_fork(path);
	if (pid[0] == 0)
	{
		if (pipes->next != NULL)
			ft_pipe(pipes->next, path, pid_2);
		if (path->exec == 0)
			pid[1] = father_0(pipes, path, buf);
	}
	return (5);
}

int	line_command(t_pipes *parser, t_path *path, pid_t *pid_2)
{
	return (ft_pipe(parser, path, pid_2));
}

void	init_path_shell(int *pid_2, t_path *path)
{
	pid_2 = 0;
	path->first[0] = 0;
	path->pipe_in = -1;
	path->pipe_out = -1;
	path->starting = 1;
	path->dont = 0;
	path->exec = 0;
	path->father = 1;
}

int	ft_shell(t_parser *parser, t_path *path)
{
	int	pid_2;
	int	status;

	init_path_shell(&pid_2, path);
	line_command(parser->pipe, path, &pid_2);
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
		get_next_line(1, NULL);
		exit(path->exit_status % 255);
	}
	waitpid(0, &status, 0);
	path->exit_status %= 255;
	if (parser->next != NULL)
		ft_shell(parser->next, path);
	return (1);
}
