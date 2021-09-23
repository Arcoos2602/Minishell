/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/24 01:51:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

/// PB QUAND FINIT PAR CTRLD

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

/*
static void	int_handler(int sig)
{
		printf("signum=%d\n", sig);
	ft_putchar_fd('\n', 2);
}

static void	quit_handler(int sig)
{
			printf("signum=%d\n", sig);
				ft_putchar_fd('\n', 2);
	exit(0);
}
*/

int ft_fork(t_path *path)
{
	pid_t pid;
	int	 pipe_fd[2];
	
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			path->pipe_in = pipe_fd[0];
					path->dont = 1;
					path->father = 0;
		return (pid);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		path->pipe_out = pipe_fd[1];
		path->father = 1;
	return (pid);
	}
}


int test_fork(t_path *path)
{
	if (path->starting == 1)
	{
		path->starting = 0;
		return (0);
	}
	return 1;
}

int	ft_pipe(t_pipes *pipes, t_path *path, pid_t *pid_2)
{
	int		buf[2];
	pid_t	pid[2];

        buf[0] = -1;
		buf[1] = -1;

	pipes->error = init_redi(pipes, buf);
	pid[0] = 0;
	 if (test_fork(path))
		pid[0] = ft_fork(path);
	if (pid[0] == 0)
	{
		child(pipes, path, pid_2);
		if (path->exec == 0)
		{
			pid[1] = father_0(pipes, path, buf);
		}
		if (pipes->next == NULL)
			return (2);
		else
			return (1);
	}
	if (pipes->next == NULL)
		return (4);
	return (3);
}

int	line_command(t_pipes *parser, t_path *path, pid_t *pid_2) // getpid
{
	if (parser->next != NULL || parser->builtin == 0)
		return (ft_pipe(parser, path, pid_2));
	else
		check_builtins(parser, path , path->path);
	return (1);
}

int	ft_shell(t_parser *parser, t_path *path)
{
	int	pid_2;
	int status;

	
	pid_2 = 0;
	path->first[0] = 0;
	path->pipe_in = -1;
	path->pipe_out = -1;
	path->starting = 1;
	path->dont = 0;
	path->exec = 0;
	path->father = 1;
	line_command(parser->pipe, path, &pid_2);
	close(path->pipe_out);
	close(path->pipe_in);
	dup2(path->out_fd, 1);
	dup2(path->in_fd, 0);
	dup2(0, STDOUT_FILENO);
	dup2(1, STDIN_FILENO);
	waitpid(-1, &status, 0);
	status = WEXITSTATUS(status);
	if (path->father == 1)
	{
		path->exit_status = status;
	}
	if (path->dont != 0)
	{	path->exit_status %= 255;
		exit(path->exit_status);
	}
	waitpid(0, &status, 0);
	path->exit_status %= 255;
	printf("%d\n", path->exit_status);
	if (parser->next != NULL)
		ft_shell(parser->next, path);
	return (1);
}
