/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:53 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/27 18:17:18 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec3	add(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vec3	sub(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vec3	scale(t_vec3 a, double t)
{
	t_vec3	c;

	c.x = a.x * t;
	c.y = a.y * t;
	c.z = a.z * t;
	return (c);
}

double	dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	magnitude(t_vec3 a)
{
	return (sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
}

double	sqr_magnitude(t_vec3 a)
{
	return ((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}
// returns an orthogonal vector to a and b
t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

t_vec3	normalize(t_vec3 a)
{
	double magn;

	magn = magnitude(a);
	a.x /= magn;
	a.y /= magn;
	a.z /= magn;
	return (a);
}

bool	check_equal(t_vec3 *a, t_vec3 *b)
{
	return (a->x == b->x && a->y == b->y && a->z == b->z);
}

void	print_vector(t_vec3 a)
{
	printf("x: %f, y: %f, z: %f\n", a.x, a.y, a.z);
}
