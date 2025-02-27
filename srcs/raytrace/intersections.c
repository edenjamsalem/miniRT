/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/27 15:04:09 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_intsec	get_pl_intsec_data(t_ray *ray, t_plane *plane)
{
	t_intsec	intersection;
	double		t;

	init_intsec(&intersection);
	t = dot(plane->normal, ray->direction);
	if (t == 0)
		return (intersection);
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	if (t > 0)
	{
		intersection.pos = add(ray->origin, mult(ray->direction, t));
		intersection.colour = plane->colour;
		intersection.shape = PLANE;
	}

	return (intersection);
}

bool	pl_intersects(t_ray *ray, t_plane *plane)
{
	double		t;

	t = dot(plane->normal, ray->direction);
	if (t == 0)
		return (false);
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	if (t > 0)
		return (true);
	return (false);
}

bool	sp_intersects(t_ray *ray, t_sphere *sphere)
{
	double		A;
	double		B;
	double		C;
	double		det;

	A = dot(ray->direction, ray->direction);
	B = 2.0 * dot(ray->direction, sub(ray->origin, sphere->center));
	C = dot(sub(ray->origin, sphere->center), sub(ray->origin, sphere->center)) - pow(sphere->diameter / 2, 2);
	
	det = B * B - (4 * A * C);
	if (det < 0) // no intersection
		return (false);
	return (true);
}

t_intsec	get_sp_intsec_data(t_ray *ray, t_sphere *sphere)
{
	double		t[2];
	double		A;
	double		B;
	double		C;
	t_intsec	intersection;

	A = dot(ray->direction, ray->direction);
	B = 2.0 * dot(ray->direction, sub(ray->origin, sphere->center));
	C = dot(sub(ray->origin, sphere->center), sub(ray->origin, sphere->center)) - pow(sphere->diameter / 2, 2);

	t[0] = (-B + sqrt((B * B) - (4 * A * C))) / 2.0;
	t[1] = (-B - sqrt((B * B) - (4 * A * C))) / 2.0;

	init_intsec(&intersection);
	if (t[0] < 0 && t[1] < 0) // no intersection
		return (intersection); 
	else if (t[0] < 0)
		intersection.pos = add(ray->origin, mult(ray->direction, t[1]));
	else if (t[1] < 0)
		intersection.pos = add(ray->origin, mult(ray->direction, t[0]));
	else
		intersection.pos = add(ray->origin, mult(ray->direction, fmin(t[0], t[1])));
		
	intersection.colour = sphere->colour;
	intersection.shape = SPHERE;
	return (intersection);
}


bool	shadow_ray_intersects(t_ray *ray, void **objs)
{
	int			i;

	i = 0;
	while (objs[i])
	{
		if (((t_sphere *)objs[i])->shape == SPHERE && sp_intersects(ray, objs[i]))
			return (true);
		if (((t_plane *)objs[i])->shape == PLANE && pl_intersects(ray, objs[i]))
			return (true);
		// else if (((t_cylinder *)objs[i])->shape == CYLINDER && cy_intersects(ray, objs[i]))
		//	return (true);
		// if (is_closer(current, nearest))
		i++;
	}
	return (false);
}

bool	is_closer(t_vec3 *current, t_vec3 *nearest, t_vec3 *origin)
{
	return (sqr_magnitude(sub(*current, *origin)) < sqr_magnitude(sub(*nearest, *origin)));
}

t_intsec	find_intersection(t_ray *ray, void **objs)
{
	int			i;
	t_intsec	current;
	t_intsec	nearest;

	i = 0;
	init_intsec(&nearest);
	while (objs[i])
	{
		if (((t_sphere *)objs[i])->shape == SPHERE)
		 	current = get_sp_intsec_data(ray, objs[i]);
		if (((t_plane *)objs[i])->shape == PLANE)
			current = get_pl_intsec_data(ray, objs[i]);
		// else if (((t_cylinder *)objs[i])->shape == CYLINDER)
		// 	current = check_cylinder_intersection(ray, objs[i]);
		if (is_closer(&current.pos, &nearest.pos, &ray->origin))
			nearest = current;
		i++;
	}
	return (nearest);
}
