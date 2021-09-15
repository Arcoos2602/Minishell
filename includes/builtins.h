/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:29:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/09/15 15:55:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H


void		ft_env(char **path);
void		ft_pwd(char **path);
void		ft_echo(t_pipes *pipes);
char 	    *ft_getenv(char **paths, char *var);
void        ft_cd(char	*str, char **env);
char        **ft_unset(t_pipes *pipes, char **env);
char        **ft_export(t_pipes *pipes, char **env);
void		ft_exit(t_pipes *pipes);

#endif