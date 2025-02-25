/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:38:27 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/24 19:03:13 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

// Writes an integer to the buffer.
int	ft_putnbr_buf(char *buffer, size_t size, int n)
{
	int	len;

	len = 0;
	if (n == INT_MIN)
	{
		len += ft_putchar_buf(buffer, size, '-');
		len += ft_putchar_buf(buffer + len, size - len, '2');
		n = 147483648;
	}
	else if (n < 0)
	{
		len += ft_putchar_buf(buffer, size, '-');
		n = -n;
	}
	if (n >= 10)
		len += ft_putnbr_buf(buffer + len, size - len, n / 10);
	len += ft_putchar_buf(buffer + len, size - len, n % 10 + '0');
	return (len);
}
