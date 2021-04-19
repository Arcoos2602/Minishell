/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:29:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/04/12 16:53:32 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

char		*check_builtins(t_pipes	*pipes, char **path, char *env);
void		ft_env(char **path);
void		ft_pwd(char **path);
void		ft_echo(t_pipes *pipes, char **path);

#endif