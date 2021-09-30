/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 06:18:48 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/30 06:40:24 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	ft_open_here_doc(t_redi *redi, t_path *path, int *pipe_in, int *put)
{
	ft_free_redi_double(redi, path);
	*pipe_in = open(".test", O_RDONLY);
	unlink(".test");
	if (*pipe_in == -1)
		return (file_error("here-doc"));
	redi->type = -1;
	*put = 1;
	return (1);
}
