/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/08 13:51:17 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

/// PB QUAND FINIT PAR CTRLD

void	father(t_pipes *pipes, pid_t pid, int pipe_fd[2], int pipe_fd_2[2], char *dest, char **exec_path) // pas a la norme
{
	int			i;
	char		*buf;
	size_t		size;
	char		*env;

	i = 0;
	if (pid == 0)
	{
		if (pipe_fd[0] != -1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
		}
		if (pipes->next != NULL)
			dup2(pipe_fd_2[1], 1);
		while (exec_path[i++] != NULL)
		{
			env = getcwd(buf, size);
			dest = ft_strjoin(exec_path[i], pipes->command[0]);
			execve(dest, &pipes->command[0], (char *const*) NULL);
		}
		//kill(pid, SIGKILL);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pipes->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int		*ft_pipe(t_pipes *pipes, char **exec_path, int pipe_fd[2])
{
	pid_t		pid;
	int			*pipe_fd_2;
	char		*dest;
	int			signum;

	pipe_fd_2 = malloc(sizeof(int) *2);
	if (pipes->next != NULL)
		if (pipe(pipe_fd_2) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (NULL);
		}
	pid = fork();
	father(pipes, pid, pipe_fd, pipe_fd_2, dest, exec_path);
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (pipes->next != NULL)
		free(pipe_fd);
	free(dest);
	return (pipe_fd_2);
}

int			*line_command(t_pipes *parser, char **exec_path, int pipe_fd[2])
{
	int		status;

	pipe_fd = ft_pipe(parser, exec_path, pipe_fd);
	if (parser->next != NULL)
		line_command(parser->next, exec_path, pipe_fd);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (pipe_fd);
}

int			*ft_shell(t_parser *parser, char **exec_path, int pipe_fd[2])
{
	int		i;

	i = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pipe_fd = line_command(parser->pipe, exec_path, pipe_fd);
	if (parser->next != NULL)
		ft_shell(parser->next, exec_path, pipe_fd);
	return (pipe_fd);
}

/// SIGINT ctrl c
/// SIGQUIT ctrl
/// EOF ctrl d