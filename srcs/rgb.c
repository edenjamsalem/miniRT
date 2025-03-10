/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:07:15 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/03 18:43:31y eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

unsigned int	rgb_to_int(t_rgb rgb)
{
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	return ((t_rgb){min(a.r + b.r, 255), min(a.g + b.g, 255), min(a.b + b.b, 255)});
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

bool    rgb_equal(t_rgb a, t_rgb b)
{
    return (a.r == b.r && a.g == b.g && a.b == b.b);
}

void	print_rgb(t_rgb rgb)
{
	printf("{%d, %d, %d}\n", rgb.r, rgb.g, rgb.b);
}

t_rgb	rgb_average(t_rgb *colours, int count)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < count)
	{
		r += colours[i].r;
		g += colours[i].g;
		b += colours[i].b;
		i++;
	}
	r = r / count;
	g = g / count;
	b = b / count;
	return ((t_rgb){r, g, b});
}