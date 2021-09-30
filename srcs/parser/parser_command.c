/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:04:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/30 03:52:17 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ft_count(char *str, int *i, char *test)
{
	int	cpt;

	cpt = 0;
	while (str[*i] != '\0' && !ft_compare_c_to_s(str[*i], test))
	{
		cpt++;
		++*i;
	}
	return (cpt);
}

char	*ft_dol(char *str, int *i, t_path *path)
{
	char	*env;
	char	*buff;
	int		cpt;

	cpt = ft_count(str, i, "'$ \" | > <?");
	env = ft_substr(str, *i - cpt, cpt);
	buff = ft_getenv(path->path, env);
	free(env);
	return (buff);
}
