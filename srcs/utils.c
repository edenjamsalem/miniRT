/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:38:19 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/10 17:38:20 by eamsalem         ###   ########.fr       */
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

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	calc_time_diff(struct timeval *start, struct timeval *end)
{
	time_t		secs;
	time_t		millisecs;
	suseconds_t	micro_secs;

	secs = end->tv_sec - start->tv_sec;
	micro_secs = end->tv_usec - start->tv_usec;
	if (micro_secs < 0)
	{
		micro_secs += 1000000;
		secs--;
	}
	millisecs = ((double)secs + (double)micro_secs / 1000000.0) * 1000;
	return (millisecs);
}
