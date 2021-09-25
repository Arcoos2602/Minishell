/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:35:25 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/25 15:40:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char *add_newline(char *line)
	{
		char *new_line;

		new_line = malloc(ft_strlen(line) + 2);
		ft_strlcpy(new_line ,line, ft_strlen(line) + 1);
		new_line[ft_strlen(line)] = '\n';
		new_line[ft_strlen(line) + 1] = '\0';
		free(line);
		return (new_line);
	}

int ft_free_redi_double(t_redi *redi)
{
	int fd;
	char *line;

	line = NULL;

		fd = open(".test", O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0664);
		ft_putstr_fd(">", 2);
		while (get_next_line(1, &line) != 0 && !(ft_strncmp(redi->put, line, ft_strlen(redi->put)) == 0 && ft_strlen(redi->put) == ft_strlen(line)))
		{
						ft_putstr_fd(">", 2);
						line = add_newline(line);
						ft_putstr_fd(line, fd);
		}
		close(fd);
		return 	(10);
}

t_redi	*init_new_redi(t_redi *redi, char **lexer, t_path *paths)
{
	redi->put = parse(lexer[1], paths);
	if (lexer[0][0] == '<')
	{
		redi->type = 0;
		if (lexer[0][1] == '<')
			redi->type = 10;//ft_free_redi_double(redi);
	}
	else if (lexer[0][1] == '\0')
		redi->type = 1;
	else
		redi->type = 2;
	return (redi);
}

t_redi	*redi_new(char **lexer, t_path *paths)
{
	t_redi	*new;

	new = malloc(sizeof(t_redi));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	return (init_new_redi(new, lexer, paths));
}

t_redi	*add_redi(t_redi *redi, t_redi *next)
{
	if (redi == NULL)
		redi = next;
	else if (redi->next == NULL)
	{
		redi->next = next;
	}
	else
		add_redi(redi->next, next);
	return (redi);
}

t_redi	*init_put(t_redi *redi, char **lexer, int *i, t_path *paths)
{
	int	deb;

	deb = 0;
	while (lexer[*i + deb] != NULL
		&& 0 == ft_compare_c_to_s(lexer[*i + deb][0], "|;"))
	{
		if (ft_compare_c_to_s(lexer[*i + deb][0], "><"))
			redi = add_redi(redi, redi_new(&lexer[*i + deb], paths));
		deb++;
	}
	return (redi);
}

static int	nbr_redi(char **lexer)
{
	int	n;
	int	i;

	n = -1;
	i = 0;
	while (lexer[++n] != NULL && 0 == ft_compare_c_to_s(lexer[n][0], "|;"))
	{
		if (1 == ft_compare_c_to_s(lexer[n][0], "><"))
			i++;
	}
	return (i);
}

t_pipes	*add_pipe(t_pipes *pipe, t_pipes *next)
{
	if (pipe == NULL)
		pipe = next;
	else if (pipe->next == NULL)
		pipe->next = next;
	else
		add_pipe(pipe->next, next);
	pipe->put[1] = -1;
	pipe->put[0] = -1;
	pipe->error =  0;
	pipe->exe = 0;
	return (next);
}

int ft_check_builtin_parser(char *command)
{
	if (ft_strncmp(command, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "echo", 3) == 0)
		return (1);
  	else if (ft_strncmp(command, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 5) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(command, "cd", 2) == 0)
		return (1);;
	return (0);
}

t_pipes	*init_new(t_pipes *new, char **lexer, int *i, t_path *paths)
{
	new->command = init_command_pipe(new->command, lexer, i, paths);
	if (new->command != NULL && new->command[0] != NULL)
		new->builtin = ft_check_builtin_parser(new->command[0]);
	if (0 != nbr_redi(&lexer[*i]))
	{
		new->redi = init_put(new->redi, lexer, i, paths);
		if (0 == new->redi)
			return (NULL);
	}
	return (new);
}

t_pipes	*pipe_new(char **lexer, int *i, t_path *paths)
{
	t_pipes	*new;

	new = malloc(sizeof(t_pipes));
	if (0 == new)
		return (NULL);
	new->builtin = 0;
	new->next = NULL;
	new->redi = NULL;
	return (init_new(new, lexer, i, paths));
}

t_pipes	*init_pipes(char **lexer, int *i, t_path *paths)
{
	int		nbr;
	t_pipes	*pipe;

	pipe = NULL;
	nbr = words_command(lexer, *i);
	while (nbr--)
	{
		if (pipe == NULL)
		{
			pipe = pipe_new(lexer, i, paths);
			if (pipe == NULL)
				return (NULL);
		}
		else if (0 == (add_pipe(pipe, pipe_new(lexer, i, paths))))
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
