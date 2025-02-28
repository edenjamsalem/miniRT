/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:46:37 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/28 18:47:06 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

	det = b * b - (4 * c);
	if (det < 0)
		return (-1);
	if (det == 0)
		return (-b / 2);
	
	t[0] = (-b + sqrt(det)) / 2;
	t[1] = (-b - sqrt(det)) / 2;

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