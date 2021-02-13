/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_comand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:04:46 by gbabeau           #+#    #+#             */
/*   Updated: 2021/02/13 16:07:26 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

char		**init_command_pipe(char **command, char **lexer, int *i)
{
	int	size;

	size = nbr_words_exe(lexer, i);
	printf("longueur comand = %d\n", size);
	if (NULL == (command = malloc_tb_str(command, &lexer[*i - size], size)))
		return (NULL);
	return (command);
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
