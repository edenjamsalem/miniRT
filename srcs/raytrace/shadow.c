/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:37:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/04 15:46:15 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	shadow_ray_intersects(t_ray *ray, void **objs, double light_distance, void *intsec_obj)
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
				return (true);
        }
		else if (((t_plane *)objs[i])->shape == PLANE)
		{
            t = get_pl_t(ray, objs[i]);
			if (t >= 0 && t < light_distance)
				return (true);
		}
	}
	return (false);
}

bool	cast_shadow_ray(t_intsec *intersection, t_scene *scene)
{
	t_ray	shadow;
    double  light_distance;
	
	shadow.origin = intersection->pos;
	shadow.direction = normalize(sub(scene->light.pos, shadow.origin));
    light_distance = magnitude(sub(scene->light.pos, shadow.origin));
	return (shadow_ray_intersects(&shadow, scene->objs->content, light_distance, intersection->obj));
}
