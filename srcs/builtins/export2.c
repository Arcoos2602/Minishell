/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 15:51:24 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 16:05:19 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char	**new_env_exp(char **env, char *to_add, int size)
{
	char	**new;
	int		x;

	x = 0;
	new = malloc(sizeof(char *) * (size + 2));
	while (env[x] != NULL)
	{
		new[x] = ft_strdup(env[x]);
		free(env[x]);
		x++;
	}
	new[x++] = ft_strdup(to_add);
	new[x++] = NULL;
	free(env);
	return (new);
}

int	ft_print_env_2(char **env, char *str, int i)
{
	int	n;
	int	pos;
	int	size;

	n = 0;
	pos = 0;
	size = ft_strlen(str);
	while (env[n] != NULL)
	{
		if (ft_strncmp(str, env[n], size) > 0)
			pos++;
		n++;
	}
	if (pos == i)
		return (1);
	return (0);
}

int	ft_compte_env(char *str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

void	ft_print_env_3(char *str)
{
	int	n;

	n = ft_compte_env(str);
	write(1, "export ", 7);
	write(1, str, n + 1);
	write(1, "\"", 1);
	write(1, &str[n + 1], ft_strlen(&str[n + 1]));
	write(1, "\"\n", 2);
}

void	ft_print_env_alp(char **env)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (env[i] != NULL)
	{
		while (env[nbr] != NULL)
		{
			if (ft_print_env_2(env, env[nbr], i))
				ft_print_env_3(env[nbr]);
			nbr++;
		}
		i++;
		nbr = 0;
	}
}
