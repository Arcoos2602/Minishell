/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:29:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/24 22:21:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H


void		ft_env(char **path);
void		ft_pwd(char **path);
void		ft_echo(t_pipes *pipes);
char 	    *ft_getenv(char **paths, char *var);
void        ft_cd(char	*str, char **env);
char        **ft_unset(t_pipes *pipes, char **env);

#endif