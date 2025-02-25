/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:30:33 by muabdi            #+#    #+#             */
/*   Updated: 2024/07/09 15:51:14 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Counts the number of nodes in a list.
int	ft_lstsize(t_list *lst)
{
	t_list	*head;
	int		count;

	count = 0;
	head = lst;
	while (lst != head)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
