/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:10:16 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/28 00:35:13 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	ft_free(t_parser *parser, t_path *paths)
{
	if (parser != NULL && parser->next != NULL)
		ft_free(parser->next, NULL);
	if (parser != NULL)
		free_parser(parser);
	parser = NULL;
	if (paths != NULL && paths->exec_path != NULL)
	{
		ft_free_paths(paths->exec_path);
		paths->exec_path = NULL;
		if (paths->path != NULL)
			ft_free_paths(paths->path);
		paths->path = NULL;
	}
	rl_clear_history();
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
	if (paths != NULL)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			paths[i++] = NULL;
		}
		free(paths);
	}
}

void	free_paths(t_path *path)
{
	int	i;

	i = 0;
	if (path != NULL && path->exec_path != NULL)
	{
		while (path->exec_path[i] != NULL)
			free(path->exec_path[i++]);
		free(path->exec_path);
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
