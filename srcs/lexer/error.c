/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:47:20 by user42            #+#    #+#             */
/*   Updated: 2021/09/24 20:17:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	display_error_token(char c)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	if (c == '\0')
		ft_putstr_fd("newline'\n", 2);
	else
	{
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (-1);
}

int	ft_error(char *str, int *i, char c)
{
	if (ft_iswhitespace(str[*i]))
	{
		while (ft_iswhitespace(str[*i]))
			++*i;
		if (token(str[*i]) || str[*i] == '\0')
			return (display_error_token(str[*i]));
		return (1);
	}
	else if (str[*i] != '\0')
	{
		if (token(str[*i]) && str[*i] != c)
			return (display_error_token(str[*i]));
		++*i;
		while (ft_iswhitespace(str[*i]))
			++*i;
		if (token(str[*i]) || str[*i] == '\0')
			return (display_error_token(str[*i]));
		return (1);
	}
	return (display_error_token(str[*i]));
}

int	ft_error2(char *str, int *i)
{
	if (ft_iswhitespace(str[*i]))
	{
		while (ft_iswhitespace(str[*i]))
			++*i;
		if (str[*i] == '|' || str[*i] == '\0')
		{
			ft_putstr_fd("Error4\n", 2);
			return (-1);
		}
		return (1);
	}
	else if (str[*i] != '\0')
	{
		if (str[*i] == '|')
		{
			ft_putstr_fd("This token: || is not in this minishell\n", 2); // a modif
			return (-1);	
		}
		return (1);
	}
	ft_putstr_fd("Error5\n", 2);
	return (-1);
}

int		check_error(char *str, int *i, int *cpt)
{
	++*cpt;
	if(str[++*i] != '|')
	{
		if (ft_error(str, i, str[*i - 1]) < 0)
			return (-1);
	} 
	else 
	{
		if (ft_error2(str, i) < 0)
			return (-1);
	}
	return (1);
}
