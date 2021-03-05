/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/05 14:27:21 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int		*ft_pipe(t_pipes *pipes, char **exec_path, int pipe_fd[2])
{
	pid_t		pid;
	int			i;
	int			*pipe_fd_2;
	char		*dest;

	i = 0;
	pipe_fd_2 = malloc(sizeof(int) *2);
	if (pipes->next != NULL)
		if (pipe(pipe_fd_2) == -1)
			return (NULL);
	pid = fork();
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
			dest = ft_strjoin(exec_path[i], pipes->command[0]);
			execve(dest, &pipes->command[0],  (char *const*) NULL);
		}
	}
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (pipes->next != NULL)
		free(pipe_fd);
	return (pipe_fd_2);
}

int			*line_command(t_pipes *parser, char **exec_path, int pipe_fd[2])
{
	int		i;
	int		status;

	i = 0;
	pipe_fd = ft_pipe(parser, exec_path, pipe_fd);
	if (parser->next != NULL)
		line_command(parser->next, exec_path, pipe_fd);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	//free(pipe_fd);
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
