/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:39:31 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 19:09:58 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Writes an unsigned integer to the buffer.
int	ft_putunbr_buf(char *buffer, size_t size, unsigned int n)
{
	int				len;
	unsigned int	num;

	len = 0;
	num = n;
	if (num >= 10)
		len += ft_putunbr_buf(buffer + len, size - len, num / 10);
	if (size > (size_t)len)
		buffer[len] = num % 10 + '0';
	len++;
	return (len);
}
