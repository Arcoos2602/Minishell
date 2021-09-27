/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/27 13:33:34 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	g_global;

char	**init_path(char **path)
{
	int		i;
	char	**tab;

	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strncmp(path[i], "PATH=", 5) == 0)
			tab = ft_split(path[i], ':');
		i++;
	}
	return (tab);
}

static void	init_values(t_path *paths)
{
	g_global = 0;
	paths = env_malloc(paths->path, paths);
	paths->path = paths;
	paths->exit_status = 0;
	paths->in_fd = dup(0);
	paths->out_fd = dup(1);
}

static void	init_token(char **token, char *line, t_path *paths)
{
	line = line_env(line, &paths);
	token = tokenization(line, &paths);
	free(line);
}

void	parse_and_exec(char **token, t_parser *parser, t_path *paths)
{
	parser = init_parser(token, paths);
	free_token(token);
	paths->parser = parser;
	ft_shell(parser, paths);
	free_parser(parser);
}

static	void	begin(char **token, char *line, t_path paths)
{
	if (line == NULL)
		exit(0);
	if (line != NULL)
		init_token(token, line, &paths);
	if (token != NULL && token[0] != NULL)
		parse_and_exec(token, parser, &paths);
	free_paths(&paths);
	if (g_global != 0)
		paths.exit_status = g_global;
	g_global = 0;
}

int	main(int argc, char **argv, char **path)
{
	char		*line;
	t_path		paths;
	t_parser	*parser;
	char		**token;

	init_values(&paths);
	while (1)
	{
		paths.exec_path = ft_split(ft_getenv(paths.path, "PATH"), ':');
		ft_signal();
		ft_putstr_fd("{minishell}", 2);
		//get_next_line(0, &line);
		//add_history(line);
		begin(token, line, paths);
	}
	rl_clear_history();
	return (1);
}
