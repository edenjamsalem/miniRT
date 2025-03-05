/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:37:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/05 15:30:12 by eamsalem         ###   ########.fr       */
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

void	cast_shadow_rays(t_intsec *intersection, t_scene *scene)
{
	t_ray	shadow;
    double  light_distance;
	t_light	*light;
	int		i;

	shadow.origin = intersection->pos;
	i = 0;
	while (scene->lights->content[i])
	{
		light = (t_light *)scene->lights->content[i];
		shadow.direction = normalize(sub(light->pos, shadow.origin));
 		light_distance = magnitude(sub(light->pos, shadow.origin));
		
		if (shadow_ray_reaches_light(&shadow, scene->objs->content, light_distance, intersection->obj))
		{
			intersection->in_shadow = false;
			light->hits_pixel = true;
		}
		i++;
	}
}
