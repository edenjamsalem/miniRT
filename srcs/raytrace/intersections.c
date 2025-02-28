/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:30:49 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/28 14:26:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	get_pl_t(t_ray *ray, t_plane *plane)
{
	double		t;

	t = dot(plane->normal, ray->direction);
	if (fabs(t) < 0.000001) // checks if parallel
		return (-1);
	t = dot(plane->normal, sub(plane->point, ray->origin)) / t;
	return (t);
}

void	get_pl_intsec_data(t_ray *ray, t_plane *plane, t_intsec *intsec)
{
	intsec->t = get_pl_t(ray, plane);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
		intsec->colour = plane->colour;
		intsec->shape = PLANE;
		intsec->normal = plane->normal;
		intsec->obj = (void *)plane;
	}	
}

double	get_sp_t(t_ray *ray, t_sphere *sphere)
{
	double		a;
	double		b;
	double		c;
	double		t[2];
	double		det;
	t_vec3		o_sub_c;

	o_sub_c = sub(ray->origin, sphere->center);
	a = dot(ray->direction, ray->direction);
	b = 2.0 * dot(ray->direction, o_sub_c);
	c = dot(o_sub_c, o_sub_c) - (sphere->radius * sphere->radius);

	det = b * b - (4 * a * c);
	if (det < 0)
		return (-1);
	if (det == 0)
		return (-b / (2 * a));
	
	t[0] = (-b + det) / (2 * a);
	t[1] = (-b - det) / (2 * a);

	if (t[0] > 0 && t[1] > 0)
		return (fmin(t[0], t[1]));
	else if (t[0] > 0)
		return (t[0]);
	else if (t[1] > 0)
		return (t[1]);
	else	
		return (-1);
}

void	get_sp_intsec_data(t_ray *ray, t_sphere *sphere, t_intsec *intsec)
{
	intsec->t = get_sp_t(ray, sphere);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
		intsec->colour = sphere->colour;
		intsec->shape = SPHERE;
		intsec->normal = normalize(sub(intsec->pos, sphere->center));
		intsec->obj = (void *)sphere;
	}
}

t_intsec	find_intersection(t_ray *ray, void **objs)
{
	int			i;
	t_intsec	current;
	t_intsec	nearest;

	init_intsec(&nearest);
	i = 0;
	while (objs[i])
	{
		init_intsec(&current);
		if (((t_sphere *)objs[i])->shape == SPHERE)
			get_sp_intsec_data(ray, objs[i], &current);
		else if (((t_plane *)objs[i])->shape == PLANE)
			get_pl_intsec_data(ray, objs[i], &current);
		if (current.t >= 0 && current.t < nearest.t)
			nearest = current;
		i++;
	}
	return (nearest);
}
