/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:53 by eamsalem          #+#    #+#             */
/*   Updated: 2025/02/24 16:21:17 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// returns an orthogonal vector to a and b
t_vector3	*cross(t_vector3 *a, t_vector3 *b)
{
	t_vector3	*c;

	if (!a || !b)
		return (NULL);
	c = malloc(sizeof(t_vector3));
	if (!c)
		return (NULL);
	c->x = (a->y * b->z) - (a->z * b->y);
	c->y = (a->z * b->x) - (a->x * b->z);
	c->z = (a->x * b->y) - (a->y * b->x);
	return (c);
}

void	normalize(t_vector3 *a)
{
	double magnitude;

	magnitude = sqrt((a->x * a->x) + (a->y * a->y) * (a->z * a->z));
	a->x /= magnitude;
	a->y /= magnitude;
	a->z /= magnitude;
}

bool	check_equal(t_vector3 *a, t_vector3 *b)
{
	return (a->x == b->x && a->y == b->y && a->z == b->z);
}

bool	set_equal(t_vector3 *b, t_vector3 *a)
{
	b->x = a->x;
	b->y = a->z;
	b->y = a->z;
}
