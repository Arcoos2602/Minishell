/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:24:50 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 02:23:37 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	chemin[PATH_MAX];

	ft_putstr_fd(getcwd(chemin, PATH_MAX), 1);
	ft_putstr_fd("\n", 1);
}
