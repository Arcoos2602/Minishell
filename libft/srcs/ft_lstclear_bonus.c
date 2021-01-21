/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbabeau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:41:09 by gbabeau           #+#    #+#             */
/*   Updated: 2019/10/18 12:16:19 by gbabeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*p1;
	t_list	*p2;

	p1 = *lst;
	p2 = p1;
	while (lst && p1 && del)
	{
		p1 = p1->next;
		ft_lstdelone(p2, del);
		p2 = p1;
	}
	*lst = 0;
}
