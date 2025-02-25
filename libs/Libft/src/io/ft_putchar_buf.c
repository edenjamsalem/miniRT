/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:34:21 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 18:35:00 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Writes a character to the buffer.
int	ft_putchar_buf(char *buffer, size_t size, char c)
{
	if (size > 0)
	{
		*buffer = c;
		return (1);
	}
	return (0);
}
