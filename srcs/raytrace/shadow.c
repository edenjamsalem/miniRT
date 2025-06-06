/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:16:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/05/28 08:42:54 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	is_lit_up(t_ray *ray, void **objs, double light_dist, void *intsec_obj)
{
	int		i;
	double	t;

	i = -1;
	while (objs[++i])
	{
		if (objs[i] == intsec_obj)
			continue ;
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

double	cast_shadow(t_shadow *shadow, t_vec3 *light_positions, t_intsec *intsec, t_scene *scene)
{
	int		i;
	double	light_d;
	t_vec3	light_dir;
	double	visibility;

	i = 0;
	visibility = 0.0;
	while (i < scene->consts.shadow_rpp)
	{
		light_dir = sub(light_positions[i], shadow->ray.origin);
		light_d = magnitude(light_dir);
		shadow->ray.dir = normalize(light_dir);
		if (is_lit_up(&shadow->ray, scene->objs->content, light_d, intsec->obj))
		{
			intsec->in_shadow = false;
			visibility += 1.0 / scene->consts.shadow_rpp;
		}
		i++;
	}
	return (visibility);
}

void	gen_rand_offsets(t_light *light, t_basis *shadow, t_consts *consts)
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
		light->rand_positions[i].x = r * cos(theta);
		light->rand_positions[i].y = r * sin(theta);
		light->rand_positions[i].z = 0;
		light->rand_positions[i] = transform_basis(&light->rand_positions[i], shadow);
		light->rand_positions[i] = add(light->rand_positions[i], light->center);
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
		light->visibility = 0.0;
		light->dir = normalize(sub(light->center, intsec->pos));
		calc_local_basis(&shadow.basis, light->dir, &scene->consts.world);
		gen_rand_offsets(light, &shadow.basis, &scene->consts);
		light->visibility = cast_shadow(&shadow, light->rand_positions, intsec, scene);
	}
}
