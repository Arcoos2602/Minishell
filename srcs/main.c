/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/25 21:51:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	g_global;

void	display_put(t_redi *redi)
{
	printf("put = %s, type = %d\n", redi->put, redi->type);
	if (redi->next != NULL)
		display_put(redi->next);
}

void	display_parser(t_pipes *parser)
{
	static int	nbr = 1;
	int			i;

	i = 0;
		//printf("command\n");
	while (parser->command[i] != NULL)
	{
		printf("command %d : ", nbr++);
		while (parser->command[i] != NULL)
			printf("[%s] ", parser->command[i++]);
		printf("\n");
	}
	if (parser->redi != NULL)
		display_put(parser->redi);
	if (parser->next != NULL)
		display_parser(parser->next);
}

void	display_total(t_parser *parser)
{
	static int	i = 1;
//      printf("((%p))\n”,parser);
	//printf("\n\nligne command:%d {%p}\n”, i++, parser");
	if (parser->pipe != NULL)
		display_parser(parser->pipe);
	if (parser->next != NULL)
	{
      printf("%d\n",i);
		display_total(parser->next);
	}
}

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

static void	int_handler(int signum)// ctrl '\'
{
	printf("signum=%d\n", signum);
	rl_on_new_line();
	g_global = 130;
}

static void	quit_handler(int signum)// ctrl '\'
{
	printf("signum=%d\n", signum);
	g_global = 131;
	//exit(0);
}

void	free_paths(t_path *path)
{
	int	i;

	i = 0;
	if(path != NULL && path->exec_path != NULL)
	{
	while (path->exec_path[i] != NULL)
		free(path->exec_path[i++]);
	free(path->exec_path);
	}
}

static char	**env_malloc(char **path, char **env)
{
	int	n;
	int	i;

	n = -1;
	while (env[++n] != NULL)
	;
	path = malloc((n + 1) * sizeof(char *));
	i = 0;
	n = -1;
	while (env[++n] != NULL)
			path[i++] = ft_strdup(env[n]);
	path[i]= NULL;
	return (path);
}


char *ft_special(char *buf)
{
	int i;
	int cpt;
	char *dest;

	cpt = 0;
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i++] == '\'')
			cpt++;
	}
	if (cpt == 0)
		return (buf);
	dest = malloc(i + (4 * cpt) + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	cpt = 0;
	while (buf[i] != '\0')
	{
		dest[i + cpt] =  buf[i];
		if (buf[i] == '\'')
		{	dest[i] =  '\'';
			dest[i+ ++cpt] =  '"';
			dest[i + ++cpt] =  '\'';
			dest[i + ++cpt] =  '"';
			dest[i + ++cpt] =  '\'';
		}
		i++;
	}
	dest[i + cpt] =  '\0';
	free(buf);
	return dest;
}

char *add_env_line(char *str, int *i, t_path *path)
{
	char	**buf;
	char	*dest;
	char 	*fin;
	int		 tmp;
	int		nbr;

	tmp = *i;
	++*i;
	nbr = 0;
	dest = NULL;
	buf = NULL;

	buf = ft_split(ft_dol(str, i, path), ' ');
	if (buf == NULL || buf[0] == NULL)
		return str;
	dest = ft_strndup(str, tmp);

	while (buf[nbr] != NULL)
	{
		buf[nbr] = ft_special(buf[nbr]);
		dest = ft_strjoin(dest, "'");
		dest = ft_strjoin(dest , buf[nbr]);
		nbr++;
		if (buf[nbr] != NULL)
			dest = ft_strjoin(dest, "' ");
		
	}
	dest = ft_strjoin(dest, "'");

	fin = ft_strndup(&str[*i], ft_strlen(&str[*i]));
	dest = ft_strjoin(dest, fin);
	free(str);
	free(buf);
	return (dest);
}

char *line_env(char *str, t_path *path)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		
		if (ft_compare_c_to_s(str[i], "'\"") == 1)
		{
			if (str[i] == '"')
			{	
				while (str[i] != '\0' && str[++i] != '"')
					;
			}
			else if (str[i] == '\'')
			{
				while (str[i] != '\0' && str[++i] != '\'')
					;
				}
		}
		else if (str[i] == '$')
		{
			printf("%i\n",i);
			str = add_env_line(str, &i, path);
//			printf("%s\n",str);
		} 
		else
			i++;
		//	printf("%s\n",str);	
	}
//	printf("%s\n",str);
	return (str);
}

int	main(int argc, char **argv, char **path)
{
	char		*line;
	t_path		paths;
	t_parser	*parser;
	char		**token;
	int			i;
//	char		**exec_path;
//	int			status;

	i = 0;
	g_global = 0;
	printf("argc = %d et argv = %s\n", argc, argv[0]);
	path = env_malloc(paths.path, path);
	paths.path = path;
	paths.exit_status = 0;
	paths.in_fd = dup(0);
	paths.out_fd = dup(1);
//	line = NULL;
	while (1)
	{
		paths.exec_path = ft_split(ft_getenv(paths.path,"PATH"), ':');
		signal(SIGINT, int_handler);
		signal(SIGQUIT, quit_handler);
		ft_putstr_fd("{minihsell}",2);
		get_next_line(0, &line);
//		printf("valeur retour = %d\n", paths.exit_status);
	//	add_history(line);
		//get_next_line(1, NULL);
		if (line == NULL)
			exit(0);	
		if (line != NULL)
		{
			line = line_env(line, &paths);
			printf("line = %s\n", line);
			token = tokenization(line, &paths);
	//		printf("token = %s\n", token[0]);
			free(line);
		}
		if (token != NULL && token[0] != NULL)
		{
			parser = init_parser(token, &i, &paths);
			free_token(token);
			paths.parser = parser;
			ft_shell(parser, &paths);
			free_parser(parser);
		}
		else
			g_global = 0;
		free_paths(&paths);
//		printf("valeur retour = %d\n",  paths.exit_status);
		g_global = 0;
	}
	rl_clear_history();
	return (1);
}
