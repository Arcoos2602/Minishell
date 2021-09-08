/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/06/08 16:16:46 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/include/libft.h"
#include "../includes/minishell.h"

/// PB QUAND FINIT PAR CTRLD


void	ft_free_pipe(t_pipes *pipe)
{
	int	i;

	i = 0;
	if (pipe != NULL && pipe->redi != NULL)
		ft_free_redi(pipe->redi);
	if (pipe != NULL)
	{
		while (pipe->command != NULL && pipe->command[i] != NULL)
		{
			free(pipe->command[i]);
			pipe->command[i++] = NULL;
		}
		if (pipe->command != NULL)
			free(pipe->command);
		pipe->command = NULL;
		free(pipe);
		pipe = NULL;
	}
}
void	ft_free_redi(t_redi *redi)
{
	free(redi);
}

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		paths[i++] = NULL;
	}
	free(paths);
}

void	ft_free(t_pipes *pipe, t_path *paths)
{
	if (pipe != NULL && pipe->next != NULL)
		ft_free(pipe->next, NULL);
	if (pipe != NULL)
		ft_free_pipe(pipe);
	if (paths != NULL && paths->exec_path != NULL)
	{
		ft_free_paths(paths->exec_path);
		paths->exec_path = NULL;
	}
}

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

int	exit_ft_parser(pid_t pid, t_parser *parser, t_path *path)
{
	if (pid != 0)
		waitpid(pid, NULL, 0);
	waitpid(pid, NULL, 0);
	free_parser(parser);
	free_paths(path);
    get_next_line(-1, NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}

int	exit_ft_pipe(pid_t pid, t_pipes *pipes, t_path *path)
{
	if (pid != 0)
		waitpid(pid, NULL, 0);
	waitpid(pid, NULL, 0);
	ft_free(pipes, path);
	free_paths(path);
    get_next_line(-1, NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
int	init_redi(t_pipes *pipes, int buf[2])
{
	pipes->put[0] = -1;
	pipes->put[1] = -1;
	if (pipes->redi == NULL)
		return (1);
	if (redirect_in(pipes->command[0], &pipes->put[0],
			pipes->redi, &buf[0]) == 0)
		return (0);
	if (pipes->put[0] == -1)
		if (redirect_out(&pipes->put[1], pipes->redi, &buf[1]) == 0)
			return (0);
	return (1);
}


int	init_fd(t_pipes *pipes, int buf[2], int pipe_fd[2], t_path *path)
{
	if (pipes->next != NULL || pipes->redi != NULL || pipes->put[0] == 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (-1);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	if (pipes->put[0] == 1)
		pipe_fd[0] = buf[0];
	else if (pipes->put[1] == 1)
		pipe_fd[1] = buf[1];
	path->pipe_in = pipe_fd[0];
	return (0);
}

int	redirect_out(char *put, t_redi *redi, int *pipe_out)
{
	if (redi->type == 1)
	{
		*put = 1;
		*pipe_out = open(redi->put,
				O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (*pipe_out == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(redi->put, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
	}
	if (redi->next != NULL)
	{
		redirect_out(put, redi->next, pipe_out);
	}
	return (1);
}

int	redirect_in(char *command, char *put, t_redi *redi, int *pipe_in)
{
	if (redi->type == 0)
	{
		*pipe_in = open(redi->put, O_RDONLY);
		if (*pipe_in == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(redi->put, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		redi->type = -1;
		*put = 1;
	}
	if (redi->next != NULL)
		redirect_in(command, put, redi->next, pipe_in);
	return (1);
}

static void int_handler(int sig)
{
  ft_putchar_fd('\n', 2);
}

static void quit_handler(int sig)
{
  exit(0);
  ft_putchar_fd('\n', 2);
}


int	ft_execve(char *s1, char *s2, char **command, char **env)
{
	char	*dst;
	int		tail1;
	int		tail2;

	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	tail1 = -1;
	tail2 = 0;
	while (s1[++tail1] != '\0')
		dst[tail1] = s1[tail1];
	dst[tail1++] = '/';
	while (s2[tail2] != '\0')
	{
		dst[tail2 + tail1] = s2[tail2];
		tail2++;
	}
	dst[tail1 + tail2] = '\0';
	execve(dst, &command[0], env);
	free(dst);
	return (0);
}

void	father_2(t_pipes *pipes, t_path *path)
{
	int		i;

	i = 0;
	while (pipes->command[0] != NULL && path->exec_path[i++] != NULL
		&& ft_compare_c_to_s('/', pipes->command[0]) == 0)
	{
		if (path->exec_path[i] != NULL)
			ft_execve(path->exec_path[i], pipes->command[0],
				pipes->command, path->path);
	}
	execve(pipes->command[0], &pipes->command[0], NULL);
	if (pipes->command[0] != NULL && pipes->command[0][0] != '$')
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(pipes->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	ft_free(pipes, path);
	exit(0);
}

void	ft_father_error(t_pipes *pipes, t_path *path)
{
	ft_free(pipes, path);
	exit(0);
}

pid_t	father(t_pipes *pipes, int pipe_fd[2], t_path *path)
{
	pid_t	pid;

	if (pipes->next != NULL || pipes->put[1] == 1)
	{
		if (pipe_fd[0] >= 0)
			close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	pid = fork();
	if (pid == 0)
	{
		if (pipes->error == 0)
			ft_father_error(pipes, path);
		father_2(pipes, path);
	}
	wait(NULL);
	if (pipes->next != NULL)
	{
		if (pipe_fd[1] >= 0)
			close(pipe_fd[1]);
	}
	return (pid);
}

pid_t	father_0(t_pipes *pipes, t_path *path,
				int pipe_fd[2])
{
	pid_t	pid_3;

	if (pipes->put[0] == 1)
		pid_3 = 0;
	else
		pid_3 = father(pipes, pipe_fd, path);
	dup2(0, STDOUT_FILENO);
	dup2(1, STDIN_FILENO);
	ft_close(pipe_fd[0], pipe_fd[1], path->pipe_in, path->pipe_out);
	return (pid_3);
}

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

int	ft_pipe(t_pipes *pipe, t_pipes *pipes, t_path *path, pid_t *pid_2)
{
	int		pipe_fd[2];
	int		buf[2];
	pid_t	pid[2];

	pipes->error = init_redi(pipes, buf);
	init_fd(pipes, buf, pipe_fd, path);
	pid[0] = fork();
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
		close(path->pipe_in);
	}
	return (1);
}

int		line_command(t_pipes *parser, t_path *path, pid_t *pid_2) // getpid
{
	ft_pipe(NULL, parser, path, pid_2);
	return (1);
}

int		ft_shell(t_parser *parser, t_path path)
{
	int		i;
	int			  status;
	int		pid_2;

	i = 0;
	pid_2 = 0;
	path.first[0] = 0;
	path.pipe_in = -1;
	path.pipe_out = -1;
	//printf("DEBUT\n");
	line_command(parser->pipe, &path, &pid_2);
	//printf("%d\n",pid_2);
	if (pid_2 != 0)
	{
		//printf("FILS\n");
		exit_ft_parser(0, parser, &path);
	}
  printf("PERE\n");
	wait(NULL);
	dup2(0, STDOUT_FILENO);
	dup2(1, STDIN_FILENO);
  //wait(NULL);
	//printf("PERE2\n");
	if (parser->next != NULL)
		ft_shell(parser->next, path);
	return (1);
}
