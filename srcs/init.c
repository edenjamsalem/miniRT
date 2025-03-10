/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:39:53 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/07 12:48:05t by eamsalem         ###   ########.fr       */
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

void	init_world_basis(t_basis *world)
{
	world->right = (t_vec3){1, 0, 0};
	world->up = (t_vec3){0, 1, 0};
	world->forward = (t_vec3){0, 0, 1};
}

void	init_local_basis(t_basis *local, t_vec3 forward, t_basis *world)
{
	local->forward = forward;
	if (dot(world->up, local->forward) >= 0.99)
		local->right = normalize(cross(world->forward, local->forward));
	else
		local->right = normalize(cross(world->up, local->forward));

	local->up = normalize(cross(local->forward, local->right));
}

void init_intsec(t_intsec *intersection)
{
	intersection->pos = (t_vec3){INFINITY, INFINITY, INFINITY};
	intersection->colour = (t_rgb){0, 0, 0};
	intersection->in_shadow = true;
	intersection->t = INFINITY;
	intersection->obj = NULL;
}

void	init_offset(t_consts *consts)
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

