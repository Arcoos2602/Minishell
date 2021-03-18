#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int				cpt(char *str)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]) && str[i] != '\0')
			i++;
		if (str[i] == '"' || str[i] == 39)
			count_quote(str, &i, &cpt);
		if (check_char(str[i]))
		{
			while (check_char(str[i]))
				i++;
			cpt++;
		}
		cpt2(str, &i, &cpt);
		i++;
	}
	return (cpt);
}

int		search_env(char **tab, char *str, int *x, char **path, int *i)
{
	int		k;
	int		j;

	k = 0;
	if (str[*i] == '$')
	{
		while (path[++k] != NULL)
		{
			j = 0;
			while (path[k][++j] != '=')
				;
			if (ft_strncmp(&str[1], path[k], j) == 0)
			{
				tab[*x] = ft_strdup(&path[k][j + 1]);
				//*i += j + 1;
				printf("%d\n", j);
				return (1);
			}
		}
	}
	return (0);
}

void			fill_tab2(char **tab, char *str, int *i, int *x)
{
	int		size_line;
	int		tmp;

	while (ft_iswhitespace(str[*i]) && str[*i] != '\0')
			++*i;
	if (str[*i] == '"' || str[*i] == 39)
		fill_quote(tab, str, i, x);
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		tab[*x] = ft_strndup(&str[*i], 2);
		*i += 2;
		++*x;
	}
	if (separators(str[*i]) && ft_iswhitespace(str[*i]) == 0)
	{
		tab[*x] = ft_strndup(&str[*i], 1);
		++*i;
		++*x;
	}
}

int				fill_tab(char **tab, char *str, char **path)
{
	int		x;
	int		i;
	int		size_line;
	int		tmp;

	tmp = 0;
	x = 0;
	i = 0;
	while (x < cpt(str))
	{
		fill_tab2(tab, str, &i, &x);
		if (check_char(str[i]) && str[i] != '\0')
		{
			tmp = i;
			size_line = 0;
			while (search_env(tab, str, &x, path , &i) == 0 && 
					check_char(str[i]) && str[i] != '\0')
			{
				size_line++;
				++i;
			}
			if (size_line != 0)
				tab[x] = ft_strndup(&str[tmp], size_line);
			++x;
		}
	}
	tab[x] = NULL;
	return (1);
}

void			print_tab(char **tab)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (tab[x] != NULL)
	{
		y = 0;
		ft_putchar_fd('[', 1);
		while (tab[x][y] != '\0')
		{
			ft_putchar_fd(tab[x][y], 1);
			y++;
		}
		ft_putchar_fd(']', 1);
		x++;
	}
}

char			**tokenization(char *str, char **path)
{
	char	**tab;
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	tab = NULL;
	i = 0;
	if (check_multi(str) == -1)
	{
		ft_putstr_fd("Multilines not handled\n", 1);
		return (NULL);
	}
	if (not_handled(str) == 1)
	{
		ft_putstr_fd("This token does not exist in this shell\n", 1);
		return (NULL);
	}
	printf("%d\n", cpt(str));
	if (!(str) || !(tab = malloc(sizeof(char *) * (cpt(str) + 1))))
		return (0);
	fill_tab(tab, str, path);
	print_tab(tab);
	ft_putchar_fd('\n', 1);
	return (tab); 
}

/*int				main(void)
{
	char	**lexer;

	(void)lexer;
	lexer = token("lol | dwa > lol\0");
	if (lexer != NULL)
		print_tab(lexer);
	ft_putchar_fd('\n', 1);
}*/