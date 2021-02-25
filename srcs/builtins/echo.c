/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:24:14 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/25 14:36:25 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../libft/include/libft.h"

int		ft_echo(char **arg, int	i)
{
	check_arg(arg[i++]);
	ft_putstr_fd(arg, 1);
}
