/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:19:34 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/09 15:00:57 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	ft_free_redi(t_redi *redi)
{
	free(redi);
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
