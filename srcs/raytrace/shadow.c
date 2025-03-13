/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:37:44 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/13 16:59:30 by eamsalem         ###   ########.fr       */
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
		if (((t_sp *)objs[i])->shape == SP)
			t = get_sp_t(ray, objs[i]);
		else if (((t_pl *)objs[i])->shape == PL)
			t = get_pl_t(ray, objs[i]);
		else if (((t_cy *)objs[i])->shape == CY)
			t = get_curved_t(ray, objs[i]);
		if (t >= 0 && t < light_dist)
			return (false);
	}
	return (true);
}

void	cast_to_light(t_light *light, t_shadow *shadow, t_intsec *intsec, t_scene *scene)
{
	int		i;
	double  light_dist;
	t_vec3	light_dir;
	
	i = 0;
	light->visibility = 0.0;
	while (i < scene->consts.shadow_rpp)
	{
		light_dir = sub(light->rand_points[i], shadow->ray.origin);
		light_dist = magnitude(light_dir);
		shadow->ray.dir = normalize(light_dir);
		
		if (hits_light(&shadow->ray, scene->objs->content, light_dist, intsec->obj))
		{
			intsec->in_shadow = false;
			light->visibility += 1.0 / scene->consts.shadow_rpp;
		}
		i++;
	}
}

void gen_rand_light_points(t_light *light, t_basis *shadow, t_consts *consts)
{
	int		i;
	double	theta;
	double	r;
	
	i = 0;
	theta = 0;
	while (i < consts->shadow_rpp)
	{
		r = light->radius * sqrt(((double)rand() / RAND_MAX));
  		theta = ((double)rand() / RAND_MAX) * 2 * PI;

		light->rand_points[i].x = r * cos(theta);
		light->rand_points[i].y = r * sin(theta);
		light->rand_points[i].z = 0;
		light->rand_points[i] = transform_local_to_world(&light->rand_points[i], shadow);
		light->rand_points[i] = add(light->rand_points[i], light->center);
		i++;
	}
}

void	cast_shadow_rays(t_intsec *intsec, t_scene *scene)
{
	t_shadow	shadow;
	t_light		*light;
	int			i;

	shadow.ray.origin = intsec->pos;
	i = -1;
	while (scene->lights->content[++i])
	{
		light = (t_light *)(scene->lights->content[i]);
		light->dir = normalize(sub(light->center, intsec->pos));
		calc_local_basis(&shadow.basis, light->dir, &scene->consts.world);
		gen_rand_light_points(light, &shadow.basis, &scene->consts);
		cast_to_light(light, &shadow, intsec, scene);
	}
}
