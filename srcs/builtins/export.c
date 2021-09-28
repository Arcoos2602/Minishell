/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:47 by user42            #+#    #+#             */
/*   Updated: 2021/09/28 16:02:23 by tcordonn         ###   ########.fr       */
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
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier", 2);
			ft_putstr_fd("\n", 2);
			free(var);
			return (1);
		}
	}
	return (0);
}

char	**env_add2(char **env, char *var, char *buf)
{
	int	x;
	int	j;

	x = 0;
	while (env[x] != NULL)
	{
		j = 0;
		while (env[x][j] != '=')
			j++;
		if (j == (int)(ft_strlen(buf))
			&& ft_strncmp(buf, env[x], ft_strlen(buf)) == 0)
		{
			free(env[x]);
			env[x] = ft_strdup(var);
		}
		x++;
	}
	free(buf);
	return (env);
}

int	ft_size_arg_add(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	**env_add(char **env, char *var, t_path *path)
{
	int	i;
	char *buf;
	(void)(path);

	i = -1;
	buf = ft_strndup(var, ft_size_arg_add(var));
	if (ft_test_new_env(buf))
		return (env);
	if (ft_getenv(env, buf) == NULL && ft_compare_c_to_s('=', var))
	{
		while (env[++i] != NULL)
			;
		env = new_env_exp(env, var, i);
		free(buf);
	}
	else if (ft_getenv(env, buf) != NULL && ft_compare_c_to_s('=', var))
	{
		return (env_add2(env, var, buf));
	}
	else
	  free(buf);
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
