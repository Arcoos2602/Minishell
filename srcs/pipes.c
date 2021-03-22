/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/22 15:33:08 by tcordonn         ###   ########.fr       */
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
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
	}
	if (redi->type == 1)
	{
		put[0] = 1;
		*pipe_out = open(redi->put, O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0666);
		//printf("{%d}\n", *pipe_out);
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

pid_t	father(t_pipes *pipes, int pipe_fd[2], int pipe_fd_2[2], t_path path) // pas a la norme
{
	int			i;
	char		*dest;
	pid_t		pid;
	int ret;

	ret = 0;
	dest = NULL;
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		if (pipe_fd[0] != -1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
		}
		if (pipes->next != NULL || pipes->output == 1)
			dup2(pipe_fd_2[1], STDOUT_FILENO);
		while (pipes->command[0] != NULL && path.exec_path[i++] != NULL)
		{
			check_builtins(pipes, path.path);
			dest = ft_strjoin(path.exec_path[i], pipes->command[0]);
			execve(dest, &pipes->command[0], (char *const*) NULL); // variable env, repertoire de travail
			free(dest);
		}
		if (pipes->command[0] != NULL && pipes->command[0][0] != '$')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(pipes->command[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(EXIT_SUCCESS);
	}
	wait(&pid);
	printf("dwadaw\n");
	if (dest != NULL)
		free(dest);
	kill(0,0);
	return (pid);
}

int		*ft_pipe(t_pipes *pipes, int pipe_fd[2], t_path path, pid_t *pid_2) // pas oublier de free le dernier dest
{
	int			*pipe_fd_2;
	int			signum;
	pid_t		  pid;

	pipe_fd_2 = ft_calloc(2, sizeof(int));
	if (pipes->next != NULL || pipes->output == 1)
		if (pipe(pipe_fd_2) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (NULL);
		}
	if (pipes->redi != NULL)
	{
		//printf("%d\n", pipe_fd_2[1]);
		if (redirect(&(pipes->output) ,pipes->redi, &pipe_fd[0], &pipe_fd_2[1]) == 0)
			return (0);
		//printf("%d, %d\n", pipe_fd_2[1], (int)pipes->output);
	}
	// printf("pipe_fd[0] = %d, pipe_fd[1] = %d\n pipe_fd_2[0] = %d, pipe_fd_2[1] = %d\n",pipe_fd[0], pipe_fd[1], pipe_fd_2[0], pipe_fd_2[1]); // pipe_fd_2 = 0 : cat | > a
	pid = fork();
	if (pid != 0)
		*pid_2 = father(pipes, pipe_fd, pipe_fd_2, path);
	else
	{
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (pipes->next != NULL)
		free(pipe_fd);
	//free(dest);
	if (0)
	{
		printf("AAAAH\n");
		close(pipe_fd_2[1]);
		close(pipe_fd_2[0]);
	}
	}
	return (pipe_fd_2);
}

int			*line_command(t_pipes *parser, int pipe_fd[2], t_path path) // getpid
{
	int			  status;
	struct        rusage rusage;

	pid_t	 		pid_2;
	int           options;

		pipe_fd = ft_pipe(parser, pipe_fd, path, &pid_2);
		if (pipe_fd == 0)
			return (0);
		if (parser->next != NULL)
			line_command(parser->next, pipe_fd, path);
	//wait3(&status, 0, &rusage);
	printf("A\n");
	return (pipe_fd);
}

int			*ft_shell(t_parser *parser, int pipe_fd[2], t_path path)
{
	int		i;
	
	i = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pipe_fd = line_command(parser->pipe, pipe_fd, path);
	if (pipe_fd == 0)
		return (0);
	if (parser->next != NULL)
		ft_shell(parser->next, pipe_fd, path);
	return (pipe_fd);
}
