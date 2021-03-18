/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcordonn <tcordonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:29:47 by tcordonn          #+#    #+#             */
/*   Updated: 2021/03/15 12:44:10 by tcordonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

void		check_builtins(t_pipes	*pipes, char **path);
void		ft_env(char **path);
void		ft_pwd(char **path);
void		ft_echo(t_pipes *pipes, char **path);

#endif