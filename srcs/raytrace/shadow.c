/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:37:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/07 16:52:57 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	hits_light(t_ray *ray, void **objs, double light_dist, void *intsec_obj)
{
	int		i;
    double	t;

	i = -1;
	while (objs[++i])
	{
		if (objs[i] == intsec_obj)
			continue;
		if (((t_sphere *)objs[i])->shape == SPHERE)
        {
            t = get_sp_t(ray, objs[i]);
			if (t >= 0 && t < light_dist)
				return (false);
        }
		else if (((t_plane *)objs[i])->shape == PLANE)
		{
            t = get_pl_t(ray, objs[i]);
			if (t >= 0 && t < light_dist)
				return (false);
		}
	}
	return (true);
}

void	fire_at_light_points(t_light *light, t_shadow *shadow, t_intsec *intsec, t_mlx *mlx)
{
	int		i;
	t_vec3	light_point;
    double  light_dist;
	
	i = 0;
	while (i < mlx->consts.shadow_rpp)
	{
		light_point = transform_local_to_world(&light->intsec_points[i], &shadow->basis);
		light_point = add(light_point, light->center);
		light_dist = magnitude(sub(light_point, shadow->ray.origin));
		shadow->ray.direction = normalize(sub(light_point, shadow->ray.origin));
		
		if (hits_light(&shadow->ray, mlx->scene.objs->content, light_dist, intsec->obj))
		{
			intsec->in_shadow = false;
			light->visibility += 1.0 / mlx->consts.shadow_rpp;
		}
		i++;
	}
}

void	cast_shadow_rays(t_intsec *intsec, t_scene *scene, t_mlx *mlx)
{
	t_shadow	shadow;
	t_light	*light;
	int		i;

	shadow.ray.origin = intsec->pos;
	i = -1;
	while (scene->lights->content[++i])
	{
		light = (t_light *)(scene->lights->content[i]);
		light->visibility = 0.0;
		shadow.ray.direction = light->dir;
		init_local_basis(&shadow.basis, shadow.ray.direction, &scene->world);
		gen_rand_light_point(light, &mlx->consts);
		fire_at_light_points(light, &shadow, intsec, mlx);
	}
	//	printf("light visibility = %f\n", light->visibility);
}