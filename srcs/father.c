/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:02:22 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/27 09:57:47 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

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
	DIR		*test;

	i = 0;
	if (pipes->builtin == 1)
	{
		check_builtins(pipes, path, path->path);
		ft_free(path->parser, path);
		exit(EXIT_SUCCESS);
	}
	while (pipes->command[0] != NULL && path->exec_path && path->exec_path[i] != NULL
		&& ft_compare_c_to_s('/', pipes->command[0]) == 0)
	{

		if (path->exec_path[i] != NULL)
			ft_execve(path->exec_path[i++], pipes->command[0],
				pipes->command, path->path);
	}
	if (pipes->command != NULL && pipes->command[0] != NULL && ft_compare_c_to_s('/', pipes->command[0]))
	{
		test = opendir(pipes->command[0]);
		if (test != NULL)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(pipes->command[0], 2);
			ft_putstr_fd(": est un dossier\n", 2);
			closedir(test);
			ft_free(path->parser, path);
			exit(126);
		}
		execve(pipes->command[0], &pipes->command[0], path->path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pipes->command[0], 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		ft_putnbr_fd(errno,2);
		get_next_line(1, NULL);
		ft_free(path->parser, path);
		if (errno == 2)
			exit(127);
		exit(126);
	}
	if (pipes->command[0] != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pipes->command[0], 2);
		ft_putstr_fd(" : command not found\n", 2);
		ft_free(path->parser, path);
		exit(127);
	}
	ft_free(path->parser, path);
	exit(EXIT_SUCCESS);
}

void	ft_father_error(t_path *path)
{
	ft_free(path->parser, path);
	exit(EXIT_FAILURE);
}

pid_t	father(t_pipes *pipes, t_path *path)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (pipes->error == 0)
			ft_father_error(path);
		father_2(pipes, path);
	}
	waitpid(pid, &path->exit_status, 0);
	return (pid);
}

void ft_dup_redi(t_pipes *pipes , int buf[2])
{
		if (pipes->put[0] == 1)
		{
			dup2(buf[0], STDIN_FILENO);	
		}
		if (pipes->put[1] == 1)
		{
			dup2(buf[1],STDOUT_FILENO);	
		}
}

pid_t	father_0(t_pipes *pipes, t_path *path, int buf[2])
{
	pid_t	pid_3;

		ft_dup_redi(pipes, buf);
		pid_3 = father(pipes, path);
	ft_close(buf[1], buf[0], path->pipe_in, path->pipe_out);
	path->exec = 1;
	return (pid_3);
}
