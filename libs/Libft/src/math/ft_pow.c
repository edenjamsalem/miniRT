/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:35:35 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/18 22:54:06 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Returns the value of the first argument raised to the power of the
	second argument.
*/
double	ft_pow(double base, int exp)
{
	double	result;
	int		i;

	result = 1.0;
	i = 0;
	while (i < exp)
	{
		result *= base;
		i++;
	}
	return (result);
}
