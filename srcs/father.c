/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:02:22 by gbabeau           #+#    #+#             */
/*   Updated: 2021/10/02 17:19:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	father_2(t_pipes *pipes, t_path *path)
{
	int		i;

	i = 0;
	if (pipes->builtin == 1)
	{
		check_builtins(pipes, path, path->path);
		ft_free(path->parser, path);
		exit(EXIT_SUCCESS);
	}
	while (pipes->command[0] != NULL
		&& path->exec_path && path->exec_path[i] != NULL
		&& ft_compare_c_to_s('/', pipes->command[0]) == 0)
	{
		if (path->exec_path[i] != NULL)
			ft_execve(path->exec_path[i++], pipes->command[0],
				pipes->command, path->path);
	}
	if (pipes->command != NULL && pipes->command[0] != NULL
		&& ft_compare_c_to_s('/', pipes->command[0]))
		ft_excve_2(pipes, path);
	if (pipes->command[0] != NULL)
		command_not_found(pipes, path);
	ft_free(path->parser, path);
	exit(EXIT_SUCCESS);
}

void	ft_father_error(t_path *path)
{
	ft_free(path->parser, path);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

pid_t	father(t_pipes *pipes, t_path *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_signal(2);
		if (pipes->error == 0)
			ft_father_error(path);
		father_2(pipes, path);
	}
	waitpid(pid, &path->exit_status, 0);
	return (pid);
}

void	ft_dup_redi(t_pipes *pipes, int buf[2])
{
	if (pipes->put[0] == 1)
	{
		dup2(buf[0], STDIN_FILENO);
	}
	if (pipes->put[1] == 1)
	{
		dup2(buf[1], STDOUT_FILENO);
	}
}

pid_t	father_0(t_pipes *pipes, t_path *path, int buf[2])
{
	pid_t	pid_3;

	ft_dup_redi(pipes, buf);
	ft_close(buf[1], buf[0], path->pipe_in, path->pipe_out);
	pid_3 = father(pipes, path);
	path->exec = 1;
	return (pid_3);
}
