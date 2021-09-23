/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:02:22 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/24 01:39:57 by user42           ###   ########.fr       */
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

	i = 0;
	while (pipes->command[0] != NULL && path->exec_path[i++] != NULL
		&& ft_compare_c_to_s('/', pipes->command[0]) == 0)
	{
		if (path->exec_path[i] != NULL)
			ft_execve(path->exec_path[i], pipes->command[0],
				pipes->command, path->path);
	}
	if (ft_compare_c_to_s('/', pipes->command[0]))
		execve(pipes->command[0], &pipes->command[0], NULL);
	if (pipes->command[0] != NULL && pipes->command[0][0] != '$' && 0 == check_builtins(pipes, path ,path->path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pipes->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	ft_free(pipes, path);
	exit(EXIT_SUCCESS);
}

void	ft_father_error(t_pipes *pipes, t_path *path)
{
	ft_free(pipes, path);
	exit(EXIT_FAILURE);
}

pid_t	father(t_pipes *pipes, t_path *path)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (pipes->error == 0)
			ft_father_error(pipes, path);
		father_2(pipes, path);
	}
	waitpid(pid, &path->exit_status, 0);


	return (pid);
}

pid_t	father_0(t_pipes *pipes, t_path *path, int buf[2])
{
	pid_t	pid_3;

		if (pipes->put[0] == 1)
		{
		dup2(buf[0], STDIN_FILENO);	
		}
		if (pipes->put[1] == 1)
		{
			ft_putnbr_fd(path->pipe_out,2);
			dup2(buf[1],STDOUT_FILENO);	
		}

		pid_3 = father(pipes, path);


//	ft_close(buf[1], buf[0], path->pipe_in, path->pipe_out);
//	dup2(path->out_fd, 1);
//	dup2(path->in_fd, 0);
	path->exec = 1;
	return (pid_3);
}
