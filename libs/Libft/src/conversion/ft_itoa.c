/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:47:17 by muabdi            #+#    #+#             */
/*   Updated: 2024/05/24 22:31:23 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*ft_convert_num_to_str(int len, unsigned int num);
static int	ft_count_digits(int n);

/*
Allocates (with malloc(3)) and returns a string representing the integer
received as an argument. Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	num;

	len = ft_count_digits(n);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		num = -n;
		str = ft_convert_num_to_str(len, num);
		if (!str)
			return (NULL);
		str[0] = '-';
	}
	else
	{
		num = n;
		str = ft_convert_num_to_str(len, num);
		if (!str)
			return (NULL);
	}
	return (str);
}

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_convert_num_to_str(int len, unsigned int num)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (num > 0)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
