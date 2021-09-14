/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:10:16 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/09 15:01:55 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

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

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	if(paths != NULL)
	{
	while (paths[i] != NULL)
	{
		free(paths[i]);
		paths[i++] = NULL;
	}
	free(paths);
	}
}

int	exit_ft_parser(pid_t pid, t_parser *parser, t_path *path)
{
	if (pid != 0)
	{
		waitpid(pid, &g_global, 0);
			ft_putstr_fd("g_global3 =",2);
	ft_putnbr_fd(g_global,2);
	ft_putstr_fd("\n",2);
	}
	waitpid(pid, &g_global, 0);
			ft_putstr_fd("g_global4 =",2);
	ft_putnbr_fd(g_global,2);
	ft_putstr_fd("\n",2);
	free_parser(parser);
	free_paths(path);
	//rl_clear_history();
	wait(&g_global);
				ft_putstr_fd("g_global8 =",2);
	ft_putnbr_fd(g_global,2);
	ft_putstr_fd("\n",2);
	ft_putstr_fd("-1-",2);
	exit(EXIT_SUCCESS);
}

int	exit_ft_pipe(pid_t pid, t_pipes *pipes, t_path *path)
{
	if (pid != 0)
	{
		waitpid(pid, &g_global, 0);
		ft_putstr_fd("g_global5 =",2);
		ft_putnbr_fd(g_global,2);
		ft_putstr_fd("\n",2);
	}
	waitpid(pid,&g_global, 0);
	ft_putstr_fd("g_global6 =",2);
	ft_putnbr_fd(g_global,2);
	ft_putstr_fd("\n",2);
	ft_free(pipes, path);
	free_paths(path);
	//rl_clear_history();
	wait(&g_global);
	ft_putstr_fd("g_global7 =",2);
	ft_putnbr_fd(g_global,2);
	ft_putstr_fd("\n",2);
	ft_putstr_fd("-2-",2);
	exit(EXIT_SUCCESS);
}
