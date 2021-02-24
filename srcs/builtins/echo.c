/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:24:14 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/24 10:34:17 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../libft/include/libft.h"


int		ft_echo(char *arg)
{
		
}

int main(int argc, char **argv)
{
	char	*path;
	(void)argc;
	(void)argv;

	path = ft_strdup("../");
	ft_ls(path);
	free(path);
}
