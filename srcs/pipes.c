/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/09 14:57:42 by gbabeau          ###   ########.fr       */
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

int	ft_pipe(t_pipes *pipe, t_pipes *pipes, t_path *path, pid_t *pid_2)
{
	int		pipe_fd[2];
	int		buf[2];
	pid_t	pid[2];

	pipes->error = init_redi(pipes, buf);
	init_fd(pipes, buf, pipe_fd, path);
	pid[0] = fork();
//	if (pipes->redi != NULL && *pid_2 != 0)
//	waitpid(0, NULL, 0); // modification
	if (pid[0] != 0)
	{
		ft_free_pipe(pipe);
		pid[1] = father_0(pipes, path, pipe_fd);
		if (*pid_2 != 0)
			exit_ft_pipe(pid[1], pipes, path);
		return (1);
	}
	else
	{
		child(pipes, path, pipe_fd, pid_2);
		waitpid(pid[0], NULL, 0);
	//	ft_putstr_fd("g_global1 =",2);
	//	ft_putnbr_fd(g_global,2);
	//	ft_putstr_fd("\n",2);
		close(path->pipe_in);
	}
	return (1);
}

int	line_command(t_pipes *parser, t_path *path, pid_t *pid_2) // getpid
{
	if (parser->next != NULL || parser->builtin == 0)
		ft_pipe(NULL, parser, path, pid_2);
	else
		check_builtins(parser, path , path->path);
	return (1);
}

int	ft_shell(t_parser *parser, t_path *path)
{
	int	pid_2;

	pid_2 = 0;
	path->first[0] = 0;
	path->pipe_in = -1;
	path->pipe_out = -1;
	line_command(parser->pipe, path, &pid_2);
	if (pid_2 != 0)
	{
		//printf("FILS\n");
		exit_ft_parser(0, parser, path);
	}
	printf("PERE\n");
	wait(&g_global);
	g_global %= 255;
			ft_putstr_fd("g_global =",2);
		ft_putnbr_fd(g_global, 2);
		ft_putstr_fd("\n",2);
	dup2(0, STDOUT_FILENO);
	dup2(1, STDIN_FILENO);
	//wait(NULL);
	//printf("PERE2\n");
	if (parser->next != NULL)
		ft_shell(parser->next, path);
	return (1);
}
