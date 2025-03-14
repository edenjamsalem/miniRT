/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_curve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:15:24 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/14 11:30:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static double	get_h(double t, t_ray *ray, t_cy *cy)
{
	t_vec3	p;
	double	h;

	p = add(ray->origin, scale(ray->dir, t));
	h = dot(sub(p, cy->center), cy->axis);
	return (h);
}

static bool	t_valid(double t, double h, t_cy *cy)
{
	return (t > 0 && h >= cy->bottom_h && h <= cy->top_h);
}

static double	get_closest_t(double t[2], t_ray *ray, t_cy *cy)
{
	double	h[2];

	h[0] = get_h(t[0], ray, cy);
	h[1] = get_h(t[1], ray, cy);
	if (t_valid(t[0], h[0], cy) && t_valid(t[1], h[1], cy))
	{
		cy->intsec_count += 2;
		return (fmin(t[0], t[1]));
	}
	else if (t_valid(t[0], h[0], cy))
	{
		cy->intsec_count += 1;
		return (t[0]);
	}
	else if (t_valid(t[1], h[1], cy))
	{
		cy->intsec_count += 1;
		return (t[1]);
	}
	else
		return (-1.0);
}

double	get_curved_t(t_ray *ray, t_cy *cy)
{
	t_quadratic	q;
	t_vec3		l;
	double		t[2];

	l = sub(ray->origin, cy->center);
	q.a = 1 - pow(dot(ray->dir, cy->axis), 2);
	q.b = 2 * (dot(ray->dir, l) - dot(ray->dir, cy->axis) * dot(l, cy->axis));
	q.c = dot(l, l) - pow(dot(l, cy->axis), 2) - pow(cy->diameter / 2.0, 2);
	q.discriminant = (q.b * q.b) - (4 * q.a * q.c);
	if (q.discriminant < 0)
		return (-1.0);
	q.discriminant = sqrt(q.discriminant);
	t[0] = (-q.b - q.discriminant) / (2 * q.a);
	t[1] = (-q.b + q.discriminant) / (2 * q.a);
	return (get_closest_t(t, ray, cy));
}
