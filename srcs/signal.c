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

static void	int_handler(int signum)
{
	rl_on_new_line();
	g_global = signum;
	//g_global = 130;
}

static void	quit_handler(int signum)
{
	g_global = signum;
	//g_global = 131;
	//exit(0);
}


void ft_signal(void)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);
}
