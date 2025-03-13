/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:19:34 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 15:20:10 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

char	*find_offset(int x, int y, t_img *img)
{
	return (img->addr + ((y * img->line_len) + (x * (img->bpp / 8))));
}

bool	within_screen(int x, int y)
{
	return (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT);
}

void	put_pixel(t_pixel *pixel, t_img *img)
{
	char	*dst;

	if (!within_screen(pixel->x, pixel->y))
		return ;

	dst = find_offset(pixel->x, pixel->y, img);
	*((unsigned int *)dst) = rgb_to_int(pixel->colour);
}