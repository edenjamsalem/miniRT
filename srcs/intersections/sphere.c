/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:36:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/03/10 17:37:00 by eamsalem         ###   ########.fr       */
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

double	get_sp_t(t_ray *ray, t_sp *sphere)
{
	double		b;
	double		c;
	double		t[2];
	double		det;
	t_vec3		l;

	l = sub(ray->origin, sphere->center);
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

void	get_sp_intsec_data(t_ray *ray, t_sp *sphere, t_intsec *intsec)
{
	intsec->t = get_sp_t(ray, sphere);
	if (intsec->t >= 0)
	{
		intsec->pos = add(ray->origin, scale(ray->direction, intsec->t));
		intsec->colour = sphere->colour;
		intsec->normal = normalize(sub(intsec->pos, sphere->center));
		if (sphere->camera_inside)
			intsec->normal = scale(intsec->normal, -1);
		intsec->obj = (void *)sphere;
		intsec->properties = sphere->properties;
	}
}

bool	camera_in_sp(t_sp *sphere, t_camera *camera)
{
	t_vec3 len;

	len = sub(camera->pos, sphere->center);
	return (dot(len, len) < (sphere->radius * sphere->radius));
}
