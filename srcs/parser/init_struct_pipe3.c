/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_pipe3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:43:11 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/30 09:05:10 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ft_free_redi_double(t_redi *redi, t_path *path)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(".test", O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd < 0)
		return (10);
	ft_putstr_fd(">", 2);
	while (get_next_line(&line, 0) != 0
		&& !(ft_strncmp(redi->put, line, ft_strlen(redi->put)) == 0
			&& ft_strlen(redi->put) == ft_strlen(line)))
	{
		ft_putstr_fd(">", 2);
		line = add_newline(line, path);
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	if (fd > 0)
		close(fd);
	return (10);
}

t_redi	*init_new_redi(t_redi *redi, char **lexer, t_path *paths)
{
	redi->put = parse(lexer[1], paths);
	if (lexer[0][0] == '<')
	{
		redi->type = 0;
		if (lexer[0][1] == '<')
		{
			if (redi->put != NULL)
				free(redi->put);
			redi->put = dup_rediput(lexer[1]);
			redi->type = 10;
		}
	}
	else if (lexer[0][1] == '\0')
		redi->type = 1;
	else
		redi->type = 2;
	if (redi->put == NULL && redi->type != 10)
		ambigous(redi, lexer, paths);
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
