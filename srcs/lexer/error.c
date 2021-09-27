/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <gbabeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:47:20 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 09:59:36 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	display_error_token(char c)
{
	printf("check\n");
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
	printf("%c %c\n", str[*i], c);
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
		if (str[*i] == c)
			++*i;
		while (ft_iswhitespace(str[*i]))
			++*i;
		if (token(str[*i]) || str[*i] == '\0')
			return (display_error_token(str[*i]));
		return (1);
	}
	return (display_error_token(str[*i]));
}

int	ft_error2(char *str, int *i, char c)
{
	int	tmp;

	tmp = *i - 1;
	if (ft_iswhitespace(str[*i]))
	{
		while (--tmp >= 0 && ft_iswhitespace(str[tmp]))
			;
		if (tmp < 0)
			return (display_error_token(c));
		while (ft_iswhitespace(str[*i]))
			++*i;
		if (str[*i] == '|' || str[*i] == '\0')
			return (display_error_token(str[*i]));
		return (1);
	}
	else if (str[*i] != '\0')
	{
		while (--tmp >= 0 && ft_iswhitespace(str[tmp]))
			;
		if (tmp < 0)
			return (display_error_token(c)); 
		if (str[*i] == '|')
		{
			if (c == '>')
				ft_putstr_fd("Error 1\n", 2);
			if (c == '<')
				ft_putstr_fd("Error 2\n", 2);
			else
				ft_putstr_fd("This token: || is not in this minishell\n", 2); // a modif
			return (-1);	
		}
		return (1);
	}
	return (display_error_token(str[*i]));
}

int		check_error(char *str, int *i, int *cpt)
{
	++*cpt;
	if(str[*i] != '|')
	{
		 ++*i;
		if (ft_error(str, i, str[*i - 1]) < 0)
			return (-1);
	} 
	else 
	{
		++*i;
		if (ft_error2(str, i, str[*i - 1]) < 0)
			return (-1);
	}
	return (1);
}
