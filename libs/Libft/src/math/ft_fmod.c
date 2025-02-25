/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:45:51 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/18 22:50:50 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the floating-point remainder of x/y (rounded towards zero).
double	ft_fmod(double x, double y)
{
	return ((x - y) * ((int)(x / y)));
}
