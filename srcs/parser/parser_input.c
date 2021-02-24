/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:51:02 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/22 12:04:10 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char		**init_input_2(char **input, char **lexer, int nbr_input, int *i)
{
	int nbr_word;
	if (*i < 2 && 1 == init_inouput_back(lexer, "<"))
	{
		nbr_word = nbr_words_exe(lexer, i);
			if (NULL == (input = malloc_tb_str(input, &lexer[*i], nbr_word)))
				return (NULL);
		return (input);
		*i -= nbr_word;
	}
	else
	{
	while (lexer[*i][0] != '<')
		*i += 1;
	if (*i >= 2)
		if (lexer[*i - 2][0] == '|')
			return (NULL);
	*i += 1;
	nbr_word = nbr_words_exe(lexer, i);
	*i -= nbr_word;
	printf("%s\n", lexer[*i]);
	if (NULL == (input = malloc_tb_str(input, &lexer[*i], nbr_word)))
		return (NULL);
	i++;
	}
	return (input);
}

char		***init_input(char ***input, char **lexer, int deb)
{
	int	nbr_input;
	int	i;
	int	n;

	n = -1;
	i = 0;
	if (deb >= 2)
		nbr_input = init_inouput_back(lexer, "<");
	else
		nbr_input = 0;
	nbr_input += init_inouput(lexer, "<");
	if (0 == (input = malloc(sizeof(char**) * (nbr_input + 1))))
		return (NULL);
	input[nbr_input] = NULL;
	while (++n != nbr_input)
		if (0 == (input[n] = init_input_2(input[n], &lexer[deb], nbr_input, &deb)))
			return (NULL);
	return (input);
}
