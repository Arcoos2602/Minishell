/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:35:10 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/04 11:14:57 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"


int	nbr_words_exe(char **lexer, int *i)
{
	int	nbr_words_exe;

	nbr_words_exe = 0;
	while (lexer[*i] != NULL && !ft_compare_c_to_s(lexer[*i += 1][0],"|><;"))
			nbr_words_exe++;

	return (nbr_words_exe);
}

int	words_command(char **lexer, int i)
{
	int nbr_words;

	nbr_words = 0;
	while ( lexer[i] != NULL && lexer[i++][0] != ';')
		if (lexer[i - 1][0] != '|')
			nbr_words++;
	if (lexer[i] == NULL)
		i = 0;
	return (nbr_words);
}

void init_command_pipe(char **command, char **lexer, int *i)
{
	int	size;
	int nbr_arg;

	size = nbr_words_exe(lexer, i);
	nbr_arg = size;
	command = malloc(sizeof(char**) * size + 1);
	command[size] = NULL;
	while (--size > 0)
	command[size] = ft_strdup(lexer[*i--]);
	*i += nbr_arg;
}

t_parser *init_new(t_parser *new, char **lexer)
{
	int	nbr_words;
	int pipe;
	int	i;

	pipe = -1;
	i = 0;
	if (0 != (new->command = malloc(sizeof(char**) * (nbr_words = words_command(lexer, i) + 1))))
	{
		while (++pipe == nbr_words)
			init_command_pipe(new->command[pipe], lexer, &i);
		new->command[pipe] = NULL;
	}


return (new);
}

t_parser *parser_tnew(char **lexer)
{
	t_parser	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (0);

	return (init_new(new, lexer));
}
int nbr_command_line(char **lexer)
{
	int		i;
	int		nbr_command_line;

	nbr_command_line = 1;
	i = 0;
	while (lexer[i] != NULL)
		if (lexer[i++][0] == ';')
		{
			if (lexer[i] != NULL && ft_compare_c_to_s(lexer[i][0],";|"))
				return (0);
			nbr_command_line++;
		}
	return (nbr_command_line);
}


t_parser	*init_parser(t_parser *parser , char **lexer)
{
	int			nbr;

	nbr = nbr_command_line(lexer);
	if (0 != (parser = malloc(sizeof(t_parser*) *
						(nbr + 1))))
		return (NULL);

	return (parser);
}

t_parser	*parser(char **lexer)
{
	int			i;
	t_parser	*parser;

	i = 0;
	init_parser(parser, lexer);
	while (parser[i].command != NULL)
	return (parser);
}
