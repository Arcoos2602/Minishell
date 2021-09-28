/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:30:04 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 02:02:34 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char	*ft_getenv(char **paths, char *var)
{
	int	x;
	int	j;

	x = 0;
	while (paths[x] != NULL)
	{
		j = 0;
		while (paths[x][j] != '=')
			j++;
		if ((int)(ft_strlen(var)) == j
			&& ft_strncmp(var, paths[x], ft_strlen(var)) == 0)
			return (&paths[x][j + 1]);
		x++;
	}
	return (NULL);
}

int	check_builtins(t_pipes	*pipes, t_path *path, char **env)
{
	if (ft_strncmp(pipes->command[0], "exit", 5) == 0)
		ft_exit(path, pipes);
	else if (ft_strncmp(pipes->command[0], "env", 4) == 0)
		ft_env(env);
	else if (ft_strncmp(pipes->command[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(pipes->command[0], "echo", 5) == 0)
		ft_echo(pipes);
	else if (ft_strncmp(pipes->command[0], "export", 7) == 0)
		env = ft_export(pipes, env, path);
	else if (ft_strncmp(pipes->command[0], "unset", 6) == 0)
		env = ft_unset(pipes, env);
	else if (ft_strncmp(pipes->command[0], "cd", 3) == 0)
		ft_cd(pipes, env);
	else
		return (0);
	path->path = env;
	return (1);
}
