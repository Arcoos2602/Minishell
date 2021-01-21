/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:04:16 by gbabeau           #+#    #+#             */
/*   Updated: 2020/10/20 17:35:20 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *srcs, size_t n);
void				*ft_memccpy(void *dest, const void *srcs, int c, size_t n);
void				*ft_memmove(void *dest, const void *srcs, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *srcs, size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int strat, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *nw);
int					ft_lstsize(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *nw);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
unsigned int		ft_atoi_base(char *str, char *base);
int					verification_atoi(char *base);
unsigned long int	verification_atoi_p(char *base_from);
unsigned long int	ft_atoi_base_p(char *str, char *base);
char				*ft_convert_base_p(char *nbr, char *base_from,
						char *base_to);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
char				*ft_uitoa(unsigned int n);
char				*ft_ultoa(unsigned long int n);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void*),
							void (*del)(void*));
int					ft_compare_c_to_s(char c, char *str);
int					ft_compare_s_to_s(char *str_1, char *str_2);
int					ft_xor(char a, char b);
#endif
