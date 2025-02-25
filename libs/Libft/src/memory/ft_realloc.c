/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:17 by muabdi            #+#    #+#             */
/*   Updated: 2024/06/26 23:18:43 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
Changes the size of the memory block pointed to by ptr to size bytes.
The contents will be unchanged in the range from the start of the region up
to the  minimum of the old and new sizes.

If the new size is larger than the old size, the added memory will not be
initialized. If ptr is NULL, then the call is equivalent to malloc(size),
for all values of size; if size is equal to zero, and  ptr is not NULL,
then the call is equivalent to	free(ptr).

Unless ptr is NULL,it must have been returned by an earlier call to
ft_malloc(), ft_calloc(), or ft_realloc(). If the area pointed to was moved,
a	free(ptr) is done.
*/
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return (NULL);
		return (new_ptr);
	}
	if (!new_size)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
