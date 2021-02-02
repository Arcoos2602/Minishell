/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:23:32 by tcordonn          #+#    #+#             */
/*   Updated: 2021/02/02 14:47:39 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../includes/minishell.h"

static int		cpt(char const *str, char *charset)
{
	int	i;
	int	cpt;

	i = 0;
	cpt = 0;
	while (str[i] != '\0')
	{
		while (ft_strncmp(&str[i], &charset[i], 1) && str[i] != '\0')
		{}
		/*while (str[i] == charset && str[i] != '\0')
			i++;
		if (str[i] != charset && str[i] != '\0')
		{
			a++;
			while (str[i] != charset && str[i] != '\0')
				i++;
		}*/
		i++;
	}
	return (cpt);
}

static int		init(char **end, char const *str, char *charset)
{
	int	b;
	int	a;
	int	i;

	i = 0;
	a = 0;
	b = 0;
	while (b < cpt(str, charset))
	{
		a = 0;
		while (str[i] == charset && str[i] != '\0')
			i++;
		while (str[i] != '\0' && str[i++] != charset)
			a++;
		if (!(end[b] = (char*)malloc(sizeof(char) * (a + 1))))
			return (0);
		b++;
	}
	end[b] = 0;
	return (1);
}

char			**ft_split_command(char const *str, char *charset)
{
	char	**tab;
	int		i;
	int		a;
	int		b;

	a = 0;
	b = 0;
	i = 0;
	tab = NULL;
	/*if (!(str) || !(end = malloc(sizeof(char*) * (cpt(str, charset) + 1))))
		return (0);*/
	print("%d", cpt(str, charset));
	/*if (!init(end, str, charset))
		return (0);
	while (str[i] == charset && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		b = 0;
		while (str[i] != charset && str[i] != '\0')
			end[a][b++] = str[i++];
		while (str[i] == charset && str[i] != '\0')
			i++;
		end[a++][b] = '\0';
	}
	return (end);*/
}

int		main()
{
	ft_split_command("ls| cat", " |"); // doit retourner [ls][|][cat]
}
		