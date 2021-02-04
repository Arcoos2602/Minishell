/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:35:10 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/04 17:25:03 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int			nbr_words_exe(char **lexer, int *i)
{
	int	nbr_words_exe;

	nbr_words_exe = 0;
	while (lexer[*i] != NULL && !ft_compare_c_to_s(lexer[*i][0], "|><;"))
	{
		nbr_words_exe++;
		*i += 1;
	}
	return (nbr_words_exe);
}
void	*p_malloc(char ***tab, int size)
{
	if (0 == (tab = malloc(sizeof(char**) * size)))
		return NULL;
	tab[size - 1] = NULL;
	return tab;
}
int			words_command(char **lexer, int i)
{
	int	nbr_words;

	nbr_words = 0;
	while (lexer[i] != NULL && lexer[i++][0] != ';')
	{
		printf("%s\n",lexer[i]);
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
	while (--size != 1)
		dst[size] = ft_strdup(in[size]);
	return (dst);
}

char		**init_command_pipe(char **command, char **lexer, int *i)
{
	int	size;
	int	nbr_arg;

	size = nbr_words_exe(lexer, i);
	nbr_arg = size;
	if (NULL == (command = malloc_tb_str(command, &lexer[*i], size)))
	{
		return (NULL);
	}
	return (command);
}

int			init_inouput(char **lexer, char *inout)
{
	int	i;
	int	size;
	int	nbr;

	nbr = 0;
	i = 0;
	size = ft_strlen(inout) + 1;
	while (lexer[i] != NULL && lexer[i][0] != ';')
	{
		if (0 == ft_strncmp(inout, lexer[i], size))
			nbr++;
	}
	return (nbr);
}

char		***init_input_2(char ***input, char **lexer, int nbr_input)
{
	int i;
	int n;
	int nbr_word;

	i = 0;
	n = 0;
	while (i != nbr_input)
	{
		while (lexer[n][0] != '<')
			n++;
		nbr_word = nbr_words_exe(lexer, &n);
		if (NULL == malloc_tb_str(input[i], &lexer[n], nbr_word))
			return (NULL);
	}
	return (input);
}

char		***init_input(char ***input, char **lexer)
{
	int	nbr_input;

	nbr_input = init_inouput(lexer, "<");
	if (0 == (input = malloc(sizeof(char**) * (nbr_input + 1))))
		return (NULL);
	input[nbr_input] = NULL;
	if (0 == init_input_2(input, lexer, nbr_input))
		return (NULL);
	return (input);
}

char		**init_output_3(char **output_1, char **output_2, char **lexer)
{
	if (NULL == malloc_tb_str(output_1, lexer, nbr_words_exe(lexer, 0)))
		return (NULL);
	output_2 = NULL;
	return (output_1);
}

void		*init_output_2(char ***output_s, char ***output_d,
			char **lexer, int nbr)
{
	int i;
	int n;

	n = 0;
	i = 0;
	while (i != nbr)
	{
		while (lexer[n][0] != '>')
			n++;
		if (lexer[n][1] == '\0')
		{
			if (0 == init_output_3(output_s[i], output_d[i], &lexer[n]))
				return (NULL);
		}
		else if (0 == init_output_3(output_d[i], output_s[i], &lexer[n]))
			return (NULL);
	}
	return (output_s);
}

t_parser	*init_output(t_parser *new, char **lexer)
{
	int	nbr;

	nbr = init_inouput(lexer, ">>") + init_inouput(lexer, ">>");
	new->output_s = malloc(sizeof(char**) * (nbr + 1));
	new->output_d = malloc(sizeof(char**) * (nbr + 1));
	new->output_s[nbr] = NULL;
	new->output_d[nbr] = NULL;
	if (NULL == init_output_2(new->output_s, new->output_d, lexer, nbr))
		return (NULL);
	return (new);
}

t_parser	*init_put(t_parser *new, char **lexer, int *i)
{
	if (NULL == init_input(new->input, &lexer[*i]))
		return (NULL);
	if (NULL == init_output(new, &lexer[*i]))
		return (NULL);
	return (new);
}

t_parser	*init_new(t_parser *new, char **lexer, int *i)
{
	int	nbr_words;
	int pipe;
	
	pipe = -1;
	*i = 0;
	new->command = p_malloc(new->command, words_command(lexer, *i) + 1);
	while (++pipe == nbr_words)
		if (NULL == init_command_pipe(new->command[pipe], lexer, i))
			{
			write(2, "TT", 2);
			return (NULL);
			}
	if (0 == init_put(new, lexer, i))
		return (NULL);
	return (new);
}

t_parser	*parser_new(char **lexer, int *i)
{
	t_parser	*new;

	if (0 == (new = malloc(sizeof(t_parser))))
	{
		return (NULL);
	}
	new->next = NULL;
	return (init_new(new, lexer, i));
}

int			nbr_command_line(char **lexer)
{
	int		i;
	int		nbr_command_line;

	nbr_command_line = 1;
	i = 0;
	while (lexer[i] != NULL)
		if (lexer[i++][0] == ';')
		{
			if (lexer[i] != NULL && ft_compare_c_to_s(lexer[i][0], ";|"))
				return (0);
			nbr_command_line++;
		}
	return (nbr_command_line);
}

t_parser	*add_parser(t_parser *parser, t_parser *next)
{
	if (parser == NULL)
		parser = next;
	if (parser->next == NULL)
		parser->next = next;
	else
		add_parser(parser->next, next);
	return (next);
}

t_parser	*init_parser(t_parser *parser, char **lexer)
{
	int			nbr;
	int			*i;

	*i = 0;
	nbr = nbr_command_line(lexer);
	while (nbr != 0)
	{
		if (parser == NULL)
		{
			if (0 == (parser = parser_new(lexer, i)))
			{
				write(2, "TT", 2);
					return (NULL);
			}
		}
		else
			if (0 == add_parser(parser, parser_new(lexer, i)))
			{
				write(2, "FF", 2);
				return (NULL);
			}
		nbr--;
	}
	return (parser);
}

t_parser	*parser(char **lexer)
{
	t_parser	*parser;

	parser = NULL;
	init_parser(parser, lexer);
	return (parser);
}

void display_parser(t_parser *parser)
{
	int i = -1;
	int n = 0;
	while (parser->command[++i] != NULL)
	{
	printf("command %d : ", i + 1);
	while(parser->command[i][n] != NULL)
		printf("<%s>",parser->command[i][n++]);
			n = 0;
	printf("\n");
	}
	i = -1;
	n = 0;
	while (parser->input[++i] != NULL)
	{
	printf("input %d : ", i + 1);
	while(parser->input[i][n] != NULL)
		printf("<%s>",parser->input[i][n++]);
			n = 0;
	printf("\n");
	}
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
	printf("output_s %d : ", i + 1);
	if (parser->output_s[i] != NULL)
		while (parser->output_s[i][n] != NULL)
			printf("<%s>",parser->output_s[i][n++]);
	else
		printf("<%s>",parser->output_s[i][n]);
			n = 0;
	printf("\n");
	}
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
	printf("output_s %d : ", i + 1);
	if (parser->output_d[i] != NULL)
		while (parser->output_s[i][n] != NULL)
			printf("<%s>",parser->output_d[i][n++]);
	else
		printf("<%s>",parser->output_d[i][n]);
			n = 0;
	printf("\n");
	}

}

int main(int a, char **argc)
{
	argc[a - 1] = NULL;
	t_parser	*parser;
	
	parser = init_parser(parser, &argc[1]);
	display_parser(parser);
	return (0);
}
