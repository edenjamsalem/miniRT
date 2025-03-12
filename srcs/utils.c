/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:38:19 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/12 15:48:59 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	perror_exit(t_err err, t_parse *parse, int i)
{
	(void)i;
	ft_fprintf(2, "Error:");
	if (err == LINE_ARG_COUNT)
		ft_fprintf(2, "Line %d: Incorrect number of args.\n", parse->line_num);
	else if (err == ARG_OUT_OF_RANGE)
		ft_fprintf(2, "Line %d: arg has invalid range.\n", parse->line_num);
	else if (err == DUPLICATE)
		ft_fprintf(2, "Line %d: is duplicate.\n", parse->line_num);
	else if (err == VEC_COUNT)
		ft_fprintf(2, "Line %d: vector has missing value.\n", parse->line_num);
	else if (err == MALLOC)
		ft_fprintf(2, "malloc error\n");
	else
		ft_fprintf(2, "undefined error\n");
	free_arrlst(parse->scene->lights, free);
	free_arrlst(parse->scene->objs, free);
	free_2darr((void **)parse->data, ft_2darr_len((void **)parse->data));
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
