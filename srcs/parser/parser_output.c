/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:43:40 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/19 14:24:44 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char		**init_output_3(char **output_1, char **output_2, char **lexer)
{
	int i;

	i = 0;
	if (NULL == (output_1 = malloc_tb_str(output_1, lexer,
						nbr_words_exe(lexer, &i))))
		return (NULL);
	output_2 = NULL;
	return (output_1);
}

void		*init_output_2(char ***output_s, char ***output_d,
		char **lexer, int nbr)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	while (++i != nbr)
	{
		while (lexer[n][0] != '>')
			n++;
		if (lexer[n++][1] == '\0')
		{
			if (0 == (output_s[i] = init_output_3(output_s[i], output_d[i],
							&lexer[n])))
				return (NULL);
			else
				output_d[i] = NULL;
		}
		else if (0 == (output_d[i] = init_output_3(output_d[i], output_s[i],
						&lexer[n])))
			return (NULL);
		else
			output_s[i] = NULL;
	}
	return (output_s);
}

t_pipe		*init_output(t_pipe *new, char **lexer)
{
	int	nbr;

	nbr = init_inouput(lexer, ">>") + init_inouput(lexer, ">");
	new->output_s = malloc(sizeof(char**) * (nbr + 1));
	new->output_d = malloc(sizeof(char**) * (nbr + 1));
	new->output_s[nbr] = NULL;
	new->output_d[nbr] = NULL;
	if (NULL == init_output_2(new->output_s, new->output_d, lexer, nbr))
		return (NULL);
	return (new);
}
