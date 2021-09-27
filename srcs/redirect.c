/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:19:34 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 12:30:16 by gbabeau          ###   ########.fr       */
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
	pipes->put[0] = -1;
	pipes->put[1] = -1;
	buf[0] = -1;
	buf[1] = -1;
	if (pipes->redi == NULL)
		return (1);
	if (redirect_in(path, &pipes->put[0], pipes->redi, &buf[0]) == 0)
		return (0);
	if (redirect_out(&pipes->put[1], pipes->redi, &buf[1]) == 0)
		return (0);
	return (1);
}

int	redirect_out(char *put, t_redi *redi, int *pipe_out)
{
	if (*pipe_out > 0)
		close(*pipe_out);
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
	if (redi->next != NULL)
	{
		redirect_out(put, redi->next, pipe_out);
	}
	return (1);
}

int	redirect_in(t_path *path, char *put, t_redi *redi, int *pipe_in)
{
	if (*pipe_in > 0)
		close(*pipe_in);
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
		ft_free_redi_double(redi, path);
		*pipe_in = open(".test", O_RDONLY);
		unlink(".test");
		if (*pipe_in == -1)
			return (file_error(redi->put));
		redi->type = -1;
		*put = 1;
	}
	if (redi->next != NULL)
		redirect_in(path, put, redi->next, pipe_in);
	return (1);
}
