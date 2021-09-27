/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:51:37 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 12:55:17 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

static void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		g_global = 130;
	}
	if (signum == SIGQUIT)
	{
		//rl_replace_line("", 0);
		g_global = 131;
	}
}

void ft_signal(void)
{
	
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
