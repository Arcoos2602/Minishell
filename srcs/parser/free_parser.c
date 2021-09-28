/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:47:34 by gbabeau           #+#    #+#             */
/*   Updated: 2021/09/28 13:28:36 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

void	free_command(char **command)
{
	int	i;

	i = 0;
	while (command != NULL && command[i] != NULL)
		free(command[i++]);
	if (command != NULL)
		free(command);
}

void	free_redi(t_redi *redi)
{
	if (redi->put != NULL)
		free(redi->put);
	if (redi->next != NULL)
		free_redi(redi->next);
	free(redi);
}

void	free_pipe(t_pipes *pipe)
{
	if (pipe->redi != NULL)
		free_redi(pipe->redi);
	if (pipe->command != NULL)
		free_command(pipe->command);
	if (pipe->next != NULL)
		free_pipe(pipe->next);
	free(pipe);
}

void	free_parser(t_parser *parser)
{
	if (parser->pipe != NULL)
		free_pipe(parser->pipe);
	if (parser->next != NULL)
		free_parser(parser->next);
	free(parser);
	parser = NULL;
}
