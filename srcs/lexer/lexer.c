#include "../../libft/include/libft.h"
#include "../../includes/minishell.h"

int	cpt(char *str)
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
		if (check_char(str[i]) && str[i] != '\0')
		{
			while (check_char(str[i]) && str[i] != '\0')
				i++;
			cpt++;
		}
		cpt2(str, &i, &cpt);
		if (str[i] != '\0')
			i++;
	}
	return (cpt);
}

int	search_env(char **tab, char *str, int *x, char **path, int *i)
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
				*i += j + 1;
				while (ft_iswhitespace(str[*i]))
					++*i;
				return (1);
			}
		}
	}
	return (0);
}

void	fill_tab2(char **tab, char *str, int *i, int *x)
{
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
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		printf("check double in\n");
		tab[*x] = ft_strndup(&str[*i], 2);
		*i += 2;
		++*x;
	}
	if (separators(str[*i]) == 1
		&& ft_iswhitespace(str[*i]) == 0)
	{
		tab[*x] = ft_strndup(&str[*i], 1);
		++*i;
		++*x;
	}
}

int	fill_tab(char **tab, char *str)
{
	int	x;
	int	i;
	int	size_line;
	int	tmp;
	int	size;

	tmp = 0;
	x = 0;
	i = 0;
	size = cpt(str);
	while (x < size)
	{
		fill_tab2(tab, str, &i, &x);
		if (check_char(str[i]) && str[i] != '\0')
		{
			tmp = i;
			size_line = 0;
			while (check_char(str[i]) && str[i] != '\0')
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

void	print_tab(char **tab)
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

char	**tokenization(char *str) // needs a parse errror function for < > etc
{
	char	**tab;

	tab = NULL;
	if (str == NULL)
		return (NULL);
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
	tab = malloc(sizeof(char *) * (cpt(str) + 1));
	if (str == NULL || tab == NULL)
		return (0);
	fill_tab(tab, str);
	return (tab);
}
