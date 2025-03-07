/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:37:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/07 10:57:51y eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	shadow_ray_reaches_light(t_ray *ray, void **objs, double light_distance, void *intsec_obj)
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
			if (t >= 0 && t < light_distance)
				return (false);
        }
		else if (((t_plane *)objs[i])->shape == PLANE)
		{
            t = get_pl_t(ray, objs[i]);
			if (t >= 0 && t < light_distance)
				return (false);
		}
	}
	return (true);
}

void	cast_shadow_rays(t_intsec *intsec, t_scene *scene, t_mlx *mlx)
{
	t_shadow	shadow;
    double  light_distance;
	t_light	*light;
	int		i;
	int		j;

	shadow.ray.origin = intsec->pos;
	i = -1;
	while (scene->lights->content[++i])
	{
		light = (t_light *)scene->lights->content[i];
 		light_distance = magnitude(sub(light->center, shadow.ray.origin));
		shadow.ray.direction = normalize(sub(light->center, shadow.ray.origin));
		init_local_basis(&shadow.basis, shadow.ray.direction, &scene->world);

		j = -1;
		while (++j < mlx->consts.shadow_rpp)
		{
			light->intsec_points[j] = transform_ndc_to_worldspace(&light->intsec_points[j], &shadow.basis);
			shadow.ray.direction = normalize(sub(light->intsec_points[j], shadow.ray.origin));
			if (shadow_ray_reaches_light(&shadow.ray, scene->objs->content, light_distance, intsec->obj))
			{
				intsec->in_shadow = false;
				light->visibility += 1.0 / mlx->consts.shadow_rpp;
			}
		}
	}
}
