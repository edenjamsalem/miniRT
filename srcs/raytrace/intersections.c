/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/28 10:24:20 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_intsec	get_pl_intsec_data(t_ray *ray, t_plane *plane, double t)
{
	t_intsec	intersection;

	intersection.pos = add(ray->origin, scale(ray->direction, t));
	intersection.colour = plane->colour;
	intersection.shape = PLANE;
	intersection.normal = plane->normal;
	intersection.exists = true;
	return (intersection);
}

double	get_t_pl(t_ray *ray, t_plane *plane)
{
	double		t;

	t = dot(plane->normal, ray->direction);
	if (t == 0)
		return (INFINITY);
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	if (t < 0)
		return (INFINITY);
	return (t);
}

bool	sp_intersects(t_ray *ray, t_sphere *sphere)
{
	double		A;
	double		B;
	double		C;
	double		det;
	t_vec3		O_sub_C;

	O_sub_C = sub(ray->origin, sphere->center);
	A = dot(ray->direction, ray->direction);
	B = 2.0 * dot(ray->direction, O_sub_C);
	C = dot(O_sub_C, O_sub_C) - (sphere->radius * sphere->radius);

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
	t_vec3		O_sub_C;

	O_sub_C = sub(ray->origin, sphere->center);
	A = dot(ray->direction, ray->direction);
	B = 2.0 * dot(ray->direction, O_sub_C);
	C = dot(O_sub_C, O_sub_C) - (sphere->radius * sphere->radius);

	t[0] = (-B + sqrt((B * B) - (4 * A * C))) / (2 * A);
	t[1] = (-B - sqrt((B * B) - (4 * A * C))) / (2 * A);

	init_intsec(&intersection);
	if (t[0] > 0 && t[1] > 0)
		intersection.pos = add(ray->origin, scale(ray->direction, fmin(t[0], t[1])));
	else if (t[0] > 0)
		intersection.pos = add(ray->origin, scale(ray->direction, t[0]));
	else if (t[1] > 0)
		intersection.pos = add(ray->origin, scale(ray->direction, t[1]));
	else
		return (intersection);
		
	intersection.colour = sphere->colour;
	intersection.shape = SPHERE;
	intersection.normal = normalize(sub(intersection.pos, sphere->center));
	intersection.exists = true;
	return (intersection);
}
/*
bool	shadow_ray_intersects(t_ray *ray, void **objs)
{
	int	i;

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
*/
bool	is_closer(t_vec3 *current, t_vec3 *nearest, t_vec3 *origin)
{
	return (sqr_magnitude(sub(*current, *origin)) < sqr_magnitude(sub(*nearest, *origin)));
}

t_intsec	find_intersection(t_ray *ray, void **objs)
{
	int			i;
	t_intsec	current;
	t_intsec	nearest;
	double		t;

	init_intsec(&nearest);
	init_intsec(&current);
	i = 0;
	while (objs[i])
	{
		if (((t_sphere *)objs[i])->shape == SPHERE)
		 	current = get_sp_intsec_data(ray, objs[i]);
		else if (((t_plane *)objs[i])->shape == PLANE)
		{
			t = get_t_pl(ray, objs[i]);
			if (t != INFINITY)
				current = get_pl_intsec_data(ray, objs[i], t);
		}
		// else if (((t_cylinder *)objs[i])->shape == CYLINDER)
		// 	current = check_cylinder_intersection(ray, objs[i]);
		if (is_closer(&current.pos, &nearest.pos, &ray->origin))
			nearest = current;
		i++;
	}
	return (nearest);
}
