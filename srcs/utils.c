/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:23:21 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/21 15:54:22by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	perror_exit(t_err err, int line_nbr, char **data, int i, t_scene *scene)
{
	ft_fprintf(2, "Error\n");
	if (err == LINE_ARG_COUNT)
		ft_fprintf(2, "Line %d: Incorrect number of args.\n", line_nbr);
	if (err == ARG_OUT_OF_RANGE)
		ft_fprintf(2, "Line %d: '%s' has invalid range.\n", line_nbr, data[i]);
	if (err == DUPLICATE)
		ft_fprintf(2, "Line %d: is duplicate.\n", line_nbr);
	if (err == MALLOC)
		ft_fprintf(2, "malloc error\n");
	
	free_arrlst(scene->objs, free);
	free_2darr((void **)data, ft_2darr_len((void **)data));
	exit(EXIT_FAILURE);
}

char	*find_offset(int x, int y, t_img *img)
{
	return (img->addr + ((y * img->line_len) + (x * (img->bpp / 8))));
}

unsigned int	rgb_to_int(t_rgb *rgb)
{
	return ((rgb->r << 16) | (rgb->g << 8) | rgb->b);
}

bool	within_screen(int x, int y)
{
	return (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT);
}

void	put_pixel(t_img *img, t_vec3 *pos, t_rgb *colour)
{
	char	*dst;

	if (within_screen(pos->x, pos->y)) // check if i still need this
	{
		dst = find_offset(pos->x, pos->y, img);
		*((unsigned int *)dst) = rgb_to_int(colour);
	}
}
