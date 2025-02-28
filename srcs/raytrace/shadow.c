/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:37:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/28 12:28:03 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	shadow_ray_intersects(t_ray *ray, void **objs, double light_distance)
{
	int		i;
    double	t;

	i = 0;
	while (objs[i])
	{
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
		i++;
	}
	return (false);
}

bool	cast_shadow_ray(t_intsec *intersection, t_scene *scene)
{
	t_ray	shadow;
	t_vec3	epsilon;
    double  light_distance;
	
	// prevents shadowray intsec calc from counting intsec point as blocking shadow ray
	epsilon = scale(intersection->normal, 0.001);
	
	shadow.origin = add(intersection->pos, epsilon);
	shadow.direction = normalize(sub(scene->light_src.pos, shadow.origin));
    light_distance = magnitude(sub(scene->light_src.pos, shadow.origin));
	return (shadow_ray_intersects(&shadow, scene->objs->content, light_distance));
}
