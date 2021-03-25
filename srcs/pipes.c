/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/25 17:01:37 by tcordonn         ###   ########.fr       */
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

pid_t	father(t_pipes *pipes, int pipe_fd[2], int pipe_fd_2[2], t_path path, pid_t pid_2) // pas a la norme
{
	int			i;
	char		*dest;
	pid_t		pid;
	int ret;

	ret = 0;
	dest = NULL;
	i = 0;
	printf("NBR_4\n");
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
	printf("NBR_3\n");
	//wait(NULL);
	printf("NBR_2\n");
	//waitpid(-1, &ret,0);
	if (dest != NULL)
		free(dest);
	return (pid);
}

int		*ft_pipe(t_pipes *pipes, int pipe_fd[2], t_path path, pid_t *pid_2) // pas oublier de free le dernier dest
{
	int			*pipe_fd_2;
	int			signum;
	pid_t		  pid;
	pid_t		 pid_3;

	pipe_fd_2 = ft_calloc(2, sizeof(int));
	if (pipes->next != NULL || pipes->output == 1)
		if (pipe(pipe_fd_2) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (NULL);
		}
	if (pipes->redi != NULL)
	{
		if (redirect(&(pipes->output) ,pipes->redi, &pipe_fd[0], &pipe_fd_2[1]) == 0)
			return (0);
	}
	pid = fork();
	if (pid != 0)
	{
		pid_3 = father(pipes, pipe_fd, pipe_fd_2, path, *pid_2);
		printf("NBR\n");
		
		if (*pid_2 == 0)
			waitpid(pid_3 ,NULL,0);
		else
		{
			printf("A\n");
			waitpid(pid,NULL,0);
			printf("B\n");
			printf("C\n");
			exit(EXIT_SUCCESS);
		}
		if (pipe_fd_2[0] != 0)
		{
			close(pipe_fd_2[1]);
			close(pipe_fd_2[0]);
		}
		return (pipe_fd);
	}
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
	}
	*pid_2 = 1;
	return (pipe_fd_2);
}

int			*line_command(t_pipes *parser, int pipe_fd[2], t_path path, pid_t *pid_2) // getpid
{
	int           options;
	int			  status;
	struct        rusage rusage;

	
	pipe_fd = ft_pipe(parser, pipe_fd, path, pid_2);
	if (pipe_fd == 0)
	{
		return (0);
	}
	if (parser->next != NULL && *pid_2 == 1)
	{
		line_command(parser->next, pipe_fd, path, pid_2);
	}
	return (pipe_fd);
}

int			*ft_shell(t_parser *parser, int pipe_fd[2], t_path path)
{
	int		i;
	int			  status;
	struct        rusage rusage;
	int		pid_2;

	i = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pid_2 = 0;
	pipe_fd = line_command(parser->pipe, pipe_fd, path, &pid_2);
	if (pid_2 != 0)
	{
		printf("FILS\n");
		exit(EXIT_SUCCESS);
	}
		printf("PERE\n");
	wait(NULL);
	if (pipe_fd == 0)
		return (0);
	if (parser->next != NULL)
		ft_shell(parser->next, pipe_fd, path);
	return (pipe_fd);
}