/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 06:18:48 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/30 09:05:08 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

int	ft_open_here_doc(t_redi *redi, t_path *path, int *pipe_in, int *put)
{
	ft_free_redi_double(redi, path);
	*pipe_in = open(".test", O_RDONLY);
	unlink(".test");
	if (*pipe_in == -1)
		return (file_error("here-doc"));
	redi->type = -1;
	*put = 1;
	return (1);
}

int	dup_rediput_size(char *lexer)
{
	int	i;
	int	cpt;

	cpt = ft_strlen(lexer);
	i = -1;
	while (lexer[++i] != '\0')
	{
		if (lexer[i] == '\'')
		{
			cpt--;
			while (lexer[i] != '\0' && lexer[++i] != '\'')
				;
			cpt--;
		}
		if (lexer[i] == '"')
		{
			cpt--;
			while (lexer[i] != '\0' && lexer[++i] != '"')
				;
			cpt--;
		}
	}
	return (cpt);
}

void	copy_rediput(char *dest, char *lexer)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (lexer[i] != '\0')
	{
		if (lexer[i] == '\'')
		{
			i++;
			while (lexer[i] != '\0' && lexer[i] != '\'')
				dest[cpt++] = lexer[i++];
			i++;
		}
		if (lexer[i] == '"')
		{
			i++;
			while (lexer[i] != '\0' && lexer[i] != '"')
				dest[cpt++] = lexer[i++];
			i++;
		}
		else if (lexer[i] != '\0')
			dest[cpt++] = lexer[i++];
	}
}

char	*dup_rediput(char *lexer)
{
	int		cpt;
	char	*dest;

	cpt = dup_rediput_size(lexer);
	dest = malloc(cpt + 1);
	dest[cpt] = '\0';
	if (dest == NULL || cpt == 0)
		return (dest);
	copy_rediput(dest, lexer);
	return (dest);
}
