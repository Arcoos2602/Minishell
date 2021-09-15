/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:04 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/15 16:04:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/builtins.h"



char 	*ft_getenv(char **paths, char *var)
{
	int		x;
	int		j;

	x = 0;

	while (paths[x] != NULL)
	{
		j = 0;
		while (paths[x][j] != '=')
        	j++;
		if (ft_strncmp(var, paths[x], j) == 0)
			return (&paths[x][j+1]);
		x++;
	}
	return (" ");
}

int		check_builtins(t_pipes	*pipes, t_path *path, char **env)
{
	if (ft_strncmp(pipes->command[0], "exit", 4) == 0)
		ft_exit(pipes);
	else if (ft_strncmp(pipes->command[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(pipes->command[0], "pwd", 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp(pipes->command[0], "echo", 3) == 0)
		ft_echo(pipes);
  	else if (ft_strncmp(pipes->command[0], "export", 6) == 0)
		env = ft_export(pipes, env);
	else if (ft_strncmp(pipes->command[0], "unset", 5) == 0)
		env = ft_unset(pipes, env);
	else if (ft_strncmp(pipes->command[0], "cd", 2) == 0)
		ft_cd(pipes->command[1], env);
	else 
		return (0);
	path->path = env;
	return (1);
}
