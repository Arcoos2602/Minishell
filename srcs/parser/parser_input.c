/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:51:02 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/19 14:48:42 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char		**init_input_2(char **input, char **lexer, int nbr_input, int *i)
{
	int nbr_word;

	while (lexer[*i][0] != '<')
		*i += 1;
	if (lexer[*i][0] == '|')
		return( NULL);
	*i += 1;
	nbr_word = nbr_words_exe(lexer, i);
	*i -= nbr_word;
	printf("%s\n", lexer[*i]);
	if (NULL == (input = malloc_tb_str(input, &lexer[*i], nbr_word)))
		return (NULL);
	i++;
	return (input);
}

char		***init_input(char ***input, char **lexer)
{
	int	nbr_input;
	int i;
	int n;

	n = -1;
	i = 0;
	nbr_input = init_inouput(lexer, "<");
	if (0 == (input = malloc(sizeof(char**) * (nbr_input + 1))))
		return (NULL);
	input[nbr_input] = NULL;
	while (++n != nbr_input)
		if (0 == (input[n] = init_input_2(input[n], &lexer[i], nbr_input, &i)))
			return (NULL);
	return (input);
}
