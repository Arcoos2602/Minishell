/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:03:47 by tcordonn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/09 10:33:13 by gbabeau          ###   ########.fr       */
=======
/*   Updated: 2021/03/15 11:36:41 by tcordonn         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

<<<<<<< HEAD
=======
void		display_put(t_redi *redi)
{
	printf("put = %s, type = %d\n", redi->put, redi->type);
	if (redi->next != NULL)
		display_put(redi->next);
}

>>>>>>> master
void		display_parser(t_pipes *parser)
{
	static int	nbr = 1;
	int			i;
	int			n;

	i = 0;
	n = 0;
<<<<<<< HEAD
=======
	
	printf("command\n");
>>>>>>> master
	while (parser->command[i] != NULL)
	{
		printf("command %d : ", nbr++);
		while (parser->command[i] != NULL)
			printf("[%s] ", parser->command[i++]);
		n = 0;
		printf("\n");
	}
<<<<<<< HEAD
	nbr = 1;
//	printf("%p\n", parser->command[i]);
	i = -1;
	n = 0;
	while (parser->input[++i] != NULL)
	{
		printf("input %d : ", i + 1);
		while (parser->input[i][n] != NULL)
			printf("[%s] ", parser->input[i][n++]);
		n = 0;
		printf("\n");
	}
	i = -1;
	n = 0;
//		printf("u\n");
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
		printf("output_s %d : ", i + 1);
		if (parser->output_s[i] != NULL)
			while (parser->output_s[i][n] != NULL)
				printf("[%s]", parser->output_s[i][n++]);
		else
			printf("<NULL>");
		n = 0;
		printf("\n");
	}
//		printf("u\n");
	i = -1;
	n = 0;
	while (parser->output_s[++i] != NULL || parser->output_d[i] != NULL)
	{
		printf("output_d %d : ", i + 1);
		if (parser->output_d[i] != NULL)
			while (parser->output_d[i][n] != NULL)
				printf("[%s]", parser->output_d[i][n++]);
		else
			printf("<NULL>");
		n = 0;
		printf("\n");
	}
//		printf("uu\n");
=======
	if (parser->redi != NULL)
		display_put(parser->redi);
>>>>>>> master
	if (parser->next != NULL)
		display_parser(parser->next);
}

void		display_total(t_parser *parser)
{
	static int	i = 1;

//		printf("((%p))\n",parser);
<<<<<<< HEAD
	printf("\n\nligne command:%d\n", i++);
=======
	printf("\n\nligne command:%d {%p}\n", i++, parser);
	if ( parser->pipe != NULL)
>>>>>>> master
	display_parser(parser->pipe);
	if (parser->next != NULL)
	{
//		printf("%p\n",parser->next);
		display_total(parser->next);
	}
}

<<<<<<< HEAD
char	**init_path(t_pipes *pipe, char **path)
=======
char	**init_path(char **path)
>>>>>>> master
{
	int		i;
	char	**tab;
	char 	*dest;


	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strncmp(path[i], "PATH=", 5) == 0)
<<<<<<< HEAD
			tab = ft_split(path[i], ':');
		i++;
	}
}

int *ft_pipe(t_pipes *pipes, char **exec_path, int pipe_fd[2])
{
	pid_t		pid;
	int		*pipe_fd_2;
	int		status;
	char	*tab2[3];

	pipe_fd_2 = malloc(sizeof(int) *2);
	tab2[0] = "/bin/cat\0";
	tab2[1] = "-n\0";
	tab2[2] = NULL;
	
	if (pipes->next != NULL)
		if (pipe(pipe_fd_2) == -1)
			return (NULL);
	pid = fork();
	if (pid == 0)
	{
		if (pipe_fd[0] != -1)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
		}
		if (pipes->next != NULL)
			dup2(pipe_fd_2[1], 1);
		execve(tab2[0], &tab2[0],  (char *const*) NULL);
	}

	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (pipe_fd_2);
}

int		line_command(t_pipes *parser, char **exec_path, int pipe_fd[2])
{
	int		i;

	i = 0;
	printf("nombre comand\n");
	pipe_fd = ft_pipe(parser, exec_path, pipe_fd);
	if (parser->next != NULL)
		line_command(parser->next, exec_path, pipe_fd);
	return (0);
}

int		ft_shell(t_parser *parser, char **exec_path, int pipe_fd[2])
{
	int		i;

	i = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	line_command(parser->pipe, exec_path, pipe_fd);
	if (parser->next != NULL)
		ft_shell(parser->next, exec_path, pipe_fd);
	return (0);
=======
			tab = ft_split(path[i], ':'); /// a free
		i++;
	}
	return (tab);
}

void	int_handler(int signum) // ctrl   c
{
	exit(0);
}

void	quit_handler(int signum) // ctrl
{
	
>>>>>>> master
}

int		main(int	argc, char **argv, char **path)
{
<<<<<<< HEAD
	t_main		vars;
=======
>>>>>>> master
	char		*line;
	int 		i;
	t_parser	*parser;
	char		**token;
	char		**exec_path;
	int			*pipe_fd;
<<<<<<< HEAD

	pipe_fd = malloc(sizeof(int) * 2);
	(void)argc;
	(void)argv;
	ft_putstr_fd("$ ", 1);
	if ((!init_all(&vars)))
		return (-1);
	exec_path = init_path(parser->pipe, path);
	while (1) // boucle principale
	{
		get_next_line(1, &line);
		token = tokenization(line);
		/*while ( token != NULL && token[i] != NULL)
			printf("{%s} ", token[i++]);
		printf("\n");*/
		parser = init_parser(token, &i);
		ft_shell(parser, exec_path, pipe_fd);
		//check_builtins(parser);
		/*if (parser != NULL)
			display_total(parser);*/
			while (1)
			;
		free(line);
	}
=======
	int			keep_running;

	keep_running = 1;
	pipe_fd = malloc(sizeof(int) * 2);
	exec_path = init_path(path);
	while (keep_running)
	{
		signal(SIGQUIT, quit_handler);
		signal(SIGINT, int_handler);
		ft_putstr_fd("[minishell]$ ", 2);
		get_next_line(1, &line);
		token = tokenization(line);
		parser = init_parser(token, &i);
		pipe_fd = ft_shell(parser, exec_path, pipe_fd, path);
		//display_total(parser);
		free(line);
		free(parser);
	}
	free(pipe_fd);
>>>>>>> master
	return (1);
}
