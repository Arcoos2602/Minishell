/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:03:19 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/30 16:41:39 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/include/libft.h"
#include "../includes/minishell.h"

/// PB QUAND FINIT PAR CTRLD

int 	redirect_out(char *put ,t_redi *redi, int *pipe_out)
{
	if (redi->type == 1)
	{
		*put = 1;
	//	if (*pipe_out > 0)
	//		close(*pipe_out);
		*pipe_out = open(redi->put, O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0666);
	}
	if (redi->type == 2)
	{
		*put = 1;
	//	if (*pipe_out > 0)
	//		close(*pipe_out);
		*pipe_out = open(redi->put, O_APPEND | O_CREAT | O_RDWR, 0666);	
	}
	printf("[%d]\n", *put);
	if (redi->next != NULL)
	{
		printf("[%d]\n", *put);
		redirect_out(put, redi->next, pipe_out);
	}
		
	return (1);
}

int		redirect_in(char put[2] ,t_redi *redi, int *pipe_in)
{
	int fd;

	if (redi->type == 0)
	{
	//	if (*pipe_in > 0)
	//		close(*pipe_in);
		if ((*pipe_in = open(redi->put, O_APPEND | O_RDWR, 0666)) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		redi->type = -1;
		put[0] = 1;
	}
		printf("PIPE_IN (REDIR) : %d\n", *pipe_in);
	if (redi->next != NULL)
		redirect_in(put, redi->next, pipe_in);
	return (1);
}

pid_t	father(t_pipes *pipes, int pipe_fd[2], t_path path, int pipe_fd_in[2]) // pas a la norme
{
	int			i;
	char		*dest;
	pid_t		pid;
	int ret;

	ret = 0;
	dest = NULL;
	i = 0;
	printf("NBR_4\n");
	//if (pipes->put[0] == 1)
	//	close(pipe_fd_in[1]);
	//else 
	if (path.pipe_out != -1 || pipes->put[1] == 1)
		close(pipe_fd[0]);
	pid = fork();
	if (pid == 0)
	{
			printf("DUP_PIPE : %d\n", pipe_fd[1]);
			if (path.pipe_out != -1 || pipes->put[1] == 1)
				dup2(pipe_fd[1], STDOUT_FILENO);
	
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
	//printf("NBR_3\n");
	waitpid(pid,NULL, 0);
	//printf("NBR_2\n");
	if (dest != NULL)
		free(dest);
	return (pid);
}

int		ft_pipe(t_pipes *pipes, t_path *path, pid_t *pid_2) // pas oublier de free le dernier dest
{
	int			pipe_fd[2];
	int			pipe_fd_in[2];
	int			signum;
	int			buf[2];
	pid_t		  pid;
	pid_t		 pid_3;

	//printf("beginning : %d\n", path->pipe_in);
	buf[0] = -1;
	buf[1] = -1;
	if (pipes->redi != NULL)
	{	
			if (redirect_in(&pipes->put[0], pipes->redi, &buf[0]) == 0) // redirection d'entrée
				return (0);
			if (redirect_out(&pipes->put[1], pipes->redi, &buf[1]) == 0)
				return (0);
	}
	if (buf[0] > -1)
	pipes->put[0] = 1;
	if(buf[1] > -1)
	pipes->put[1] = 1;
	printf("%d %d\n",pipes->put[0], pipes->put[1]);
	if (pipes->put[0] == 1)
	{
		//if (pipe(pipe_fd_in) == -1)
		//{
		//	ft_putstr_fd(strerror(errno), 2);
		//	return (-1);
		//}
		pipe_fd_in[0] = buf[0];
		pipe_fd_in[1] = pipe_fd[0];
	}
	else if (pipes->next != NULL || pipes->put[1] == 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (-1);
		}
		if(pipes->put[1] == 1)
			pipe_fd[1] = buf[1];
	}
	
		
	


	pid = fork();
	if (pid != 0)
	{
		path->pipe_out = pipe_fd[1];
		printf("%d\n", path->pipe_out);
		pid_3 = father(pipes, pipe_fd, *path, pipe_fd_in);
		close(path->pipe_out);
		close(path->pipe_in);
		close(pipe_fd[1]);
		if (*pid_2 != 0)
		{
			waitpid(pid, NULL, 0);;
			exit(EXIT_SUCCESS);
	}
		return (1);
	}
	else
	{
		path->pipe_in = pipe_fd[0];
		if (pipes->next != NULL || pipes->put[1] == 1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
		}
		path->first[0] = 1;
		close(pipe_fd[0]);
		*pid_2 = 1;
		if(pipes->next != NULL)
			ft_pipe(pipes->next, path, pid_2);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int		line_command(t_pipes *parser, t_path *path, pid_t *pid_2) // getpid
{
	int           options;
	int			  status;

	ft_pipe(parser, path, pid_2);
	//printf("[%d]\n", *pid_2);
	/*if (pipe_fd == 0)
	{
		return (0);
	}*/
//	if (parser->next != NULL && *pid_2 == 1)
//	{
	//	line_command(parser->next, path, pid_2);
//	}
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
		exit(EXIT_SUCCESS);
	}
	//printf("PERE\n");
	wait(NULL);
	//printf("PERE2\n");
	if (parser->next != NULL)
		ft_shell(parser->next, path);
	return (1);
}
