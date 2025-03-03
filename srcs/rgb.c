/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:07:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/03 18:19:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

unsigned int	rgb_to_int(t_rgb *rgb)
{
	return ((rgb->r << 16) | (rgb->g << 8) | rgb->b);
}

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	return ((t_rgb){min(a.r + b.r, 255), min(a.g + b.g, 255), min(a.b + b.b, 255)});
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	return ((t_rgb){max(a.r - b.r, 0), max(a.g - b.g, 0), max(a.b - b.b, 0)});
}

t_rgb	rgb_scale(t_rgb a, double t)
{
	return ((t_rgb){min(a.r * t, 255), min(a.g * t, 255), min(a.b * t, 255)});
}
