/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:42:16 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/21 21:22:43 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Adds the node ’new’ at the end of the list.
void	ft_lstadd_back(t_list **lst, t_list *new_list)
{
	t_list	*last;

	if (!lst || !new_list)
		return ;
	if (!*lst)
	{
		*lst = new_list;
		return ;
	}
	last = *lst;
	while (last->next != *lst)
		last = last->next;
	last->next = new_list;
}
