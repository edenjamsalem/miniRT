/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:07:53 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 19:08:02 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Writes a string followed by a newline character to the buffer.
int	ft_putendl_buf(char *buffer, size_t size, const char *str)
{
	size_t	len;

	len = ft_putstr_buf(buffer, size, str);
	if (len == 0)
		return (0);
	if (len + 1 < size)
	{
		buffer[len] = '\n';
		return (len + 1);
	}
	return (len);
}
