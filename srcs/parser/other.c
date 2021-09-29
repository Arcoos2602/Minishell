/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:30:09 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/29 14:36:52 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	nbr_words_exe(char **lexer, int *i)
{
	int	nbr_words_exe;

	nbr_words_exe = 0;
	if (*i > 1 && lexer[*i - 1][0] == '|'
		&& ft_compare_c_to_s(lexer[*i - 2][0], "><"))
		return (0);
	while (lexer[*i] != NULL && !ft_compare_c_to_s(lexer[*i][0], "|><;"))
	{
		nbr_words_exe++;
		*i += 1;
	}
	return (nbr_words_exe);
}

void	*p_malloc(char ***tab, int size)
{
	tab = malloc(sizeof(char **) * size);
	if (tab == NULL)
		return (NULL);
	tab[size - 1] = NULL;
	return (tab);
}

void	ambigous(t_redi *redi, char **lexer, t_path *path)
{
	redi->type = -10;
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(lexer[1], 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	path->exit_status = 1;
}

int	words_command(char **lexer, int i)
{
	int	nbr_words;

	nbr_words = 1;
	while (lexer[i] != NULL)
	{
		i++;
		if (lexer[i - 1][0] == '|')
			nbr_words++;
	}
	if (lexer[i] == NULL)
		i = 0;
	return (nbr_words);
}

char	**malloc_tb_str(char **dst, char **in, int size)
{
	dst = malloc(sizeof(char *) * (size + 1));
	if (dst == NULL)
		return (NULL);
	dst[size] = NULL;
	while (size-- > 0)
		dst[size] = ft_strdup(in[size]);
	return (dst);
}
