/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:01:00 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:37 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
Outputs the integer 'n' to the given file descriptor.
Returns the number of characters printed.
*/
int	ft_putnbr_fd(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putchar_fd('-', fd);
		len += ft_putchar_fd('2', fd);
		n = 147483648;
	}
	else if (n < 0)
	{
		len += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		len += ft_putnbr_fd(n / 10, fd);
	len += ft_putchar_fd(n % 10 + '0', fd);
	return (len);
}
