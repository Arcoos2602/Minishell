/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:30:09 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/28 13:57:00 by tcordonn         ###   ########.fr       */
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

int	words_command(char **lexer, int i)
{
	int	nbr_words;

	nbr_words = 1;
	while (lexer[i] != NULL && lexer[i++][0] != ';')
	{
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
	dst[size] = NULL;
	while (size-- > 0)
		dst[size] = ft_strdup(in[size]);
	return (dst);
}
