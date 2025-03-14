/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:54 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 11:16:55 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_mlx_data(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		exit(EXIT_FAILURE);
	mlx->win = mlx_new_window(mlx->ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!mlx->win)
	{
		free_mem(mlx);
		exit(EXIT_FAILURE);
	}
}

void	init_img_data(t_img *img, t_mlx *mlx)
{
	img->ptr = mlx_new_image(mlx->ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->ptr)
	{
		free_mem(mlx);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp, \
							&mlx->img.line_len, &mlx->img.endian);
	if (!img->addr)
	{
		free_mem(mlx);
		exit(EXIT_FAILURE);
	}
}

void init_intsec(t_intsec *intersection)
{
	intersection->pos = (t_vec3){INFINITY, INFINITY, INFINITY};
	intersection->colour = (t_rgb){0, 0, 0};
	intersection->in_shadow = true;
	intersection->t = INFINITY;
	intersection->obj = NULL;
}

void	init_pixel_offsets(t_consts *consts)
{
	int	i;
	int	j;
	int	k;
	double	step;

	if (consts->rpp > 64)
		consts->rpp = 64;
	i = 0;
	k = 0;
	step = sqrt(consts->rpp);
	while (i < step)
	{
		j = 0;
		while (j < step)
		{
			consts->pixel_offsets[k].x = (1.0 / step) * j;
			consts->pixel_offsets[k].y = (1.0 / step) * i;
			k++;
			j++;
		}
		i++;
	}
}

void	init_project(t_mlx *mlx, t_scene *scene, t_camera *camera)
{
	init_mlx_data(mlx);
	init_img_data(&mlx->img, mlx);
	init_world_basis(&scene->consts.world);
	calc_local_basis(&camera->basis, camera->orientation, &scene->consts.world);
	scene->consts.rpp = 1; // max == 64
	scene->consts.shadow_rpp = 20; // max == 128
	init_pixel_offsets(&scene->consts);
	check_camera_inside_objs(scene->objs->content, &scene->camera);
}


