/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:35:20 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 18:35:49 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Writes a string to the buffer.
int	ft_putstr_buf(char *buffer, size_t size, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && i < size)
	{
		buffer[i] = str[i];
		i++;
	}
	return (i);
}
