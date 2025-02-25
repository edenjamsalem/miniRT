/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:22:54 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/21 21:22:53 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Adds the node ’new’ at the beginning of the list.
void	ft_lstadd_front(t_list **lst, t_list *new_list)
{
	t_list	*last;

	last = *lst;
	while (last->next != *lst)
		last = last->next;
	if (!lst || !new_list)
		return ;
	new_list->next = *lst;
	*lst = new_list;
}
