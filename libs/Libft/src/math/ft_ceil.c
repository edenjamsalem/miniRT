/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ceil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:37:30 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/18 22:50:40 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the smallest integer value greater than or equal to x.
double	ft_ceil(double x)
{
	int	int_part;

	int_part = (int)x;
	if (x < int_part)
		return (int_part - 1);
	else
		return (int_part);
}
