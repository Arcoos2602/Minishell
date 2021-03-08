
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 13:51:02 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/25 17:09:07 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char		**init_input_2(char **input, char **lexer, int nbr_input, int *i)
{
	int nbr_word;
	int n;

	n = 0;
	if (*i < 2 &&  lexer[0] != NULL && 1 == init_inouput_back(lexer, "<"))
	{
		nbr_word = nbr_words_exe(lexer, i);
			if (NULL == (input = malloc_tb_str(input, &lexer[nbr_word + 1], nbr_word + 1)))
				return (NULL);
		return (input);
		*i -= nbr_word;
	}
	else if (lexer[0] != NULL)
	{
	while (lexer[n] != NULL && lexer[n][0] != '<')
	{
		*i += 1;
		n++;
	}
	if (n >= 2)
		if (lexer[n] == NULL|| lexer[n][0] == '|')
			return (input);
	if (lexer[n] != NULL)
	{
		*i += 1;
		n++;
	}
	nbr_word = nbr_words_exe(&lexer[n-*i], i);
	if (NULL == (input = malloc_tb_str(input, &lexer[n], nbr_word)))
		return (NULL);
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
	if (deb >= 2 && lexer[0] != NULL)
		nbr_input = init_inouput_back(lexer, "<");
	else
		nbr_input = 0;
	nbr_input += init_inouput(&lexer[nbr_input], "<");
	if (0 == (input = malloc(sizeof(char**) * (nbr_input + 1))))
		return (NULL);
	input[nbr_input] = NULL;
	while (++n != nbr_input)
		if (0 == (input[n] = init_input_2(input[n], lexer, nbr_input, &deb)))
			return (NULL);
	return (input);
}
