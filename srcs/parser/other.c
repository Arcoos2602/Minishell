/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:30:09 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/22 16:42:07 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int			nbr_words_exe(char **lexer, int *i)
{
	int	nbr_words_exe;

	nbr_words_exe = 0;

	if (*i > 1 && lexer[*i - 1][0] == '|' && ft_compare_c_to_s(lexer[*i - 2][0], "><"))
		return (0);
	while (lexer[*i] != NULL && !ft_compare_c_to_s(lexer[*i][0], "|><;"))
	{
		nbr_words_exe++;
		*i += 1;
	}
	return (nbr_words_exe);
}

void		*p_malloc(char ***tab, int size)
{
	if (0 == (tab = malloc(sizeof(char**) * size)))
		return (NULL);
	tab[size - 1] = NULL;
	return (tab);
}

int			words_command(char **lexer, int i)
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

char		**malloc_tb_str(char **dst, char **in, int size)
{
	dst = malloc(sizeof(char*) * (size + 1));
	dst[size] = NULL;
	while (size-- > 0)
		dst[size] = ft_strdup(in[size]);
	return (dst);
}

int			init_inouput(char **lexer, char *inout)
{
	int	i;
	int	size;
	int	nbr;

	nbr = 0;
	i = 0;
	size = ft_strlen(inout) + 1;
	while (lexer[i] != NULL && lexer[i][0] != ';' && lexer[i][0] != '|')
	{
		if (0 == ft_strncmp(inout, lexer[i++], size))
		{
			if (lexer[i][0] == '|')
				return (nbr);
			nbr++;
		}
	}
	return (nbr);
}

int init_inouput_back(char **lexer, char *inout)
{
	if (lexer[0][0] == inout[0] && lexer[-1][0] == '|')
		return (1);
	return (0);
}
