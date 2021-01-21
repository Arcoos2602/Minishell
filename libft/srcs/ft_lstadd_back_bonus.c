/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:38:42 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/18 11:39:27 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*renv;

	if (alst && new && *alst)
	{
		renv = ft_lstlast(*alst);
		renv->next = new;
		new->next = 0;
	}
	else if (alst && !*alst && new)
	{
		*alst = new;
		(*alst)->next = 0;
	}
}
