/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:59:22 by tcordonn          #+#    #+#             */
/*   Updated: 2021/01/28 15:22:56 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int	argc, char **argv, char **path)
{
	char	*const		*env;
	char *tab[] = { "/bin/ls", "-l", NULL}; // path puis option puis envp
	
	execve(tab[0], tab, path);
}