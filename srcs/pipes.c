/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/12 10:43:32 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

/// PB QUAND FINIT PAR CTRLD

int		redirect(char put[1] ,t_redi *redi, int *pipe_in, int *pipe_out)
{
	int fd;

	if (redi->type == 0)
	{
		if ((*pipe_in = open(redi->put, O_APPEND | O_RDWR, 0666)) == -1)
			return (0);
	}
	if (redi->type == 1)
	{
		put[0] = 1;
		*pipe_out = open(redi->put, O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0666);
		printf("{%d}\n", *pipe_out);
	}
	if (redi->type == 2)
	{
		put[0] = 1;
		*pipe_out = open(redi->put, O_APPEND | O_CREAT | O_RDWR, 0666);	
	}
	if (redi->next != NULL)
		redirect(put, redi->next, pipe_in, pipe_out);
	return (1);
}

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
		if (pipes->next != NULL || pipes->output == 1)
			dup2(pipe_fd_2[1], 1);
		while (exec_path[i++] != NULL)
		{
			dest = ft_strjoin(exec_path[i], pipes->command[0]);
			execve(dest, &pipes->command[0], (char *const*) NULL); // variable env, repertoire de travail
			free(dest);
		}
		if (pipes->command != NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(pipes->command[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
}

int		*ft_pipe(t_pipes *pipes, char **exec_path, int pipe_fd[2])
{
	pid_t		pid;
	int			*pipe_fd_2;
	char		*dest;
	int			signum;

	pipe_fd_2 = malloc(sizeof(int) *2);
	if (pipes->next != NULL || pipes->output == 1)
		if (pipe(pipe_fd_2) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (NULL);
		}	
	if (pipes->redi != NULL)
	{

		printf("%d\n",pipe_fd_2[1]);
		redirect(&(pipes->output) ,pipes->redi, &pipe_fd[0], &pipe_fd_2[1]);
		printf("%d, %d\n",pipe_fd_2[1], (int)pipes->output);
	}
	printf("%d\n",pipe_fd_2[1]);
	pid = fork();
	father(pipes, pid, pipe_fd, pipe_fd_2, dest, exec_path);
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (pipes->next != NULL)
		free(pipe_fd);
	//free(dest);
	/*if (pipes->next != NULL || pipe_fd_2[1] != -1)
	{
		close(pipe_fd_2[1]);
		close(pipe_fd_2[0]);
	}*/
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
