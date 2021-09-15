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

void	fill_var(char **tab, char *str,  int len[2], char **paths)
{
	len[1]++;
	printf("%s\n", &str[len[1]]);
	tab[len[0]] = ft_strdup(ft_getenv(paths, &str[len[1]]));
	printf("%s\n", tab[len[0]]);
}

void	fill_tab2(char **tab, char *str, int len[2], char **paths)
{
	while (ft_iswhitespace(str[len[1]]) && str[len[1]] != '\0')
		++len[1];
	if (str[len[1]] == '"' || str[len[1]] == 39)
		fill_quote(tab, str, &len[1], &len[0]); // gerer $ dans les quotes
	if (str[len[1]] == '>' && str[len[1] + 1] == '>')
	{
		tab[len[0]] = ft_strndup(&str[len[1]], 2);
		len[1] += 2;
		len[0]++;
	}
	if (str[len[1]] == '<' && str[len[1] + 1] == '<')
	{
		tab[len[0]] = ft_strndup(&str[len[1]], 2);
		len[1] += 2;
		len[0]++;
	}
	if (str[len[1]] == '$')
		fill_var(tab, str, len, paths);
	if (separators(str[len[1]]) == 1
		&& ft_iswhitespace(str[len[1]]) == 0)
	{
		tab[len[0]] = ft_strndup(&str[len[1]], 1);
		len[1]++;
		len[0]++;
	}
}

int	fill_tab(char **tab, char *str, char **paths)
{
	int	len[2];
	int	size_line;
	int	tmp;
	int	size;

	tmp = 0;
	len[0] = 0;
	len[1] = 0;
	size = cpt(str);
	while (len[0] < size)
	{
		fill_tab2(tab, str, len, paths);
		if (check_char(str[len[1]]) && str[len[1]] != '\0')
		{
			tmp = len[1];
			size_line = 0;
			while (check_char(str[len[1]]) && str[len[1]] != '\0')
			{
				size_line++;
				++len[1];
			}
			if (size_line != 0)
				tab[len[0]] = ft_strndup(&str[tmp], size_line);
			++len[0];
		}
	}
	tab[len[0]] = NULL;
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

char	**tokenization(char *str, char **paths)
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
	// parser errror des redirections
	if (not_handled(str) == 1)
	{
		ft_putstr_fd("This token does not exist in this shell\n", 1);
		return (NULL);
	}
	tab = malloc(sizeof(char *) * (cpt(str) + 1));
	if (str == NULL || tab == NULL)
		return (0);
	fill_tab(tab, str, paths);
	return (tab);
}
