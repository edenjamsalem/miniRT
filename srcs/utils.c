/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:17:02 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 11:17:03 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	perror_exit(t_err err, t_parse *parse, int i)
{
	(void)i;
	ft_fprintf(2, "Error\n");
	if (err == LINE_ARG_COUNT)
		ft_fprintf(2, "Line %d: Incorrect number of args.\n", parse->line_num);
	else if (err == ARG_OUT_OF_RANGE)
		ft_fprintf(2, "Line %d: '%s' has invalid range.\n", parse->line_num, parse->data[i]);
	else if (err == DUPLICATE)
		ft_fprintf(2, "Line %d: only 1 '%s' permitted.\n", parse->line_num, parse->data[0]);
	else if (err == VEC_COUNT)
		ft_fprintf(2, "Line %d: '%s' must be 3D vec.\n", parse->line_num, parse->data[i]);
	else if(err == _FILE)
		ft_fprintf(2, "Invalid file.\n");
	else if (err == MALLOC)
		ft_fprintf(2, "Malloc error\n");
	else
		ft_fprintf(2, "Undefined error\n");
		
	free_arrlst(parse->scene->lights, free);
	free_arrlst(parse->scene->objs, free);
	free_2darr((void **)parse->data, ft_2darr_len((void **)parse->data));
	exit(EXIT_FAILURE);
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

void	free_mem(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->img.ptr);
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_display(mlx->ptr);
	free_arrlst(mlx->scene.objs, free);
	free_arrlst(mlx->scene.lights, free);
	free(mlx->ptr);
}
