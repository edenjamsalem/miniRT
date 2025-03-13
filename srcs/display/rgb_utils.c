/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:38:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 15:29:25 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		min(a.r + b.r, 255),
		min(a.g + b.g, 255),
		min(a.b + b.b, 255)
	});
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	return ((t_rgb){max(a.r - b.r, 0), max(a.g - b.g, 0), max(a.b - b.b, 0)});
}

t_rgb rgb_scale(t_rgb a, double t)
{
	return ((t_rgb){
		min((int)round(a.r * t), 255), 
		min((int)round(a.g * t), 255), 
		min((int)round(a.b * t), 255)
	});
}

t_rgb rgb_mult(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		min(((a.r * b.r) / 255.0), 255),
		min(((a.g * b.g) / 255.0), 255),
		min(((a.b * b.b) / 255.0), 255)
	});
}
