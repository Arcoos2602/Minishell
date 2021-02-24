/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:43:40 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/24 15:05:24 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char		**init_output_3(char **output_1, char **output_2, char **lexer)
{
	int	i;

	i = 0;
	if (NULL == (output_1 = malloc_tb_str(output_1, lexer,
						nbr_words_exe(lexer, &i))))
		return (NULL);
	output_2 = NULL;
	return (output_1);
}

void		*init_output_2(t_pipe *new, char **lexer, int *deb, int nbr)
{
	int	i;
	int	n;
	int	nbr_word;

	i = -1;
	if (*deb >= 2 && lexer[0] != NULL && 1 == init_inouput_back(lexer, ">"))
	{
		i++;
		nbr_word = nbr_words_exe(&lexer[-*deb], deb);
		if(lexer[-2][1]== '\0')
		{
			if (NULL == (new->output_s[i] = malloc_tb_str(new->output_s[i], lexer, nbr_word)))
				return (NULL);
				new->output_d[i] = NULL;
		}
		else
		{
			if (NULL == (new->output_d[i] = malloc_tb_str(new->output_d[i], lexer, nbr_word)))
				return (NULL);
				new->output_s[i] = NULL;
		}
	}
	i++;
//	printf("[%p][%p](%d)\n", new->output_s[i], new->output_d[i], i);
	n = 0;
	while (i < nbr)
	{
			printf("(%d)\n", *deb);
		while (lexer[n][0] != '>')
			n++;
		if (lexer[n++][1] == '\0')
		{
//			printf("(%d)\n", *deb);
			if (0 == (new->output_s[i] = init_output_3(new->output_s[i], new->output_d[i],
							&lexer[n])))
				return (NULL);
			else
				new->output_d[i] = NULL;
		}
		else if (0 == (new->output_d[i] = init_output_3(new->output_d[i], new->output_s[i],
						&lexer[n])))
			return (NULL);
		else
			new->output_s[i] = NULL;
		i++;
	}
	return (new);
}

t_pipe		*init_output(t_pipe *new, char **lexer, int deb)
{
	int	nbr;

		if (deb >= 2 && lexer[0] != NULL)
			nbr = init_inouput_back(lexer, ">");
		else
			nbr = 0;
	nbr += init_inouput(lexer, ">>") + init_inouput(lexer, ">");
	new->output_s = malloc(sizeof(char**) * (nbr + 1));
	new->output_d = malloc(sizeof(char**) * (nbr + 1));
	if (NULL == init_output_2(new, lexer, &deb, nbr))
		return (NULL);
	new->output_s[nbr] = NULL;
	new->output_d[nbr] = NULL;
	return (new);
}
