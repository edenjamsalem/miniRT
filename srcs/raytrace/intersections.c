/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/26 19:27:28 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_intsec	check_plane_intersection(t_ray *ray, t_plane *plane)
{
	t_intsec	intsec;
	double		t;

	t = dot(plane->normal, ray->direction);
	// printf("dot product: %f\n", t);
	if (t == 0)
	{
		intsec.pos = (t_vec3){0, 0, 0};
		intsec.colour = (t_rgb){0, 0, 0};
		intsec.shape = NONE;
		return (intsec);
	}
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	if (t > 0)
	{
		intsec.pos = add(ray->origin,
							(t_vec3){
								ray->direction.x * t, ray->direction.y * t,
									ray->direction.z * t});
		intsec.colour = plane->colour;
		intsec.shape = PLANE;
	}
	else
	{
		intsec.pos = (t_vec3){0, 0, 0};
		intsec.colour = (t_rgb){0, 0, 0};
		intsec.shape = NONE;
	}
	return (intsec);
}

/*
t_intsec	check_sphere_intersection(t_ray *ray, t_sphere *sphere)
{
	t_intsec	intersection;

	
	
}
*/
/*
t_intsec	find_intersection(t_ray *ray, void **objs)
{
	int			i;
	t_intsec	current;
	t_intsec	nearest;

	i = 0;
	nearest.colour = (t_rgb){0, 0, 0};
	while (objs[i])
	{
		// if (((t_sphere *)objs[i])->shape == SPHERE)
		// 	current = check_sphere_intersection(ray, objs[i]);
		if (((t_plane *)objs[i])->shape == PLANE)
			current = check_plane_intersection(ray, objs[i]);
		// else if (((t_cylinder *)objs[i])->shape == CYLINDER)
		// 	current = check_cylinder_intersection(ray, objs[i]);
		// if (is_closer(current, nearest))
		nearest = current;
		i++;
	}
	return (nearest);
}
*/