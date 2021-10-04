/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:29:37 by gbabeau           #+#    #+#             */
/*   Updated: 2021/10/04 15:35:47 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

void	init_path_shell(t_path *path)
{
	path->first[0] = 0;
	path->pipe_in = -1;
	path->pipe_out = -1;
	path->starting = 1;
	path->dont = 0;
	path->exec = 0;
	path->father = 1;
	path->buffer_fd[0] = -1;
	path->buffer_fd[1] = -1;
}

void	init_ft_pipe(t_pipes *pipes, int buf[2])
{
	pipes->put[0] = -1;
	pipes->put[1] = -1;
	buf[0] = -1;
	buf[1] = -1;
}
