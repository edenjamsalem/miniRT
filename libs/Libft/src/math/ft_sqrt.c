/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:32:55 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/18 22:51:50 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the square root of x.
double	ft_sqrt(double x)
{
	double	epsilon;
	double	guess;

	epsilon = 0.00001;
	guess = x / 2.0;
	while ((guess * guess - x) > epsilon || (x - guess * guess) > epsilon)
		guess = (guess + x / guess) / 2.0;
	return (guess);
}
