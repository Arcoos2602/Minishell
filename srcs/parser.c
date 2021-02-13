/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2021/01/21 14:11:46 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/03 09:41:14 by tcordonn         ###   ########.fr       */
=======
/*   Created: 2021/02/02 13:35:10 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/09 14:39:04 by gbabeau          ###   ########.fr       */
>>>>>>> parser
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

<<<<<<< HEAD
t_bi_parser		*parser(char *vars)
=======
int			nbr_words_exe(char **lexer, int *i)
>>>>>>> parser
{
	int	nbr_words_exe;

<<<<<<< HEAD
	//exec();
	//return (1);
=======
	nbr_words_exe = 0;
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

char		**init_command_pipe(char **command, char **lexer, int *i)
{
	int	size;

	size = nbr_words_exe(lexer, i);
	printf("longueur comand = %d\n", size);
	if (NULL == (command = malloc_tb_str(command, &lexer[*i - size], size)))
		return (NULL);
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
		if (0 == ft_strncmp(inout, lexer[i++], size))
			nbr++;
	}
	return (nbr);
}

char		**init_input_2(char **input, char **lexer, int nbr_input, int *i)
{
	int nbr_word;

	while (lexer[*i][0] != '<')
		*i += 1;
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

t_pipe		*init_put(t_pipe *new, char **lexer, int *i)
{
	int	deb;

	deb = *i - 1;
	if (NULL == (new->input = init_input(new->input, &lexer[deb])))
		return (NULL);
	if (NULL == init_output(new, &lexer[deb]))
		return (NULL);
	return (new);
}

t_pipe		*init_new(t_pipe *new, char **lexer, int *i)
{
	if (NULL == (new->command = init_command_pipe(new->command, lexer, i)))
		return (NULL);
	if (0 == init_put(new, lexer, i))
		return (NULL);
	return (new);
}

t_pipe		*pipe_new(char **lexer, int *i)
{
	t_pipe	*new;

	if (0 == (new = malloc(sizeof(t_pipe))))
		return (NULL);
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

t_pipe		*add_pipe(t_pipe *pipe, t_pipe *next)
{
	if (pipe == NULL)
		pipe = next;
	else if (pipe->next == NULL)
		pipe->next = next;
	else
		add_pipe(pipe->next, next);
	return (next);
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

t_pipe		*init_pipe(char **lexer, int *i)
{
	int		nbr;
	t_pipe	*pipe;

	pipe = NULL;
	nbr = words_command(lexer, *i);
	printf("nombre pipe = %d\n", nbr);
	while (nbr--)
	{
		if (pipe == NULL)
		{
			if (0 == (pipe = pipe_new(lexer, i)))
				return (NULL);
		}
		else if (0 == (pipe->next = add_pipe(pipe, pipe_new(lexer, i))))
			return (NULL);
		if (nbr != 0)
		{
			while (lexer[*i][0] != '|')
				*i += 1;
			*i += 1;
		}
	}
	return (pipe);
}

t_parser	*parser_new(char **lexer, int *i)
{
	t_parser	*parser;

	if (0 == (parser = malloc(sizeof(t_parser))))
		return (NULL);
	parser->pipe = NULL;
	parser->next = NULL;
	if (0 == (parser->pipe = init_pipe(lexer, i)))
		return (NULL);
	return (parser);
}

t_parser	*init_parser(char **lexer, int *i)
{
	int			nbr;
	t_parser	*parser;

	*i = 0;
	parser = NULL;
	nbr = nbr_command_line(lexer);
	printf("nombre command  = %d\n", nbr);
	while (nbr != 0)
	{
		if (parser == NULL)
		{
			if (0 == (parser = parser_new(lexer, i)))
				return (NULL);
		}
		else if (0 == add_parser(parser, parser_new(lexer, i)))
			return (NULL);
		nbr--;
		if (nbr != 0)
		{
			while (lexer[*i][0] != ';')
				*i += 1;
			*i += 1;
		}
	}
	return (parser);
}

void		display_parser(t_pipe *parser)
{
	static int	nbr = 1;
	int			i;
	int			n;

	i = 0;
	n = 0;
	while (parser->command[i] != NULL)
	{
		printf("command %d : ", nbr++);
		while (parser->command[i] != NULL)
			printf("<%s> ", parser->command[i++]);
		n = 0;
		printf("\n");
	}
	printf("%p\n", parser->command[i]);
	i = -1;
	n = 0;
	while (parser->input[++i] != NULL)
	{
		printf("input %d : ", i + 1);
		while (parser->input[i][n] != NULL)
			printf("<%s> ", parser->input[i][n++]);
		n = 0;
		printf("\n");
	}
	i = -1;
	n = 0;
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
		printf("output_s %d : ", i + 1);
		if (parser->output_s[i] != NULL)
			while (parser->output_s[i][n] != NULL)
				printf("<%s>", parser->output_s[i][n++]);
		else
			printf("<NULL>");
		n = 0;
		printf("\n");
	}
	i = -1;
	n = 0;
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
		printf("output_d %d : ", i + 1);
		if (parser->output_d[i] != NULL)
			while (parser->output_d[i][n] != NULL)
				printf("<%s>", parser->output_d[i][n++]);
		else
			printf("<NULL>");
		n = 0;
		printf("\n");
	}
	if (parser->next != NULL)
		display_parser(parser->next);
}

void		display_total(t_parser *parser)
{
	static int	i = 1;

	printf("\n\nligne command:%d\n", i++);
	display_parser(parser->pipe);
	if (parser->next != NULL)
		display_total(parser->next);
}

int			main(int a, char **argc)
{
	int			i;
	t_parser	*parser;

	argc[a - 1] = NULL;
	parser = init_parser(&argc[1], &i);
	display_total(parser);
	free(parser);
	return (0);
>>>>>>> parser
}
