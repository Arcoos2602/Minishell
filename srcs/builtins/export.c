/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:47 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 16:03:00 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ft_test_new_env(char *var)
{
	int	a;

	a = 0;
	while (var[a] != '\0' && var[a] != '=')
	{
		if (ft_compare_c_to_s(var[a++], "\"'?$|<>"))
		{
			ft_putstr_fd("ERROR:", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (0);
}

char	**env_add2(char **env, char *var)
{
	int	x;
	int	j;

	x = 0;
	while (env[x] != NULL)
	{
		j = 0;
		while (env[x][j] != '=')
			j++;
		if (ft_strncmp(var, env[x], j) == 0)
			env[x] = ft_strdup(var);
		x++;
	}
	return (env);
}

char	**env_add(char **env, char *var, t_path *path)
{
	int	i;

	i = -1;
	if (ft_test_new_env(var))
		return (env);
	if (ft_getenv(path->path, var) == NULL && ft_compare_c_to_s('=', var))
	{
		while (env[++i] != NULL)
			;
		env = new_env_exp(env, var, i);
	}
	else if (ft_getenv(path->path, var) != NULL && ft_compare_c_to_s('=', var))
		return (env_add2(env, var));
	return (env);
}

char	**ft_export(t_pipes *pipes, char **env, t_path *path)
{
	int	i;

	i = 1;
	if (pipes->command[i] == NULL)
	{
		ft_print_env_alp(env);
		return (env);
	}
	while (pipes->command[i] != NULL)
		env = env_add(env, pipes->command[i++], path);
	return (env);
}
