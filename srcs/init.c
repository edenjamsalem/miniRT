/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:53 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/06 15:55:50 by eamsalem         ###   ########.fr       */
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

void	init_scene_basis(t_scene *scene)
{
	scene->world.right = (t_vec3){1, 0, 0};
	scene->world.up = (t_vec3){0, 1, 0};
	scene->world.forward = (t_vec3){0, 0, 1};
}

void	init_camera_basis(t_camera *camera, t_basis *world)
{
	camera->basis.forward = camera->orientation;
	if (check_equal(&world->up, &camera->basis.forward)) // need better check for parallelism
		camera->basis.right = normalize(cross(world->forward, camera->basis.forward));
	else
		camera->basis.right = normalize(cross(world->up, camera->basis.forward));

	camera->basis.up = normalize(cross(camera->basis.forward, camera->basis.right));
}

void	init_offset(t_vec2 *offset, int rpp)
{
	int	i;
	int	j;
	int	k;
	double	step;

	i = 0;
	k = 0;
	step = sqrt(rpp);
	while (i < step)
	{
		j = 0;
		while (j < step)
		{
			offset[k].x = (1.0 / step) * j;
			offset[k].y = (1.0 / step) * i;
			j++;
			k++;
		}
		i++;
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
