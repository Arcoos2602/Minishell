/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/28 00:45:43 by thomas           ###   ########.fr       */
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

static void	init_values(t_path *paths, char **env)
{
	g_global = 0;
	env = env_malloc(paths->path, env);
	paths->path = env;
	paths->exit_status = 0;
	paths->in_fd = dup(0);
	paths->out_fd = dup(1);
}

void	parse_and_exec(char **token, t_parser *parser, t_path *paths)
{
	parser = init_parser(token, paths);
	free_token(token);
	paths->parser = parser;
	ft_shell(parser, paths);
	free_parser(parser);
}

static	void	begin(char *line, t_path *paths)
{
	char		**token;
	t_parser	*parser;

	parser = NULL;
	token = NULL;
		
	if (line != NULL)
	{
		line = line_env(line, paths);
		token = tokenization(line, paths);
		free(line);
	}
	if (token != NULL && token[0] != NULL)
		parse_and_exec(token, parser, paths);
	free_paths(paths);
	if (g_global != 0)
		paths->exit_status = g_global;
	g_global = 0;
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_path		paths;

	(void)argc;
	(void)argv;
	line = NULL;
	init_values(&paths, env);
	while (1)
	{
		paths.exec_path = ft_split(ft_getenv(paths.path, "PATH"), ':');
		ft_signal(0);
		line = readline("{minishell}");
		add_history(line);
		if (line == NULL)
		{
			ft_free(NULL, &paths);
			ft_putstr_fd("exit\n", 2);
			exit(EXIT_SUCCESS);
		}
		ft_signal(1);
		begin(line, &paths);
	}
	rl_clear_history();
	return (1);
}
