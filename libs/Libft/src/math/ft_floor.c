/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:39:37 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/18 22:50:45 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the largest integer value less than or equal to x.
double	ft_floor(double x)
{
	int	int_part;

	int_part = (int)x;
	if (x < int_part)
		return (int_part - 1);
	else
		return (int_part);
}
