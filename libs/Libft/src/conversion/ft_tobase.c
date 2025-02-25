/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:21:47 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:25 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	calculate_length(unsigned long num, int base);

/*
Converts the number to a string representation of the number in the given base.
The base must be between 2 and 16.
*/
char	*ft_tobase(unsigned long num, int base)
{
	const char	*digits = "0123456789abcdef";
	char		*str;
	int			len;

	if (num == 0)
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	len = calculate_length(num, base);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = digits[num % base];
		num /= base;
	}
	return (str);
}

static int	calculate_length(unsigned long num, int base)
{
	int	len;

	len = 0;
	while (num)
	{
		num /= base;
		len++;
	}
	return (len);
}
