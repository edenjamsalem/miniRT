/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:41:19 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/18 22:50:58 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the value of the argument rounded to the nearest integer value.
double	ft_round(double x)
{
	if (x >= 0.0)
		return ((int)(x + 0.5));
	else
		return ((int)(x - 0.5));
}
