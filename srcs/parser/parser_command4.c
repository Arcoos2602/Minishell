/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 00:26:09 by thomas            #+#    #+#             */
/*   Updated: 2021/09/29 13:53:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	ftsizecommand(char **command, char **lexer)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (command[i] != NULL && lexer[i] != NULL)
	{
		if (command[i][0] != '\0' || ft_compare_c_to_s('\"', lexer[i]))
			cpt++;
		i++;
	}
	return (cpt);
}

char	**ft_finish_command(char **command, char **lexer)
{
	int		i;
	int		cpt;
	char	**dest;

	if (command == NULL || lexer == NULL)
		return (NULL);
	dest = malloc(sizeof(char *) * (ftsizecommand(command, lexer) + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	cpt = 0;
	while (command[i] != NULL && lexer[i] != NULL)
	{
		if (command[i][0] != '\0' || ft_compare_s_to_s("\"'", lexer[i]))
			dest[cpt++] = ft_strdup(command[i]);
		i++;
	}
	dest[cpt++] = NULL;
	i = 0;
	while (command[i] != NULL)
		free(command[i++]);
	free(command);
	return (dest);
}

static char	**comand_malloc(char **command, char **lexer)
{
	int	n;
	int	i;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|"))
	{
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
		{
			command[i++] = ft_strdup(lexer[n]);
			printf("%s\n",command[i - 1]);
			if (command[i - 1] == NULL)
				i--;
		}
		else
			n++;
	}

	return (command);
}

char	**comand_malloc_2(char **command, t_path *paths, int size)
{
	int	n;
	int i;
	char **dest;

	dest = malloc(sizeof(char *) * (size + 1));
	dest[size] = NULL;
	n = 0;
	i = 0;
	while (size != i)
	{
			if(command[i] != NULL)
			{
				dest[n] = parse(command[i], paths);
				if (dest[n] != NULL)
					n++;
			}
			i++;
	}
	dest[n] = NULL;
		size = 0;
		while (command[size] != NULL)
			free(command[size++]);
		free(command);
	return (dest);
}

static int	command_size(char **lexer)
{
	int		i;
	int		n;

	i = 0;
	n = -1;
	while (lexer[n + 1] != NULL && 0 == ft_compare_c_to_s(lexer[++n][0], "|"))
	{
		if (1 != (ft_compare_c_to_s(lexer[n][0], "><")))
			i++;
		else
			n++;
	}
	printf("\n");
	return (i);
}

static int count_trad_2(char *command)
{
	int i;

	i = 0;
	while(!ft_compare_c_to_s(command[i],"$'\"") && command[i] !='\0')
		i++;
	return (i);
}

char *command_trad_2(char *command, t_path *paths)
{
	int i;
	int size;
	char *dest;
	char *buf;

	i = 0;
	dest = NULL;
	buf = NULL;
	while (command[i] != '\0')
	{
		size = count_trad_2(&command[i]);

		if (command[i + size] == '\'')
		{
			size++;
			buf = ft_strndup(&command[i], size);
			dest = ft_strjoin(dest, buf);
			free(buf);
			i += size;
			size = 0;
			while (!ft_compare_c_to_s(command[i + size],"'") && command[i + size] != '\0')
				size++;
			if (command[i + size] != '\0')
				size++;
			size++;
			buf = ft_strndup(&command[i], size);
			dest = ft_strjoin(dest, buf);
			free(buf);
		}
		else if (command[i + size] == '"')
		{
			size++;
			buf = ft_strndup(&command[i], size);
			dest = ft_strjoin(dest, buf);
			free(buf);
			i += size;
			size = 0;
			while (!ft_compare_c_to_s(command[i + size],"\"") && command[i + size] != '\0')
				size++;
			if (command[i + size] != '\0')
				size++;
			buf = ft_strndup(&command[i], size);
			dest = ft_strjoin(dest, buf);
			free(buf);
		}
		else if (command[i + size] == '$')
		{
			buf = ft_strndup(&command[i], size);
			dest = ft_strjoin(dest, buf);
			i +=size;
			size = 0;
			free(buf);
			dest = parse_4(&i, command, dest, paths);
				if (command[i] == '?' && command[i - 1] == '$')
						i++;
		}
		else if ( command[i + size] == '\0')
			dest = ft_strjoin(dest, &command[i]);
				printf("dest boucle = %s\n",dest);
		i += size;
	}
	printf("dest final = %s\n",dest);
	return (dest);
}

int count_tab2(char *command)
{
	int i;
	int cpt;

	i = -1;
	cpt = 1;
	while (command[++i] != '\0')
	{
		if (command[i] == '\'')
			while(command[i] != '\0' && command[++i] != '\'')
				;
		if (command[i] == '"')
			while(command[i] != '\0' && command[++i] != '"')
				;
		if (ft_iswhitespace(command[i])  && command[++i] != '\0')
		{
			while (ft_iswhitespace(command[i]))
				i++; 
			if (command[i] != '\0')
				cpt++;
		}
	}
	return (cpt);
}

int count_tab(char **command)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (command[i] != NULL)
	{
		cpt += count_tab2(command[i]);
		printf("nombre de comand dans i %d\n", count_tab2(command[i++]));
	}
	printf("nombre de command final toto %d\n", cpt);
	return cpt;
}

char	**command_trad(char **command, t_path *paths, int size)
{
	int		i;
	char	**dest;

	i = 0;
	dest = malloc(sizeof(char *) * (size + 1));
		if (command == NULL)
			return (NULL);
	while (command[i] != NULL)
	{
		dest[i] = command_trad_2(command[i], paths);
		i++;
	}
	dest[i] = NULL;
	i = 0;
		while (command[i] != NULL)
			free(command[i++]);
		free(command);
	return (dest);

}

char	**command_split_2(char **dest, char **command, int *i, int *d)
{
	int x;
	int cpt;
	int dep;

	x = -1;
	dep = 0;
	cpt = 1;
	while (command[*i] != NULL && command[*i][++x] != '\0')
	{
		if (command[*i][x] == '\'')
			while(command[*i][x] != '\0' && command[*i][++x] != '\'')
				;
		if (command[*i][x] == '"')
			while(command[*i][x] != '\0' && command[*i][++x] != '"')
				;
		if (ft_iswhitespace(command[*i][x])  && command[*i][++x] != '\0')
		{
			dest[*d] = ft_strndup(&command[*i][dep], x - dep - 1);
			++*d;
			while (command[*i] != NULL &&  ft_iswhitespace(command[*i][x]))
				x++;
			dep = x;
			if (command[*i] != NULL && command[*i][x] != '\0')
				cpt++;
		}
	}
	if (command[*i] != NULL)
		dest[*d] = ft_strdup(&command[*i][dep]);
	++*i;
	++*d;
	return (dest);
}


char	**split_command(char **command, int *size)
{
	int i;
	char **dest;
	int count;
	int d;

	i = 0;
	d = 0;
	count = count_tab(command);
	*size = count;
	dest = malloc(sizeof(char *) * (count + 1));
		if (command == NULL)
			return (NULL);
	dest[count] = NULL;
	while (command[i] != NULL)
		dest = command_split_2(dest, command, &i, &d);
	dest[count] = NULL;
	i = 0;
		while (command[i] != NULL)
			free(command[i++]);
		free(command);
	return (dest);

}


char	**init_command_pipe(char **command, char **lexer, int *i, t_path *paths)
{
	int		size;

	if (lexer[0] != NULL)
	{
		size = command_size(&lexer[*i]);
		command = malloc(sizeof(char *) * (size + 1));
		if (command == NULL)
			return (NULL);
		command[size] = NULL;
		command = comand_malloc(command, &lexer[*i]);
		command = command_trad(command, paths, size);
		command = split_command(command, &size);
		command = comand_malloc_2(command, paths, size);

		if (command == NULL)
			return (NULL);
		return (command);
	}
	return (NULL);
}
