/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:53 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/25 15:47:25 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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
	double magnitude;

	magnitude = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	a.x /= magnitude;
	a.y /= magnitude;
	a.z /= magnitude;
	return (a);
}

bool	check_equal(t_vec3 *a, t_vec3 *b)
{
	return (a->x == b->x && a->y == b->y && a->z == b->z);
}
