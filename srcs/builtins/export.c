/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:47 by user42            #+#    #+#             */
/*   Updated: 2021/10/04 15:27:32 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ft_test_new_env(char *var, t_path *path, char *dst)
{
	int	a;
	int	b;

	b = 0;
	a = 0;
	while (var[a] != '\0' && var[a] != '='
		&& (var[a] != '+' || var[a + 1] != '='))
	{
		if (!ft_compare_c_to_s(var[a++], ENV))
			b = 1;
	}
	if (a == 0 || b == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(dst, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		ft_putstr_fd("\n", 2);
		free(var);
		path->exit_status = 1;
		return (1);
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
			if (var[ft_strlen(buf)] != '+')
			{
				free(env[x]);
				env[x] = ft_strdup(var);
			}
			else
				env[x] = ft_strjoin(env[x], &var[ft_strlen(buf) + 2]);
		}
		x++;
	}
	free(buf);
	return (env);
}

int	ft_size_arg_add(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '='
		&& (str[i] != '+' || str[i + 1] != '='))
		i++;
	return (i);
}

char	**env_add(char **env, char *var, t_path *path)
{
	int		i;
	char	*buf;

	(void)(path);
	i = -1;
	buf = ft_strndup(var, ft_size_arg_add(var));
	if (ft_test_new_env(buf, path, var))
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
