/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:46:37 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/04 16:23:02 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static double get_t(double t[2])
{
	if (t[0] > 0 && t[1] > 0)
		return (fmin(t[0], t[1]));
	else if (t[0] > 0)
		return (t[0]);
	else if (t[1] > 0)
		return (t[1]);
	else	
		return (-1);
}

double	get_sp_t(t_ray *ray, t_sphere *sphere)
{
	double		b;
	double		c;
	double		t[2];
	double		det;
	t_vec3		l;

	l = sub(ray->origin, sphere->center);
	//a == dot(ray.direction, ray.direction) == 1 as ray.direction is normalized
	b = 2.0 * dot(ray->direction, l);
	c = dot(l, l) - (sphere->radius * sphere->radius);

	det = (b * b) - (4.0 * c);
	if (det < 0)
		return (-1);
	if (det == 0)
		return (-b / 2);
	
	det = sqrt(det);
	t[0] = (-b + det) / 2;
	t[1] = (-b - det) / 2;
	return (get_t(t));
}

void	get_sp_intsec_data(t_ray *ray, t_sphere *sphere, t_intsec *intsec)
{
	intsec->t = get_sp_t(ray, sphere);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
		intsec->colour = sphere->colour;
		intsec->normal = normalize(sub(intsec->pos, sphere->center));
		intsec->obj = (void *)sphere;
		intsec->properties = sphere->properties;
	}
}
