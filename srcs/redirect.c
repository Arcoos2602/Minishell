/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:23:02 by user42            #+#    #+#             */
/*   Updated: 2021/10/04 09:35:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	file_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

void	ft_free_redi(t_redi *redi)
{
	free(redi);
}

int	init_redi(t_path *path, t_pipes *pipes, int buf[2])
{
	if (pipes->redi == NULL)
		return (1);
	if (pipes->redi->type == -10)
		return (0);
	if (redirect_in(path, &pipes->put[0], pipes->redi, &buf[0]) == 0)
		return (0);
	if (redirect_out(&pipes->put[1], pipes->redi, &buf[1]) == 0)
		return (0);
	return (1);
}

int	redirect_out(int *put, t_redi *redi, int *pipe_out)
{
	if (redi->type == 1)
	{
		*put = 1;
		*pipe_out = open(redi->put,
				O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (*pipe_out == -1)
			return (file_error(redi->put));
	}
	if (redi->type == 2)
	{
		*put = 1;
		*pipe_out = open(redi->put,
				O_APPEND | O_CREAT | O_RDWR, 0664);
		if (*pipe_out == -1)
			return (file_error(redi->put));
	}
	if (redi->type == -10)
		return (0);
	if (redi->next != NULL)
	{
		if (*pipe_out >= 0 && (redi->type == 1 || redi->type == -10))
			close(*pipe_out);
		redirect_out(put, redi->next, pipe_out);
	}
	return (1);
}

int	redirect_in(t_path *path, int *put, t_redi *redi, int *pipe_in)
{
	if (redi->type == 0)
	{
		*pipe_in = open(redi->put, O_RDONLY);
		if (*pipe_in == -1)
			return (file_error(redi->put));
		redi->type = -1;
		*put = 1;
	}
	else if (redi->type == 10)
	{
		if (0 == ft_open_here_doc(redi, path, pipe_in, put))
			return (0);
	}
	if (redi->type == -10)
		return (0);
	if (redi->next != NULL)
	{
		if (*pipe_in >= 0 && (redi->type == 0 || redi->type == 10))
			close(*pipe_in);
		redirect_in(path, put, redi->next, pipe_in);
	}
	return (1);
}
